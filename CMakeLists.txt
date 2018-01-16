cmake_minimum_required(VERSION 3.8)
project(snake)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
add_executable(snake ${SOURCE_FILES})