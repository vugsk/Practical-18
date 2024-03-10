
set(PROJECT_NAME Lexer_lib)

project(${PROJECT_NAME} VERSION ${VERSION_PROJECT} LANGUAGES ${LANGUAGES_PROJECT})


add_library(${PROJECT_NAME} SHARED
    Lexer.cpp
    include/Lexer.hpp
    Vocabulary.cpp
    include/Vocabulary.hpp
    include/TypeToken.hpp
    include/ILexer.hpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

if (TEST_LEXER)
    add_subdirectory(../../tests/LexerTest build)
endif()