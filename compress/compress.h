//
// Created by paulo on 09/09/2018.
//

#ifndef HUFFMAN_COMPRESS_H
#define HUFFMAN_COMPRESS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../TADs/hash_table.h"
#include "../TADs/heap.h"
#include "../TADs/utilities.h"



unsigned short getTreeSize(HeapNode *tree, unsigned short cont) {

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


unsigned char totalBits(HashTable *ht) {

    unsigned long total = 0;
    int i;

    for(i = 0; i < MAX_TABLE_SIZE; i++) {
        if(ht->table[i]) {
            total += (ht->table[i]->frequency * ht->table[i]->compressed_len);
        }
    }

    return total%8;
}

void createBits(HeapNode *tree, HashTable *ht, unsigned short bits, unsigned char len) {

    HeapNode *current = tree;
    if(current) {
//        printf("byte: %c\n", current->byte);
        if(check_leaf(current)) {
//            printf("Inserting %c\n", current->byte);
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
unsigned char createTwoFirstBytes(HashTable *ht, unsigned short treeSize, FILE *out) {

    unsigned char trashSize = (unsigned char) (8 - totalBits(ht));
//    printf("Lixo: %d\tArvore: %d\n", trashSize, treeSize);

    unsigned short aux = trashSize;
    aux <<= 13;
    aux ^= treeSize;

//    printf("aux: %d\n", aux);
    unsigned char second = aux, first = aux >> 8;
    // TODO mudar para fprintf
    fprintf(out, "%c%c", first, second);

    return trashSize;

}

void compress_bytes(HashTable *ht, FILE *in, FILE *out, unsigned char trashSize){

    int tam = 0, auxTamByte, tamByte = 0, i = 0;
    short int caractere = 0;
    unsigned char auxByte = 0, byte;


    while(!feof(in)){

        if(i >= tamByte){
            i = 0;
            fread(&byte, sizeof(byte), 1, in);
            if(feof(in)) {
                auxByte <<= trashSize;
                fprintf(out, "%c", auxByte);
                return;
            }
            caractere = ht->table[byte]->compressed;
            tamByte = ht->table[byte]->compressed_len;
        }

        auxTamByte = 8 - tam;


        if(auxTamByte < tamByte) {

            auxByte <<= auxTamByte;
            auxByte ^= caractere >> (tamByte - auxTamByte);
            i += tamByte - (tamByte - auxTamByte);
            fprintf(out, "%c", auxByte);

            if((8 - tamByte + auxTamByte) < 0) {
                auxByte = caractere >> abs(8 - tamByte + auxTamByte); // - >>
            } else {
                auxByte = caractere << (8 - tamByte + auxTamByte); // - >>
            }
            i += 8 - (8 - tamByte + auxTamByte);
            tam = (tamByte - auxTamByte) - abs(8 - tamByte + auxTamByte);

            if(tam != 8) {
                auxByte >>= (8 - tamByte + auxTamByte);
                tam = tamByte - auxTamByte;
            } else {
                fprintf(out, "%c", auxByte);
                auxByte = caractere << (8 - (tamByte - 8 - auxTamByte));
                auxByte >>= (8 - (tamByte - 8 - auxTamByte));
                tam = tamByte - 8 - auxTamByte;
            }

        } else {

            auxByte <<= tamByte;
            auxByte += caractere;
            tam += tamByte;
            i += tamByte;

        }

    }


}


void start_compression() {

    FILE *in = fopen("../teste.txt", "rb");
    FILE *out = fopen("../compressed.huff", "wb");

    HashTable *ht = get_frequency(in);

//    print_table(ht);

//    printf("Printando a Heap:\n");

    Heap *heap = create_heap();
    heap = ht_to_heap(ht, heap);

//    print_heap(heap);

    int i = 1;
    while(heap->size > 1 || i == 1){
        remove_node(heap);
        i++;
//        print_heap(heap);
    }


    createBits(heap->data[1], ht, 0, 0);

//    print_table(ht);

    unsigned short treeSize = getTreeSize(heap->data[1], 0);
    unsigned char trashSize = createTwoFirstBytes(ht, treeSize, out);

//    printf("Printando arvore:\n");
    print_heap_as_tree(heap->data[1], out);
    fseek(in, 0, SEEK_SET);
    compress_bytes(ht, in, out, trashSize);

    fclose(in);
    fclose(out);

}

#endif //HUFFMAN_COMPRESS_H
