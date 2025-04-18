#include "../include/array.h"
#include "../src/array.c"
#include "../src/binop.c"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>

//struct Array* merge(struct Array* arr1, struct Array* arr2);
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

void test_union() {
    // Test Case 1: Unite two non-empty sorted arrays
    struct Array arr1 = {{1, 2, 3, 4, 5}, 5, 5}; 
    struct Array arr2 = {{2, 4, 6}, 3, 5};
    struct Array* merged = un(&arr1, &arr2);

    CU_ASSERT_EQUAL(merged->length, 6);
    CU_ASSERT_EQUAL(merged->A[0], 1);
    CU_ASSERT_EQUAL(merged->A[1], 2);
    CU_ASSERT_EQUAL(merged->A[2], 3);
    CU_ASSERT_EQUAL(merged->A[3], 4);
    CU_ASSERT_EQUAL(merged->A[4], 5);
    CU_ASSERT_EQUAL(merged->A[5], 6);
  
    free(merged);

    // Test Case 2: Unite with one empty array
    struct Array arr_1 = {{1, 3, 5}, 3, 5};
    struct Array arr3 = {{}, 0, 5};

    struct Array* merged1 = un(&arr3, &arr_1);
    //int templog = arrtest->length;
    //printf("log of arrtest current length %d\n", templog);
    CU_ASSERT_EQUAL(merged1->length, 3);
    CU_ASSERT_EQUAL(merged1->A[0], 1);
    CU_ASSERT_EQUAL(merged1->A[1], 3);
    CU_ASSERT_EQUAL(merged1->A[2], 5);

    free(merged1);

    // Test Case 3: Unite two empty arrays 
    struct Array arr4 = {{}, 0, 5};
    struct Array* merged2 = un(&arr3, &arr4);
    CU_ASSERT_EQUAL(merged2->length, 0);
    
    free(merged2);

    // Test Case 4: Unite arrays with different lengths 
    struct Array arr5 = {{10, 15, 20}, 3, 5}; 
    struct Array arr6 = {{5, 15, 20, 25}, 4, 5};
    struct Array* merged3 = un(&arr5, &arr6);
    CU_ASSERT_EQUAL(merged3->length, 5);
    CU_ASSERT_EQUAL(merged3->A[0], 5);
    CU_ASSERT_EQUAL(merged3->A[1], 10);
    CU_ASSERT_EQUAL(merged3->A[2], 15);
    CU_ASSERT_EQUAL(merged3->A[3], 20);
    CU_ASSERT_EQUAL(merged3->A[4], 25);

    free(merged3);
}

void test_int() {
    // Test Case 1: Intersect two non-empty sorted arrays
    struct Array arr1 = {{1, 2, 3, 4, 5}, 5, 5}; 
    struct Array arr2 = {{2, 4, 6}, 3, 5};
    struct Array* merged = in(&arr1, &arr2);

    CU_ASSERT_EQUAL(merged->length, 2);
    CU_ASSERT_EQUAL(merged->A[0], 2);
    CU_ASSERT_EQUAL(merged->A[1], 4);
  
    free(merged);

    // Test Case 2: Intersect with one empty array
    struct Array arr_1 = {{1, 3, 5}, 3, 5};
    struct Array arr3 = {{}, 0, 5};

    struct Array* merged1 = in(&arr3, &arr_1);
    CU_ASSERT_EQUAL(merged1->length, 0);

    free(merged1);

    // Test Case 3: Intersect two empty arrays 
    struct Array arr4 = {{}, 0, 5};
    struct Array* merged2 = in(&arr3, &arr4);
    CU_ASSERT_EQUAL(merged2->length, 0);
    
    free(merged2);

    // Test Case 4: Intersect arrays with different lengths 
    struct Array arr5 = {{10, 15, 20}, 3, 5}; 
    struct Array arr6 = {{5, 15, 20, 25}, 4, 5};
    struct Array* merged3 = in(&arr5, &arr6);
    CU_ASSERT_EQUAL(merged3->length, 2);
    CU_ASSERT_EQUAL(merged3->A[0], 15);
    CU_ASSERT_EQUAL(merged3->A[1], 20);

    free(merged3);
}

void test_dif() {
    // Test Case 1: Diff two non-empty sorted arrays
    struct Array arr1 = {{1, 2, 3, 4, 5}, 5, 5}; 
    struct Array arr2 = {{2, 4, 6}, 3, 5};
    struct Array* merged = dif(&arr1, &arr2);

    CU_ASSERT_EQUAL(merged->length, 3);
    CU_ASSERT_EQUAL(merged->A[0], 1);
    CU_ASSERT_EQUAL(merged->A[1], 3);
    CU_ASSERT_EQUAL(merged->A[2], 5);
  
    free(merged);

    // Test Case 2: Diff with one empty array
    struct Array arr_1 = {{1, 3, 5}, 3, 5};
    struct Array arr3 = {{}, 0, 5};

    struct Array* merged1 = dif(&arr_1, &arr3);
    CU_ASSERT_EQUAL(merged1->length, 3);
    CU_ASSERT_EQUAL(merged1->A[0], 1);
    CU_ASSERT_EQUAL(merged1->A[1], 3);
    CU_ASSERT_EQUAL(merged1->A[2], 5);
    
    free(merged1);

    // Test Case 3: Diff two empty arrays 
    struct Array arr4 = {{}, 0, 5};
    struct Array* merged2 = dif(&arr3, &arr4);
    CU_ASSERT_EQUAL(merged2->length, 0);
    
    free(merged2);

    // Test Case 4: Diff arrays with different lengths 
    struct Array arr5 = {{10, 15, 20}, 3, 5}; 
    struct Array arr6 = {{5, 15, 20, 25}, 4, 5};
    struct Array* merged3 = dif(&arr5, &arr6);
    CU_ASSERT_EQUAL(merged3->length, 1);
    CU_ASSERT_EQUAL(merged1->A[0], 10);
    free(merged3);    
// Test Case 5: Difference empty array with normal array
    struct Array* merged4 = dif(&arr3, &arr_1);
    CU_ASSERT_EQUAL(merged4->length, 0);
    free(merged4);
}

int main() {
    // Initialize CUnit registry
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    // Add test suite
    CU_pSuite merge_suite = CU_add_suite("Merge Suite", NULL, NULL);
    CU_pSuite union_suite = CU_add_suite("Union Suite", NULL, NULL);
    CU_pSuite int_suite = CU_add_suite("Intersection Suite", NULL, NULL);
    CU_pSuite dif_suite = CU_add_suite("Difference Suite", NULL, NULL);
    if (merge_suite == NULL || union_suite == NULL || int_suite == NULL || dif_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add test to suite
    if (((CU_add_test(merge_suite, "Test merge", test_merge) == NULL || CU_add_test(union_suite, "Test union", test_union) == NULL)) || (CU_add_test(int_suite, "Test intersection", test_int) == NULL || CU_add_test(dif_suite, "Test Difference", test_dif) == NULL)){ 
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all tests
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}
