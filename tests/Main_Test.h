//
// Created by paulo on 26/09/2018.
//

#ifndef HUFFMAN_MAIN_TEST_H
#define HUFFMAN_MAIN_TEST_H

#include "HashTable_Test.h"
#include "Heap_Test.h"
#include "Tree_Test.h"
#include "minunit.h"

static char *all_tests() {
    mu_run_test(test_create_table);
    mu_run_test(test_put);
    mu_run_test(test_get_frequency);
    mu_run_test(test_create_heap);
    mu_run_test(test_get_parent_index);
    mu_run_test(test_get_left_index);
    mu_run_test(test_get_right_index);
    mu_run_test(test_swap_nodes);
    mu_run_test(test_ht_to_heap);
    mu_run_test(test_add_node);
    mu_run_test(test_remove_node);
    mu_run_test(test_check_leaf);
    mu_run_test(test_getTreeSize);
    mu_run_test(test_make_tree);
    return 0;
}

int runTests() {
    char *result = all_tests();
    if(result != 0) {
        printf("%s\n", result);
    }
    return result != 0;
}

#endif //HUFFMAN_MAIN_TEST_H
