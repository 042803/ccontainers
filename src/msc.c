#include "../include/array.h"
#include "../include/msc.h"
#include "../include/math.h"
#include "../include/algo.h"
#include "../include/iterator.h"
#include "../include/const_iterator.h"
#include <limits.h> 

#define FLAGGED INT_MAX
#define SHOULD_COMPACT(arr) ((arr)->flagged_count >= (arr)->length / 4)

bool equals_not_sorted(struct Array* a, struct Array* b){
    if (a->length != b->length)
        return false;
    
    if (!is_sorted(a))
        quick_sort(a);

    if (!is_sorted(b))
        quick_sort(b);

    return equals(a, b); 
}

bool equals(const struct Array* a, const struct Array* b) {
    if (a->length != b->length) return false;

    ConstArrayIterator it_a = const_iterator_begin(a);
    ConstArrayIterator it_b = const_iterator_begin(b);
    while (const_iterator_has_next(&it_a) && const_iterator_has_next(&it_b)) {
        if (const_iterator_next(&it_a) != const_iterator_next(&it_b)) {
            return false;
        }
    }
    
    return true;
}

bool remove_value(struct Array* arr, int value) {
    if (!arr || !arr->A) return false;

    int v;
    for (ArrayIterator it = iterator_begin(arr); iterator_has_next(&it); ) {
        v = iterator_next(&it);
        if (v == value) {
            iterator_set(&it, FLAGGED);
            arr->flagged_count++;
        }
    }

    if (SHOULD_COMPACT(arr)) {
        compact(arr);
    }

    return true;
}

void compact(struct Array* arr) {
    if (!arr || !arr->A) return;

    size_t write_index = 0;

    for (ArrayIterator it = iterator_begin(arr); iterator_has_next(&it); ) {
        int value = iterator_next(&it);
        if (value != FLAGGED) {
            arr->A[write_index++] = value;
        }
    }

    arr->length = write_index;
    arr->flagged_count = 0;
}

void pop_flagged(struct Array* arr) {
    if (!arr || !arr->A) return;

    while (arr->length > 0 && arr->A[arr->length - 1] == FLAGGED) {
        arr->length--;
        arr->flagged_count--;
    }
}

struct Array slice(const struct Array* arr, int start, int end) {
    if (!arr || !arr->A || start < 0 || end > arr->length || start >= end) {
        return init(0);
    }

    size_t new_len = end - start;
    struct Array result = init(new_len);

    for (int i = 0; i < new_len; ++i) {
        result.A[i] = arr->A[start + i];
    }

    result.length = new_len;
    return result;
}
