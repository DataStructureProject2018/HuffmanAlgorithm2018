#include <CUnit/CUnit.h>
#include "CUnit/Basic.h"
#include "./main_test.h"

int init_suite(void)  { return 0; }
int clean_suite(void) { return 0; }

int start_tests (void)
{
   	CU_pSuite pSuite = NULL;

   /* Initialize CUnit test registry */
   	if (CUE_SUCCESS != CU_initialize_registry())
      	return CU_get_error();

   /* Add suite to registry */
   	pSuite = CU_add_suite("Basic_Test_Suite", init_suite, clean_suite);
   	if (NULL == pSuite) {
      	CU_cleanup_registry();
      	return CU_get_error();
    }

   /* add test to suite */
   	if ((NULL == CU_add_test(pSuite, "test_put", test_put)))
   	{
      	CU_cleanup_registry();
      	return CU_get_error();
   	}

   	if ((NULL == CU_add_test(pSuite, "test_get_parent_index", test_get_parent_index)))
   	{
      	CU_cleanup_registry();
      	return CU_get_error();
   	}

   	if ((NULL == CU_add_test(pSuite, "test_get_right_index", test_get_right_index)))
   	{
      	CU_cleanup_registry();
      	return CU_get_error();
   	}

   	if ((NULL == CU_add_test(pSuite, "test_get_left_index", test_get_left_index)))
   	{
      	CU_cleanup_registry();
      	return CU_get_error();
   	}

   	if ((NULL == CU_add_test(pSuite, "test_swap_nodes", test_swap_nodes)))
   	{
      	CU_cleanup_registry();
      	return CU_get_error();
   	}

   	if ((NULL == CU_add_test(pSuite, "test_add_node", test_add_node)))
   	{
      	CU_cleanup_registry();
      	return CU_get_error();
   	}

    if ((NULL == CU_add_test(pSuite, "test_check_leaf", test_check_leaf)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "test_ht_to_heap", test_ht_to_heap)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "test_merge_nodes", test_merge_nodes)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "test_create_huffTree", test_create_huffTree)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "test_get_treeSize", test_get_treeSize)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "test_create_bits", test_create_bits)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "test_min_heapify", test_min_heapify)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }


    /* Run tests using Basic interface */
   	CU_basic_run_tests();

   /* Clean up registry and return */
   	CU_cleanup_registry();
   	return CU_get_error();
}