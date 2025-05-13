#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/vector.h" 

void test_avg(void) {
    int values1[] = {10, 20, 30, 40};
    struct Array arr1 = array_init_from(values1, 4);
    CU_ASSERT_EQUAL(array_avg(&arr1), 25);
    free_arr(&arr1);

    int values2[] = {5};
    struct Array arr2 = array_init_from(values2, 1);
    CU_ASSERT_EQUAL(array_avg(&arr2), 5);
    free_arr(&arr2);

    struct Array arr3 = array_init(5);
    CU_ASSERT_EQUAL(array_avg(&arr3), -1);
    free_arr(&arr3);

    int values4[] = {-5, 0, 5};
    struct Array arr4 = array_init_from(values4, 3);
    CU_ASSERT_EQUAL(array_avg(&arr4), 0); 
    free_arr(&arr4);
}

void test_is_sorted(void) {
    int values1[] = {1, 2, 3, 4, 5};
    struct Array arr1 = array_init_from(values1, 5);
    CU_ASSERT_TRUE(array_is_sorted(&arr1));
    free_arr(&arr1);

    int values2[] = {1, 3, 2, 4};
    struct Array arr2 = array_init_from(values2, 4);
    CU_ASSERT_FALSE(array_is_sorted(&arr2));
    free_arr(&arr2);

    int values3[] = {42};
    struct Array arr3 = array_init_from(values3, 1);
    CU_ASSERT_TRUE(array_is_sorted(&arr3));
    free_arr(&arr3);

    struct Array arr4 = array_init(5);
    CU_ASSERT_TRUE(array_is_sorted(&arr4));
    free_arr(&arr4);

    int values5[] = {5, 5, 5};
    struct Array arr5 = array_init_from(values5, 3);
    CU_ASSERT_TRUE(array_is_sorted(&arr5));
    free_arr(&arr5);
}

void test_max(void) {
    int values1[] = {10, 30, 20, 50, 40};
    struct Array arr1 = array_init_from(values1, 5);
    CU_ASSERT_EQUAL(array_max(&arr1), 50);
    free_arr(&arr1);

    int values2[] = {-5, -1, -10};
    struct Array arr2 = array_init_from(values2, 3);
    CU_ASSERT_EQUAL(array_max(&arr2), -1);
    free_arr(&arr2);

    int values3[] = {7};
    struct Array arr3 = array_init_from(values3, 1);
    CU_ASSERT_EQUAL(array_max(&arr3), 7);
    free_arr(&arr3);

    struct Array arr4 = array_init(5);
    CU_ASSERT_EQUAL(array_max(&arr4), -1);
    free_arr(&arr4);
}

void test_min(void) {
    int values1[] = {50, 30, 40, 10, 20};
    struct Array arr1 = array_init_from(values1, 5);
    CU_ASSERT_EQUAL(array_min(&arr1), 10);
    free_arr(&arr1);

    int values2[] = {-1, -5, -3};
    struct Array arr2 = array_init_from(values2, 3);
    CU_ASSERT_EQUAL(array_min(&arr2), -5);
    free_arr(&arr2);

    int values3[] = {9};
    struct Array arr3 = array_init_from(values3, 1);
    CU_ASSERT_EQUAL(array_min(&arr3), 9);
    free_arr(&arr3);

    struct Array arr4 = array_init(5);
    CU_ASSERT_EQUAL(array_min(&arr4), -1);
    free_arr(&arr4);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Array Math Tests", NULL, NULL);

    // Add tests
    CU_add_test(suite, "test_avg", test_avg);
    CU_add_test(suite, "test_is_sorted", test_is_sorted);
    CU_add_test(suite, "test_max", test_max);
    CU_add_test(suite, "test_min", test_min);

    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
