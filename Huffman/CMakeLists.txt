cmake_minimum_required(VERSION 3.13)
project(Huffman C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Huffman
        binary_tree.c
        binary_tree.h
        compress.c
        compress.h
        descompress.c
        descompress.h
        hash.c
        hash.h
        heap.c
        heap.h
        huffman.c
        huffman.h
        main.c)
