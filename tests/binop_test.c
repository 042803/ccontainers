#include "../include/array.h"
#include "../src/array.c"
#include "../src/binop.c"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>

struct Array* merge(struct Array* arr1, struct Array* arr2);
//struct Array* un(struct Array* arr1, struct Array* arr2);
//struct Array* in(struct Array* arr1, struct Array* arr2);
//struct Array* dif(struct Array* arr1, struct Array* arr2);

void test_merge() {
    // Test Case 1: Merge two non-empty sorted arrays
    struct Array arr1 = {{1, 3, 5}, 3, 5}; 
    struct Array arr2 = {{2, 4, 6}, 3, 5};
    struct Array* merged = merge(&arr1, &arr2);

    CU_ASSERT_EQUAL(merged->length, 6);
    CU_ASSERT_EQUAL(merged->A[0], 1);
    CU_ASSERT_EQUAL(merged->A[1], 2);
    CU_ASSERT_EQUAL(merged->A[2], 3);
    CU_ASSERT_EQUAL(merged->A[3], 4);
    CU_ASSERT_EQUAL(merged->A[4], 5);
    CU_ASSERT_EQUAL(merged->A[5], 6);
    
    free(merged);

    // Test Case 2: Merge with one empty array
    struct Array arr_1 = {{1, 3, 5}, 3, 5};
    struct Array arr3 = {{}, 0, 5};
    //struct Array* merged1 = merge(&arr_1, &arr3);
    struct Array* arrtest = merge(&arr3, &arr_1);
    //int templog = arrtest->length;
    //printf("log of arrtest current length %d\n", templog);
    CU_ASSERT_EQUAL(arrtest->length, 3);
    CU_ASSERT_EQUAL(arrtest->A[0], 1);
    CU_ASSERT_EQUAL(arrtest->A[1], 3);
    CU_ASSERT_EQUAL(arrtest->A[2], 5);

    //free(merged1);

    // Test Case 3: Merge two empty arrays 
    struct Array arr4 = {{}, 0, 5};
    struct Array* merged2 = merge(&arr3, &arr4);
    CU_ASSERT_EQUAL(merged2->length, 0);
    
    free(merged2);

    // Test Case 4: Merge arrays with different lengths 
    struct Array arr5 = {{10, 20}, 2, 5}; 
    struct Array arr6 = {{5, 15, 25}, 3, 5};
    struct Array* merged3 = merge(&arr5, &arr6);
    CU_ASSERT_EQUAL(merged3->length, 5);
    CU_ASSERT_EQUAL(merged3->A[0], 5);
    CU_ASSERT_EQUAL(merged3->A[1], 10);
    CU_ASSERT_EQUAL(merged3->A[2], 15);
    CU_ASSERT_EQUAL(merged3->A[3], 20);
    CU_ASSERT_EQUAL(merged3->A[4], 25);

    free(merged3);
}

int main() {
    // Initialize CUnit registry
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    // Add test suite
    CU_pSuite merge_suite = CU_add_suite("Merge Suite", NULL, NULL);
    if (merge_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add test to suite
    if (CU_add_test(merge_suite, "Test merge", test_merge) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all tests
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}
