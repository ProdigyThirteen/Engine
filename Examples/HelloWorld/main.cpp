#define LOG_VERBOSITY VeryVerbose

#include <Core.h>
#include <iostream>

#include <Object/Object.h>
#include <Object/Component.h>

DECLARE_LOG_CATEGORY(Temp)

using Engine::Core::Object;
using Engine::Core::Component;

class SomeComp final : public Component
{
public:
    explicit SomeComp(const int SomeVal = 5)
        : Component()
    {
        LOG(Temp, Info, "SomeComp: %d", SomeVal);
    }
};

int main(int argc, char *argv[])
{
    Engine::Core::Initialize();
    Engine::Core::Shutdown();

    auto obj = Object::Instantiate<Object>();
    obj->AddComponent<SomeComp>(12);

    std::cin.get();
    return 0;
}