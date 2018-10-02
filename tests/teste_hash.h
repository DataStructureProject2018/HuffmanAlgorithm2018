#ifndef HUFFMAN_TEST_HASH_H
#define HUFFMAN_TEST_HASH_H

#include <CUnit/CUnit.h>
#include "CUnit/Basic.h"
#include "../TADs/hash_table.h"
#include "../TADs/heap.h"

void test_put (void)
{
	HashTable *ht = create_table();
	ht = put(ht, 'A');
	ht = put(ht, 'A');
	ht = put(ht, 'A');
	ht = put(ht, 'B');
	ht = put(ht, 'B');
  	CU_ASSERT(ht->table['A']->frequency == 3);
  	CU_ASSERT(ht->table['B']->frequency == 2);
  	destroy_table(ht);
}

void test_create_bits() {

	int i;
	Heap *heap = create_heap();
	HashTable *ht = create_table();
	add_node(heap, create_heapNode((void *)'A', 6));
	for(i=0;i<6;i++) ht = put(ht, 'A');
	add_node(heap, create_heapNode((void *)'B', 5));
	for(i=0;i<5;i++) ht = put(ht, 'B');
	add_node(heap, create_heapNode((void *)'C', 4));
	for(i=0;i<4;i++) ht = put(ht, 'C');
	add_node(heap, create_heapNode((void *)'D', 3));
	for(i=0;i<3;i++) ht = put(ht, 'D');
	add_node(heap, create_heapNode((void *)'E', 2));
	for(i=0;i<2;i++) ht = put(ht, 'E');
	add_node(heap, create_heapNode((void *)'F', 1));
	for(i=0;i<1;i++) ht = put(ht, 'F');

	heap = createHuffTree(heap);

	createBits(heap->data[1], ht, 0, 0);

	CU_ASSERT(ht->table['A']->compressed_len == 2 && ht->table['A']->compressed == 3);
    CU_ASSERT(ht->table['B']->compressed_len == 2 && ht->table['B']->compressed == 1);
    CU_ASSERT(ht->table['C']->compressed_len == 2 && ht->table['C']->compressed == 0);
    CU_ASSERT(ht->table['D']->compressed_len == 3 && ht->table['D']->compressed == 5);
    CU_ASSERT(ht->table['E']->compressed_len == 4 && ht->table['E']->compressed == 9);
    CU_ASSERT(ht->table['F']->compressed_len == 4 && ht->table['F']->compressed == 8);

    destroy_heap(heap);
    destroy_table(ht);

}


#endif //HUFFMAN_TEST_HASH_H