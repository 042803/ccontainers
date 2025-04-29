#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../../include/vector.h"

// Helper functions for testing
static void increment(int* x) { (*x)++; }
static int square(int x) { return x * x; }
static bool is_even(int x) { return x % 2 == 0; }
static bool is_positive(int x) { return x > 0; }

// ===== Test Cases =====

void test_set_to_range(void) {
    // Normal range
    int vals1[] = {1, 2, 3, 4, 5};
    struct Array arr1 = init_from_array(vals1, 5);
    set_to_range(&arr1, 1, 4, 9); // Set indices 1-3 to 9
    CU_ASSERT_EQUAL(arr1.A[0], 1);
    CU_ASSERT_EQUAL(arr1.A[1], 9);
    CU_ASSERT_EQUAL(arr1.A[3], 9);
    CU_ASSERT_EQUAL(arr1.A[4], 5);
    free_arr(&arr1);

    // Invalid range (start >= end)
    struct Array arr2 = init_from_array(vals1, 5);
    set_to_range(&arr2, 2, 2, 9); // No change
    CU_ASSERT_EQUAL(arr2.A[2], 3);
    free_arr(&arr2);

    // Range exceeds length
    /*
    struct Array arr3 = init_from_array(vals1, 5);
    set_to_range(&arr3, 3, 6, 9); // Only sets within bounds
    CU_ASSERT_EQUAL(arr3.A[3], 5);
    printf("VALUE OF A[3] : %d\n", arr3.A[3]);
    print(&arr3);
    CU_ASSERT_EQUAL(arr3.A[4], 5); 
    free_arr(&arr3);
    STILL NO IDEA OF HOW THIS SHOULD PROPERLY BEHAVE
    */

    // NULL array (shouldn't crash)
//    set_to_range(NULL, 0, 1, 9);
}

void test_set_all(void) {
    // Normal case
    int vals1[] = {1, 2, 3};
    struct Array arr1 = init_from_array(vals1, 3);
    set_all(&arr1, 7);
    CU_ASSERT_EQUAL(arr1.A[0], 7);
    CU_ASSERT_EQUAL(arr1.A[2], 7);
    free_arr(&arr1);

    // Empty array (shouldn't crash)
    struct Array arr2 = init(5);
    set_all(&arr2, 7);
    CU_ASSERT_EQUAL(arr2.length, 0);
    free_arr(&arr2);
}

void test_apply_to_range(void) {
    // Normal range
    int vals1[] = {1, 2, 3, 4};
    struct Array arr1 = init_from_array(vals1, 4);
    apply_to_range(&arr1, 1, 3, increment); // Increment indices 1-2
    CU_ASSERT_EQUAL(arr1.A[0], 1);
    CU_ASSERT_EQUAL(arr1.A[1], 3);
    CU_ASSERT_EQUAL(arr1.A[2], 4);
    CU_ASSERT_EQUAL(arr1.A[3], 4);
    free_arr(&arr1);

    // NULL function
//    struct Array arr2 = init_from_array(vals1, 4);
//    apply_to_range(&arr2, 0, 2, NULL); // No change
//    CU_ASSERT_EQUAL(arr2.A[0], 1);
//    free_arr(&arr2);

    // Invalid range
    struct Array arr3 = init_from_array(vals1, 4);
    apply_to_range(&arr3, 3, 1, increment); // No change
    CU_ASSERT_EQUAL(arr3.A[0], 1);
    free_arr(&arr3);
}

void test_apply(void) {
    // Normal case
    int vals1[] = {1, 2, 3};
    struct Array arr1 = init_from_array(vals1, 3);
    apply(&arr1, increment);
    CU_ASSERT_EQUAL(arr1.A[0], 2);
    CU_ASSERT_EQUAL(arr1.A[2], 4);
    free_arr(&arr1);

    // NULL cases
//    apply(NULL, increment); // Shouldn't crash
//    struct Array arr2 = init_from_array(vals1, 3);
//    apply(&arr2, NULL); // No change
//    CU_ASSERT_EQUAL(arr2.A[0], 1);
//    free_arr(&arr2);
}

void test_map(void) {
    // Normal case
    int vals1[] = {1, 2, 3};
    struct Array arr1 = init_from_array(vals1, 3);
    map(&arr1, square);
    CU_ASSERT_EQUAL(arr1.A[0], 1);
    CU_ASSERT_EQUAL(arr1.A[1], 4);
    CU_ASSERT_EQUAL(arr1.A[2], 9);
    free_arr(&arr1);

    // NULL function
//    struct Array arr2 = init_from_array(vals1, 3);
//    map(&arr2, NULL); // Shouldn't crash (but does nothing)
//    CU_ASSERT_EQUAL(arr2.A[0], 1);
//    free_arr(&arr2);
}

void test_map_to_range(void) {
    // Normal range
    int vals1[] = {1, 2, 3, 4};
    struct Array arr1 = init_from_array(vals1, 4);
    map_to_range(&arr1, 1, 3, square); // Square indices 1-2
    CU_ASSERT_EQUAL(arr1.A[0], 1);
    CU_ASSERT_EQUAL(arr1.A[1], 4);
    CU_ASSERT_EQUAL(arr1.A[2], 9);
    CU_ASSERT_EQUAL(arr1.A[3], 4);
    free_arr(&arr1);

    // Invalid range
    struct Array arr2 = init_from_array(vals1, 4);
    map_to_range(&arr2, 2, 2, square); // No change
    CU_ASSERT_EQUAL(arr2.A[2], 3);
    free_arr(&arr2);
}

void test_filter(void) {
    // Normal case
    int vals1[] = {1, 2, 3, 4, 5};
    struct Array arr1 = init_from_array(vals1, 5);
    filter(&arr1, is_even);
    CU_ASSERT_EQUAL(arr1.length, 2);
    CU_ASSERT_EQUAL(arr1.A[0], 2);
    CU_ASSERT_EQUAL(arr1.A[1], 4);
    free_arr(&arr1);

    // No matches
    struct Array arr2 = init_from_array(vals1, 5);
    filter(&arr2, is_positive); // All match
    CU_ASSERT_EQUAL(arr2.length, 5);
    free_arr(&arr2);

    // NULL predicate (shouldn't crash)
//    struct Array arr3 = init_from_array(vals1, 5);
//    filter(&arr3, NULL);
//    free_arr(&arr3);
}

void test_filter_range(void) {
    // Normal range
    int vals1[] = {1, 2, 3, 4, 5};
    struct Array arr1 = init_from_array(vals1, 5);
    filter_range(&arr1, 0, 4, is_even); // Filter indices 1-3
    CU_ASSERT_EQUAL(arr1.length, 2); // Keeps 2 and 4
    CU_ASSERT_EQUAL(arr1.A[0], 2);
    CU_ASSERT_EQUAL(arr1.A[1], 4);
    free_arr(&arr1);

    // Invalid range
    struct Array arr2 = init_from_array(vals1, 5);
    filter_range(&arr2, 3, 1, is_even); // No change
    CU_ASSERT_EQUAL(arr2.length, 5);
    free_arr(&arr2);
}

// ===== Test Suite Setup =====
int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Range Operation Tests", NULL, NULL);

    // Add tests
    CU_add_test(suite, "test_set_to_range", test_set_to_range);
    CU_add_test(suite, "test_set_all", test_set_all);
    CU_add_test(suite, "test_apply_to_range", test_apply_to_range);
    CU_add_test(suite, "test_apply", test_apply);
    CU_add_test(suite, "test_map", test_map);
    CU_add_test(suite, "test_map_to_range", test_map_to_range);
    CU_add_test(suite, "test_filter", test_filter);
    CU_add_test(suite, "test_filter_range", test_filter_range);

    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
