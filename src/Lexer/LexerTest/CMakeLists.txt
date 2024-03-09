cmake_minimum_required(VERSION 3.28)
project(LexerTest)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_executable(LexerTest
    tests.cpp
)

target_link_libraries(LexerTest
    gtest
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(LexerTest)
