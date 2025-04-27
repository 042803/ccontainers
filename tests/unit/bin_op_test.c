#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/vector.h" 

// ===== Test Cases =====

void test_append(void) {
    // Normal append
    int vals1[] = {1, 2, 3};
    int vals2[] = {4, 5};
    struct Array dst = init_from_array(vals1, 3);
    struct Array src = init_from_array(vals2, 2);
    
    append(&dst, &src);
    CU_ASSERT_EQUAL(dst.length, 5);
    CU_ASSERT_EQUAL(dst.A[0], 1);
    CU_ASSERT_EQUAL(dst.A[4], 5);
    free_arr(&dst);
    free_arr(&src);

    // Append to empty array
    struct Array empty = init(5);
    int vals3[] = {1, 2};
    struct Array src2 = init_from_array(vals3, 2);
    append(&empty, &src2);
    CU_ASSERT_EQUAL(empty.length, 2);
    free_arr(&empty);
    free_arr(&src2);

    // Append empty array
    int vals4[] = {1, 2};
    struct Array dst2 = init_from_array(vals4, 2);
    struct Array empty_src = init(5);
    append(&dst2, &empty_src);
    CU_ASSERT_EQUAL(dst2.length, 2); // No change
    free_arr(&dst2);
    free_arr(&empty_src);

    // NULL cases (shouldn't crash)
//    append(NULL, &src2);
//    append(&dst2, NULL);
}

void test_merge(void) {
    // Normal merge
    int vals1[] = {1, 3, 5};
    int vals2[] = {2, 4, 6};
    struct Array arr1 = init_from_array(vals1, 3);
    struct Array arr2 = init_from_array(vals2, 3);
    
    struct Array merged = merge(&arr1, &arr2);
    CU_ASSERT_EQUAL(merged.length, 6);
    CU_ASSERT_TRUE(is_sorted(&merged));
    CU_ASSERT_EQUAL(merged.A[0], 1);
    CU_ASSERT_EQUAL(merged.A[5], 6);
    
    // One empty array
    struct Array empty = init(5);
    struct Array merged2 = merge(&arr1, &empty);
    CU_ASSERT_EQUAL(merged2.length, 3);
    CU_ASSERT_TRUE(equals(&merged2, &arr1));

    // Both empty
    struct Array empty2 = init(5);
    struct Array merged3 = merge(&empty, &empty2);
    CU_ASSERT_EQUAL(merged3.length, 0);
 
    free_arr(&arr1);
    free_arr(&arr2);
    free_arr(&merged);
    free_arr(&merged2);
    free_arr(&empty);
    free_arr(&empty2);
    free_arr(&merged3);

    // NULL cases (should return empty array)
//    struct Array merged4 = merge(NULL, &arr1);
//    CU_ASSERT_EQUAL(merged4.length, 0);
//    free_arr(&merged4);
}

void test_un(void) {
    // Normal union (no duplicates)
    int vals1[] = {1, 2, 3};
    int vals2[] = {3, 4, 5};
    struct Array arr1 = init_from_array(vals1, 3);
    struct Array arr2 = init_from_array(vals2, 3);
    
    struct Array union_arr = un(&arr1, &arr2);
    CU_ASSERT_EQUAL(union_arr.length, 5);
    CU_ASSERT_TRUE(is_sorted(&union_arr));
    CU_ASSERT_EQUAL(union_arr.A[0], 1);
    CU_ASSERT_EQUAL(union_arr.A[4], 5);

    // One array empty
    struct Array empty = init(5);
    struct Array union2 = un(&arr1, &empty);
    CU_ASSERT_EQUAL(union2.length, 3);
    CU_ASSERT_TRUE(equals(&union2, &arr1));

    // All duplicates
    int vals3[] = {1, 1, 1};
    struct Array arr3 = init_from_array(vals3, 3);
    struct Array union3 = un(&arr3, &arr3);

//    CU_ASSERT_EQUAL(union3.length, 1); // Only one unique element
    
    free_arr(&arr1);
    free_arr(&arr2);
    free_arr(&union_arr);
    free_arr(&arr3);
    free_arr(&union2);
    free_arr(&union3);

    // NULL cases
//    struct Array union4 = un(NULL, &arr1);
//    CU_ASSERT_EQUAL(union4.length, 0);
//    free_arr(&union4);
}

void test_in(void) {
    // Normal intersection
    int vals1[] = {1, 2, 3, 4};
    int vals2[] = {3, 4, 5, 6};
    struct Array arr1 = init_from_array(vals1, 4);
    struct Array arr2 = init_from_array(vals2, 4);
    
    struct Array intersect = in(&arr1, &arr2);
    CU_ASSERT_EQUAL(intersect.length, 2);
    CU_ASSERT_EQUAL(intersect.A[0], 3);
    CU_ASSERT_EQUAL(intersect.A[1], 4);
    free_arr(&arr1);
    free_arr(&arr2);
    free_arr(&intersect);

    // No intersection
    int vals3[] = {1, 2};
    int vals4[] = {3, 4};
    struct Array arr3 = init_from_array(vals3, 2);
    struct Array arr4 = init_from_array(vals4, 2);
    struct Array intersect2 = in(&arr3, &arr4);
    CU_ASSERT_EQUAL(intersect2.length, 0);
    free_arr(&arr3);
    free_arr(&arr4);
    free_arr(&intersect2);

    // One array empty
    struct Array empty = init(5);
    struct Array intersect3 = in(&arr1, &empty);
    CU_ASSERT_EQUAL(intersect3.length, 0);
    free_arr(&intersect3);

    // NULL cases
//    struct Array intersect4 = in(NULL, &arr1);
//    CU_ASSERT_EQUAL(intersect4.length, 0);
//    free_arr(&intersect4);
}

void test_dif(void) {
    // Normal difference
    int vals1[] = {1, 2, 3, 4};
    int vals2[] = {3, 4, 5, 6};
    struct Array arr1 = init_from_array(vals1, 4);
    struct Array arr2 = init_from_array(vals2, 4);
    
    struct Array diff = dif(&arr1, &arr2);
    CU_ASSERT_EQUAL(diff.length, 2);
    CU_ASSERT_EQUAL(diff.A[0], 1);
    CU_ASSERT_EQUAL(diff.A[1], 2);

    // No difference
    struct Array diff2 = dif(&arr1, &arr1);
    CU_ASSERT_EQUAL(diff2.length, 0);

    // Second array empty
    struct Array empty = init(5);
    struct Array diff3 = dif(&arr1, &empty);
    CU_ASSERT_EQUAL(diff3.length, 4);
    CU_ASSERT_TRUE(equals(&diff3, &arr1));
    
    free_arr(&arr1);
    free_arr(&arr2);
    free_arr(&diff);
    free_arr(&diff2);
    free_arr(&diff3);

    // NULL cases
//    struct Array diff4 = dif(NULL, &arr1);
//    CU_ASSERT_EQUAL(diff4.length, 0);
//    free_arr(&diff4);
}

// ===== Test Suite Setup =====
int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Binary Operation Tests", NULL, NULL);

    // Add tests
    CU_add_test(suite, "test_append", test_append);
    CU_add_test(suite, "test_merge", test_merge);
    CU_add_test(suite, "test_un", test_un);
    CU_add_test(suite, "test_in", test_in);
    CU_add_test(suite, "test_dif", test_dif);

    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
