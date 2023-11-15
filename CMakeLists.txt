cmake_minimum_required(VERSION 3.26)
project(Project_Library C)

set(CMAKE_C_STANDARD 11)

add_executable(Project_Library
        main.c
        app.h
        app.c)
