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

    return i/2;

}

// Retorna a posição do Filho da esquerda do nó de índice i
int get_left_index(int i) {

    return 2*i;

}

// Retorna a posição do Filho da direita do nó de índice i
int get_right_index(int i) {

    return 2*i+1;

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

    if(leftIndex <= heap->size && heap->data[leftIndex]->frequency < heap->data[i]->frequency) {
        smallest = leftIndex;
    }

    if(rightIndex <= heap->size && heap->data[rightIndex]->frequency < heap->data[smallest]->frequency) {
        smallest = rightIndex;
    }

    if(heap->data[smallest]->frequency != heap->data[i]->frequency) {
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
Heap* add_heap(HashTable *ht, Heap *heap) {

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

void print_heap(Heap *heap){

    int i = 1;

    while(i < heap->size){

        printf("(%c , %ld) | ", heap->data[i]->byte, heap->data[i]->frequency);
        i++;

    }

    printf("(%c , %ld)\n", heap->data[i]->byte, heap->data[i]->frequency);

}

#endif //HUFFMAN_HEAP_H
