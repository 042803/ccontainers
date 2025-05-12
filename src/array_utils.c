#include "../include/array_utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// Helper functions 
void swap(int* a, int* b){
    assert(a != NULL);
    assert(b != NULL);
    
    int temp = *a; 
    *a = *b; 
    *b = temp; 
}

void internal_copy(int* dest, const int* src, size_t length){
    assert(dest != NULL);
    assert(src != NULL);
    
    for (size_t index = 0; index < length; ++index){
        dest[index] = src[index];
    }
}

bool internal_resize_to(struct Array* arr, size_t new_size) {
    if (!arr) return false;

    if (new_size < ARR_MIN_SIZE)
        new_size = ARR_MIN_SIZE;    

    int* new_A = (int*)calloc(new_size, sizeof(int));
    
    if (!new_A) {
        fprintf(stderr, "allocation failed\n");
        return false;
    }

    if (arr->A != NULL) {
        internal_copy(new_A, arr->A, arr->length);
        free(arr->A);
    }

    arr->A = new_A;
    arr->size = new_size;
    return true;
}

bool internal_resize(struct Array* arr){
    return internal_resize_to(arr, arr->size * 2);
}

int internal_partition(struct Array* arr, int low, int high){
    if (!arr || !arr->A || low < 0 || high < 0 || low >= arr->length || high > arr->length || low >= high) {
        return -1;
    }
    int pivot = arr->A[low];
    int left = low;
    int right = high;

    while (left < right){
        do { left++; } while (left <= high && arr->A[left] <= pivot);
        do { right--; } while (right >= low && arr->A[right] > pivot);
        if (left < right){
            swap(&arr->A[left], &arr->A[right]);
        }
    }
    swap(&arr->A[low], &arr->A[right]);
    return right;
}
/*
 * OLD IMPLEMENTATION, CAUSING SEG FAULT
int c_partition(struct Array* arr, int low, int high, comparator_fn cmp) {
    if (!arr || !arr->A || low < 0 || high >= (int)arr->length || low >= high) {
        return -1;
    }

    int pivot = arr->A[low];
    int i = low;
    int j = high;

    while (i < j) {                                             // previous
        do { i++; } while (i <= high && cmp(&arr->A[i], &pivot) <= 0);// <=
        do { j--; } while (j >= low && cmp(&arr->A[j], &pivot) > 0); // >
        if (i < j) {
            swap(&arr->A[i], &arr->A[j]);
        }
    }
    swap(&arr->A[low], &arr->A[j]);
    return j;
}
*/

int c_internal_partition(struct Array* arr, int low, int high, comparator_fn cmp) {

    if (!arr || !arr->A || !cmp || low < 0 || high > (int)arr->length || low >= high) {
        return -1;
    }

    int pivot_idx = low + (high - low) / 2;
    int pivot = arr->A[pivot_idx];
    swap(&arr->A[low], &arr->A[pivot_idx]); 

    int left = low + 1;
    int right = high - 1; 

    while (1) {
        while (left <= right && cmp(&arr->A[left], &pivot) < 0) left++;
        while (left <= right && cmp(&arr->A[right], &pivot) > 0) right--;
        
        if (left >= right) break;
        swap(&arr->A[left], &arr->A[right]);
        left++;
        right--;
    }
    swap(&arr->A[low], &arr->A[right]);
    return right;
}

void internal_quicksort(struct Array* arr, int low, int high){
    if (low < high){
        int right = internal_partition(arr, low, high);
        internal_quicksort(arr, low, right);
        internal_quicksort(arr, right + 1, high);
    }
}
/*
void c_quicksort(struct Array* arr, int low, int high, comparator_fn cmp) {
    if (low < high) {
        int j = c_partition(arr, low, high, cmp);
        c_quicksort(arr, low, j, cmp);
        c_quicksort(arr, j + 1, high, cmp);
    }
}
*/

void c_internal_quicksort(struct Array* arr, int low, int high, comparator_fn cmp) {
    #define MAX_STACK_DEPTH 10000
    static int depth = 0;
    if (depth++ > MAX_STACK_DEPTH) {
        depth--;
        return;
    }

    if (high - low > 1) { 
        int right = c_internal_partition(arr, low, high, cmp);
        if (right != -1) { 
            c_internal_quicksort(arr, low, right, cmp);
            c_internal_quicksort(arr, right + 1, high, cmp);
        }
    }
    depth--;
}
void internal_merge(struct Array* arr, int low, int mid, int high){
    if (!arr || !arr->A || low < 0 || mid < low || high < mid || high >= arr->length) {
        return;
    }
    struct Array temp_array = array_init(arr->size);
    if (!temp_array.A) return;
    
    int left_index = low, right_index = mid + 1, temp_index = low;

    while (left_index <= mid && right_index <= high){
        if (arr->A[left_index] < arr->A[right_index]){
            temp_array.A[temp_index++] = arr->A[left_index++];
        } else {
            temp_array.A[temp_index++] = arr->A[right_index++];
        }
    }

    while (left_index <= mid){
        temp_array.A[temp_index++] = arr->A[left_index++];
    }

    while (right_index <= high){
        temp_array.A[temp_index++] = arr->A[right_index++];
    }

    for (left_index = low; left_index <= high; left_index++){
        arr->A[left_index] = temp_array.A[left_index];
    }

    free_arr(&temp_array);
}

void c_internal_merge(struct Array* arr, int low, int mid, int high, comparator_fn cmp) {
    if (!arr || !arr->A || low < 0 || mid < low || high < mid || high >= arr->length) {
        return;
    }

    struct Array temp_array = array_init(arr->size);
    if(!temp_array.A) return;

    int left_index = low, right_index = mid + 1, temp_index = low;

    while (left_index <= mid && right_index <= high) {
        if (cmp(&arr->A[left_index], &arr->A[right_index]) <= 0) {
            temp_array.A[temp_index++] = arr->A[left_index++];
        } else {
            temp_array.A[temp_index++] = arr->A[right_index++];
        }
    }

    while (left_index <= mid) {
        temp_array.A[temp_index++] = arr->A[left_index++];
    }

    while (right_index <= high) {
        temp_array.A[temp_index++] = arr->A[right_index++];
    }

    for (left_index = low; left_index <= high; left_index++) {
        arr->A[left_index] = temp_array.A[left_index];
    }

    free_arr(&temp_array);
}

void internal_merge_sort(struct Array* arr, int low, int high){
    if (low < high){
        int mid = (low + high) / 2;
        internal_merge_sort(arr, low, mid);
        internal_merge_sort(arr, mid + 1, high);
        internal_merge(arr, low, mid, high);
    }
}

void c_internal_mergesort(struct Array* arr, int low, int high, comparator_fn cmp) {
    if (low < high) {
        int mid = (low + high) / 2;
        c_internal_mergesort(arr, low, mid, cmp);
        c_internal_mergesort(arr, mid + 1, high, cmp);
        c_internal_merge(arr, low, mid, high, cmp);
    }
}
