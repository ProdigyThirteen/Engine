#pragma once
#include <CoreIncludes.h>

namespace Engine::Core
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

        std::weak_ptr<Object> GetOwner() const { return OwningObject; }
        void SetOwner(const std::weak_ptr<Object>& InOwner) { OwningObject = InOwner; }

        bool IsEnabled() const { return bIsEnabled; }
        void SetEnabled(const bool InIsEnabled) { bIsEnabled = InIsEnabled; }

        bool ShouldTick() const { return bShouldTick; }
        void SetShouldTick(const bool InShouldTick) { bShouldTick = InShouldTick; }

    private:
        std::weak_ptr<Object> OwningObject;

        bool bIsEnabled;
        bool bShouldTick;
    };
}
