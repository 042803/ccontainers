#include "../include/array.h"
#include "../include/search.h"
#include "../include/array_utils.h"
#include "../include/math.h"

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

int linear_search(struct Array* arr, int key){
	for (int i = 0; i < arr->length; i++){
		if (arr->A[i] == key){
			swap(&arr->A[i], &arr->A[0]);
			return i; 	
		}		
	}       	
	return -1;
}

bool contains(const struct Array* arr, int key){
    if (arr == NULL || arr->A == NULL)
        return false;

    if (is_sorted(arr))
        return binary_search(arr, key) != -1;

    for (int i = 0; i < arr->length; ++i){
        if (arr->A[i] == key)
            return true;
    }
    return false;
}
