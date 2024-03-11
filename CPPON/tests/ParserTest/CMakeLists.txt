
set(PROJECT_NAME Parser_test)

project(${PROJECT_NAME} VERSION ${VERSION_PROJECT} LANGUAGES ${LANGUAGES_PROJECT})


add_executable(${PROJECT_NAME}
    test.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Lexer_lib
    gtest
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})