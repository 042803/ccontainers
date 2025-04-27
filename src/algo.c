#include "../include/array.h"
#include "../include/algo.h"
#include "../include/array_utils.h"
#include "../include/msc.h"
#include "../include/comparators.h"

void reverse(struct Array* arr){
    if (arr->length == 0 || arr->length == 1)
	return;
    
    if (arr->flagged_count > 0)
        compact(arr);

    for (int i = 0, j = arr->length - 1; i <= j; i++, j--){
	swap(&arr->A[i], &arr->A[j]);
    }
}

int shift(struct Array* arr){
    if (arr->length == 0) return -1; 
	
    if (arr->flagged_count > 0)
        compact(arr);

    int shifted = arr->A[0]; 
    for (int i = 0; i < arr->length; i++)
    	arr->A[i] = arr->A[i + 1];
    if (arr->length == arr->size)
    	arr->A[arr->length -1] = 0; 
    
    arr->length--;  
    
    if (arr->length < arr->size) {
        arr->A[arr->length] = 0;
    }

    return shifted;
}

void quick_sort(struct Array* arr){
    if (arr->flagged_count > 0)
        compact(arr);
    if (arr->length > 1){
        internal_quicksort(arr, 0, arr->length);
    }
}

void c_quick_sort(struct Array* arr, comparator_fn cmp){
    if (!arr || !cmp) return;    
    if (arr->flagged_count > 0)
        compact(arr);
    if (arr->length > 1){
        c_quicksort(arr, 0, arr->length, cmp);
    }
}

void merge_sort(struct Array* arr){
    if (arr->flagged_count > 0)
        compact(arr);
    if (arr->length > 1){
        internal_merge_sort(arr, 0, arr->length - 1);
    }
}

void c_merge_sort(struct Array* arr, comparator_fn cmp){
    if (arr->flagged_count > 0)
        compact(arr);
    if (arr->length > 1){
        c_mergesort(arr, 0, arr->length - 1, cmp);
    }
}
