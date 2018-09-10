//
// Created by paulo on 09/09/2018.
//

#ifndef HUFFMAN_COMPRESS_H
#define HUFFMAN_COMPRESS_H

#include <stdio.h>
#include <stdlib.h>

#include "../TADs/hash_table.h"

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

#endif //HUFFMAN_COMPRESS_H
