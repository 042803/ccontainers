#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/array.h"
#include "../src/array.c"

void push_back(struct Array* arr, int elt);
void emplace_at(struct Array* arr, int index, int elt);
int remove_at(struct Array* arr, int index);

// Test suite for push_back
void test_push_back() {
	struct Array arr = {{}, 0, 10};

    	// Test Case 1: Add one element	
    	push_back(&arr, 5);
    	CU_ASSERT_EQUAL(arr.length, 1);
    	CU_ASSERT_EQUAL(arr.A[0], 5);

    	// Test Case 2: Add multiple elements			
    	push_back(&arr, 10);
    	push_back(&arr, 15);
    	CU_ASSERT_EQUAL(arr.length, 3);
    	CU_ASSERT_EQUAL(arr.A[1], 10);
    	CU_ASSERT_EQUAL(arr.A[2], 15);

    	for (int i = 0; i < 7; i++){
        	push_back(&arr, i);
   	}

   	// Test Case 3: Adding elements to full array	
    	CU_ASSERT_EQUAL(arr.length, 10); // Array is full
   	push_back(&arr, 100); // Should not add
}

int main() {
    // Initialize the CUnit test registry
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    // Add a suite for the emplace_at function
    CU_pSuite emplace_at_suite = CU_add_suite("Push Back Suite", NULL, NULL);
    if (emplace_at_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add the test function to the suite
    if (CU_add_test(emplace_at_suite, "Test push_back", test_push_back) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all tests using the basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}
