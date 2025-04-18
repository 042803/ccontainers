#include "../include/array.h"
#include "../src/array.c"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>

int linear_search(struct Array* arr, int key);
int binary_search(struct Array arr, int key);
void swap(int* a, int* b);

void test_linear_search() {
    struct Array arr = {{}, 0, 10};

    arr.A[0] = 10;
    arr.A[1] = 20;
    arr.A[2] = 30;
    arr.A[3] = 40;
    arr.A[4] = 50;
    arr.length = 5;

    // Test Case 1: Key is found at the beginning
    int index = linear_search(&arr, 10);
    CU_ASSERT_EQUAL(index, 0);
    CU_ASSERT_EQUAL(arr.A[0], 10); // No swap since key is already at the beginning

    // Test Case 2: Key is found in the middle
    index = linear_search(&arr, 30);
    CU_ASSERT_EQUAL(index, 2);
    CU_ASSERT_EQUAL(arr.A[0], 30); // Swapped with the first element
    CU_ASSERT_EQUAL(arr.A[2], 10); // Original first element moved to index 2

    // Test Case 3: Key is found at the end
    index = linear_search(&arr, 50);
    CU_ASSERT_EQUAL(index, 4);
    CU_ASSERT_EQUAL(arr.A[0], 50); // Swapped with the first element
    CU_ASSERT_EQUAL(arr.A[4], 30); // Original first element moved to index 4

    // Test Case 4: Key is not found
    index = linear_search(&arr, 100);
    CU_ASSERT_EQUAL(index, -1); // Key not found

    // Test Case 5: Key is found multiple times
    arr.A[0] = 20;
    arr.A[1] = 20;
    arr.A[2] = 20;
    arr.length = 3;
    index = linear_search(&arr, 20);
    CU_ASSERT_EQUAL(index, 0); // First occurrence is returned
    CU_ASSERT_EQUAL(arr.A[0], 20); // No swap since key is already at the beginning
}


void test_binary_search() {
    // Binary search requires a sorted array
    struct Array arr = {{}, 0, 10};

    // Initialize array with sorted elements
    
    push_back(&arr, 5);
    push_back(&arr, 15);
    push_back(&arr, 25);
    push_back(&arr, 35);
    push_back(&arr, 45);
    
    // Test Case 1: Key found in the middle
    int index = binary_search(arr, 25);
    CU_ASSERT_EQUAL(index, 2);

    // Test Case 2: Key found at the beginning
    index = binary_search(arr, 5);
    CU_ASSERT_EQUAL(index, 0);

    // Test Case 3: Key found at the end
    index = binary_search(arr, 45);
    CU_ASSERT_EQUAL(index, 4);

    // Test Case 4: Key not found
    index = binary_search(arr, 20);
    CU_ASSERT_EQUAL(index, -1);

    // Test Case 5: Larger sorted array
    push_back(&arr, 65);
    push_back(&arr, 75);
    push_back(&arr, 85);    
    index = binary_search(arr, 75);
    CU_ASSERT_EQUAL(index, 6);

    // Test Case 6: Empty array
    struct Array empty_arr = {{}, 0, 10};
    index = binary_search(empty_arr, 10);
    CU_ASSERT_EQUAL(index, -1);
}


int main(){
	if (CU_initialize_registry() != CUE_SUCCESS){
		return CU_get_error();
	}	

	CU_pSuite linear_search_suite = CU_add_suite("Linear Search Suite", NULL, NULL);
	CU_pSuite binary_search_suite = CU_add_suite("Binary Search Suite", NULL, NULL);
	if (linear_search_suite == NULL || binary_search_suite == NULL){
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (CU_add_test(linear_search_suite, "Test linear_search", test_linear_search) == NULL || CU_add_test(binary_search_suite, "Test binary_search", test_binary_search) == NULL) {
        	CU_cleanup_registry();
        	return CU_get_error();
    	}	

    	// Run all tests using the basic interface
    	CU_basic_set_mode(CU_BRM_VERBOSE);
    	CU_basic_run_tests();
    	CU_cleanup_registry();

    	return CU_get_error();
}
