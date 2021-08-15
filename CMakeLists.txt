cmake_minimum_required(VERSION 3.20)
project(psychic_octo_memory_assembler C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -ansi -pedantic")

add_executable(psychic_octo_memory_assembler assembler.c assembler_language.c
        assembler_language.h assembler.h assembler_first_pass.c
        assembler_first_pass.h assembler_second_pass.c assembler_second_pass.h assembler_error.c assembler_error.h assembler_line_parser.c assembler_line_parser.h assembler_utility_func.c assembler_utility_func.h)
