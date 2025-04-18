#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/array.h"
#include "../src/array.c"

// Test suite for emplace_at
void test_emplace_at() {
    	struct Array arr = {{}, 0, 10};

    	// Initialize array with some elements
    	push_back(&arr, 1);
    	push_back(&arr, 2);
    	push_back(&arr, 3);

    	// Test Case 1: Insert at the beginning
    	emplace_at(&arr, 0, 0);
    	CU_ASSERT_EQUAL(arr.length, 4);
    	CU_ASSERT_EQUAL(arr.A[0], 0);
    	CU_ASSERT_EQUAL(arr.A[1], 1);

	// Test Case 2: Insert in the middle
    	emplace_at(&arr, 2, 10);
   	CU_ASSERT_EQUAL(arr.length, 5);
    	CU_ASSERT_EQUAL(arr.A[2], 10);
    	CU_ASSERT_EQUAL(arr.A[3], 2);
  
	// Test Case 3: Insert at invalid index (should not insert)
	emplace_at(&arr, -1, 100); // Invalid index
	emplace_at(&arr, 10, 100); // Invalid index
	CU_ASSERT_EQUAL(arr.length, 5);
}

	int main() {
	    // Initialize the CUnit test registry
    	if (CU_initialize_registry() != CUE_SUCCESS) {
        	return CU_get_error();
    	}

    	// Add a suite for the emplace_at function
    	CU_pSuite emplace_at_suite = CU_add_suite("Emplace At Suite", 
	NULL, NULL);
    	if (emplace_at_suite == NULL) {
        	CU_cleanup_registry();
        	return CU_get_error();
    	}

    	// Add the test function to the suite
    	if (CU_add_test(emplace_at_suite, "Test emplace_at", test_emplace_at) == NULL) {
        	CU_cleanup_registry();
        	return CU_get_error();
   	}

    	// Run all tests using the basic interface
    	CU_basic_set_mode(CU_BRM_VERBOSE);
    	CU_basic_run_tests();
    	CU_cleanup_registry();

    	return CU_get_error();
}
