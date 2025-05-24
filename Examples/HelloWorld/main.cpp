
#define LOG_VERBOSITY VeryVerbose

#include <Core.h>

DECLARE_LOG_CATEGORY(Temp)

int main(int argc, char *argv[])
{
    Engine::Core::Initialize();
    Engine::Core::Shutdown();

    std::cin.get();
    return 0;
}