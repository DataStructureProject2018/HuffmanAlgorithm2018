#ifndef HUFFMAN_TEST_HASH_H
#define HUFFMAN_TEST_HASH_H

#include <CUnit/CUnit.h>
#include "CUnit/Basic.h"
#include "../TADs/hash_table.h"

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


#endif //HUFFMAN_TEST_HASH_H