#pragma once

#include <CoreIncludes.h>
#include <Object/Component.h>
#include <type_traits>
#include <mutex>

namespace Engine::Core::Objects
{
    class Object : public std::enable_shared_from_this<Object>
    {
    public:
        Object() = default;
        virtual ~Object() = default;

        // Returns the first component of type T
        template <class T>
        std::weak_ptr<T> GetComponent()
        {
            std::lock_guard lock(ComponentMutex);
            for (auto& component : Components)
            {
                if (auto castedComponent = std::dynamic_pointer_cast<T>(component))
                {
                    return castedComponent;
                }
            }
            return {};
        }

        // Adds a new component of type T
        template<typename T, typename... Args>
        std::weak_ptr<T> AddComponent(Args&&... args)
        {
            static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");

            auto comp = std::make_shared<T>(std::forward<Args>(args)...);
            comp->SetOwner(shared_from_this());

            std::lock_guard lock(ComponentMutex);
            Components.push_back(comp);

            return comp;
        }


        // Removes the first component of type T
        template <class T>
        void RemoveComponent()
        {
            for (auto it = Components.begin(); it != Components.end(); ++it)
            {
                if (std::dynamic_pointer_cast<T>(*it))
                {
                    Components.erase(it);
                    return;
                }
            }
        }

        // Returns a vector of all objects with component T
        template <class T>
        static std::vector<std::shared_ptr<Object>> GetObjectsWithComponent()
        {
            std::vector<std::shared_ptr<Object>> result;
            for (auto& weakObj : Objects)
            {
                if (auto obj = weakObj.lock())
                {
                    if (!obj->GetComponent<T>().expired())
                    {
                        result.push_back(obj);
                    }
                }
            }
            return result;
        }

        // Returns the first object with component T
        template <class T>
        static std::weak_ptr<Object> GetObjectWithComponent()
        {
            for (auto& weakObj : Objects)
            {
                if (auto obj = weakObj.lock())
                {
                    if (!obj->GetComponent<T>().expired())
                    {
                        return obj;
                    }
                }
            }
            return {};
        }

        // Creates a new instance of an object
        template <class T, typename... Args>
        [[nodiscard]] static std::shared_ptr<T> Instantiate(Args&&... args)
        {
            static_assert(std::is_base_of_v<Object, T>, "T must derive from Object");

            auto newObject = std::make_shared<T>(std::forward<Args>(args)...);

            std::lock_guard lock(ObjectMutex);
            Objects.push_back(newObject);
            return newObject;
        }

    private:
        static std::vector<std::weak_ptr<Object>> Objects;
        static std::mutex ObjectMutex;

        std::vector<std::shared_ptr<Component>> Components;
        mutable std::mutex ComponentMutex;

    };
}
