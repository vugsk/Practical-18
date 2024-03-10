cmake_minimum_required(VERSION 3.28)

set(VERSION_PROJECT 0.0.1)
set(LANGUAGES_PROJECT CXX)

project(P18 VERSION ${VERSION_PROJECT} LANGUAGES ${LANGUAGES_PROJECT})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


enable_testing()
add_subdirectory(CPPON)
add_subdirectory(practichka_18)



