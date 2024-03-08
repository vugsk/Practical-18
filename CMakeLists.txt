cmake_minimum_required(VERSION 3.28)
project(Practical-18)

set(CMAKE_CXX_STANDARD 20)

include_directories(include/Practical-18)

add_executable(Practical-18
    src/main.cpp
    src/Config.cpp
    src/WorkFile.cpp
    include/Practical-18/WorkFile.hpp
    include/Practical-18/ILexer.hpp
    src/Lexer.cpp
    include/Practical-18/Lexer.hpp
    include/Practical-18/IToken.hpp
    src/Token.cpp
    include/Practical-18/Token.hpp
    include/Practical-18/Config.hpp
    include/Practical-18/TokenType.hpp
    src/IToken.cpp
)