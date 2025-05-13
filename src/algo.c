#include "../include/array.h"
#include "../include/algo.h"
#include "../include/array_utils.h"
#include "../include/msc.h"
#include "../include/comparators.h"

void array_reverse(struct Array* arr){ 
    if (!arr || !arr->A || arr->length < 2)
	return;
    if (arr->flagged_count > 0)
        compact(arr);
    
    size_t front_index = 0;
    size_t back_index = arr->length - 1;

    while (front_index < back_index) {
        swap(&arr->A[front_index], &arr->A[back_index]);
        front_index++;
        back_index--;
    }
}

int shift(struct Array* arr){
    if (!arr || !arr->A || arr->length == 0) 
        return -1; 
	
    if (arr->flagged_count > 0)
        compact(arr);

    int first_value = arr->A[0]; 
    
    for (size_t index = 0; index < arr->length - 1; index++)
    	arr->A[index] = arr->A[index + 1];
    
    arr->length--;    
    arr->A[arr->length] = 0;
    return first_value;
}

void quick_sort(struct Array* arr){
    if (!arr || !arr->A)
        return;

    if (arr->flagged_count > 0)
        compact(arr);
    if (arr->length > 1){
        internal_quicksort(arr, 0, arr->length);
    }
}

void quick_sort_cmp(struct Array* arr, comparator_fn cmp){
    if (!arr || !arr->A || !cmp) return;    
    if (arr->flagged_count > 0)
        compact(arr);
    if (arr->length > 1){
        c_internal_quicksort(arr, 0, arr->length, cmp);
    }
}

void merge_sort(struct Array* arr){
    if (!arr || !arr->A) return;    
    if (arr->flagged_count > 0)
        compact(arr);
    if (arr->length > 1){
        internal_merge_sort(arr, 0, arr->length - 1);
    }
}

void merge_sort_cmp(struct Array* arr, comparator_fn cmp){ 
    if (!arr || !arr->A || !cmp) return;    
    if (arr->flagged_count > 0)
        compact(arr);
    if (arr->length > 1){
        c_internal_mergesort(arr, 0, arr->length - 1, cmp);
    }
}
