//
// Created by paulo on 11/09/2018.
//

#ifndef HUFFMAN_DECOMPRESS_H
#define HUFFMAN_DECOMPRESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../TADs/tree.h"
#include "../TADs/utilities.h"

unsigned short extract_trash_and_tree_size(FILE *arquivo) { //gets the size of: tree and trash

    unsigned char byte;
    fread(&byte, sizeof(byte), 1, arquivo);
    unsigned short twoFirstBytes = byte;
    twoFirstBytes <<= 8;
    fread(&byte, sizeof(byte), 1, arquivo);
    twoFirstBytes ^= byte;

    return twoFirstBytes;

}

void decompress_file(FILE *arquivo, off_t fileSize, TreeNode *tree, short int treeSize, unsigned char lixo, FILE *newFile) {

    TreeNode *treeRoot = tree; //saves the root of the tree
    int i, bit;
    unsigned char c;
    unsigned long long j = 0;

    while(j < fileSize - 3 - treeSize) {

        fread(&c, sizeof(c), 1, arquivo);

        for(i = 7; i >= 0 ; --i) {

            bit = is_bit_i_set(c, i);// bit will receive the value of the searched bit

            if(bit > 0) {
                treeRoot = treeRoot->right;
            } else {
                treeRoot = treeRoot->left;
            }

            if(!treeRoot->right && !treeRoot->left) {// if a leaf is found
                fprintf(newFile, "%c", (unsigned char)treeRoot->byte);//write data into file
                treeRoot = tree; // returning to the root
            }
        }
        j++;
    }
    fread(&c, sizeof(c), 1, arquivo); //giving c the last byte

    for(i = 7; i >= 0 + lixo; --i) { //last byte operation
        bit = is_bit_i_set(c, i);// bit will receive the value of the searched bit

        if(bit > 0) {
            treeRoot = treeRoot->right;
        } else {
            treeRoot = treeRoot->left;
        }

        if(!treeRoot->right && !treeRoot->left) {// if a leaf is found
            fprintf(newFile, "%c", (unsigned char)treeRoot->byte);//write data into file
            treeRoot = tree; // returning to the root
        }
    }

}


void start_decompression() {

    TreeNode *tree = NULL;
    FILE *arquivo, *newFile;
    unsigned short twoFirstBytes, treeSize;
    unsigned char trashSize;

    char fileName[255], dir[255];

    printf("Type file name: ");
    scanf("%s", fileName);

    arquivo = fopen(fileName, "rb");
    if(!arquivo) {
        printf("Failed to open %s...\n", fileName);
        return;
    }

    memcpy(dir, fileName, strlen(fileName)-5);
    dir[strlen(fileName)-5] = '\0';
    newFile = fopen(dir, "wb");
    if(!newFile) {
        printf("Failed to create the decompressed file...\n");
        return;
    }

    fseek(arquivo, 0, SEEK_END); //arquivo will now point to the end of the file

    off_t fileSize = ftello(arquivo); // off_t can support 2^63 , we use this to support large files
    fseek(arquivo, 0, SEEK_SET);
    printf("Getting trash and tree size...\n");
    twoFirstBytes = extract_trash_and_tree_size(arquivo);
    treeSize = (twoFirstBytes << 3); // >> 3 in the same line, does not work
    treeSize >>= 3;
    trashSize = twoFirstBytes >> 13;
    printf("%d %d\n", treeSize, trashSize);

    printf("Done...!\n");
    printf("Building tree from file...\n");
    tree = make_tree(arquivo, &treeSize, tree);
    printf("Done...!\n");
    printf("Starting decompression...\n");
    decompress_file(arquivo, fileSize, tree, treeSize, trashSize, newFile);
    printf("Done...!\n");

    destroy_tree(tree);

    fclose(arquivo);
    fclose(newFile);
    printf("Program finished, exiting now...\n");

}

#endif //HUFFMAN_DECOMPRESS_H