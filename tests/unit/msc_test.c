#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/vector.h" 

// ===== Test Cases =====

void test_equals(void) {
    // Equal arrays
    int vals1[] = {1, 2, 3};
    int vals2[] = {1, 2, 3};
    struct Array a1 = array_init_from(vals1, 3);
    struct Array a2 = array_init_from(vals2, 3);
    CU_ASSERT_TRUE(array_equals(&a1, &a2));
    free_arr(&a1);
    free_arr(&a2);

    // Different lengths
    int vals3[] = {1, 2};
    struct Array a3 = array_init_from(vals3, 2);
    CU_ASSERT_FALSE(array_equals(&a1, &a3));
    free_arr(&a3);

    // Different values
    int vals4[] = {1, 2, 4};
    struct Array a4 = array_init_from(vals4, 3);
    CU_ASSERT_FALSE(array_equals(&a1, &a4));
    free_arr(&a4);

    // Empty arrays
    struct Array empty1 = array_init(5);
    struct Array empty2 = array_init(5);
    CU_ASSERT_TRUE(array_equals(&empty1, &empty2));
    free_arr(&empty1);
    free_arr(&empty2);

    // NULL cases (shouldn't crash)
//    struct Array a5 = array_init(5);
//    CU_ASSERT_FALSE(array_equals(NULL, &a5));
//    CU_ASSERT_FALSE(array_equals(&a5, NULL));
//    free_arr(&a5);
}

void test_equals_not_sorted(void) {
    // Equal but unsorted
    int vals1[] = {3, 1, 2};
    int vals2[] = {1, 2, 3};
    struct Array a1 = array_init_from(vals1, 3);
    struct Array a2 = array_init_from(vals2, 3);
    CU_ASSERT_TRUE(array_equals_not_sorted(&a1, &a2));
    free_arr(&a1);
    free_arr(&a2);

    // Different contents
    int vals3[] = {3, 1, 4};
    struct Array a3 = array_init_from(vals3, 3);
    CU_ASSERT_FALSE(array_equals_not_sorted(&a1, &a3));
    free_arr(&a3);

    // One sorted, one not
    int vals4[] = {1, 2, 3};
    int vals5[] = {3, 2, 1};
    struct Array a4 = array_init_from(vals4, 3);
    struct Array a5 = array_init_from(vals5, 3);
    CU_ASSERT_TRUE(array_equals_not_sorted(&a4, &a5));
    free_arr(&a4);
    free_arr(&a5);

    // Empty arrays
    struct Array empty1 = array_init(5);
    struct Array empty2 = array_init(5);
    CU_ASSERT_TRUE(array_equals_not_sorted(&empty1, &empty2));
    free_arr(&empty1);
    free_arr(&empty2);
}

void test_remove_value(void) {
    // Normal case
    int vals1[] = {1, 2, 3, 2, 4};
    struct Array a1 = array_init_from(vals1, 5);
    CU_ASSERT_TRUE(array_remove_value(&a1, 2));
    CU_ASSERT_EQUAL(a1.length, 3);
    CU_ASSERT_EQUAL(a1.flagged_count, 0); // COMPACT WAS INTERNALLY CALLED
    CU_ASSERT_EQUAL(a1.A[0], 1);
    CU_ASSERT_EQUAL(a1.A[1], 3);
    CU_ASSERT_EQUAL(a1.A[2], 4);
    free_arr(&a1);

    // Value not present
    struct Array a2 = array_init_from(vals1, 5);
    CU_ASSERT_TRUE(array_remove_value(&a2, 5)); // No change
    CU_ASSERT_EQUAL(a2.length, 5);
    CU_ASSERT_EQUAL(a2.flagged_count, 0);
    free_arr(&a2);

    // Remove all elements
    int vals3[] = {2, 2, 2, 1, 1, 0, 0, 5, 6, 7, 8, 10, 11, 12, 10, 15};
    struct Array a3 = array_init_from(vals3, sizeof(vals3) / sizeof(int));
    CU_ASSERT_TRUE(array_remove_value(&a3, 2));
    CU_ASSERT_EQUAL(a3.length, 16);
    CU_ASSERT_EQUAL(a3.flagged_count, 3);
    compact(&a3);
    CU_ASSERT_EQUAL(a3.length, 13);
    CU_ASSERT_EQUAL(a3.flagged_count, 0);
    free_arr(&a3);
    // NULL case
//    CU_ASSERT_FALSE(array_remove_value(NULL, 2));
}

void test_compact(void) {
    // Normal case with flagged values
    int vals1[] = {1, FLAGGED, 2, FLAGGED, 3};
    struct Array a1 = array_init_from(vals1, 5);
    a1.flagged_count = 2;
    compact(&a1);
    CU_ASSERT_EQUAL(a1.length, 3);
    CU_ASSERT_EQUAL(a1.flagged_count, 0);
    CU_ASSERT_EQUAL(a1.A[0], 1);
    CU_ASSERT_EQUAL(a1.A[1], 2);
    CU_ASSERT_EQUAL(a1.A[2], 3);
    free_arr(&a1);

    // All flagged
    int vals2[] = {FLAGGED, FLAGGED};
    struct Array a2 = array_init_from(vals2, 2);
    a2.flagged_count = 2;
    compact(&a2);
    CU_ASSERT_EQUAL(a2.length, 0);
    CU_ASSERT_EQUAL(a2.flagged_count, 0);
    free_arr(&a2);

    // No flagged
    int vals3[] = {1, 2, 3};
    struct Array a3 = array_init_from(vals3, 3);
    compact(&a3);
    CU_ASSERT_EQUAL(a3.length, 3);
    CU_ASSERT_EQUAL(a3.flagged_count, 0);
    free_arr(&a3);

    // NULL case (shouldn't crash)
//    compact(NULL);
}

void test_pop_flagged(void) {
    // Flagged at end
    int vals1[] = {1, 2, FLAGGED, FLAGGED};
    struct Array a1 = array_init_from(vals1, 4);
    a1.flagged_count = 2;
    array_pop_flagged(&a1);
    CU_ASSERT_EQUAL(a1.length, 2);
    CU_ASSERT_EQUAL(a1.flagged_count, 0);
    free_arr(&a1);

    // Mixed flagged
    int vals2[] = {1, FLAGGED, 2, FLAGGED};
    struct Array a2 = array_init_from(vals2, 4);
    a2.flagged_count = 2;
    array_pop_flagged(&a2); // Only removes trailing flagged
    CU_ASSERT_EQUAL(a2.length, 3); // Only one FLAGGED removed
    CU_ASSERT_EQUAL(a2.flagged_count, 1);
    free_arr(&a2);

    // No flagged
    int vals3[] = {1, 2, 3};
    struct Array a3 = array_init_from(vals3, 3);
    array_pop_flagged(&a3);
    CU_ASSERT_EQUAL(a3.length, 3);
    free_arr(&a3);

    // NULL case (shouldn't crash)
//    array_pop_flagged(NULL);
}

void test_slice(void) {
    // Normal array_slice
    int vals1[] = {1, 2, 3, 4, 5};
    struct Array a1 = array_init_from(vals1, 5);
    struct Array s1 = array_slice(&a1, 1, 4);
    CU_ASSERT_EQUAL(s1.length, 3);
    CU_ASSERT_EQUAL(s1.A[0], 2);
    CU_ASSERT_EQUAL(s1.A[1], 3);
    CU_ASSERT_EQUAL(s1.A[2], 4);
    free_arr(&a1);
    free_arr(&s1);

    // Full range
    struct Array a2 = array_init_from(vals1, 5);
    struct Array s2 = array_slice(&a2, 0, 5);
    CU_ASSERT_TRUE(array_equals(&a2, &s2));
    free_arr(&a2);
    free_arr(&s2);

    // Invalid indices
    struct Array a3 = array_init_from(vals1, 5);
    struct Array s3 = array_slice(&a3, 3, 2); // start > end
    CU_ASSERT_EQUAL(s3.length, 0);
    struct Array s4 = array_slice(&a3, -1, 3); // negative start
    CU_ASSERT_EQUAL(s4.length, 0);
    struct Array s5 = array_slice(&a3, 0, 6); // end > length
    CU_ASSERT_EQUAL(s5.length, 0);
    free_arr(&a3);
    free_arr(&s3);
    free_arr(&s4);
    free_arr(&s5);

    // NULL case
//    struct Array s6 = array_slice(NULL, 0, 1);
//    CU_ASSERT_EQUAL(s6.length, 0);
//    free_arr(&s6);
}

// ===== Test Suite Setup =====
int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Array Utility Tests", NULL, NULL);

    // Add tests
    CU_add_test(suite, "test_equals", test_equals);
    CU_add_test(suite, "test_equals_not_sorted", test_equals_not_sorted);
    CU_add_test(suite, "test_remove_value", test_remove_value);
    CU_add_test(suite, "test_compact", test_compact);
    CU_add_test(suite, "test_pop_flagged", test_pop_flagged);
    CU_add_test(suite, "test_slice", test_slice);

    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
