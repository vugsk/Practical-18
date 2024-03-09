cmake_minimum_required(VERSION 3.28)
project(LexerLibrary)

set(CMAKE_CXX_STANDARD 20)

add_library(LexerLibrary
    IToken.cpp
    include/IToken.hpp
    Lexer.cpp
    include/Lexer.hpp
    include/ILexer.hpp
    Token.cpp
    include/Token.hpp
    include/TokenType.hpp
    include/ConfigLexer.hpp
    ConfigLexer.cpp
)

set(TEST_LEXER ON)

if (TEST_LEXER EQUAL ON AND TESTS)
    enable_testing()
    add_subdirectory(LexerTest)
endif()

add_library(sub::LexerLib ALIAS LexerLibrary)

target_link_libraries(LexerLibrary
    ${LexerTest}
)

target_include_directories(LexerLibrary
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)
