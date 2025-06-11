#include <Object/Component.h>

using namespace Engine::Core::Objects;

void Component::FixedUpdate()
{
    if(!bIsEnabled || !bShouldTick)
    {
        return;
    }
}

void Component::Update()
{
    if(!bIsEnabled || !bShouldTick)
    {
        return;
    }
}

void Component::LateUpdate()
{
    if(!bIsEnabled || !bShouldTick)
    {
        return;
    }
}
