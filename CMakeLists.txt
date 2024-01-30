cmake_minimum_required(VERSION 3.28)
project(argprs C)

set(CMAKE_C_STANDARD 17)

add_library(argprs STATIC
        arg_result_set.c
        argprs.h
        argprs.c
        main.c)
