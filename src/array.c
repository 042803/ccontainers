#include "../include/array.h"
#include "../include/array_utils.h"
#include "../include/array_operations.h"

#define ARRAY_MIN_SIZE 4

struct Array init(size_t initial_size) {
    if (initial_size < ARR_MIN_SIZE)
        initial_size = ARR_MIN_SIZE;

    int* A = (int*)calloc(initial_size, sizeof(int));
    if (!A) {
        fprintf(stderr, "memory allocation failed in init\n");
        exit(EXIT_FAILURE);
    }

    struct Array arr = {
        .A = A,
        .length = 0,
        .size = initial_size,
        .flagged_count = 0
    };

    return arr;
}

struct Array init_from_array(const int* values, size_t length) {
    struct Array arr = init(length);
    cpy(arr.A, values, length);
    arr.length = length;
    arr.flagged_count = 0; 
    return arr;
}

bool array_resize(struct Array* arr, size_t new_size){
    if (new_size < arr->length){
        fprintf(stderr, "cannot shrink below current length\n");
        return false;
    }
    return resize_to(arr, new_size);
}


bool shrink(struct Array* arr) {
    if (arr->length == arr->size) {
        fprintf(stderr, "Cannot shrink when the array is full\n");
        return false;  
    }

    size_t new_size = arr->length > ARR_MIN_SIZE ? arr->length : ARR_MIN_SIZE;
    return resize_to(arr, new_size);
}

void free_arr(struct Array* arr){
    if (arr->A != NULL){
        free(arr->A);
        arr->A = NULL;
    }
    arr->length = 0;
    arr->size = 0;
}

void print(const struct Array* arr) {
    int val;
    CONST_ARRAY_FOREACH(val, arr) {
        printf("%d ", val);
    }
    printf("\n");
}

bool push_back(struct Array* arr, int elt){
    if (arr->length == arr->size){
        if(!internal_resize(arr))
            return false; 
    }

    arr->A[arr->length] = elt; 
    arr->length++;
    return true;
}

bool emplace_at(struct Array* arr, int index, int elt){
    if (index < 0 || index > arr->length)
        return false;
    
    if (arr->length == arr->size){
        if (!internal_resize(arr))
            return false; 
    }
   
    for (int i = arr->length; i > index; --i){
        arr->A[i] = arr->A[i - 1];
    }

    arr->A[index] = elt;
    arr->length++;
    return true; 
}

void fill(struct Array* arr, int elt) {
    if (!arr || !arr->A) return;
    for (size_t i = 0; i < arr->length; ++i) {
        arr->A[i] = elt;
    }
    arr->flagged_count = 0;
}

bool remove_at(struct Array* arr, int index) {
    if (index < 0 || index >= arr->length) {
        return false;
    }

    for (int i = index; i < arr->length - 1; i++) {
        arr->A[i] = arr->A[i + 1];
    }

    arr->length--;
    return true;
}

int get(const struct Array* arr, int index){
	if (index < 0 || index >= arr->length){
		return -1; 
	}
	return arr->A[index];
}

void set(struct Array* arr, int index, int elt){
	if (index < 0 || index >= arr->length){
		return; 
	}
	arr->A[index] = elt;
}


