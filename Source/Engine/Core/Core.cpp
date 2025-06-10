#include <Core.h>

namespace Engine::Core
{
    EngineRuntime::EngineRuntime()
        : Window(nullptr)
        , Renderer(nullptr)
    {
        if (!SDL_Init(SDL_INIT_VIDEO))
        {
            LOG(LogCore, Error, "SDL_Init failed: %s", SDL_GetError());
            return;
        }

        if (!InitWindow())
        {
            LOG(LogCore, Error, "InitWindow failed");
            return;
        }

        if (!InitRenderer())
        {
            LOG(LogCore, Error, "InitRenderer failed");
            return;
        }

        LOG(LogCore, Info, "Engine initialized successfully");
    }

    EngineRuntime::~EngineRuntime()
    {
        SDL_DestroyWindow(Window);
        SDL_Quit();
    }

    void EngineRuntime::Run()
    {
        while (true)
        {
            SDL_Event event;

            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_EVENT_QUIT)
                {
                    break;
                }
            }

            SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
            SDL_RenderClear(Renderer);
            SDL_RenderPresent(Renderer);
        }
    }

    bool EngineRuntime::InitWindow()
    {
        Window = SDL_CreateWindow(
            "Game Engine",
            1280,
            720,
            SDL_WINDOW_RESIZABLE);

        if (!Window)
        {
            LOG(LogCore, Fatal, "SDL_CreateWindow failed: %s", SDL_GetError());
            return false;
        }

        return true;
    }

    bool EngineRuntime::InitRenderer()
    {
        Renderer = SDL_CreateRenderer(Window, nullptr);
        if (!Renderer)
        {
            LOG(LogCore, Fatal, "SDL_CreateRenderer failed: %s", SDL_GetError());
            return false;
        }

        return true;
    }
}
