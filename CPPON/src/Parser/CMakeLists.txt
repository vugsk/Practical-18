
set(PROJECT_NAME Parser_lib)

project(${PROJECT_NAME} VERSION ${VERSION_PROJECT} LANGUAGES ${LANGUAGES_PROJECT})


add_library(${PROJECT_NAME} SHARED
    Parser.cpp
    include/Parser.hpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE Lexer_lib)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

if (TEST_PARSER)
    add_subdirectory(${PATH_TEST}ParserTest build)
endif()