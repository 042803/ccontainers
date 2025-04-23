#ifndef     CONST_ARRAY_ITERATOR
#define CONST_ARRAY_ITERATOR

#include "array.h"

// ========================
// Const Forward Iterator Section
// ========================
typedef struct {
    const struct Array* array;
    size_t index;
} ConstArrayIterator;

static inline ConstArrayIterator const_iterator_begin(const struct Array* arr) {
    return (ConstArrayIterator){.array = arr, .index = 0};
}

static inline bool const_iterator_has_next(const ConstArrayIterator* it) {
    return it->index < it->array->length;
}

static inline int const_iterator_next(ConstArrayIterator* it) {
    return it->array->A[it->index++];
}

#define CONST_ARRAY_FOREACH(var, arr_ptr) \
    for (ConstArrayIterator it = const_iterator_begin(arr_ptr); const_iterator_has_next(&it) && ((var = const_iterator_next(&it)), 1); )

// ==========================
// Const Reverse Iterator Section
// ==========================

typedef struct {
    const struct Array* array;
    ssize_t index; 
} ConstArrayReverseIterator;

static inline ConstArrayReverseIterator const_reverse_iterator_begin(struct Array* arr) {
    return (ConstArrayReverseIterator){.array = arr, .index = (ssize_t)arr->length - 1};
}

static inline bool const_reverse_iterator_has_prev(const ConstArrayReverseIterator* it) {
    return it->index >= 0;
}

static inline int const_reverse_iterator_prev(ConstArrayReverseIterator* it) {
    return it->array->A[it->index--];
}

#define CONST_ARRAY_REVERSE_FOREACH(var, arr_ptr) \
    for (ConstArrayReverseIterator it = const_reverse_iterator_begin(arr_ptr); const_reverse_iterator_has_prev(&it) && ((var = const_reverse_iterator_prev(&it)), 1); )

#endif


