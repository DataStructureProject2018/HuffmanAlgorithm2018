//
// Created by paulo on 09/09/2018.
//

#ifndef HUFFMAN_NODES_H
#define HUFFMAN_NODES_H

#include <stdio.h>
#include <stdlib.h>

// Node usado na hashTable
typedef struct hashNode {
    unsigned long int frequency;
    unsigned short int compressed;
    unsigned char compressed_len;
    void *byte;
} HashNode;

// Node usado na Heap
typedef struct heapNode {
    unsigned long int frequency;
    void *byte;
    struct heapNode *left;
    struct heapNode *right;
} HeapNode;

// Node usado na arvore
typedef struct treeNode {
    void *byte;
    struct treeNode *right;
    struct treeNode *left;
} TreeNode;

// Cria um novo node para a arvore
TreeNode *create_node(unsigned char byte){

    TreeNode *new_node = (TreeNode *) malloc(sizeof(TreeNode));
    new_node->byte = (void *)byte;
    new_node->right = NULL;
    new_node->left = NULL;

    return new_node;

}

// Cria um novo node para a hashTable com frequencia 1
HashNode *create_hashNode(unsigned char byte) {

    HashNode *new_node = (HashNode *)malloc(sizeof(HashNode));
    new_node->byte = (void *)byte;
    new_node->frequency = 1;
    new_node->compressed = 0;
    new_node->compressed_len = 0;

    return new_node;

}

HeapNode *create_heapNode(void *byte, unsigned long frequency) {

    HeapNode *new_node = (HeapNode *)malloc(sizeof(HeapNode));
    new_node->byte = byte;
    new_node->frequency = frequency;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;

}

#endif //HUFFMAN_NODES_H
