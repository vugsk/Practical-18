cmake_minimum_required(VERSION 3.28)
project(Practical-18)

set(CMAKE_CXX_STANDARD 20)

option(TESTS "ON/OFF tests?" OFF)
option(TEST_LEXER "build test for lexerLib?" ON)
#option(TEST_PARSER "build test for parserLib?" OFF)


include_directories(include/Practical-18)

add_subdirectory(src/Lexer)
add_subdirectory(src/Parser)


add_executable(Practical-18
    src/main.cpp
    include/Practical-18/Config.hpp
#    src/WorkFile.cpp
#    include/Practical-18/WorkFile.hpp
)

target_link_libraries(Practical-18
    sub::LexerLib
    sub::ParserLib
)