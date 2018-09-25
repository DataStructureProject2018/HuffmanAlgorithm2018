//
// Created by paulo on 09/09/2018.
//

#ifndef HUFFMAN_COMPRESS_H
#define HUFFMAN_COMPRESS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

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
        if(check_leaf(current)) {
            ht->table[current->byte]->compressed = bits;
            ht->table[current->byte]->compressed_len = len;
        }
        len++;
        bits <<= 1;
        createBits(current->left, ht, bits, len);
        bits++;
        createBits(current->right, ht, bits, len);
    }

}

unsigned char createTwoFirstBytes(HashTable *ht, unsigned short treeSize, FILE *out) {

    unsigned char trashSize = (unsigned char) (8 - totalBits(ht));

    unsigned short aux = trashSize;
    aux <<= 13;
    aux ^= treeSize;

    unsigned char second = aux, first = aux >> 8;
    fprintf(out, "%c%c", first, second);

    return trashSize;

}

void compress_bytes(HashTable *ht, FILE *in, FILE *out, unsigned char trashSize){

    short int caractere = 0;
    unsigned char auxByte = 0, byte, tam = 0, auxTamByte, tamByte = 0, i = 0;

    /*
     * auxByte = byte usado para receber a versão comprimida do(s) byte(s) atual(is)
     * i = contador para saber quantos bits do auxByte ja foram usados
     * tamByte = variavel que recebe quantos bits o byte atual possui em sua versão comprimida
     * tam = variavel usada para saber quantos bits setados o nosso auxByte possui
     * auxTamByte = usado para saber quantos bits estão livres no byte que vai ser printado no arquivo
     * caractere = recebe a versão comprimida do byte lido
     */

    while(!feof(in)){ //lemos o arquivo por completo

        if(i >= tamByte){ //caso ja tenhamos percorrido completamente os bits da representacao comprimida do byte atual
            i = 0; // zeramos a quantidade de bits percorridos
            fread(&byte, sizeof(byte), 1, in); //lemos um novo byte
            if(feof(in)) { // caso seja o final do arquivo apos lermos o ultimo
                auxByte <<= trashSize; // colocamos o lixo no byte a ser printado
                fprintf(out, "%c", auxByte); // printamos o ultimo byte
                return; //saimos da funcao
            }
            caractere = ht->table[byte]->compressed; // salvamos a versão comprimida do byte atual
            tamByte = ht->table[byte]->compressed_len; // salvamos a quantidade de bits que a versão comprimida possui
        }

        auxTamByte = 8 - tam; // vemos quantos bits do byte a ser printado estao livres

        if(auxTamByte < tamByte) { // caso a quantidade de bits da versao comprimida seja maior do que a quantidade de bits disponiveis no byte a ser printado
            auxByte <<= auxTamByte; //
            auxByte ^= caractere >> (tamByte - auxTamByte); // É adicionado alguns bits do caractere lido no Byte que vai ser escrito no arquivo comprimido
            i += tamByte - (tamByte - auxTamByte); // atualizamos quantos bits da versao comprimida do byte ja foram utilizados
            fprintf(out, "%c", auxByte);    // Printamos o novo Byte no arquivo comprimido

            if((8 - tamByte + auxTamByte) < 0) {
                auxByte = caractere >> abs(8 - tamByte + auxTamByte);
            } else {
                auxByte = caractere << (8 - tamByte + auxTamByte);
            }

            i += 8 - (8 - tamByte + auxTamByte); // atualizamos quantos bits da versao comprimida do byte ja foram utilizados

            tam = (tamByte - auxTamByte) - abs(8 - tamByte + auxTamByte); // atualizamos a quantidade de bits setados que possuimos no byte a ser printado

            if(tam != 8) { //caso não tenhamos um byte completo
                auxByte >>= (8 - tamByte + auxTamByte); // mandamos todos os bits setados para a direita, para que fiquem no inicio
                tam = tamByte - auxTamByte; // atualizamos a quantidade de bits setados que possuimos no byte a ser printado
            } else { // se tivermos um byte completo
                fprintf(out, "%c", auxByte); // printamos o byte no arquivo
                auxByte = caractere << (8 - (tamByte - 8 - auxTamByte)); // recebemos o restante dos bits que faltam na versao comprimida do byte
                auxByte >>= (8 - (tamByte - 8 - auxTamByte)); // mandamos todos os bits setados para a direita, de forma que estao no inicio
                tam = tamByte - 8 - auxTamByte; // atulaizamos a quantidade de bits setados que possuimos no byte a ser printado
            }
        } else { // caso tenhamos mais bits nao setados no byte do que a quantidade total de bits da versao comprimida
            auxByte <<= tamByte; // liberamos os bits das posicoes iniciais
            auxByte ^= caractere; // colocamos os bits da versao comprimida no byte a ser printado
            tam += tamByte; // atualizamos a quantidade de bits setados que possuimos no byte a ser printado
            i += tamByte; // ataulizamos a quantidade de bits da versão comprimida que ja foram utilizados
        }
    }
}

void start_compression() {

    char fileName[255] = "../", dir[255];

    printf("Type file name: ");
    scanf("%s", dir);
    strcat(fileName, dir);

    FILE *in = fopen(fileName, "rb");
    FILE *out = fopen("../compressed.huff", "wb");

    HashTable *ht = get_frequency(in);

    Heap *heap = create_heap();
    heap = ht_to_heap(ht, heap);

    heap = createHuffTree(heap);

    createBits(heap->data[1], ht, 0, 0);

    unsigned short treeSize = getTreeSize(heap->data[1], 0);
    unsigned char trashSize = createTwoFirstBytes(ht, treeSize, out);

    print_heap_as_tree(heap->data[1], out);
    fseek(in, 0, SEEK_SET);
    compress_bytes(ht, in, out, trashSize);

    destroy_table(ht);

    fclose(in);
    fclose(out);

}

#endif //HUFFMAN_COMPRESS_H
