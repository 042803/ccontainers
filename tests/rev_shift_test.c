#include "../include/array.h"
#include "../src/array.c"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
//reverse and shift
/*
void reverse(struct Array* arr){
	for (int i = 0, j = arr->length - 1; i <= j; i++, j--){
		swap(&arr->A[i], &arr->A[j]);
	}
}


int shift(struct Array* arr){
	for (int i = 0; i < arr->length; i++){
		arr->A[i] = arr->A[i + 1];
	}

}

bool is_sorted(struct Array arr){
	for (int i = 0; i < arr.length - 2; i++){
		if (arr.A[i] > arr.A[i + 1]){
			return false;
		}
	}
	return true;
}
*/
void reverse(struct Array* arr);
int shift(struct Array* arr);
bool is_sorted(struct Array arr);


void test_reverse(){
	struct Array arr = {{1, 2, 3, 4, 5, 6}, 6, 10};
	reverse(&arr);
	// Test Case 1: reverse even length array
	CU_ASSERT_EQUAL(arr.A[0], 6);
	CU_ASSERT_EQUAL(arr.A[1], 5);
	CU_ASSERT_EQUAL(arr.A[2], 4);
	CU_ASSERT_EQUAL(arr.A[3], 3);
	CU_ASSERT_EQUAL(arr.A[4], 2);
	CU_ASSERT_EQUAL(arr.A[5], 1);
	
	int temp_val = remove_at(&arr, 5); // delete element A[5]
	CU_ASSERT_EQUAL(temp_val, 1);
	reverse(&arr);	
	
	// Test Case 2:  reverse odd length array
	CU_ASSERT_EQUAL(arr.A[0], 2);
	CU_ASSERT_EQUAL(arr.A[1], 3);
	CU_ASSERT_EQUAL(arr.A[2], 4);
	CU_ASSERT_EQUAL(arr.A[3], 5);
	CU_ASSERT_EQUAL(arr.A[4], 6);
	
	// Test Case 3: reversing single element array
	struct Array arr2 = {{5}, 1, 10};
    	reverse(&arr2);
    	CU_ASSERT_EQUAL(arr2.A[0], 5);
}

void test_shift(){
	struct Array arr = {{1, 2, 3, 4, 5, 6}, 6, 10};
	int temp_shift_val = shift(&arr);
	
	// Test Case 1: Shift left
	CU_ASSERT_EQUAL(temp_shift_val, 1);
	CU_ASSERT_EQUAL(arr.A[0], 2);
	CU_ASSERT_EQUAL(arr.A[1], 3);
	CU_ASSERT_EQUAL(arr.A[2], 4);
	CU_ASSERT_EQUAL(arr.A[3], 5);
	CU_ASSERT_EQUAL(arr.A[4], 6);
	
	// Test Case 2: Shift single-element array
	struct Array single_array = {{42}, 1, 10};
	temp_shift_val = shift(&single_array);
	CU_ASSERT_EQUAL(temp_shift_val, 42);
	CU_ASSERT_EQUAL(single_array.A[0], 0);

	// Test Case 3: Shift empty array
	struct Array empty_array = {{}, 0, 10};
	temp_shift_val = shift(&empty_array);
	CU_ASSERT_EQUAL(temp_shift_val, -1);
}


void test_is_sorted(){

	struct Array arr = {{1, 2, 3, 4, 5, 6}, 6, 10};
	// Test Case 1: Sorted array
	CU_ASSERT_TRUE(is_sorted(arr));
	
	// Test Case 2: Unsorted array 1 10 3 4 5 6
	set(&arr, 1, 10);
	CU_ASSERT_FALSE(is_sorted(arr));

	// Test Case 3: Single element array
	struct Array single_array = {{42}, 1, 10};
	CU_ASSERT_TRUE(is_sorted(single_array));
	
	// Test Case 4: Empty array 
	struct Array empty_array = {{}, 0, 10};
	CU_ASSERT_TRUE(is_sorted(empty_array));
}


int main() {
    // Initialize CUnit registry
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    // Add test suites
    CU_pSuite reverse_suite = CU_add_suite("Reverse Suite", NULL, NULL);
    CU_pSuite shift_suite = CU_add_suite("Shift Suite", NULL, NULL);
    CU_pSuite sorted_suite = CU_add_suite("IsSorted Suite", NULL, NULL);

    if (reverse_suite == NULL || shift_suite == NULL || sorted_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add tests to suites
    if (CU_add_test(reverse_suite, "Test reverse", test_reverse) == NULL ||
        CU_add_test(shift_suite, "Test shift", test_shift) == NULL ||
        CU_add_test(sorted_suite, "Test is_sorted", test_is_sorted) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all tests
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}






