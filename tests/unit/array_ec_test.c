#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/vector.h" 

// ===== Helper Macros =====
#define ASSERT_ARRAY_INITIALIZED(arr) \
    CU_ASSERT_PTR_NOT_NULL((arr).A); \
    CU_ASSERT_EQUAL((arr).length, 0); \
    CU_ASSERT_TRUE((arr).size >= ARR_MIN_SIZE)

// ===== Test Cases =====

// --- init() ---
void test_init(void) {
    struct Array arr_small = init(1); 
    CU_ASSERT_EQUAL(arr_small.size, ARR_MIN_SIZE);
    CU_ASSERT_EQUAL(arr_small.length, 0);
    free_arr(&arr_small);

    // Test normal initialization
    struct Array arr_large = init(100);
    CU_ASSERT_EQUAL(arr_large.size, 100);
    CU_ASSERT_EQUAL(arr_large.length, 0);
    free_arr(&arr_large);
}

void test_init_from_array(void) {
    int values[] = {1, 2, 3, 4, 5};
    size_t length = sizeof(values) / sizeof(values[0]);

    struct Array arr = init_from_array(values, length);
    CU_ASSERT_EQUAL(arr.length, length);
    CU_ASSERT_TRUE(arr.size >= length);
    for (size_t i = 0; i < length; i++) {
        CU_ASSERT_EQUAL(get(&arr, i), values[i]);
    }
    free_arr(&arr);

//    struct Array arr_empty = init_from_array(NULL, 0);
//    ASSERT_ARRAY_INITIALIZED(arr_empty);
//    free_arr(&arr_empty);
}

void test_push_back(void) {
    struct Array arr = init(2); 
    CU_ASSERT_TRUE(push_back(&arr, 42));
    CU_ASSERT_EQUAL(arr.length, 1);
    CU_ASSERT_EQUAL(get(&arr, 0), 42);

    CU_ASSERT_TRUE(push_back(&arr, 99));
    CU_ASSERT_TRUE(push_back(&arr, 100)); 
    CU_ASSERT_TRUE(arr.size > 2); 
    CU_ASSERT_EQUAL(arr.length, 3);
    CU_ASSERT_EQUAL(get(&arr, 2), 100);

 //   CU_ASSERT_FALSE(push_back(NULL, 42)); 
    free_arr(&arr);
}

void test_emplace_at(void) {
    struct Array arr = init(5);
    push_back(&arr, 10);
    push_back(&arr, 20);

    CU_ASSERT_TRUE(emplace_at(&arr, 1, 15)); 
    CU_ASSERT_EQUAL(arr.length, 3);
    CU_ASSERT_EQUAL(get(&arr, 1), 15);

    CU_ASSERT_FALSE(emplace_at(&arr, -1, 0));  
    CU_ASSERT_FALSE(emplace_at(&arr, 999, 0)); 
    CU_ASSERT_TRUE(emplace_at(&arr, arr.length, 30)); 
    CU_ASSERT_EQUAL(get(&arr, 3), 30);

    while (arr.length < arr.size) push_back(&arr, 0);
    CU_ASSERT_TRUE(emplace_at(&arr, 0, 5));
    CU_ASSERT_TRUE(arr.size > 5); 
    free_arr(&arr);
}

void test_remove_at(void) {
    struct Array arr = init(5);
    push_back(&arr, 10);
    push_back(&arr, 20);
    push_back(&arr, 30);

    CU_ASSERT_TRUE(remove_at(&arr, 1)); 
    CU_ASSERT_EQUAL(arr.length, 2);
    CU_ASSERT_EQUAL(get(&arr, 1), 30);

    CU_ASSERT_FALSE(remove_at(&arr, -1));  
    CU_ASSERT_FALSE(remove_at(&arr, 999)); // Invalid index (out of bounds)
    CU_ASSERT_TRUE(remove_at(&arr, 0));    // Remove first element
    CU_ASSERT_EQUAL(arr.length, 1);

    remove_at(&arr, 0);
    CU_ASSERT_FALSE(remove_at(&arr, 0));   // Empty array
    free_arr(&arr);
}

void test_get(void) {
    struct Array arr = init(5);
    push_back(&arr, 42);

    CU_ASSERT_EQUAL(get(&arr, 0), 42);

    CU_ASSERT_EQUAL(get(&arr, -1), -1);  // Invalid index (negative)
    CU_ASSERT_EQUAL(get(&arr, 999), -1); // Invalid index (out of bounds)
//    CU_ASSERT_EQUAL(get(NULL, 0), -1);   // NULL array
    free_arr(&arr);
}

void test_set(void) {
    struct Array arr = init(5);
    push_back(&arr, 10);

    // Valid set
    set(&arr, 0, 20);
    CU_ASSERT_EQUAL(get(&arr, 0), 20);

    // Edge cases (should silently fail)
    set(&arr, -1, 30);  // Invalid index (no effect)
    set(&arr, 999, 30); // Invalid index (no effect)
//    set(NULL, 0, 40);   // NULL array (no effect)
    CU_ASSERT_EQUAL(arr.length, 1); // Length unchanged
    free_arr(&arr);
}

void test_fill(void) {
    struct Array arr = init(5);
    fill(&arr, 42);
    CU_ASSERT_EQUAL(arr.length, arr.size); // Filled to capacity
    for (size_t i = 0; i < arr.size; i++) {
        CU_ASSERT_EQUAL(get(&arr, i), 42);
    }

    // Edge case: NULL array (should do nothing)
 //   fill(NULL, 42);
    free_arr(&arr);
}

void test_array_resize(void) {
    struct Array arr = init(5);
    push_back(&arr, 1);
    push_back(&arr, 2);

    // Grow
    CU_ASSERT_TRUE(array_resize(&arr, 10));
    CU_ASSERT_EQUAL(arr.size, 10);
    CU_ASSERT_EQUAL(arr.length, 2); // Length unchanged

    // Shrink (to length)
    CU_ASSERT_TRUE(array_resize(&arr, arr.length));
    CU_ASSERT_EQUAL(arr.size, 4);

    // Edge cases
    CU_ASSERT_FALSE(array_resize(&arr, 1)); // New size < length (should fail)
//    CU_ASSERT_FALSE(array_resize(NULL, 10)); // NULL array
    free_arr(&arr);
}

void test_shrink(void) {
    struct Array arr = init(10);
    push_back(&arr, 1);
    push_back(&arr, 2);

    // Normal shrink
    CU_ASSERT_TRUE(shrink(&arr));
    CU_ASSERT_EQUAL(arr.size, (arr.length > ARR_MIN_SIZE) ? arr.length : ARR_MIN_SIZE);

    // Edge cases
 //   CU_ASSERT_FALSE(shrink(NULL)); // NULL array
    while (arr.length < arr.size) push_back(&arr, 0); // Fill to capacity
    CU_ASSERT_FALSE(shrink(&arr));  // Already at minimal size
    free_arr(&arr);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Dynamic Array Tests", NULL, NULL);

    // Add tests
    CU_add_test(suite, "test_init", test_init);
    CU_add_test(suite, "test_init_from_array", test_init_from_array);
    CU_add_test(suite, "test_push_back", test_push_back);
    CU_add_test(suite, "test_emplace_at", test_emplace_at);
    CU_add_test(suite, "test_remove_at", test_remove_at);
    CU_add_test(suite, "test_get", test_get);
    CU_add_test(suite, "test_set", test_set);
    CU_add_test(suite, "test_fill", test_fill);
    CU_add_test(suite, "test_array_resize", test_array_resize);
    CU_add_test(suite, "test_shrink", test_shrink);

    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
