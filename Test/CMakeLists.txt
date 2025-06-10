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

add_test(NAME MyEngineTests COMMAND MyEngineTests)
