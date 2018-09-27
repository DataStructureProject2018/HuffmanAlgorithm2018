//
// Created by paulo on 26/09/2018.
//

#ifndef HUFFMAN_HASHTABLE_TEST_H
#define HUFFMAN_HASHTABLE_TEST_H

#include "minunit.h"
#include "../TADs/hash_table.h"

static char *test_create_table() {
    HashTable *ht = create_table();
    mu_assert("err, failed to create table", ht != NULL);
    destroy_table(ht);
    return 0;
}

static char *test_put() {
    HashTable *ht = create_table();
    mu_assert("err, failed to put at table", put(ht, 'a') != NULL);
    destroy_table(ht);
    return 0;
}

static char *test_get_frequency(){
    FILE *in = fopen("../tests/teste.txt", "rb");
    if(!in) {
        return "err, could not open file";
    }
    mu_assert("err, failed to get frequency", get_frequency(in) != NULL);
    fclose(in);
}


#endif //HUFFMAN_HASHTABLE_TEST_H
