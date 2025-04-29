#include "../../include/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <limits.h>

#define STRESS_SIZE (1 << 20)  // 1 million elements
#define TEST_ROUNDS 1000
#define WARMUP_ROUNDS 5

void increment(int* x) { (*x)++; }
int square(int x) { return x * x; }
bool is_even(int x) { return x % 2 == 0; }
bool is_positive(int x) { return x > 0; }

static int safe_op(int x) {
    return x / 32;  // Scale down to prevent overflow
}
/* ================== Range Operations Tests ================== */

void test_set_operations() {
    struct Array arr = init(STRESS_SIZE);
    for (int i = 0; i < (int)STRESS_SIZE; i++) {
        push_back(&arr, i);
    }

    // Test set_all
    set_all(&arr, 42);
    for (size_t i = 0; i < arr.length; i++) {
        assert(arr.A[i] == 42);
    }

    // Test set_to_range
    set_to_range(&arr, 100, 200, -1);
    for (size_t i = 0; i < arr.length; i++) {
        if (i >= 100 && i < 200) {
            assert(arr.A[i] == -1);
        } else {
            assert(arr.A[i] == 42);
        }
    }

    // Edge cases
//    set_to_range(&arr, 0, 0, 99);  // Empty range
//    set_to_range(&arr, arr.length, arr.length + 10, 99);  // Invalid range
    free_arr(&arr);
}

void test_apply_operations() {
    struct Array arr = init(STRESS_SIZE);
    for (int i = 0; i < (int)STRESS_SIZE; i++) {
        push_back(&arr, i);
    }

    // Test apply
    apply(&arr, increment);
    for (size_t i = 0; i < arr.length; i++) {
        assert(arr.A[i] == (int)i + 1);
    }

    // Test apply_to_range
    apply_to_range(&arr, 500, 600, increment);
    for (size_t i = 0; i < arr.length; i++) {
        if (i >= 500 && i < 600) {
            assert(arr.A[i] == (int)i + 2);
        } else {
            assert(arr.A[i] == (int)i + 1);
        }
    }

    // Test NULL function
//    apply(&arr, NULL);
//    apply_to_range(&arr, 0, 10, NULL);
    free_arr(&arr);
}

/* ================== Map Operations Tests ================== */

void test_map_operations() {
    struct Array arr = init(STRESS_SIZE);
    for (int i = 0; i < (int)STRESS_SIZE; i++) {
        push_back(&arr, i);
    }

    // Test map
    map(&arr, square);
    for (size_t i = 0; i < arr.length; i++) {
        assert(arr.A[i] == (int)(i * i));
    }

    // Test map_to_range
    map_to_range(&arr, 100, 200, square);
    for (size_t i = 0; i < arr.length; i++) {
        if (i >= 100 && i < 200) {
            assert(arr.A[i] == (int)(i * i * i * i));
        } else {
            assert(arr.A[i] == (int)(i * i));
        }
    }

    // Edge cases
//    map_to_range(&arr, 0, 0, square);  // Empty range
//    map_to_range(&arr, arr.length, arr.length + 10, square);  // Invalid range
    free_arr(&arr);
}

/* ================== Filter Operations Tests ================== */

void test_filter_operations() {
    struct Array arr = init(STRESS_SIZE);
    for (int i = 0; i < (int)STRESS_SIZE; i++) {
        push_back(&arr, i - (int)STRESS_SIZE/2);  // Mix of positive/negative
    }

    // Test filter
    size_t original_length = arr.length;
    filter(&arr, is_positive);
    assert(arr.length <= original_length);
    for (size_t i = 0; i < arr.length; i++) {
        assert(arr.A[i] > 0);
    }

    // Test filter_range
    for (int i = 0; i < (int)STRESS_SIZE/2; i++) {
        push_back(&arr, i);
    }
    filter_range(&arr, 0, STRESS_SIZE/2, is_even);
    for (size_t i = 0; i < STRESS_SIZE/2; i++) {
        if (i < arr.length) {
            assert(arr.A[i] % 2 == 0);
        }
    }

    // Edge cases
//    filter_range(&arr, 0, 0, is_even);  // Empty range
//    filter_range(&arr, arr.length, arr.length + 10, is_even);  // Invalid range
    free_arr(&arr);
}

/* ================== Performance Tests ================== */

void test_performance() {
    // Initialize array with safe values
    struct Array arr = init(STRESS_SIZE);
    for (int i = 0; i < (int)STRESS_SIZE; i++) {
        push_back(&arr, i % 1024);  // Keep numbers small
    }

    // Warm-up phase
    for (int i = 0; i < WARMUP_ROUNDS; i++) {
        set_to_range(&arr, 0, STRESS_SIZE, i);
        map(&arr, safe_op);
    }

    // Benchmark set_to_range
    clock_t start = clock();
    for (int i = 0; i < TEST_ROUNDS; i++) {
        set_to_range(&arr, 0, STRESS_SIZE, i % 256);
    }
    double elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("set_to_range: %.2f million elements/sec\n", 
          (TEST_ROUNDS * STRESS_SIZE) / elapsed / 1e6);

    // Benchmark map with safe operation
    start = clock();
    for (int i = 0; i < TEST_ROUNDS; i++) {
        map(&arr, safe_op);
    }
    elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("map: %.2f million elements/sec\n", 
          (TEST_ROUNDS * STRESS_SIZE) / elapsed / 1e6);

    free_arr(&arr);
}
/* ================== Main Test Runner ================== */

int main() {
    printf("[1] Testing set operations...\n");
    test_set_operations();

    printf("[2] Testing apply operations...\n");
    test_apply_operations();

    printf("[3] Testing map operations...\n");
    test_map_operations();

    printf("[4] Testing filter operations...\n");
    test_filter_operations();

    printf("[5] Performance benchmarks...\n");
    test_performance();

    printf("All array operations tests passed!\n");
    return 0;
}
