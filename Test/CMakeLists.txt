enable_testing()

add_executable(
        EngineTests
        CoreTests.cpp
)

add_subdirectory(ThirdParty/googletest)

target_link_libraries(
        EngineTests
        Core
        gtest
        gtest_main
)

add_custom_command(TARGET EngineTests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3::SDL3>
        $<TARGET_FILE_DIR:EngineTests>
)

add_test(NAME EngineTests COMMAND EngineTests)
