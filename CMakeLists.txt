cmake_minimum_required(VERSION 3.20)
project(processos C)

set(CMAKE_C_STANDARD 11)

add_executable(processos
        test_struct.c
        read_file.c
        structs.c
)