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

    fclose(in);

}

#endif //HUFFMAN_COMPRESS_H
