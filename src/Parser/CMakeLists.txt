cmake_minimum_required(VERSION 3.28)
project(ParserLibrary)

set(CMAKE_CXX_STANDARD 20)

add_library(ParserLibrary
    Parser.cpp
)

add_library(sub::ParserLib ALIAS ParserLibrary)

target_include_directories(ParserLibrary
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)