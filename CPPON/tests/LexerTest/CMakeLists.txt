
set(PROJECT_NAME Lexer_test)

project(${PROJECT_NAME} VERSION ${VERSION_PROJECT} LANGUAGES ${LANGUAGES_PROJECT})


add_executable(${PROJECT_NAME}
    test.cpp
    ConfigTest.hpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Lexer_lib
    gtest
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
