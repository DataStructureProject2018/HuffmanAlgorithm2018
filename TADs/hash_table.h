//
// Created by paulo on 09/09/2018.
//

#ifndef HUFFMAN_HASH_TABLE_H
#define HUFFMAN_HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include "nodes.h"

#define MAX_TABLE_SIZE 256

typedef struct hashTable {
    HashNode *table[MAX_TABLE_SIZE];
} HashTable;

// Cria uma hashTable com tamanho 256
HashTable *create_table() {

    int i;
    HashTable *new_ht = (HashTable *)malloc(sizeof(HashTable));

    for(i = 0; i < MAX_TABLE_SIZE; i += 1) {
        new_ht->table[i] = NULL;
    }

    return new_ht;

}
// Insere um  byte na hashTable, caso ele já exista a sua frequência somente aumenta.
HashTable *put(HashTable *ht, unsigned char byte) {


    if(ht->table[byte]) {
        ht->table[byte]->frequency += 1;
    } else {
        ht->table[byte] = create_hashNode(byte);
    }

    return ht;

}

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

// Apaga a hashTable
void destroy_table(HashTable *ht) {

    int i;

    for(i = 0; i < MAX_TABLE_SIZE; i += 1) {
        if(ht->table[i]) {
            free(ht->table[i]);
        }
    }
    free(ht);
}

#endif //HUFFMAN_HASH_TABLE_H
