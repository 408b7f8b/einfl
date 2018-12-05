cmake_minimum_required(VERSION 2.4)
project(einfl C)

set(CMAKE_C_STANDARD 90)

add_executable(einfl_test example.c)
SET_TARGET_PROPERTIES(einfl_test PROPERTIES LINKER_LANGUAGE C)