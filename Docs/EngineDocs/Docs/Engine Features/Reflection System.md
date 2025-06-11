#### Goals
- Engine Editor?
- imgui support

#### Runtime vs Compile Time reflection 
Leaning towards runtime reflection due to seemingly better fit for game engine use cases. 

#### API
Unreal style UPROPERTY, UCLASS, USTRUCT?
- Requires custom tooling; python script in pre-build step?
- Cleaner in-code implementation

```cpp
// Unreal
UPROPERTY()
int SomeValue = 10;

// Best I can come up with without a pre-build step
UPROPERTY(SomeValue, int)
```

#### Current Implementation
```cpp
class SomeClass
{
	CLASS(SomeClass) // Reflects a class, required for property reflection

	// Declare reflected property ( Name, Type )
	PROPERTY(SomeValue, int);

	// Declare a reflected static property ( Name, Type )
	STATIC(SomeStatic, int);

	// Declare a reflected static const property ( Name, Type, Value )
	STATIC_CONST(SomeStaticConst, int, 10);
}
```