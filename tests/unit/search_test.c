#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/vector.h" 

int cmp_ascending_wrapper(const void* a, const void* b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    return (ia > ib) - (ia < ib);
}

int cmp_mod3(const void* a, const void* b) {
    int ia = *(const int*)a % 3;
    int ib = *(const int*)b % 3;
    return (ia > ib) - (ia < ib);
}

// ===== Test Cases =====

void test_binary_search(void) {
    int values[] = {1, 3, 5, 7, 9};
    struct Array arr = init_from_array(values, sizeof(values)/sizeof(values[0]));
    
    // Existing elements
    CU_ASSERT_EQUAL(binary_search(&arr, 1), 0);
    CU_ASSERT_EQUAL(binary_search(&arr, 5), 2);
    CU_ASSERT_EQUAL(binary_search(&arr, 9), 4);
    
    // Non-existing elements
    CU_ASSERT_EQUAL(binary_search(&arr, 0), -1);
    CU_ASSERT_EQUAL(binary_search(&arr, 4), -1);
    CU_ASSERT_EQUAL(binary_search(&arr, 10), -1);
    
    // Edge cases
//    CU_ASSERT_EQUAL(binary_search(NULL, 5), -1); // NULL array
    
    struct Array empty = init(5);
    CU_ASSERT_EQUAL(binary_search(&empty, 5), -1); // Empty array
    free_arr(&empty);
    free_arr(&arr);
}

void test_c_binary_search(void) {
    int values[] = {9, 7, 5, 3, 1}; // Descending order
    struct Array arr = init_from_array(values, sizeof(values)/sizeof(values[0]));
    // Test with descending comparator
    CU_ASSERT_EQUAL(c_binary_search(&arr, 9, cmp_descending), 0);
    CU_ASSERT_EQUAL(c_binary_search(&arr, 5, cmp_descending), 2);
    CU_ASSERT_EQUAL(c_binary_search(&arr, 1, cmp_descending), 4);
    CU_ASSERT_EQUAL(c_binary_search(&arr, 4, cmp_descending), -1);
    
    // Test with modulus comparator
    int mod_values[] = {2, 4, 6, 1, 3}; 
    struct Array mod_arr = init_from_array(mod_values, 5);
    //c_quick_sort(&mod_arr, cmp_mod3);
    
    qsort(mod_arr.A, mod_arr.length, sizeof(int), cmp_mod3);
    CU_ASSERT_EQUAL(c_binary_search(&mod_arr, 6, cmp_mod3), 0);
    CU_ASSERT_EQUAL(c_binary_search(&mod_arr, 2, cmp_mod3), 4);
    //CU_ASSERT_EQUAL(c_binary_search(&mod_arr, 5, cmp_mod3), -1);
//    print(&mod_arr);
    // Edge cases
//    CU_ASSERT_EQUAL(c_binary_search(NULL, 5, cmp_ascending), -1); // NULL array
//    CU_ASSERT_EQUAL(c_binary_search(&arr, 5, NULL), -1); // NULL comparator
    
    free_arr(&mod_arr);
    free_arr(&arr);
}

void test_linear_search(void) {
    int values[] = {5, 3, 1, 4, 2};
    struct Array arr = init_from_array(values, sizeof(values)/sizeof(values[0]));
    
    // Existing elements
    CU_ASSERT_EQUAL(linear_search(&arr, 5), 0);
    CU_ASSERT_EQUAL(linear_search(&arr, 2), 4);
    
    // Verify move-to-front works
    CU_ASSERT_EQUAL(linear_search(&arr, 4), 3);
    CU_ASSERT_EQUAL(arr.A[0], 4); // Should be moved to front
    
    // Non-existing elements
    CU_ASSERT_EQUAL(linear_search(&arr, 6), -1);
    
    // Edge cases
//    CU_ASSERT_EQUAL(linear_search(NULL, 5), -1); // NULL array
    
    struct Array empty = init(5);
    CU_ASSERT_EQUAL(linear_search(&empty, 5), -1); // Empty array
    free_arr(&empty);
    free_arr(&arr);
}

void test_c_linear_search(void) {
    int values[] = {5, -3, 1, -4, 2};
    struct Array arr = init_from_array(values, sizeof(values)/sizeof(values[0]));
    
    // Test with absolute value comparator
    CU_ASSERT_EQUAL(c_linear_search(&arr, 3, cmp_modulus), 1); // Finds -3
    CU_ASSERT_EQUAL(arr.A[0], -3); // Should be moved to front
    
    // Test with even-first comparator
    CU_ASSERT_EQUAL(c_linear_search(&arr, 1, cmp_even_first), 2);
    CU_ASSERT_EQUAL(c_linear_search(&arr, 2, cmp_even_first), 4);
    
    // Edge cases
//    CU_ASSERT_EQUAL(c_linear_search(NULL, 5, cmp_ascending), -1); // NULL array
//    CU_ASSERT_EQUAL(c_linear_search(&arr, 5, NULL), -1); // NULL comparator
    
    free_arr(&arr);
}

void test_contains(void) {
    int sorted_values[] = {1, 3, 5, 7, 9};
    struct Array sorted = init_from_array(sorted_values, sizeof(sorted_values)/sizeof(sorted_values[0]));
    
    int unsorted_values[] = {5, 3, 1, 4, 2};
    struct Array unsorted = init_from_array(unsorted_values, sizeof(unsorted_values)/sizeof(unsorted_values[0]));
    
    // Sorted array (uses binary search)
    CU_ASSERT_TRUE(contains(&sorted, 3));
    CU_ASSERT_FALSE(contains(&sorted, 4));
    
    // Unsorted array (uses linear search)
    CU_ASSERT_TRUE(contains(&unsorted, 4));
    CU_ASSERT_FALSE(contains(&unsorted, 6));
    
    // Edge cases
//    CU_ASSERT_FALSE(contains(NULL, 5)); // NULL array
    
    struct Array empty = init(5);
    CU_ASSERT_FALSE(contains(&empty, 5)); // Empty array
    free_arr(&empty);
    free_arr(&sorted);
    free_arr(&unsorted);
}

void test_c_contains(void) {
    int values[] = {9, -3, 5, -1, 2};
    struct Array arr = init_from_array(values, sizeof(values)/sizeof(values[0]));
    
    // Test with absolute value comparator
    CU_ASSERT_TRUE(c_contains(&arr, 3, cmp_modulus)); // Finds -3
    CU_ASSERT_FALSE(c_contains(&arr, 4, cmp_modulus));
    
    // Test with even-first comparator
    CU_ASSERT_TRUE(c_contains(&arr, 2, cmp_even_first));
    CU_ASSERT_FALSE(c_contains(&arr, 6, cmp_even_first));
    
    // Edge cases
//    CU_ASSERT_FALSE(c_contains(NULL, 5, cmp_ascending)); // NULL array
//    CU_ASSERT_FALSE(c_contains(&arr, 5, NULL)); // NULL comparator
    
    free_arr(&arr);
}

// ===== Test Suite Setup =====
int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Array Search Tests", NULL, NULL);

    // Add tests
    CU_add_test(suite, "test_binary_search", test_binary_search);
    CU_add_test(suite, "test_c_binary_search", test_c_binary_search);
    CU_add_test(suite, "test_linear_search", test_linear_search);
    CU_add_test(suite, "test_c_linear_search", test_c_linear_search);
    CU_add_test(suite, "test_contains", test_contains);
    CU_add_test(suite, "test_c_contains", test_c_contains);

    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
