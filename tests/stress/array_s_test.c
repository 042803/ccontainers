#include "../../include/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>

#define ARRAY_MIN_SIZE 4
#define STRESS_TEST_SIZE (1 << 20)  // 1 million elements for heavy tests

// --- Helper Functions ---
void shuffle(int* array, size_t n) {
    for (size_t i = n - 1; i > 0; i--) {
        size_t j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

// --- Stress Tests ---

// Test 1: Mass push_back and resize
void test_push_back_resize() {
    struct Array arr = init(ARRAY_MIN_SIZE);
    for (size_t i = 0; i < STRESS_TEST_SIZE; i++) {
        assert(push_back(&arr, (int)i));
        assert(arr.length == i + 1);
        if (i == ARRAY_MIN_SIZE * 2) {
            assert(arr.size > ARRAY_MIN_SIZE * 2);  // Exponential growth check
        }
    }
    assert(arr.length == STRESS_TEST_SIZE);
    free_arr(&arr);
}

// Test 2: Random insertions/deletions with shadow validation
void test_random_ops_consistency() {
    struct Array arr = init(ARRAY_MIN_SIZE);
    int* shadow = malloc(STRESS_TEST_SIZE * sizeof(int)); // Shadow array
    size_t shadow_len = 0;

    for (size_t i = 0; i < STRESS_TEST_SIZE / 2; i++) {
        if (arr.length == 0 || rand() % 2 == 0) {
            // Insertion
            int val = rand();
            size_t index = (arr.length == 0) ? 0 : (rand() % arr.length);
            assert(emplace_at(&arr, (int)index, val));
            
            // Update shadow array
            if (shadow_len > 0 && index < shadow_len) {
                memmove(shadow + index + 1, shadow + index, 
                       (shadow_len - index) * sizeof(int));
            }
            shadow[index] = val;
            shadow_len++;
        } else {
            // Deletion (only if array is not empty)
            size_t index = rand() % arr.length;
            assert(remove_at(&arr, (int)index));
            
            // Update shadow array
            memmove(shadow + index, shadow + index + 1, 
                   (shadow_len - index - 1) * sizeof(int));
            shadow_len--;
        }
    }

    // Validate consistency
    assert(arr.length == shadow_len);
    for (size_t i = 0; i < shadow_len; i++) {
        assert(get(&arr, (int)i) == shadow[i]);
    }

    free(shadow);
    free_arr(&arr);
}
// Test 3: Edge cases (NULL, empty, invalid indices)
/*
void test_edge_cases() {
    struct Array arr = init(10);

    // Invalid operations
//    assert(!emplace_at(NULL, 0, 42));
    assert(!remove_at(&arr, -1));
    assert(!remove_at(&arr, 100));

    // Empty array ops
    assert(arr.length == 0);
    assert(!remove_at(&arr, 0));
    assert(shrink(&arr));  // Shrink empty array
    assert(arr.size == ARRAY_MIN_SIZE);

    free_arr(&arr);
}
*/
// Test 4: Fill, get, set, and shrink
void test_fill_get_set_shrink() {
    struct Array arr = init(1000);
    const int MAGIC = 0xABCD1234;

    fill(&arr, MAGIC);
    assert(arr.length == arr.size);

    // Verify fill
    for (size_t i = 0; i < arr.length; i++) {
        assert(get(&arr, (int)i) == MAGIC);
        set(&arr, (int)i, (int)i);
        assert(get(&arr, (int)i) == (int)i);
    }

    // Remove half and shrink
    for (size_t i = 0; i < arr.length / 2; i++) {
        assert(remove_at(&arr, 0));
    }
    assert(shrink(&arr));
    assert(arr.size >= arr.length && arr.size >= ARRAY_MIN_SIZE);

    free_arr(&arr);
}

// Test 5: Memory integrity (Valgrind will check)
void test_memory_integrity() {
    struct Array arr = init(ARRAY_MIN_SIZE);
    for (size_t i = 0; i < 100000; i++) {
        push_back(&arr, (int)i);
    }
    free_arr(&arr);
    assert(arr.A == NULL && arr.length == 0 && arr.size == 0);
}

// --- Main ---
int main() {
    srand(time(NULL));  // Seed for random tests

    printf("[1] Testing push_back and resize...\n");
    test_push_back_resize();

    printf("[2] Testing random ops consistency...\n");
    test_random_ops_consistency();

    //printf("[3] Testing edge cases...\n");
    //test_edge_cases();

    printf("[4] Testing fill/get/set/shrink...\n");
    test_fill_get_set_shrink();

    printf("[5] Testing memory integrity (Valgrind will verify)...\n");
    test_memory_integrity();

    printf("All tests passed!\n");
    return 0;
}
