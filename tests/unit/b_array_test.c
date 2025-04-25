#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/vector.h" 

void test_init(void) {
    struct Array arr = init(10);
    CU_ASSERT_EQUAL(arr.length, 0);
    CU_ASSERT_EQUAL(arr.size, 10);
    free_arr(&arr);
}

void test_init_from_array(void) {
    int values[] = {1, 2, 3, 4, 5};
    size_t len = sizeof(values) / sizeof(values[0]);
    struct Array arr = init_from_array(values, len);

    CU_ASSERT_EQUAL(arr.size, len);
    for (size_t i = 0; i < len; i++) {
        CU_ASSERT_EQUAL(get(&arr, i), values[i]);
    }
    free_arr(&arr);
}

void test_push_back(void) {
    struct Array arr = init(2);
    CU_ASSERT_TRUE(push_back(&arr, 42));
    CU_ASSERT_EQUAL(get(&arr, 0), 42);
    CU_ASSERT_EQUAL(arr.length, 1);

    CU_ASSERT_TRUE(push_back(&arr, 99));
    CU_ASSERT_EQUAL(get(&arr, 1), 99);
    CU_ASSERT_EQUAL(arr.length, 2);

    CU_ASSERT_TRUE(push_back(&arr, 100));
    CU_ASSERT_EQUAL(get(&arr, 2), 100);
    CU_ASSERT_TRUE(arr.size > 2);
    free_arr(&arr);
}

void test_get(void) {
    struct Array arr = init(5);
    push_back(&arr, 10);
    push_back(&arr, 20);

    CU_ASSERT_EQUAL(get(&arr, 0), 10);
    CU_ASSERT_EQUAL(get(&arr, 1), 20);
    CU_ASSERT_EQUAL(get(&arr, 999), -1); 
    free_arr(&arr);
}

void test_set(void) {
    struct Array arr = init(5);
    push_back(&arr, 1);
    push_back(&arr, 2);

    set(&arr, 0, 100);
    set(&arr, 1, 200);

    CU_ASSERT_EQUAL(get(&arr, 0), 100);
    CU_ASSERT_EQUAL(get(&arr, 1), 200);

    set(&arr, 999, 300);
    CU_ASSERT_EQUAL(arr.length, 2);
    free_arr(&arr);
}

void test_remove_at(void) {
    struct Array arr = init(5);
    push_back(&arr, 10);
    push_back(&arr, 20);
    push_back(&arr, 30);

    CU_ASSERT_TRUE(remove_at(&arr, 1));
    CU_ASSERT_EQUAL(arr.length, 2);
    CU_ASSERT_EQUAL(get(&arr, 0), 10);
    CU_ASSERT_EQUAL(get(&arr, 1), 30);

    CU_ASSERT_FALSE(remove_at(&arr, 999));
    free_arr(&arr);
}

void test_fill(void) {
    struct Array arr = init(5);
    fill(&arr, 42);

    CU_ASSERT_EQUAL(arr.size, arr.size);
    for (size_t i = 0; i < arr.length; i++) {
        CU_ASSERT_EQUAL(get(&arr, i), 42);
    }
    free_arr(&arr);
}

void test_resize(void) {
    struct Array arr = init(5);
    push_back(&arr, 1);
    push_back(&arr, 2);

    CU_ASSERT_TRUE(array_resize(&arr, 10));
    CU_ASSERT_EQUAL(arr.size, 10);
    CU_ASSERT_EQUAL(arr.length, 2);

    CU_ASSERT_TRUE(array_resize(&arr, 4));
    CU_ASSERT_EQUAL(arr.size, 4);
    CU_ASSERT_EQUAL(arr.length, 2);
    free_arr(&arr);
}

void test_shrink(void) {
    struct Array arr = init(10);
    push_back(&arr, 1);
    push_back(&arr, 2);

    CU_ASSERT_TRUE(shrink(&arr));
    CU_ASSERT_EQUAL(arr.size, 4);
    free_arr(&arr);
}

// ===== Test Suite Runner =====

int main(void) {
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    CU_pSuite suite = CU_add_suite("Array Unit Tests", NULL, NULL);
    if (!suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_add_test(suite, "init", test_init);
    CU_add_test(suite, "init_from_array", test_init_from_array);
    CU_add_test(suite, "push_back", test_push_back);
    CU_add_test(suite, "get", test_get);
    CU_add_test(suite, "set", test_set);
    CU_add_test(suite, "remove_at", test_remove_at);
    CU_add_test(suite, "fill", test_fill);
    CU_add_test(suite, "resize", test_resize);
    CU_add_test(suite, "shrink", test_shrink);

    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
