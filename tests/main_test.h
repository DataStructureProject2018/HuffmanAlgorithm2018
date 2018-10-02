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
}


#endif //HUFFMAN_MAIN_TEST_H