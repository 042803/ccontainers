#ifndef ARRAY_OPERATIONS_H
#define ARRAY_OPERATIONS_H

#include "iterator.h"
#include "const_iterator.h"

// =======================
// Range Operations
// =======================

static inline void set_to_range(struct Array* arr, size_t start, size_t end, int value) {
    if (start >= end || end > arr->length) return;
    for (size_t i = start; i < end; ++i) {
        arr->A[i] = value;
    }
}

static inline void set_all(struct Array* arr, int value) {
    set_to_range(arr, 0, arr->length, value);
}

static inline void apply_to_range(struct Array* arr, size_t start, size_t end, void (*func)(int*)) {
    if (!func || start >= end || end > arr->length) return;
    for (size_t i = start; i < end; ++i) {
        func(&arr->A[i]);
    }
}

static inline void apply(struct Array* arr, void (*func)(int*)) {
    apply_to_range(arr, 0, arr->length, func); 
}

// =======================
// Map Operations
// =======================

static inline void map(struct Array* arr, int (*func)(int)) {
    for (ArrayIterator it = iterator_begin(arr); iterator_has_next(&it); ) {
        int value = iterator_next(&it);
        iterator_set(&it, func(value));
    }
}

static inline void map_to_range(struct Array* arr, size_t start, size_t end, int (*func)(int)) {
    if (start >= end || end > arr->length) return;
    for (size_t i = start; i < end; ++i) {
        arr->A[i] = func(arr->A[i]);
    }
}

// =======================
// Filter Operations
// =======================

static inline void filter(struct Array* arr, bool (*predicate)(int)) {
    size_t j = 0;

    for (size_t i = 0; i < arr->length; ++i) {
        if (predicate(arr->A[i])) {
            arr->A[j++] = arr->A[i];  
        }
    }
    arr->length = j;  
}

static inline void filter_range(struct Array* arr, size_t start, size_t end, bool (*predicate)(int)) {
    if (start >= end || end > arr->length) return;
    size_t j = start;

    for (size_t i = start; i < end; ++i) {
        if (predicate(arr->A[i])) {
            arr->A[j++] = arr->A[i];
        }
    }
    arr->length = j;
}

#endif 
