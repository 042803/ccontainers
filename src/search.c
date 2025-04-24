#include "../include/array.h"
#include "../include/search.h"
#include "../include/array_utils.h"
#include "../include/math.h"
#include "../include/iterator.h"
#include "../include/comparators.h"

int binary_search(const struct Array* arr, int key){
	int l = 0; 
	int r = arr->length - 1; 
	while (l <= r){
		int m = (l + r) / 2;
		if (arr->A[m] == key){
			return m; 
		} else if (arr->A[m] < key){
			l = m + 1;
		} else {
			r = m - 1;
		}
	}
	return -1; 
}


int c_binary_search(const struct Array* arr, int key, comparator_fn cmp) {
    if (!arr || !arr->A) return -1;

    int left = 0, right = arr->length - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp_result = cmp(&arr->A[mid], &key);
        
        if (cmp_result == 0) {
            return mid;  
        } else if (cmp_result < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int linear_search(struct Array* arr, int key){
    if (!arr || !arr->A) return -1;
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

int c_linear_search(struct Array* arr, int key, comparator_fn cmp) {
    if (!arr || !arr->A) return -1;

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

bool contains(const struct Array* arr, int key){
    if (arr == NULL || arr->A == NULL)
        return false;

    if (is_sorted(arr))
        return binary_search(arr, key) != -1;

    for (ArrayIterator it = iterator_begin((struct Array*)arr); iterator_has_next(&it); ) {
        if (iterator_next(&it) == key) return true;
    
    }    return false;
}


bool c_contains(const struct Array* arr, int key, comparator_fn cmp) {
    if (!arr || !arr->A) return false;

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
