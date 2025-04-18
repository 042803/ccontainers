#include "../include/array_utils.h"
#include <stdlib.h>
#include <stdio.h>


// Helper functions 

void swap(int* a, int* b){
	int temp = *a; 
	*a = *b; 
	*b = temp; 
}

void cpy(int* dest, const int* src, size_t length){
    for (size_t index = 0; index < length; ++index){
        dest[index] = src[index];
    }
}

bool resize_to(struct Array* arr, size_t new_size) {
    if (new_size < 4) new_size = ARR_MIN_SIZE;

    int* new_A = (int*)calloc(new_size, sizeof(int));
    if (!new_A) {
        fprintf(stderr, "allocation failed\n");
        return false;
    }

    if (arr->A != NULL) {
        cpy(new_A, arr->A, arr->length);
        free(arr->A);
    }

    arr->A = new_A;
    arr->size = new_size;
    return true;
}

bool internal_resize(struct Array* arr){
    return resize_to(arr, arr->size * 2);
}

int internal_partition(struct Array* arr, int low, int high){
    int pivot = arr->A[low];
    int i = low;
    int j = high;

    while (i < j){
        do { i++; } while (i <= high && arr->A[i] <= pivot);
        do { j--; } while (j >= low && arr->A[j] > pivot);
        if (i < j){
            swap(&arr->A[i], &arr->A[j]);
        }
    }

    swap(&arr->A[low], &arr->A[j]);
    return j;
}


void internal_quicksort(struct Array* arr, int low, int high){
    if (low < high){
        int j = internal_partition(arr, low, high);
        internal_quicksort(arr, low, j);
        internal_quicksort(arr, j + 1, high);
    }
}

void internal_merge(struct Array* arr, int low, int mid, int high){
    struct Array temp = init(arr->size);
    int i = low, j = mid + 1, k = low;

    while (i <= mid && j <= high){
        if (arr->A[i] < arr->A[j]){
            temp.A[k++] = arr->A[i++];
        } else {
            temp.A[k++] = arr->A[j++];
        }
    }

    while (i <= mid){
        temp.A[k++] = arr->A[i++];
    }

    while (j <= high){
        temp.A[k++] = arr->A[j++];
    }

    for (i = low; i <= high; i++){
        arr->A[i] = temp.A[i];
    }

    free_arr(&temp);
}

void internal_merge_sort(struct Array* arr, int low, int high){
    if (low < high){
        int mid = (low + high) / 2;
        internal_merge_sort(arr, low, mid);
        internal_merge_sort(arr, mid + 1, high);
        internal_merge(arr, low, mid, high);
    }
}
