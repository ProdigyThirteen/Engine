#include <Object/Object.h>

using namespace Engine::Core::Objects;

std::vector<std::weak_ptr<Object>> Object::Objects;
std::mutex Object::ObjectMutex;
