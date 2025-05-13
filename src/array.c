#include "../include/array.h"
#include "../include/array_utils.h"
#include "../include/array_operations.h"

#define ARRAY_MIN_SIZE 4

struct Array array_init(size_t initial_size) {
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

struct Array array_init_from(const int* values, size_t length) {
    if(!values || length == 0){
        struct Array arr = { NULL, 0, 0, 0 }; 
        return arr; 
    }
    struct Array arr = array_init(length);
    internal_copy(arr.A, values, length);
    arr.length = length;
    arr.flagged_count = 0; 
    return arr;
}

struct Array array_clone(const struct Array* src) {
    struct Array copy_array = array_init(src->length);
    internal_copy(copy_array.A, src->A, src->length);
    copy_array.length = src->length;
    return copy_array;
}

bool array_resize(struct Array* arr, size_t new_size){
    if (!arr || !arr->A){
        return false;
    }
    if (new_size < arr->length){
        fprintf(stderr, "cannot shrink below current length\n");
        return false;
    }
    return internal_resize_to(arr, new_size);
}

bool shrink(struct Array* arr) {
    if (!arr || !arr->A){
        return false;
    }
    if (arr->length == arr->size) {
        fprintf(stderr, "Cannot shrink when the array is full\n");
        return false;  
    }

    size_t new_size = arr->length > ARR_MIN_SIZE ? arr->length : ARR_MIN_SIZE;
    return internal_resize_to(arr, new_size);
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
    if (!arr || !arr->A){
        return;
    }
    int val;
    CONST_ARRAY_FOREACH(val, arr) {
        printf("%d ", val);
    }
    printf("\n");
}

bool push_back(struct Array* arr, int elt){
    if (!arr || !arr->A){
        return false;
    }
    
    if (arr->length == arr->size){
        if(!internal_resize(arr))
            return false; 
    }

    arr->A[arr->length] = elt; 
    arr->length++;
    return true;
}

bool insert_at(struct Array* arr, int index, int elt){
    if (!arr || !arr->A || index < 0 || index > arr->length) {
        return false;
    }

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
    if (!arr || !arr->A){
        return;
    }
    for (size_t i = 0; i < arr->size; ++i) {
        push_back(arr, elt);
    }
    arr->flagged_count = 0;
}

int pop_back(struct Array* arr){
    if (!arr || !arr->A || arr->length == 0){
        return -1;
    }
    int elt = arr->A[arr->length - 1];
    arr->A[arr->length - 1] = 0;
    arr->length--;
    return elt; 
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

int array_get(const struct Array* arr, int index){
    if (!arr || !arr->A){
        return false;
    }
    if (index < 0 || index >= arr->length){
    	return -1; 
    }
    return arr->A[index];
}

bool array_set(struct Array* arr, int index, int elt){
    if (!arr || !arr->A){
        return false; 
    }
    if (index < 0 || index >= arr->length){
    	return false; 
    }
    arr->A[index] = elt;
    return true;
}
