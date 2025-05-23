#include <iostream>
#include <Core.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main(int argc, char *argv[])
{
    Engine::Core::Initialize();
    printf("Hello, World!");
    std::cin.get();
    return 0;
}