cmake_minimum_required(VERSION 3.26)
project(2048 C)

set(CMAKE_C_STANDARD 11)

add_executable(2048 main.c
        board.h
        init.h
        move.h
        game.h
        printTools.h
        input.h)
