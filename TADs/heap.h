//
// Created by ricardo on 09/09/2018.
//

#ifndef HUFFMAN_HEAP_H
#define HUFFMAN_HEAP_H

#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"
#include "nodes.h"

#define MAX_HEAP_SIZE 257

typedef struct heap {
    int size;
    HeapNode *data[MAX_HEAP_SIZE];
} Heap;

// Cria uma Heap
Heap* create_heap() {

    Heap *new_heap = (Heap *) malloc(sizeof(Heap));
    new_heap->size = 0;

    int i;
    for(i = 1; i < MAX_HEAP_SIZE; i++){
        new_heap->data[i] = NULL;
    }


    return new_heap;

}

// Retorna a posição do Pai do índice i
int get_parent_index(int i) {

    return (i >> 1);

}

// Retorna a posição do Filho da esquerda do nó de índice i
int get_left_index(int i) {

    return (i << 1);

}

// Retorna a posição do Filho da direita do nó de índice i
int get_right_index(int i) {

    return (i << 1)+1;

}

void swap_nodes(HeapNode **first, HeapNode **second) {

    HeapNode *aux = *first;
    *first = *second;
    *second = aux;

}

void min_heapify(Heap *heap, int i) {

    int smallest = i;
    int leftIndex = get_left_index(i);
    int rightIndex = get_right_index(i);

    if(leftIndex <= heap->size && heap->data[leftIndex]->frequency <= heap->data[i]->frequency) {
        smallest = leftIndex;
    }

    if(rightIndex <= heap->size && heap->data[rightIndex]->frequency <= heap->data[smallest]->frequency) {
        smallest = rightIndex;
    }

    if(smallest != i) {
        swap_nodes(&heap->data[i], &heap->data[smallest]);

        min_heapify(heap, smallest);
    }

}

// Transforma o array em uma heap mínima
void build_min_heap(Heap *heap) {

    int i;

    for (i = heap->size / 2; i > 0; i--) {
        min_heapify(heap, i);
    }

}

// Adiciona todos os nós da hashTable na heap e faz a heap mínima
Heap* ht_to_heap(HashTable *ht, Heap *heap) {

    int i, j = 1;

    for(i = 0; i < 256; i += 1) {

        if(ht->table[i]){
            heap->data[j] = create_heapNode(ht->table[i]->byte, ht->table[i]->frequency);
            heap->size++;
            j++;
        }

    }

    build_min_heap(heap);

    return heap;

}

// Adiciona novo node na Heap
void add_node(Heap *heap, HeapNode *node) {

    heap->data[++heap->size] = node;

    int key_index = heap->size;
    int parent_index = get_parent_index(heap->size);

    while(parent_index >= 1 && heap->data[key_index]->frequency <= heap->data[parent_index]->frequency){
        swap_nodes(&heap->data[key_index], &heap->data[parent_index]);
        key_index = parent_index;
        parent_index = get_parent_index(key_index);
    }

}

// Remove os 2 nodes com menor frequencia e adiciona um novo node com os nodes removidos
Heap *remove_node(Heap *heap) {

    if(heap->size){
        HeapNode *node = create_heapNode('*', heap->data[1]->frequency);
        node->left = heap->data[1];

        heap->data[1] = heap->data[heap->size];
        heap->data[heap->size] = NULL;
        heap->size--;

        min_heapify(heap, 1);

        if(heap->size >= 1) {
            node->frequency += heap->data[1]->frequency;
            node->right = heap->data[1];
            heap->data[1] = heap->data[heap->size];
            heap->data[heap->size] = NULL;
            heap->size--;

            min_heapify(heap, 1);
        }

        add_node(heap, node);
    }

    return heap;

}

void print_heap(Heap *heap) {

    int i = 1;
    while(i < heap->size){
        printf("(%c , %ld) | ", (unsigned char)heap->data[i]->byte, heap->data[i]->frequency);
        i++;
    }

    printf("(%c , %ld)\n", (unsigned char)heap->data[i]->byte, heap->data[i]->frequency);

}

void print_heap_as_tree(HeapNode *tree, FILE *out) {

    if(tree) {
        if((unsigned char)tree->byte == '\\' || ((unsigned char)tree->byte == '*' && !tree->left)) {
            fprintf(out, "\\");
        }
        fprintf(out, "%c", (unsigned char)tree->byte);

        print_heap_as_tree(tree->left, out);
        print_heap_as_tree(tree->right, out);
    }

}

int check_leaf(HeapNode *tree) {

    return (!tree->left && !tree->right);

}

Heap *createHuffTree(Heap *heap) {

    int i = 1;
    while(heap->size > 1 || i == 1){
        heap = remove_node(heap);
        i++;
    }

    return heap;

}

#endif //HUFFMAN_HEAP_H
