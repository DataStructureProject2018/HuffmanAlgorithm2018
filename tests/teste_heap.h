#ifndef HUFFMAN_TEST_HEAP_H
#define HUFFMAN_TEST_HEAP_H

#include <CUnit/CUnit.h>
#include "CUnit/Basic.h"
#include "../TADs/heap.h"

void test_get_treeSize() {

    Heap *heap = create_heap();
    add_node(heap, create_heapNode((void *)'A', 6));
    add_node(heap, create_heapNode((void *)'B', 5));
    add_node(heap, create_heapNode((void *)'C', 4));
    add_node(heap, create_heapNode((void *)'D', 3));
    add_node(heap, create_heapNode((void *)'E', 2));
    add_node(heap, create_heapNode((void *)'F', 1));

    heap = createHuffTree(heap);

    CU_ASSERT(getTreeSize(heap->data[1], 0) == 11);
    destroy_heap(heap);

}

void test_get_parent_index (void)
{
	CU_ASSERT(get_parent_index(2) == 1);
	CU_ASSERT(get_parent_index(4) == 2);
	CU_ASSERT(get_parent_index(6) == 3);
}

void test_get_left_index (void) {

	CU_ASSERT(get_left_index(2) == 4);
	CU_ASSERT(get_left_index(4) == 8);
	CU_ASSERT(get_left_index(6) == 12);

}

void test_get_right_index (void) {

	CU_ASSERT(get_right_index(2) == 5);
	CU_ASSERT(get_right_index(4) == 9);
	CU_ASSERT(get_right_index(6) == 13);

}

void test_swap_nodes (void) {

	HeapNode *node1 = create_heapNode((void *)'A', 1);
	HeapNode *node2 = create_heapNode((void *)'B', 2);
	
	swap_nodes(&node1, &node2);

	CU_ASSERT((unsigned char)node1->byte == 'B' && node1->frequency == 2);
	CU_ASSERT((unsigned char)node2->byte == 'A' && node2->frequency == 1);

}

void test_add_node() {

	Heap *heap = create_heap();
	add_node(heap, create_heapNode((void *)'A', 3));
	CU_ASSERT((unsigned char)heap->data[1]->byte == 'A' && heap->data[1]->frequency == 3 && heap->size == 1);
	add_node(heap, create_heapNode((void *)'B', 2));
	CU_ASSERT((unsigned char)heap->data[1]->byte == 'B' && heap->data[1]->frequency == 2 && heap->size == 2)
	CU_ASSERT((unsigned char)heap->data[2]->byte == 'A' && heap->data[2]->frequency == 3 && heap->size == 2);
	destroy_heap(heap);

}

void test_check_leaf() {

    HeapNode *node = create_heapNode((void *)'A', 1);
    CU_ASSERT(check_leaf(node) == 1);
    node->left = create_heapNode((void *)'B', 2);
    CU_ASSERT(check_leaf(node) == 0);
    free(node);
}

void test_ht_to_heap() {

    HashTable *ht = create_table();
    ht = put(ht, 'A');
    Heap *heap = create_heap();
    ht_to_heap(ht, heap);
    CU_ASSERT((unsigned char)heap->data[1]->byte == 'A');
    destroy_table(ht);
    destroy_heap(heap);

}

void test_merge_nodes() {

    Heap *heap = create_heap();
    add_node(heap, create_heapNode((void *)'A', 2));
    add_node(heap, create_heapNode((void *)'B', 3));
    heap = merge_nodes(heap);
    CU_ASSERT((unsigned char)heap->data[1]->byte == '*' && heap->data[1]->frequency == 5);
    destroy_heap(heap);

}

void test_create_huffTree() {

    Heap *heap = create_heap();
    add_node(heap, create_heapNode((void *)'A', 6));
    add_node(heap, create_heapNode((void *)'B', 5));
    add_node(heap, create_heapNode((void *)'C', 4));
    add_node(heap, create_heapNode((void *)'D', 3));
    add_node(heap, create_heapNode((void *)'E', 2));
    add_node(heap, create_heapNode((void *)'F', 1));

    heap = createHuffTree(heap);

    CU_ASSERT(heap->data[1]->frequency == 21);
    destroy_heap(heap);

}


void test_min_heapify() {

    Heap *heap = create_heap();

    heap->data[1] = create_heapNode((void *)'A', 3);
    heap->data[2] = create_heapNode((void *)'B', 2);
    heap->data[3] = create_heapNode((void *)'C', 1);
    heap->size = 3;

    min_heapify(heap, 1);

    CU_ASSERT((unsigned char)heap->data[1]->byte == 'C' &&
              (unsigned char)heap->data[2]->byte == 'B' &&
              (unsigned char)heap->data[3]->byte == 'A');

    destroy_heap(heap);
}




#endif //HUFFMAN_TEST_HEAP_H