//
// Created by danie on 17/09/2018.
//

#ifndef PROJECT_TREE_H
#define PROJECT_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include "./nodes.h"

TreeNode* make_tree(FILE *arquivo, int treeSize, TreeNode *tree) {

    if(!treeSize) {
        return tree;
    }
    unsigned char c;
    fread(&c, sizeof(c), 1, arquivo);

    if(c != '*') {
        if(c == '\\') {
            fread(&c, sizeof(c), 1, arquivo);
            treeSize--;
        }
        tree = create_node(c);
        treeSize--;
        return tree;
    } else {
        tree = create_node(c);
        treeSize--;
        tree->left = make_tree(arquivo, treeSize, tree->left);
        tree->right = make_tree(arquivo, treeSize, tree->right);
    }

    return tree;

}
//
//void print_tree(TreeNode *tree){
//
//    if(tree){
//        printf("%c ", (unsigned char)tree->byte);
//        print_tree(tree->left);
//        print_tree(tree->right);
//    }
//
//}

void destroy_tree(TreeNode *tree) {

    if(tree) {
        destroy_tree(tree->left);
        destroy_tree(tree->right);
        free(tree);
    }

}



#endif //PROJECT_TREE_H
