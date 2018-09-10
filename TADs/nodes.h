//
// Created by paulo on 09/09/2018.
//

#ifndef HUFFMAN_NODES_H
#define HUFFMAN_NODES_H

#include <stdio.h>
#include <stdlib.h>

// Node usado na hashTable
typedef struct hashNode {
    long int frequency;
    unsigned char byte;
} HashNode;

// Node usado na Heap
typedef struct heapNode {
    long int frequency;
    unsigned char byte;
    struct HeapNode *left;
    struct HeapNode *right;
} HeapNode;

// Cria um novo node para a hashTable com frequencia 1
HashNode *create_hashNode(unsigned char byte) {

    HashNode *new_node = (HashNode *)malloc(sizeof(HashNode));
    new_node->byte = byte;
    new_node->frequency = 1;

    return new_node;

}

HeapNode *create_heapNode(unsigned char byte, long int frequency) {

    HeapNode *new_node = (HeapNode *)malloc(sizeof(HeapNode));
    new_node->byte = byte;
    new_node->frequency = frequency;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;

}

#endif //HUFFMAN_NODES_H
