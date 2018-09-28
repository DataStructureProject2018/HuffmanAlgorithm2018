//
// Created by paulo on 26/09/2018.
//

#ifndef HUFFMAN_TREE_TEST_H
#define HUFFMAN_TREE_TEST_H

#include "minunit.h"
#include "../TADs/tree.h"

static char *test_make_tree() {
    FILE *in = fopen("../tests/teste_arvore.txt", "rb");
    TreeNode *node = NULL;
    node = make_tree(in, 3, node);
    mu_assert("err, failed to make tree", ((unsigned char)node->left->byte == 'A' && (unsigned char)node->right->byte == 'B'));
    destroy_tree(node);
    return 0;
}


#endif //HUFFMAN_TREE_TEST_H
