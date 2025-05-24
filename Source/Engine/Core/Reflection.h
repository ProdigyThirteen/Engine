#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <any>
#include <type_traits>
#include <iostream>
#include <typeinfo>
#include <cassert>
#include <Log.h>

// -------------------------------------------------

DECLARE_LOG_CATEGORY(LogReflection)

// -------------------------------------------------

struct Variant
{
public:
    std::any value;

public:
    Variant() = default;

    template<typename T>
    Variant(const T& val)
            : value(val)
    {}

    template<typename T>
    T& get()
    {
        assert(value.has_value() && value.type() == typeid(T));
        return std::any_cast<T&>(value);
    }

    template<typename T>
    const T& get() const
    {
        assert(value.has_value() && value.type() == typeid(T));
        return std::any_cast<const T&>(value);
    }

    std::string toString() const
    {
        if (value.type() == typeid(int))
            return std::to_string(std::any_cast<int>(value));

        if (value.type() == typeid(float))
            return std::to_string(std::any_cast<float>(value));

        if (value.type() == typeid(double))
            return std::to_string(std::any_cast<double>(value));

        if (value.type() == typeid(bool))
            return std::any_cast<bool>(value) ? "true" : "false";

        if (value.type() == typeid(std::string))
            return std::any_cast<std::string>(value);

        if (value.type() == typeid(const char*))
            return std::string(std::any_cast<const char*>(value));

        return "<cannot convert value to string>";
    }
};

// -------------------------------------------------

struct FieldInfo
{
    std::string name;
    std::function<Variant(void*)> getter;
    std::function<void(void*, const Variant&)> setter; // New setter support
    std::string type_name;                              // Optional type name info
    size_t offset = 0;                                  // Optional offset (only meaningful for non-static fields)
    bool is_const = false;
    bool is_static = false;
    std::unordered_map<std::string, std::string> attributes; // Editor/networking metadata
};

// -------------------------------------------------

struct TypeInfo
{
    std::string name;
    std::vector<FieldInfo> fields;
    std::vector<TypeInfo*> baseTypes; // Support for inheritance
};

// -------------------------------------------------

class TypeRegistry
{
public:
    void add(const std::string& name, TypeInfo* info)
    {
        LOG(LogReflection, Debug, "Adding type to registry: %s", name.c_str());
        types[name] = info;
    }

    TypeInfo* get(const std::string& name)
    {
        auto it = types.find(name);

        if (it != types.end())
        {
            LOG(LogReflection, Debug, "Found type in registry: %s", name.c_str());
            return it->second;
        }

        LOG(LogReflection, Debug, "Type not found in registry: %s", name.c_str());
        return nullptr;
    }

    static TypeRegistry& instance()
    {
        static TypeRegistry registry;
        return registry;
    }

private:
    std::unordered_map<std::string, TypeInfo*> types;
};

// -------------------------------------------------

template<typename T>
struct remove_cvref
{
    using type = std::remove_cv_t<std::remove_reference_t<T>>;
};

template<typename T>
using remove_cvref_t = typename remove_cvref<T>::type;

// -------------------------------------------------

template<typename ClassT, typename FieldT>
struct FieldReflector
{
    static int Register(const char* name, FieldT ClassT::*member, TypeInfo& typeInfo, bool isConst)
    {
        LOG(LogReflection, Debug, "Registering field: %s in type: %s", std::string(name), typeInfo.name);

        auto getter = [member](void* obj) -> Variant
        {
            ClassT* instance = reinterpret_cast<ClassT*>(obj);
            return instance->*member;
        };

        std::function<void(void*, const Variant&)> setter = nullptr;

        if constexpr (!std::is_const_v<FieldT>)
        {
            setter = [member](void* obj, const Variant& val)
            {
                ClassT* instance = reinterpret_cast<ClassT*>(obj);
                instance->*member = val.get<FieldT>();

                LOG(LogReflection, Debug, "Setter called for field, value set.");
            };
        }

        FieldInfo fieldInfo
                {
                        name,
                        getter,
                        setter,
                        typeid(FieldT).name(),
                        reinterpret_cast<size_t>(&(reinterpret_cast<ClassT const volatile*>(0)->*member)),
                        isConst,
                        false
                };

        typeInfo.fields.push_back(fieldInfo);

        LOG(LogReflection, Debug, "Field registered successfully: %s", std::string(name));

        return 0;
    }
};

// -------------------------------------------------

template<typename FieldT>
struct StaticFieldReflector
{
    static int Register(const char* name, const FieldT& value, TypeInfo& typeInfo, bool isConst)
    {
        LOG(LogReflection, Debug, "Registering static field: %s in type: %s", std::string(name), typeInfo.name);

        auto getter = [value](void* /*unused*/) -> Variant
        {
            return value;
        };

        std::function<void(void*, const Variant&)> setter = nullptr;

        if constexpr (!std::is_const_v<FieldT>)
        {
            setter = [](void* /*unused*/, const Variant& /*val*/)
            {
                LOG(LogReflection, Debug, "Setter called on static field, but no action taken.");
            };
        }

        FieldInfo fieldInfo
                {
                        name,
                        getter,
                        setter,
                        typeid(FieldT).name(),
                        0,
                        isConst,
                        true
                };

        typeInfo.fields.push_back(fieldInfo);

        LOG(LogReflection, Debug, "Static field registered successfully: %s", std::string(name));

        return 0;
    }
};

// -------------------------------------------------

#define CLASS(CLASS_NAME) \
    using ThisClass = CLASS_NAME; \
    static inline TypeInfo __typeInfo__ = TypeInfo{ #CLASS_NAME, {}, {} }; \
    struct __RegisterTypeInRegistry \
    { \
        __RegisterTypeInRegistry() \
        { \
            TypeRegistry::instance().add(#CLASS_NAME, &__typeInfo__); \
            LOG(LogReflection, Debug, "Registered type in TypeRegistry: " #CLASS_NAME); \
        } \
    }; \
    inline static __RegisterTypeInRegistry __registerTypeInstance__; \
    static TypeInfo* reflect() \
    { \
        return &__typeInfo__; \
    }

// -------------------------------------------------

#define PROPERTY(NAME, TYPE) \
private: \
    static constexpr const char* __field_name_##NAME() { return #NAME; } \
public: \
    TYPE NAME; \
    inline static auto __register_##NAME = FieldReflector<ThisClass, TYPE>::Register( \
        #NAME, &ThisClass::NAME, ThisClass::__typeInfo__, std::is_const_v<remove_cvref_t<TYPE>>)

// -------------------------------------------------

#define STATIC(NAME, TYPE) \
public: \
    static TYPE NAME; \
    inline static auto __register_static_##NAME = StaticFieldReflector<TYPE>::Register( \
        #NAME, ThisClass::NAME, ThisClass::__typeInfo__, std::is_const_v<remove_cvref_t<TYPE>>)

// -------------------------------------------------

#define STATIC_CONST(NAME, TYPE, VALUE) \
public: \
    static constexpr TYPE NAME = VALUE; \
    inline static auto __register_static_const_##NAME = StaticFieldReflector<TYPE>::Register( \
        #NAME, ThisClass::NAME, ThisClass::__typeInfo__, true)

// -------------------------------------------------
