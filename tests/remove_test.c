#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/array.h"
#include "../src/array.c"

// Test suite for remove_at
void test_remove_at() {
    struct Array arr = {{}, 0, 10};

    // Initialize array with some elements
    push_back(&arr, 1);
    push_back(&arr, 2);
    push_back(&arr, 3);
    push_back(&arr, 4);
    push_back(&arr, 5);

    // Test Case 1: Remove from the beginning
    int removed = remove_at(&arr, 0);
    CU_ASSERT_EQUAL(removed, 1);
    CU_ASSERT_EQUAL(arr.length, 4);
    CU_ASSERT_EQUAL(arr.A[0], 2);

    // Test Case 2: Remove from the middle
    removed = remove_at(&arr, 1);
    CU_ASSERT_EQUAL(removed, 3);
    CU_ASSERT_EQUAL(arr.length, 3);
    CU_ASSERT_EQUAL(arr.A[1], 4);

    // Test Case 3: Remove from the end
    removed = remove_at(&arr, 2);
    CU_ASSERT_EQUAL(removed, 5);
    CU_ASSERT_EQUAL(arr.length, 2);

    // Test Case 4: Remove from invalid index (should not remove)
    removed = remove_at(&arr, -1); // Invalid index
    CU_ASSERT_EQUAL(removed, -1);   // Default return value for invalid index
    removed = remove_at(&arr, 10); // Invalid index
    CU_ASSERT_EQUAL(removed, -1);   // Default return value for invalid index
    CU_ASSERT_EQUAL(arr.length, 2);
}

int main() {
    // Initialize the CUnit test registry
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    // Add a suite for the remove_at function
    CU_pSuite remove_at_suite = CU_add_suite("Remove At Suite", NULL, NULL);
    if (remove_at_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add the test function to the suite
    if (CU_add_test(remove_at_suite, "Test remove_at", test_remove_at) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all tests using the basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}
