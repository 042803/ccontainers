#ifndef ARRAY_ITERATOR_H
#define ARRAY_ITERATOR_H

#include "array.h"

#if defined(_WIN32) || defined(_WIN64)
    #ifndef _SSIZE_T_DEFINED
        typedef long ssize_t;
        #define _SSIZE_T_DEFINED
    #endif
#else
    #include <sys/types.h>  
#endif

// ========================
// Forward Iterator Section
// ========================

typedef struct {
    struct Array* array;
    size_t index;
} ArrayIterator;

static inline ArrayIterator iterator_begin(struct Array* arr) {
    return (ArrayIterator){.array = arr, .index = 0};
}

static inline bool iterator_has_next(const ArrayIterator* it) {
    return it->index < it->array->length;
}

static inline int iterator_next(ArrayIterator* it) {
    return it->array->A[it->index++];
}

static inline void iterator_set(ArrayIterator* it, int value) {
    if (it->index == 0 || it->index > it->array->length) {
        fprintf(stderr, "invalid iterator position in iterator_set\n");
        return;
    }
    it->array->A[it->index - 1] = value;
}

#define ARRAY_FOREACH(var, arr_ptr) \
    for (ArrayIterator it = iterator_begin(arr_ptr); iterator_has_next(&it) && ((var = iterator_next(&it)), 1); )

// ==========================
// Reverse Iterator Section
// ==========================

typedef struct {
    struct Array* array;
    ssize_t index; 
} ArrayReverseIterator;

static inline ArrayReverseIterator reverse_iterator_begin(struct Array* arr) {
    return (ArrayReverseIterator){.array = arr, .index = (ssize_t)arr->length - 1};
}

static inline bool reverse_iterator_has_prev(const ArrayReverseIterator* it) {
    return it->index >= 0;
}

static inline int reverse_iterator_prev(ArrayReverseIterator* it) {
    return it->array->A[it->index--];
}

static inline void reverse_iterator_set(ArrayReverseIterator* it, int value) {
    if (it->index + 1 < 0 || (size_t)(it->index + 1) >= it->array->length) {
        fprintf(stderr, "invalid iterator position in reverse_iterator_set\n");
        return;
    }
    it->array->A[it->index + 1] = value;
}

#define ARRAY_REVERSE_FOREACH(var, arr_ptr) \
    for (ArrayReverseIterator it = reverse_iterator_begin(arr_ptr); reverse_iterator_has_prev(&it) && ((var = reverse_iterator_prev(&it)), 1); )

#endif // ARRAY_ITERATOR_H
