#include <gtest/gtest.h>
#include <Core.h>
#include <Object/Component.h>
#include <Object/Object.h>

namespace Engine::Core::Objects
{
    class EngineObjectTests : public testing::Test
    {
    protected:
        EngineObjectTests() = default;
        ~EngineObjectTests() override = default;

        void SetUp() override
        {
        }

        void TearDown() override
        {
        }
    };

    class TestObject : public Object
    {
    public:
        TestObject(const char* Name = "Default")
            : name(Name)
        {
        }

        const char* GetName() const { return name; }

    private:
        const char* name = "Default";
    };

    class TestComponent : public Component
    {
    public:
        TestComponent(const int SomeParam)
            : SomeValue(SomeParam)
        {
        }

        int GetSomeValue() const { return SomeValue; }

    private:
        int SomeValue = 0;
    };

    TEST_F(EngineObjectTests, GivenObject_WhenAddComponent_ThenComponentIsAdded)
    {
        int testValue = 42;

        auto obj = Object::Instantiate<TestObject>();
        obj->AddComponent<TestComponent>(testValue);

        auto component = obj->GetComponent<TestComponent>().lock();

        ASSERT_NE(component, nullptr);
        EXPECT_EQ(component->GetSomeValue(), testValue);
    }

    TEST_F(EngineObjectTests, GivenObjectWithComponent_WhenGetComponent_ThenReturnsCorrectType)
    {
        auto obj = Object::Instantiate<TestObject>();
        obj->AddComponent<TestComponent>(123);

        auto component = obj->GetComponent<TestComponent>().lock();

        ASSERT_NE(component, nullptr);
        EXPECT_EQ(component->GetSomeValue(), 123);
    }

    TEST_F(EngineObjectTests, GivenObjectWithComponent_WhenRemoveComponent_ThenComponentIsRemoved)
    {
        auto obj = Object::Instantiate<TestObject>();
        obj->AddComponent<TestComponent>(999);

        obj->RemoveComponent<TestComponent>();

        auto component = obj->GetComponent<TestComponent>();

        EXPECT_TRUE(component.expired());
    }

    TEST_F(EngineObjectTests, GivenObjectsWithComponents_WhenGetObjectsWithComponent_ThenCorrectObjectsReturned)
    {
        std::vector<std::shared_ptr<Object>> Objs;
        for (int i = 0; i < 5; i++)
        {
            auto obj = Object::Instantiate<TestObject>();
            obj->AddComponent<TestComponent>(i);
            Objs.push_back(obj);
        }

        auto objects = Object::GetObjectsWithComponent<TestComponent>();

        EXPECT_EQ(objects.size(), 5);
    }

    TEST_F(EngineObjectTests, GivenObjectsWithComponents_WhenGetObjectWithComponent_ThenFirstObjectReturned)
    {
        auto first = Object::Instantiate<TestObject>();
        first->AddComponent<TestComponent>(111);

        auto second = Object::Instantiate<TestObject>();

        auto found = Object::GetObjectWithComponent<TestComponent>().lock();

        ASSERT_NE(found, nullptr);
        EXPECT_EQ(first.get(), found.get());
    }

    TEST_F(EngineObjectTests, GivenObject_WhenInstantiated_ThenCorrectNameIsSet)
    {
        const char* expectedName = "SpecialObject";
        auto obj = Object::Instantiate<TestObject>(expectedName);

        EXPECT_STREQ(obj->GetName(), expectedName);
    }
}
