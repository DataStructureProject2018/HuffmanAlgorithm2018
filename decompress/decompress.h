//
// Created by paulo on 11/09/2018.
//

#ifndef HUFFMAN_DECOMPRESS_H
#define HUFFMAN_DECOMPRESS_H

#include <stdio.h>
#include <stdlib.h>
int is_bit_i_set(unsigned char c, int i){

    unsigned char mask = 1 << i;
    return mask & c;
}
int extractTrashAndTreeSize(FILE *arquivo){ //gets the size of: tree and trash

    unsigned char c;
    int lixo = 0, tree = 0, bit, i; // bit will receive the value of the searched bit
    fread(&c, sizeof(c), 1, arquivo); //reads the first character and c receives it
    for(i = 7; i >= 0; i--){
        bit = is_bit_i_set(c, i);
        if(i > 4){
            if(bit == 0){
                lixo = lixo << 1;
            }
            else{
                lixo  = lixo << 1;
                lixo++;
            }
        }
        else{
            if(bit == 0){
                tree = tree << 1;
            }
            else{
                tree  = tree << 1;
                tree++;
            }
        }
    }
    fread(&c, sizeof(c), 1, arquivo); //reads the second character and c receives it
    for(i = 7; i >= 0; i--){
        bit = is_bit_i_set(c, i);
        if(bit == 0){
            tree = tree << 1;
        }
        else{
            tree = tree << 1;
            tree++;
        }
    }
    int *array = (int *)malloc(sizeof(int) * 2);
    array[0] = lixo;
    array[1] = tree;
    return array;
}
void start_decompression() {

    FILE *arquivo;
    int *array;

    arquivo = fopen("../teste.txt", "r");

    array = extractTrashAndTreeSize(arquivo);
    printf("lixo: %d e tree %d", array[0], array[1]);
    fclose(arquivo);

//    if (arquivo) {
//        while(!feof(arquivo)) {
//            fread(&c, sizeof(c), 1, arquivo);
//            if(!feof(arquivo)) {
//                printf("%c", c);
//            }
//        }
//
//        fclose(arquivo);
//    }
}

#endif //HUFFMAN_DECOMPRESS_H
