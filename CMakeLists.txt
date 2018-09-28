cmake_minimum_required(VERSION 3.10)
project(Huffman C)

set(CMAKE_C_STANDARD 99)

add_executable(main main.c TADs/heap.h TADs/hash_table.h TADs/nodes.h compress/compress.h decompress/decompress.h TADs/utilities.h TADs/tree.h tests/minunit.h tests/HashTable_Test.h tests/Main_Test.h tests/Heap_Test.h tests/Tree_Test.h)
