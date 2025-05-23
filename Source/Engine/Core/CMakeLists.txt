add_library(Core STATIC
    Core.cpp
    Core.h
)

target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(
    Core
    PUBLIC
    SDL3::SDL3
)