#include "../include/array.h"
#include "../include/search.h"
#include "../include/array_utils.h"
#include "../include/math.h"
#include "../include/iterator.h"
#include "../include/comparators.h"

int array_binary_search(const struct Array* arr, int key){
    if (!arr || !arr->A){
        return -1; 
    }

    size_t left_index = 0; 
    size_t right_index = arr->length - 1; 
    while (left_index <= right_index){
    	size_t mid_index = (left_index + right_index) / 2;
    	if (arr->A[mid_index] == key){
    	    return (int)mid_index; 
    	} else if (arr->A[mid_index] < key){
    	    left_index = mid_index + 1;
    	} else {
    	    right_index = mid_index - 1;
    	}
    }
    return -1; 
}

int array_binary_search_cmp(const struct Array* arr, int key, comparator_fn cmp) {
    if (!arr || !arr->A){
        return -1;
    }

    size_t left_index = 0;
    size_t right_index = arr->length - 1;

    while (left_index <= right_index) {
        size_t mid_index = left_index + (right_index - left_index) / 2;
        int cmp_result = cmp(&arr->A[mid_index], &key);
        
        if (cmp_result == 0) {
            return (int)mid_index;  
        } else if (cmp_result < 0) {
            left_index = mid_index + 1;
        } else {
            right_index = mid_index - 1;
        }
    }
    return -1;
}

int array_linear_search(struct Array* arr, int key){
    if (!arr || !arr->A){
        return -1;
    }

    for (ArrayIterator it = iterator_begin(arr); iterator_has_next(&it); ) {
        int val = iterator_next(&it);
        if (val == key) {
            size_t idx = it.index - 1;
            if (idx != 0) {
                int tmp = arr->A[idx];
                arr->A[idx] = arr->A[0];
                arr->A[0] = tmp;
            }
            return (int)idx;
        }
    }
    return -1;
}

int array_linear_search_cmp(struct Array* arr, int key, comparator_fn cmp) {
    if (!arr || !arr->A){
        return -1;
    }

    for (ArrayIterator it = iterator_begin(arr); iterator_has_next(&it); ) {
        int val = iterator_next(&it);
        if (cmp(&val, &key) == 0) {
            size_t idx = it.index - 1;
            if (idx != 0) {
                int tmp = arr->A[idx];
                arr->A[idx] = arr->A[0];
                arr->A[0] = tmp;
            }
            return (int)idx;
        }
    }
    return -1;
}

bool array_contains(const struct Array* arr, int key){
    if (!arr || !arr->A){
        return false;
    }

    if (is_sorted(arr))
        return binary_search(arr, key) != -1;

    for (ArrayIterator it = iterator_begin((struct Array*)arr); iterator_has_next(&it); ) {
        if (iterator_next(&it) == key) 
            return true;
    
    }    
    return false;
}


bool array_contains_cmp(const struct Array* arr, int key, comparator_fn cmp) {
    if (!arr || !arr->A){
        return false;
    } 

    if (is_sorted(arr)) {
        return c_binary_search(arr, key, cmp) != -1;
    }

    for (ArrayIterator it = iterator_begin((struct Array*)arr); iterator_has_next(&it); iterator_next(&it)) {
        if (cmp(&it.array->A[it.index], &key) == 0) {
            return true;
        }
    }
    return false;
}
