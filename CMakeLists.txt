cmake_minimum_required(VERSION 3.20)
project(lNlab1 C)

set(CMAKE_C_STANDARD 99)

add_executable(lNlab1 main.c complex.c complex.h matrix.c matrix.h ringinfo.c ringinfo.h
        tests.c
        int_algebra.c)
target_compile_options(lNlab1 PRIVATE -Wpointer-arith)