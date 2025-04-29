#include "../../include/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <limits.h>

#define STRESS_SIZE (1 << 20) // 1 million elements
#define BENCHMARK_ROUNDS 1000

// Custom comparator for testing
int reverse_cmp(const void* a, const void* b) {
    return (*(int*)b - *(int*)a);
}

/* Helper to create sorted array for binary search tests */
struct Array create_sorted_array(size_t size, int start) {
    struct Array arr = init(size);
    for (int i = 0; i < (int)size; i++) {
        push_back(&arr, start + i*2); // Even numbers only
    }
    return arr;
}

/* Helper to create randomized array for linear search */
struct Array create_random_array(size_t size) {
    struct Array arr = init(size);
    for (size_t i = 0; i < size; i++) {
        push_back(&arr, rand() % (int)(size * 2));
    }
    return arr;
}

/* ================== Binary Search Stress Tests ================== */

void test_binary_search_correctness() {
    struct Array arr = create_sorted_array(STRESS_SIZE, 0);
    
    // Test all existing elements
    for (int i = 0; i < (int)arr.length; i++) {
        int key = arr.A[i];
        int idx = binary_search(&arr, key);
        assert(idx == i);
        assert(arr.A[idx] == key);
    }

    // Test non-existent elements
//    assert(binary_search(&arr, -1) == -1);
//    assert(binary_search(&arr, arr.A[arr.length-1] + 1) == -1);
    
    // Test with custom comparator (reverse sorted)
    /*
    struct Array rev_arr = create_sorted_array(1000, 0);
    qsort(rev_arr.A, rev_arr.length, sizeof(int), reverse_cmp);
    
    for (int i = 0; i < (int)rev_arr.length; i++) {
        int key = rev_arr.A[i];
        int idx = c_binary_search(&rev_arr, key, reverse_cmp);
        assert(idx == i);
    }
    */
    free_arr(&arr);
    //free_arr(&rev_arr);
}

void test_binary_search_performance() {
    struct Array arr = create_sorted_array(STRESS_SIZE, 0);
    clock_t start = clock();
    
    for (int i = 0; i < BENCHMARK_ROUNDS; i++) {
        int key = rand() % (int)arr.size;
        int idx = binary_search(&arr, key);
        assert(idx == -1 || arr.A[idx] == key);
    }
    
    double elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("Binary search: %.2f ops/sec\n", BENCHMARK_ROUNDS/elapsed);
    
    free_arr(&arr);
}

/* ================== Linear Search Stress Tests ================== */

void test_linear_search_correctness() {
    struct Array arr = create_random_array(STRESS_SIZE);
    
    // Add known values at specific positions
    set(&arr, 0, INT_MIN);
    set(&arr, arr.length/2, INT_MAX);
    set(&arr, arr.length-1, 0);

    // Test edge cases
    //assert(linear_search(&arr, INT_MIN) == 0);
    //assert(linear_search(&arr, INT_MAX) == (int)arr.length/2);
    //assert(linear_search(&arr, 0) == (int)arr.length-1);
    
    // Test with custom comparator
    assert(c_linear_search(&arr, INT_MAX, reverse_cmp) == (int)arr.length/2);

    free_arr(&arr);
}
/*
void test_linear_search_performance() {
    struct Array arr = create_random_array(STRESS_SIZE);
    clock_t start = clock();
    
    for (int i = 0; i < BENCHMARK_ROUNDS; i++) { // Fewer rounds due to slowness
        int key = rand() % (int)(STRESS_SIZE * 2);
        int idx = linear_search(&arr, key);
        assert(idx == -1 || arr.A[idx] == key);
    }
    
    double elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("Linear search: %.2f ops/sec\n", (BENCHMARK_ROUNDS/10)/elapsed);
    
    free_arr(&arr);
}
*/
void test_linear_search_thorough() {
    struct Array arr = create_random_array(STRESS_SIZE);
    
    // 1. Test all existing elements
    for (int i = 0; i < (int)arr.length; i++) {
        int key = arr.A[i];
        int idx = linear_search(&arr, key);
        assert(idx != -1 && arr.A[idx] == key); // Must find existing elements
    }

    // 2. Test guaranteed missing elements
    int missing_key = -1; // Value we know isn't in the array
    assert(linear_search(&arr, missing_key) == -1);

    // 3. Randomized stress test (with validation)
    for (int i = 0; i < BENCHMARK_ROUNDS; i++) {
        int key = rand() % (INT_MAX / 2); // Wider range than array values
        int idx = linear_search(&arr, key);
        
        // Verify result is either -1 or points to the correct key
        if (idx != -1) {
            assert(arr.A[idx] == key); // If found, must match
        } else {
            // Verify key is truly missing (optional but thorough)
            bool found = false;
            for (int j = 0; j < (int)arr.length; j++) {
                if (arr.A[j] == key) found = true;
            }
            assert(!found); // If not found, ensure it's actually missing
        }
    }

    free_arr(&arr);
}
/* ================== Contains Stress Tests ================== */

void test_contains_operations() {
    struct Array arr = init(STRESS_SIZE);
    for (int i = 0; i < (int)STRESS_SIZE; i++) {
        push_back(&arr, i * 2); // Even numbers only
    }

    // Test existing elements
    for (int i = 0; i < 1000; i++) {
        int key = (rand() % (int)arr.length) * 2;
        assert(contains(&arr, key));
    }

    // Test non-existent elements
    for (int i = 0; i < 1000; i++) {
        int key = (rand() % (int)arr.length) * 2 + 1; // Odd numbers
        assert(!contains(&arr, key));
    }

    // Test custom comparator
    qsort(arr.A, arr.length, sizeof(int), reverse_cmp);
    for (int i = 0; i < 100; i++) {
        int key = arr.A[rand() % arr.length];
        assert(c_contains(&arr, key, reverse_cmp));
    }

    free_arr(&arr);
}

/* ================== Main Test Runner ================== */

int main() {
    srand(time(NULL));

    printf("[1] Testing binary search correctness...\n");
    test_binary_search_correctness();

    printf("[2] Testing binary search performance...\n");
    test_binary_search_performance();

    printf("[3] Testing linear search correctness...\n");
    test_linear_search_correctness();

    printf("[4] Testing linear search performance...\n");
    void test_linear_search_thorough();

    printf("[5] Testing contains operations...\n");
    test_contains_operations();

    printf("All search tests passed!\n");
    return 0;
}
