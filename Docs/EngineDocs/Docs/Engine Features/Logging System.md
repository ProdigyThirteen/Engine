Inspired by Unreal's UE_LOG macro-based logging system.

## Use
#### Log Verbosity
```cpp
// Available verbosity
enum LogVerbosity {  
    Fatal,  
    Error,  
    Warning,  
    Info,  // Default
    Debug,  
    Verbose,  
    VeryVerbose  
};
```

To override default log verbosity, define a new verbosity prior to including any engine components in a project

```cpp
#define LOG_VERBOSITY VeryVerbose  
#include <Core.h>

int main(int argc, char *argv[])  
{
	// Logs will now display everything up to VeryVerbose
}
```

#### Logging
`DECLARE_LOG_CATEGORY(CategoryName)`

`LOG(LogCategory, LogVerbosity, LogMessage)`

Log messages support C-style string [format specifiers](https://www.geeksforgeeks.org/format-specifiers-in-c/)


## TODO:
Fatal logs should terminate the process.