## Overview

```cpp
// Creates a new instance of an object
// Note: returned pointer is owner of object.
// Failing to store the returned object will
// cause it to be destroyed.
static std::shared_ptr<T> Instantiate();

// Adds a new component of type T
// Returns pointer to component
std::weak_ptr<T> AddComponent();

// Returns the first component of type T
std::weak_ptr<T> GetComponent();

// Removes the first component of type T
void RemoveComponent();

// Returns the first object with component T
static std::weak_ptr<Object> GetObjectWithComponent()

// Returns a vector of all objects with component T
static std::vector<std::shared_ptr<Object>> GetObjectsWithComponent()
```


## Considerations
Creating an object returns a shared pointer with sole ownership, as such that pointer going out of scope will cause the destruction of the created object. As such, Object instantiation will later be wrapped in a Level/Scene class with a Level/Scene `CreateObject` method that ensures the scene owns Objects created within.