//
// Created by paulo on 26/09/2018.
//

#ifndef HUFFMAN_HEAP_TEST_H
#define HUFFMAN_HEAP_TEST_H

#include "minunit.h"
#include "../TADs/heap.h"

static char *test_create_heap() {
    mu_assert("err, failed to create heap", create_heap() != NULL);
    return 0;
}

static char *test_get_parent_index() {
    mu_assert("err, failed to get parent index", get_parent_index(2) == 1);
    return 0;
}

static char *test_get_left_index() {
    mu_assert("err, failed to get left index", get_left_index(2) == 4);
    return 0;
}

static char *test_get_right_index() {
    mu_assert("err, failed to get right index", get_right_index(2) == 5);
    return 0;
}

static char *test_swap_nodes() {
    HeapNode *first = create_heapNode('1', 1);
    HeapNode *second = create_heapNode('2', 2);
    swap_nodes(&first, &second);
    mu_assert("err, failed to swap nodes", ((int)first->byte == '2' && first->frequency == 2)
                                             &&
                                           ((int)second->byte == '1' && second->frequency == 1));
    free(first);
    free(second);
    return 0;
}

static char *test_ht_to_heap() {
    HashTable *ht = create_table();
    Heap *heap = create_heap();
    ht = put(ht, 'a');
    heap = ht_to_heap(ht, heap);
    mu_assert("err, failed to transfer hash table to heap", (unsigned char)heap->data[1]->byte == 'a');
    destroy_table(ht);
    destroy_heap(heap);
    return 0;
}

static char *test_add_node() {
    Heap *heap = create_heap();
    HeapNode *node = create_heapNode('A', 2);
    add_node(heap, node);
    mu_assert("err, failed to add node to heap", heap->data[1] == node);
    free(node);
    destroy_heap(heap);
    return 0;
}

static char *test_remove_node() {
    Heap *heap = create_heap();
    add_node(heap, create_heapNode('A', 2));
    add_node(heap, create_heapNode('B', 3));
    remove_node(heap);
    mu_assert("err, failed to remove node from heap", heap->size == 1);
    destroy_HuffTree(heap->data[1]);
    destroy_heap(heap);
    return 0;
}

static char *test_check_leaf() {
    HeapNode *node = create_heapNode('A', 2);
    mu_assert("err, failed to check leaf", check_leaf(node) == 1);
    return 0;
}

static char *test_getTreeSize() {
    Heap *heap = create_heap();
    add_node(heap, create_heapNode('A', 2));
    heap = createHuffTree(heap);
    mu_assert("err, failed to get tree size", getTreeSize(heap->data[1], 0) == 2);
    destroy_HuffTree(heap->data[1]);
    destroy_heap(heap);
    return 0;
}

#endif //HUFFMAN_HEAP_TEST_H
