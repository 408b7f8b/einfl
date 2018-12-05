cmake_minimum_required(VERSION 2.4)
project(einfl C)

set(CMAKE_C_STANDARD 90)

add_library(einfl einfl.h test.c)
SET_TARGET_PROPERTIES(einfl PROPERTIES LINKER_LANGUAGE C)