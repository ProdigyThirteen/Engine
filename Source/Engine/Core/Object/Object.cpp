
#include <Object/Object.h>

namespace Engine::Core
{
    std::vector<std::weak_ptr<Object>> Object::Objects;
    std::mutex Object::ObjectMutex;
}
