#define LOG_VERBOSITY VeryVerbose

#include <Core.h>
#include <Object/Object.h>
#include <Object/Component.h>

DECLARE_LOG_CATEGORY(Temp)

using namespace Engine::Core;

int main(int argc, char *argv[])
{
#if 1 // Runtime example
    EngineRuntime e;
    e.Run();
#endif

#if 0 // Component example
    class SomeComp final : public Component
    {
    public:
        explicit SomeComp(const int SomeVal = 5)
            : Component()
        {
            LOG(Temp, Info, "SomeComp: %d", SomeVal);
        }
    };

    auto obj = Object::Instantiate<Object>();
    obj->AddComponent<SomeComp>(12);
#endif

    std::cin.get();
    return 0;
}