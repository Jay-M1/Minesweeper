cmake_minimum_required(VERSION 3.5.0)

project(Minesweeper VERSION 0.1.0 LANGUAGES CXX)

file(GLOB SOURCES "src/*.cpp")

add_executable(Minesweeper ${SOURCES})

set_property(TARGET Minesweeper PROPERTY CXX_STANDARD 23)
