#ifndef HUFFMAN_MAIN_TEST_H
#define HUFFMAN_MAIN_TEST_H

#include "./teste_hash.h"
#include "./teste_heap.h"

int run_tests() {
	test_put();
	test_get_parent_index();
	test_get_left_index();
	test_get_right_index();
	test_swap_nodes();
	test_add_node();
	test_check_leaf();
	test_ht_to_heap();
	test_merge_nodes();
	test_create_huffTree();
	test_get_treeSize();
	test_create_bits();
	test_min_heapify();
}


#endif //HUFFMAN_MAIN_TEST_H