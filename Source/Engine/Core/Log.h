#pragma once

#include <cstdio>
#include <cstdarg>
#include <string>
#include <mutex>

// ------------------- Log Verbosity Levels -------------------

enum LogVerbosity {
    Fatal = 0,
    Error,
    Warning,
    Info,
    Debug,
    Verbose,
    VeryVerbose
};

namespace Logging {
// ------------------- Compile-Time Verbosity -------------------

// Default compile-time minimum verbosity is Info
#ifndef LOG_VERBOSITY
#define LOG_VERBOSITY Info
#endif

// ------------------- Colour Output by Verbosity -------------------

    inline const char* VerbosityColour(LogVerbosity verbosity)
    {
        switch (verbosity)
        {
            case Fatal:       return "\033[1;31m";  // Bold Red
            case Error:       return "\033[31m";    // Red
            case Warning:     return "\033[33m";    // Yellow
            case Info:        return "\033[37m";    // White
            case Debug:       return "\033[36m";    // Cyan
            case Verbose:     return "\033[35m";    // Magenta
            case VeryVerbose: return "\033[90m";    // Dark Gray
            default:          return "\033[0m";     // Reset
        }
    }

// ------------------- Log Category -------------------

    struct LogCategory
    {
        const char* Name;

        constexpr LogCategory(const char* name) : Name(name) {}
    };

// ------------------- Logging Implementation -------------------

    inline std::mutex& GetLogMutex()
    {
        static std::mutex mtx;
        return mtx;
    }

    inline void LogPrint(const LogCategory& category, LogVerbosity verbosity, const char* fmt, va_list args)
    {
        char buffer[1024];
        std::vsnprintf(buffer, sizeof(buffer), fmt, args);

        const char* verbosityStr = nullptr;
        switch (verbosity)
        {
            case Fatal:       verbosityStr = "Fatal"; break;
            case Error:       verbosityStr = "Error"; break;
            case Warning:     verbosityStr = "Warning"; break;
            case Info:        verbosityStr = "Info"; break;
            case Debug:       verbosityStr = "Debug"; break;
            case Verbose:     verbosityStr = "Verbose"; break;
            case VeryVerbose: verbosityStr = "VeryVerbose"; break;
            default:          verbosityStr = "Unknown"; break;
        }

        const char* colour = VerbosityColour(verbosity);

        std::lock_guard<std::mutex> lock(GetLogMutex());

        std::fprintf(stdout, "%s[%s][%s] %s\033[0m\n", colour, category.Name, verbosityStr, buffer);
        std::fflush(stdout);
    }

    inline void LogPrint(const LogCategory& category, LogVerbosity verbosity, const char* fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        LogPrint(category, verbosity, fmt, args);
        va_end(args);
    }

} // namespace Logging

// ------------------- Macros -------------------

#define DECLARE_LOG_CATEGORY(CategoryName) \
    inline constexpr Logging::LogCategory CategoryName{#CategoryName};

#define LOG(Category, Verbosity, ...)                            \
    do                                                           \
    {                                                            \
        if ((Verbosity) <= LOG_VERBOSITY)                        \
            Logging::LogPrint(Category, Verbosity, __VA_ARGS__); \
    } while(0)