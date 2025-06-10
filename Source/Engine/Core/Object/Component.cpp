#include <Object/Component.h>

void Engine::Core::Component::FixedUpdate()
{
    if(!bIsEnabled || !bShouldTick)
    {
        return;
    }
}

void Engine::Core::Component::Update()
{
    if(!bIsEnabled || !bShouldTick)
    {
        return;
    }
}

void Engine::Core::Component::LateUpdate()
{
    if(!bIsEnabled || !bShouldTick)
    {
        return;
    }
}
