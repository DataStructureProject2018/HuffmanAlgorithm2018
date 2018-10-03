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


unsigned char trash_size(HashTable *ht) {

    off_t total = 0; // to support large files
    int i;

    for(i = 0; i < MAX_TABLE_SIZE; i++) {
        if(ht->table[i]) {
            total += (ht->table[i]->frequency * ht->table[i]->compressed_len);
        }
    }

    return 8 - (total % 8);
}

unsigned char createTwoFirstBytes(HashTable *ht, unsigned short treeSize, FILE *out) {

    unsigned char trashSize = (trash_size(ht));

    unsigned char first = (unsigned char)((trashSize << 5) ^ (treeSize >> 8)), second = (unsigned char)treeSize;

    fprintf(out, "%c%c", first, second);

    return trashSize;

}

void compress_bytes(HashTable *ht, FILE *in, FILE *out, unsigned char trashSize){

    short int caractere = 0;
    unsigned char auxByte = 0, byte, quantBitsUsados = 0, quantBitsLivres, tamByte = 0, i = 0;

    /*
     * auxByte = byte usado para receber a versão comprimida do(s) byte(s) atual(is)
     * i = contador para saber quantos bits do auxByte ja foram usados
     * tamByte = variavel que recebe quantos bits o byte atual possui em sua versão comprimida
     * quantBitsUsados = variavel usada para saber quantos bits setados o nosso auxByte possui
     * quantBitsLivres = usado para saber quantos bits estão livres no byte que vai ser printado no arquivo
     * caractere = recebe a versão comprimida do byte lido
     */

    while(!feof(in)){ //lemos o arquivo por completo

        if(i >= tamByte){ //caso ja tenhamos percorrido completamente os bits da representacao comprimida do byte atual
            i = 0; // zeramos a quantidade de bits percorridos
            fread(&byte, sizeof(byte), 1, in); //lemos um novo byte
            if(feof(in)) { // caso seja o final do arquivo apos lermos o ultimo
                auxByte <<= trashSize; // colocamos o lixo no byte a ser printado
                fprintf(out, "%c", auxByte); // printamos o ultimo byte
                return;
            }
            caractere = ht->table[byte]->compressed; // salvamos a versão comprimida do byte atual
            tamByte = ht->table[byte]->compressed_len; // salvamos a quantidade de bits que a versão comprimida possui
        }

        quantBitsLivres = 8 - quantBitsUsados; // vemos quantos bits do byte a ser printado estao livres

        if(quantBitsLivres < tamByte) { // caso a quantidade de bits da versao comprimida seja maior do que a quantidade de bits disponiveis no byte a ser printado
            auxByte <<= quantBitsLivres; //
            auxByte ^= caractere >> (tamByte - quantBitsLivres); // É adicionado alguns bits do caractere lido no Byte que vai ser escrito no arquivo comprimido
            i += tamByte - (tamByte - quantBitsLivres); // atualizamos quantos bits da versao comprimida do byte ja foram utilizados
            fprintf(out, "%c", auxByte);    // Printamos o novo Byte no arquivo comprimido

            if((8 - tamByte + quantBitsLivres) < 0) {
                auxByte = caractere >> abs(8 - tamByte + quantBitsLivres);
            } else {
                auxByte = caractere << (8 - tamByte + quantBitsLivres);
            }

            i += 8 - (8 - tamByte + quantBitsLivres); // atualizamos quantos bits da versao comprimida do byte ja foram utilizados

            quantBitsUsados = (tamByte - quantBitsLivres) - abs(8 - tamByte + quantBitsLivres); // atualizamos a quantidade de bits setados que possuimos no byte a ser printado

            if(quantBitsUsados != 8) { //caso não tenhamos um byte completo
                auxByte >>= (8 - tamByte + quantBitsLivres); // mandamos todos os bits setados para a direita, para que fiquem no inicio
                quantBitsUsados = tamByte - quantBitsLivres; // atualizamos a quantidade de bits setados que possuimos no byte a ser printado
            } else { // se tivermos um byte completo
                fprintf(out, "%c", auxByte); // printamos o byte no arquivo
                auxByte = caractere << (8 - (tamByte - 8 - quantBitsLivres)); // recebemos o restante dos bits que faltam na versao comprimida do byte
                auxByte >>= (8 - (tamByte - 8 - quantBitsLivres)); // mandamos todos os bits setados para a direita, de forma que estao no inicio
                quantBitsUsados = tamByte - 8 - quantBitsLivres; // atualizamos a quantidade de bits setados que possuimos no byte a ser printado
            }
        } else { // caso tenhamos mais bits nao setados no byte do que a quantidade total de bits da versao comprimida
            auxByte <<= tamByte; // liberamos os bits das posicoes iniciais
            auxByte ^= caractere; // colocamos os bits da versao comprimida no byte a ser printado
            quantBitsUsados += tamByte; // atualizamos a quantidade de bits setados que possuimos no byte a ser printado
            i += tamByte; // ataulizamos a quantidade de bits da versão comprimida que ja foram utilizados
        }
    }
}

void start_compression() {

    char fileName[255];

    printf("Type file name: ");
    scanf("%s", fileName);

    FILE *in = fopen(fileName, "rb");
    if(!in) {
        printf("Failed to open %s\n", fileName);
        return;
    }
    strcat(fileName, ".huff");
    FILE *out = fopen(fileName, "wb");
    if(!out) {
        printf("Failed to open the compressed file\n");
        return;
    }

    printf("Getting bytes frequency...\n");
    HashTable *ht = get_frequency(in);
    printf("Done...\n");
    printf("Creating heap...\n");
    Heap *heap = create_heap();
    printf("Done...\n");
    printf("Transferring hashTable to heap...\n");
    heap = ht_to_heap(ht, heap);
    printf("Done...\n");
    printf("Creating HuffTree...\n");
    heap = createHuffTree(heap);
    printf("Done...\n");
    printf("Creating compressed bytes representation...\n");
    createBits(heap->data[1], ht, 0, 0);
    printf("Done...\n");
    printf("Getting tree size...\n");
    unsigned short treeSize = getTreeSize(heap->data[1], 0);
    printf("Done...\n");
    printf("Getting trash size and creating the first two bytes...\n");
    unsigned char trashSize = createTwoFirstBytes(ht, treeSize, out);
    printf("Done...\n");
    printf("Printing tree in file...\n");
    print_huffTree(heap->data[1], out);
    printf("Done...\n");
    fseek(in, 0, SEEK_SET);
    printf("Starting compression...\n");
    compress_bytes(ht, in, out, trashSize);
    printf("Done...\n");

    destroy_table(ht);
    destroy_heap(heap);

    fclose(in);
    fclose(out);;
    printf("Program finished, exiting now...\n");

}

#endif //HUFFMAN_COMPRESS_H
