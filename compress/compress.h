//
// Created by paulo on 09/09/2018.
//

#ifndef HUFFMAN_COMPRESS_H
#define HUFFMAN_COMPRESS_H

#include <stdio.h>
#include <stdlib.h>

#include "../TADs/hash_table.h"
#include "../TADs/heap.h"

// Percorre o arquivo completamento e adiciona os caracteres na hashTable
HashTable *get_frequency(FILE *in) {

    HashTable *ht = create_table();
    unsigned char byte;

    while(!feof(in)) {
        fread(&byte, sizeof(byte), 1, in);
        if(!feof(in)) {
            ht = put(ht, byte);
        }
    }

    return ht;
}

unsigned int getTreeSize(HeapNode *tree, unsigned int cont) {

    HeapNode *current = tree;
    if(current != NULL) {
        cont++;
        if(check_leaf(current)) {
            if(current->byte == '\\' || current->byte == '*') {
                cont++;
            }
        }
        cont = getTreeSize(current->left, cont);
        cont = getTreeSize(current->right, cont);
    }
    return cont;

}


unsigned long totalBits(HashTable *ht) {

    unsigned long total = 0;
    int i;

    for(i = 0; i < MAX_TABLE_SIZE; i++) {
        if(ht->table[i]) {
            total += (ht->table[i]->frequency * ht->table[i]->compressed_len);
        }
    }

    return total%8;
}

void createBits(HeapNode *tree, HashTable *ht, unsigned short int bits, unsigned short int len) {

    HeapNode *current = tree;
    if(current) {
        printf("byte: %c\n", current->byte);
        if(check_leaf(current)) {
            printf("Inserting %c\n", current->byte);
            int key = create_key(current->byte);
            ht->table[key]->compressed = bits;
            ht->table[key]->compressed_len = len;
        }
        len++;
        bits <<= 1;
        createBits(current->left, ht, bits, len);
        bits++;
        createBits(current->right, ht, bits, len);
    }

}

// TODO UNFINISHED
void createTwoFirstBytes(HashTable *ht, unsigned int treeSize, FILE *in) {
    unsigned char trashSize = (unsigned char) (8 - totalBits(ht));
    unsigned char byte;

    fread(&byte, sizeof(byte), 1, in);




    printf("Lixo: %d\tArvore: %d\n", trashSize, treeSize);
}

void start_compression() {

    FILE *in = fopen("../teste.txt", "rb");

    HashTable *ht = get_frequency(in);

    print_table(ht);

    printf("Printando a Heap:\n");

    Heap *heap = create_heap();
    heap = ht_to_heap(ht, heap);

    print_heap(heap);

    int i = 1;
    while(heap->size > 1 || i == 1){
        printf("\n%d: Removeu os 2 menores nos\nAdicionou um novo no\n", i++);
        remove_node(heap);
        print_heap(heap);
    }

    print_heap_as_tree(heap->data[1]);

    createBits(heap->data[1], ht, 0, 0);

    print_table(ht);

    createTwoFirstBytes(ht, getTreeSize(heap->data[1], 0));

    fclose(in);

}

#endif //HUFFMAN_COMPRESS_H
