
set(PROJECT_NAME Lexer_lib)

project(${PROJECT_NAME} VERSION ${VERSION_PROJECT}
    LANGUAGES ${LANGUAGES_PROJECT})


add_library(${PROJECT_NAME} SHARED
    include/ConfigLexer.hpp
    Lexer.cpp
    include/Lexer.hpp
    include/IToken.hpp
    include/Token.hpp
    Token.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include/
)

if (TEST_LEXER)
    add_subdirectory(${PATH_TEST}LexerTest build)
endif()