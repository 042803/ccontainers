#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/vector.h" 
#include <limits.h>

int cmp_mod3(const void* a, const void* b) {
    int ia = *(const int*)a % 3;
    int ib = *(const int*)b % 3;
    return (ia > ib) - (ia < ib);
}


bool is_reversed(const struct Array* original, const struct Array* reversed) {
    if (original->length != reversed->length) return false;
    for (size_t i = 0; i < original->length; i++) {
        if (original->A[i] != reversed->A[original->length - 1 - i]) {
            return false;
        }
    }
    return true;
}

bool is_sorted_asc(const struct Array* arr) {
    for (size_t i = 0; i < arr->length - 1; i++) {
        if (arr->A[i] > arr->A[i + 1]) {
            return false;
        }
    }
    return true;
}

// ===== Test Cases =====

void test_reverse(void) {
    int values1[] = {1, 2, 3, 4, 5};
    struct Array arr1 = init_from_array(values1, 5);
    reverse(&arr1);
    CU_ASSERT_EQUAL(arr1.A[0], 5);
    CU_ASSERT_EQUAL(arr1.A[4], 1);
    free_arr(&arr1);

    struct Array arr2 = init(5);
    reverse(&arr2); 
    CU_ASSERT_EQUAL(arr2.length, 0);
    free_arr(&arr2);

    // Single element
    int values3[] = {42};
    struct Array arr3 = init_from_array(values3, 1);
    reverse(&arr3);
    CU_ASSERT_EQUAL(arr3.A[0], 42);
    free_arr(&arr3);

    // With flagged elements (test compact is called)
    
    int values4[] = {1, 2, 3, INT_MAX, 5}; 
    struct Array arr4 = init_from_array(values4, 5);
    arr4.flagged_count = 1;
    reverse(&arr4);
    CU_ASSERT_EQUAL(arr4.length, 4); 
    CU_ASSERT_EQUAL(arr4.A[0], 5);
    CU_ASSERT_EQUAL(arr4.A[3], 1);
    free_arr(&arr4);
}

void test_shift(void) {
    // Normal case
    int values1[] = {10, 20, 30};
    struct Array arr1 = init_from_array(values1, 3);
    CU_ASSERT_EQUAL(shift(&arr1), 10);
    CU_ASSERT_EQUAL(arr1.length, 2);
    CU_ASSERT_EQUAL(arr1.A[0], 20);
    CU_ASSERT_EQUAL(arr1.A[1], 30);
    free_arr(&arr1);

    // Single element
    int values2[] = {7};
    struct Array arr2 = init_from_array(values2, 1);
    CU_ASSERT_EQUAL(shift(&arr2), 7);
    CU_ASSERT_EQUAL(arr2.length, 0);
    free_arr(&arr2);

    // Empty array
    struct Array arr3 = init(5);
    CU_ASSERT_EQUAL(shift(&arr3), -1);
    free_arr(&arr3);

    // With flagged elements
    int values4[] = {INT_MAX, 20, 30}; // Assuming -1 is flagged
    struct Array arr4 = init_from_array(values4, 3);
    arr4.flagged_count = 1;
    CU_ASSERT_EQUAL(shift(&arr4), 20); // After compact
    CU_ASSERT_EQUAL(arr4.length, 1);
    free_arr(&arr4);
}

void test_quick_sort(void) {
    // Normal case
    int values1[] = {5, 3, 1, 4, 2};
    struct Array arr1 = init_from_array(values1, 5);
    quick_sort(&arr1);
    CU_ASSERT_TRUE(is_sorted_asc(&arr1));
    free_arr(&arr1);

    // Already sorted
    int values2[] = {1, 2, 3, 4, 5};
    struct Array arr2 = init_from_array(values2, 5);
    quick_sort(&arr2);
    CU_ASSERT_TRUE(is_sorted_asc(&arr2));
    free_arr(&arr2);

    // Empty array
    struct Array arr3 = init(5);
    quick_sort(&arr3); // Should do nothing
    CU_ASSERT_EQUAL(arr3.length, 0);
    free_arr(&arr3);

    // With flagged elements
    int values4[] = {5, INT_MAX, 3, 2}; // Assuming -1 is flagged
    struct Array arr4 = init_from_array(values4, 4);
    arr4.flagged_count = 1;
    compact(&arr4);
    quick_sort(&arr4);
    CU_ASSERT_EQUAL(arr4.length, 3);
    CU_ASSERT_TRUE(is_sorted_asc(&arr4));
    free_arr(&arr4);
}

void test_c_quick_sort(void) {
    // NULL cases
    c_quick_sort(NULL, cmp_ascending); // Should not crash
    struct Array arr = init(5);
    c_quick_sort(&arr, NULL); // Should not crash
    free_arr(&arr);

    // Empty array
    struct Array empty = init(5);
    c_quick_sort(&empty, cmp_ascending); // Should handle gracefully
    free_arr(&empty);

    // Already sorted (ascending)
    int sorted_asc[] = {1, 2, 3, 4, 5};
    struct Array arr_sorted = init_from_array(sorted_asc, 5);
    c_quick_sort(&arr_sorted, cmp_ascending);
    CU_ASSERT_TRUE(is_sorted_asc(&arr_sorted));
    free_arr(&arr_sorted);

    // Reverse sorted
    int reverse_sorted[] = {5, 4, 3, 2, 1};
    struct Array arr_reverse = init_from_array(reverse_sorted, 5);
    c_quick_sort(&arr_reverse, cmp_ascending);
    CU_ASSERT_TRUE(is_sorted_asc(&arr_reverse));
    free_arr(&arr_reverse);

    // All equal elements
    int equal[] = {2, 2, 2, 2};
    struct Array arr_equal = init_from_array(equal, 4);
    c_quick_sort(&arr_equal, cmp_ascending);
    CU_ASSERT_TRUE(is_sorted_asc(&arr_equal));
    free_arr(&arr_equal);

    // Custom comparator (descending)
    int values[] = {1, 3, 5, 2, 4};
    struct Array arr_l = init_from_array(values, 5);
    c_quick_sort(&arr_l, cmp_descending);
    for (size_t i = 0; i < arr_l.length - 1; i++) {
        CU_ASSERT_TRUE(arr_l.A[i] >= arr_l.A[i + 1]);
    }
    free_arr(&arr_l);
}
void test_merge_sort(void) {
    // Normal case
    int values1[] = {5, 3, 1, 4, 2};
    struct Array arr1 = init_from_array(values1, 5);
    merge_sort(&arr1);
    CU_ASSERT_TRUE(is_sorted_asc(&arr1));
    free_arr(&arr1);

    // Already sorted
    int values2[] = {1, 2, 3, 4, 5};
    struct Array arr2 = init_from_array(values2, 5);
    merge_sort(&arr2);
    CU_ASSERT_TRUE(is_sorted_asc(&arr2));
    free_arr(&arr2);

    // With flagged elements
    int values3[] = {5, INT_MAX, 3, 2}; // Assuming -1 is flagged
    struct Array arr3 = init_from_array(values3, 4);
    arr3.flagged_count = 1;
    compact(&arr3);
    merge_sort(&arr3);
    CU_ASSERT_EQUAL(arr3.length, 3);
    CU_ASSERT_TRUE(is_sorted_asc(&arr3));
    free_arr(&arr3);
}

void test_c_merge_sort(void) {
    // Modulus sort
    int values1[] = {5, 2, 8, 1, 9};
    struct Array arr1 = init_from_array(values1, 5);
    c_merge_sort(&arr1, cmp_mod3);
    for (size_t i = 0; i < arr1.length - 1; i++) {
        CU_ASSERT_TRUE((arr1.A[i] % 3) <= (arr1.A[i + 1] % 3));
    }
    free_arr(&arr1);

    // Even-first sort
    int values2[] = {1, 2, 3, 4, 5};
    struct Array arr2 = init_from_array(values2, 5);
    c_merge_sort(&arr2, cmp_even_first);
    CU_ASSERT_EQUAL(arr2.A[0] % 2, 0); // First elements should be even
    CU_ASSERT_EQUAL(arr2.A[1] % 2, 0);
    free_arr(&arr2);
}

// ===== Test Suite Setup =====
int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Algorithm Tests", NULL, NULL);

    CU_add_test(suite, "test_reverse", test_reverse);
    CU_add_test(suite, "test_shift", test_shift);
    CU_add_test(suite, "test_quick_sort", test_quick_sort);
    CU_add_test(suite, "test_c_quick_sort", test_c_quick_sort);
    CU_add_test(suite, "test_merge_sort", test_merge_sort);
    CU_add_test(suite, "test_c_merge_sort", test_c_merge_sort);

    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
