//
// Created by paulo on 11/09/2018.
//

#ifndef HUFFMAN_DECOMPRESS_H
#define HUFFMAN_DECOMPRESS_H

#include <stdio.h>
#include <stdlib.h>
#include "../TADs/tree.h"
#include "../TADs/utilities.h"

short int *extract_trash_and_tree_size(FILE *arquivo) { //gets the size of: tree and trash

    unsigned char c, lixo = 0, bit, i;
    short int tree = 0;
    fread(&c, sizeof(c), 1, arquivo);
    for(i = 7; i >= 0; i--) {
        bit = is_bit_i_set(c, i);
        if(i > 4){
            if(bit == 0){
                lixo <<= 1;
            } else {
                lixo <<= 1;
                lixo++;
            }
        } else {
            if(bit == 0){
                tree <<= 1;
            } else {
                tree <<= 1;
                tree++;
            }
        }
    }
    fread(&c, sizeof(c), 1, arquivo); //reads the second character and c receives it
    for(i = 7; i >= 0; i--) {
        bit = is_bit_i_set(c, i);
        if(bit == 0) {
            tree <<= 1;
        } else {
            tree <<= 1;
            tree++;
        }
    }
    short int *array = (short int *)malloc(sizeof(short int) * 2);
    array[0] = lixo;
    array[1] = tree;

    return array;

}

void decompress_file(FILE *arquivo, unsigned long fileSize, TreeNode *tree, short int treeSize, unsigned char lixo, FILE *newFile) {

    TreeNode *treeRoot = tree; //saves the root of the tree
    int i, bit;
    unsigned char c;
    unsigned long j = 0;

    while(j < fileSize - 3 - treeSize) {

        fread(&c, sizeof(c), 1, arquivo);

        for(i = 7; i >= 0 ; i--) {

            bit = is_bit_i_set(c, i);// bit will receive the value of the searched bit

            if(bit > 0) {
                treeRoot = treeRoot->right;
            } else {
                treeRoot = treeRoot->left;
            }

            if(treeRoot->right == NULL && treeRoot->left == NULL) {// if a leaf is found
                fprintf(newFile, "%c", (unsigned char)treeRoot->byte);//write data into file
                treeRoot = tree; // returning to the root
            }
        }
        j++;
    }

    fread(&c, sizeof(c), 1, arquivo); //giving c the last byte

    for(i = 7; i >= 0 + lixo; i--) { //last byte operation

        bit = is_bit_i_set(c, i);// bit will receive the value of the searched bit

        if(bit > 0) {
            treeRoot = treeRoot->right;
        } else {
            treeRoot = treeRoot->left;
        }

        if(treeRoot->right == NULL && treeRoot->left == NULL) {// if a leaf is found
            fprintf(newFile, "%c", (unsigned char)treeRoot->byte);//write data into file
            treeRoot = tree; // returning to the root
        }
    }

    //end of function
}


void start_decompression() {

    TreeNode *tree = NULL;
    FILE *arquivo, *newFile;
    short int *array;

    arquivo = fopen("../compressed.huff", "rb");
    newFile = fopen("../decompressedfile", "wb");

    fseek(arquivo, 0, SEEK_END); //arquivo will now point to the end of the file

    unsigned long fileSize = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);
    array = extract_trash_and_tree_size(arquivo);
    tree = make_tree(arquivo, array[1], tree);
    decompress_file(arquivo, fileSize, tree, array[1], (unsigned char)array[0], newFile);

    destroy_tree(tree);

    fclose(arquivo);
    fclose(newFile);
    printf("processo finalizado");

}

#endif //HUFFMAN_DECOMPRESS_H