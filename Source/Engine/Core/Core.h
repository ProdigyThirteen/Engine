#pragma once

#include <CoreIncludes.h>
#include <SDL3/SDL.h>

namespace Engine::Core
{
    DECLARE_LOG_CATEGORY(LogCore)

    class EngineRuntime
    {
    public:
        EngineRuntime();
        ~EngineRuntime();

        void Run();

    private:
        bool InitWindow();
        bool InitRenderer();

        SDL_Window* Window;
        SDL_Renderer* Renderer;
    };
}
