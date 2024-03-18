
set(PROJECT_NAME CPPON_lib)
set(PATH_TEST ../../tests/)

project(${PROJECT_NAME} VERSION ${VERSION_PROJECT}
    LANGUAGES ${LANGUAGES_PROJECT})


option(TEST_LEXER "build test for lexer?" OFF)
add_subdirectory(src/LexicalAnalyzer)

option(TEST_PARSER "build test for parser" OFF)
add_subdirectory(src/Parser)


add_library(${PROJECT_NAME} SHARED
    include/Config.hpp
    Config.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Lexer_lib
    Parser_lib
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)
