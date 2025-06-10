#pragma once

#include <CoreIncludes.h>

DECLARE_LOG_CATEGORY(LogCore)

namespace Engine::Core
{
    void Initialize();
    void Shutdown();

    class EngineRuntime
    {
    public:

        EngineRuntime();
        ~EngineRuntime();
    };
}
