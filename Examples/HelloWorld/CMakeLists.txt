add_executable(HelloWorld main.cpp)

target_include_directories(HelloWorld PRIVATE
    ${CMAKE_SOURCE_DIR}/Source/Engine/Core
)

target_link_libraries(
    HelloWorld
    Core
)

add_custom_command(TARGET HelloWorld POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3::SDL3>
        $<TARGET_FILE_DIR:HelloWorld>
)
