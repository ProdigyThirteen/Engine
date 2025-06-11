#pragma once
#include <CoreIncludes.h>

namespace Engine::Core::Objects
{
    class Object;

    class Component
    {
    public:
        explicit Component() = default;
        virtual ~Component() = default;

        virtual void FixedUpdate();
        virtual void Update();
        virtual void LateUpdate();

        [[nodiscard]] std::weak_ptr<Object> GetOwner() { return OwningObject; }
        void SetOwner(const std::weak_ptr<Object>& InOwner) { OwningObject = InOwner; }

        [[nodiscard]] bool IsEnabled() const { return bIsEnabled; }
        void SetEnabled(const bool InIsEnabled) { bIsEnabled = InIsEnabled; }

        [[nodiscard]] bool ShouldTick() const { return bShouldTick; }
        void SetShouldTick(const bool InShouldTick) { bShouldTick = InShouldTick; }

    private:
        std::weak_ptr<Object> OwningObject;

        bool bIsEnabled;
        bool bShouldTick;
    };
}
