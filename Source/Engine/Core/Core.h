#pragma once

#include <Reflection.h>
#include <Log.h>

DECLARE_LOG_CATEGORY(LogCore)

namespace Engine::Core
{
    void Initialize();
    void Shutdown();

    class EngineRuntime
    {
    public:
        CLASS(EngineRuntime)

        EngineRuntime();
        ~EngineRuntime();
    };
}
