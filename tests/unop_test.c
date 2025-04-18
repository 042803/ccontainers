#include "../include/array.h"
#include "../src/array.c"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>

int get(struct Array arr, int index);
void set(struct Array* arr, int index, int elt);
int max(struct Array arr);
int min(struct Array arr);
int avg(struct Array arr);

void test_get() {
    struct Array arr = {{}, 0, 10};

    // Initialize array with elements
    push_back(&arr, 10);	    
    push_back(&arr, 20);	    
    push_back(&arr, 30);	    

    // Test Case 1: Valid index
    CU_ASSERT_EQUAL(get(arr, 0), 10);
    CU_ASSERT_EQUAL(get(arr, 1), 20);
    CU_ASSERT_EQUAL(get(arr, 2), 30);

    // Test Case 2: Invalid index (negative)
    CU_ASSERT_EQUAL(get(arr, -1), -1);

    // Test Case 3: Invalid index (out of bounds)
    CU_ASSERT_EQUAL(get(arr, 3), -1);
}

void test_set() {
    struct Array arr = {{}, 0, 10};

    // Initialize array with elements
    push_back(&arr, 10);	    
    push_back(&arr, 20);	    
    push_back(&arr, 30);	    
   
    // Test Case 1: Valid index
    set(&arr, 1, 50);
    CU_ASSERT_EQUAL(arr.A[1], 50);

    // Test Case 2: Invalid index (negative)
    set(&arr, -1, 100);
    CU_ASSERT_EQUAL(arr.A[0], 10); // No change

    // Test Case 3: Invalid index (out of bounds)
    set(&arr, 3, 100);
    CU_ASSERT_EQUAL(arr.A[2], 30); // No change
}

void test_max() {

    struct Array arr = {{}, 0, 10};
    // Test Case 1: Array with positive numbers
    push_back(&arr, 10);	    
    push_back(&arr, 50);	    
    push_back(&arr, 30); 
    CU_ASSERT_EQUAL(max(arr), 50);

    // Test Case 2: Array with negative numbers
    set(&arr, 0, -10);	    
    set(&arr, 1, -50);	    
    set(&arr, 2, -30);	    
    CU_ASSERT_EQUAL(max(arr), -10);

    // Test Case 3: Array with mixed numbers
    set(&arr, 1, 50);	    
    set(&arr, 2, 0);	   
    CU_ASSERT_EQUAL(max(arr), 50);
}

void test_min() {

    struct Array arr = {{}, 0, 10};
    // Test Case 1: Array with positive numbers
    push_back(&arr, 10);	    
    push_back(&arr, 50);	    
    push_back(&arr, 30); 
    CU_ASSERT_EQUAL(min(arr), 10);

    // Test Case 2: Array with negative numbers
    set(&arr, 0, -10);	    
    set(&arr, 1, -50);	    
    set(&arr, 2, -30);	    
    CU_ASSERT_EQUAL(min(arr), -50);

    // Test Case 3: Array with mixed numbers
    set(&arr, 1, 50);	    
    set(&arr, 2, 0);	   
    CU_ASSERT_EQUAL(min(arr), -10);
}


void test_avg() {

    struct Array arr = {{}, 0, 10};
    // Test Case 1: Array with positive numbers
    push_back(&arr, 10);	    
    push_back(&arr, 50);	    
    push_back(&arr, 30); 
    CU_ASSERT_EQUAL(avg(arr), 30);

    // Test Case 2: Array with negative numbers
    set(&arr, 0, -10);	    
    set(&arr, 1, -20);	    
    set(&arr, 2, -30);	    
    CU_ASSERT_EQUAL(avg(arr), -20);

    // Test Case 3: Array with mixed numbers
    set(&arr, 1, 40);	    
    set(&arr, 2, 0);	   
    CU_ASSERT_EQUAL(avg(arr), 10);
}

int main() {
    // Initialize CUnit registry
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    // Add suites for all functions
    CU_pSuite get_suite = CU_add_suite("Get Suite", NULL, NULL);
    CU_pSuite set_suite = CU_add_suite("Set Suite", NULL, NULL);
    CU_pSuite max_suite = CU_add_suite("Max Suite", NULL, NULL);
    CU_pSuite min_suite = CU_add_suite("Min Suite", NULL, NULL);
    CU_pSuite avg_suite = CU_add_suite("Avg Suite", NULL, NULL);

    if (get_suite == NULL || set_suite == NULL || max_suite == NULL || min_suite == NULL || avg_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add tests to suites
    if (CU_add_test(get_suite, "Test get", test_get) == NULL ||
        CU_add_test(set_suite, "Test set", test_set) == NULL ||
        CU_add_test(max_suite, "Test max", test_max) == NULL ||
        CU_add_test(min_suite, "Test min", test_min) == NULL ||
        CU_add_test(avg_suite, "Test avg", test_avg) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all tests
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}
