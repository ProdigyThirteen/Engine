## Overview
```cpp
// These methods should ALWAYS be called
// by derived classes to ensure bShouldUpdate
// and bIsEnabled behave correctly
virtual void FixedUpdate();  
virtual void Update();  
virtual void LateUpdate();

std::weak_ptr<Object> GetOwner();
void SetOwner(const std::weak_ptr<Object>& InOwner); // Should not be used

bool IsEnabled();
void SetEnabled(const bool InIsEnabled);

bool ShouldTick();
void SetShouldTick(const bool InShouldTick);

```

## Considerations
`SetOwner` is an internally used method to assign ownership of a component to its owning Object. Should not be called directly.