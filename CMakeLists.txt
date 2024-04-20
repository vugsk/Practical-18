cmake_minimum_required(VERSION 3.28)

set(VERSION_PROJECT 0.1.5)
set(LANGUAGES_PROJECT CXX)

project(P18 VERSION ${VERSION_PROJECT} LANGUAGES ${LANGUAGES_PROJECT})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_subdirectory(CPPON)
add_subdirectory(practichka_18)



