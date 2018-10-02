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

    // Verificamos se o filho da esquerda é menor do que o pai dele
    if(leftIndex <= heap->size && heap->data[leftIndex]->frequency <= heap->data[i]->frequency) {
        smallest = leftIndex;
    }

    // Verificamos se o filho da direita é menor do que o da esquerda (caso o da esquerda seja menor do que o pai)
    if(rightIndex <= heap->size && heap->data[rightIndex]->frequency <= heap->data[smallest]->frequency) {
        smallest = rightIndex;
    }

    // Caso tenhamos achado um filho menor, trocamos ele com o pai e continuamos a arrumar a heap
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

    unsigned short i, j = 1;

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
Heap *merge_nodes(Heap *heap) {

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

void print_huffTree(HeapNode *tree, FILE *out) {

    if(tree) {
        if(!tree->left && ( (unsigned char)tree->byte == '\\' || ((unsigned char)tree->byte == '*')) ) {
            fprintf(out, "\\");
        }
        fprintf(out, "%c", (unsigned char)tree->byte);

        print_huffTree(tree->left, out);
        print_huffTree(tree->right, out);
    }

}

int check_leaf(HeapNode *tree) {

    return (!tree->left && !tree->right);

}

Heap *createHuffTree(Heap *heap) {

    unsigned char i = 1;
    while(heap->size > 1 || i == 1){
        heap = merge_nodes(heap);
        ++i;
    }

    return heap;

}

unsigned short getTreeSize(HeapNode *tree, unsigned short cont) {

    if(tree) {
        ++cont;
        if(check_leaf(tree)) {
            if((unsigned char)tree->byte == '\\' || (unsigned char)tree->byte == '*') {
                cont++;
            }
        }
        cont = getTreeSize(tree->left, cont);
        cont = getTreeSize(tree->right, cont);
    }
    return cont;

}

// Cria a versao comprimida de cada byte, e salva na hashTable ela e a quantidade de bits que usaremos dela
void createBits(HeapNode *tree, HashTable *ht, unsigned short bits, unsigned char len) {

    if(tree) {
        if(check_leaf(tree)) {
            ht->table[(unsigned char)tree->byte]->compressed = bits;
            ht->table[(unsigned char)tree->byte]->compressed_len = len;
            return;
        }
        len++;
        bits <<= 1;
        createBits(tree->left, ht, bits, len);
        bits++;
        createBits(tree->right, ht, bits, len);
    }

}

void destroy_HuffTree(HeapNode *tree) {

    if(tree) {
        destroy_HuffTree(tree->left);
        destroy_HuffTree(tree->right);
        free(tree);
    }

}

void destroy_heap(Heap *heap) {

    int i;

    destroy_HuffTree(heap->data[1]);

    for(i = 2; i < MAX_HEAP_SIZE; i++) {
        if(heap->data[i]) {
            free(heap->data[i]);
        }
    }

    free(heap);

};

#endif //HUFFMAN_HEAP_H
