#include "../include/array.h"
#include "../include/msc.h"
#include "../include/math.h"
#include "../include/algo.h"
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

bool equals(const struct Array* a, const struct Array* b){
    for (int i = 0; i < a->length; ++i){
        if (a->A[i] != b->A[i])
            return false;
    }
    return true;
}

bool remove_value(struct Array* arr, int value) {
    if (!arr || !arr->A) return false;

    for (int i = 0; i < arr->length; ++i) {
        if (arr->A[i] == value) {
            arr->A[i] = FLAGGED;
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

    int new_len = 0;
    for (int i = 0; i < arr->length; ++i) {
        if (arr->A[i] != FLAGGED) {
            arr->A[new_len++] = arr->A[i];
        }
    }
    arr->length = new_len;
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
