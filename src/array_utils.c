#include "../include/array_utils.h"
#include <stdlib.h>
#include <stdio.h>


// helper functions 

static void swap(int* a, int* b){
	int temp = *a; 
	*a = *b; 
	*b = temp; 
}

static void cpy(int* dest, int* src, size_t length){
    for (size_t index = 0; index < length; ++index){
        dest[index] = src[index];
    }
}

static void resize_to(struct Array* arr, size_t new_size) {
    if (new_size < 4) new_size = ARR_MIN_SIZE;

    int* new_A = (int*)calloc(new_size, sizeof(int));
    if (!new_A) {
        fprintf(stderr, "allocation failed\n");
        exit(EXIT_FAILURE);
    }

    if (arr->A != NULL) {
        cpy(new_A, arr->A, arr->length);
        free(arr->A);
    }

    arr->A = new_A;
    arr->size = new_size;
}

static void internal_resize(struct Array* arr){
    resize_to(arr, arr->size * 2);
}
