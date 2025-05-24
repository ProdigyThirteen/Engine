#include <Core.h>

namespace Engine::Core
{
    void Initialize()
    {
        EngineRuntime e;
    }

    void Shutdown()
    {

    }

    EngineRuntime::EngineRuntime()
    {
        LOG(LogCore, Info, "Hello, World!");
    }

    EngineRuntime::~EngineRuntime()
    {
        LOG(LogCore, Info, "Goodbye, World!");
    }
}
