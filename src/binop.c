#include "../include/array.h"
#include "../include/binop.h"
#include "../include/array_utils.h"

void append(struct Array* dst, const struct Array* src){
    if (dst == NULL || src == NULL || dst->A == NULL || src->A == NULL) {
        return;
    }

    if (dst->size < dst->length + src->length){
        if(!internal_resize_to(dst, dst->length + src->length)){
            fprintf(stderr, "memory allocation failed\n");
            return;
        }
    }
    for (int i = 0; i < src->length; ++i){
        dst->A[dst->length++] = src->A[i];
    }
}

struct Array array_merge(const struct Array* arr1, const struct Array* arr2) {
    if (!arr1 || !arr1->A) {
        if (!arr2 || !arr2->A) return array_init(ARR_MIN_SIZE);
        return array_clone(arr2);  
    }
    if (!arr2 || !arr2->A) return array_clone(arr1);

    struct Array temp_array = array_init(arr1->length + arr2->length);
    if (!temp_array.A) return array_init(ARR_MIN_SIZE); 
    
    size_t left_index = 0, right_index = 0, temp_index = 0;
    while (left_index < arr1->length && right_index < arr2->length) {
    	if (arr1->A[left_index] < arr2->A[right_index]) {
    	    temp_array.A[temp_index++] = arr1->A[left_index++];
    	} else {
	    temp_array.A[temp_index++] = arr2->A[right_index++];
        }
    }
    while (left_index < arr1->length) 
    	temp_array.A[temp_index++] = arr1->A[left_index++];
    while (right_index < arr2->length) 
        temp_array.A[temp_index++] = arr2->A[right_index++];    
    temp_array.length = temp_index;
    return temp_array;
}


struct Array array_union(const struct Array* arr1, const struct Array* arr2) {
    if (!arr1 || !arr1->A) {
        if (!arr2 || !arr2->A) return array_init(ARR_MIN_SIZE);
        return array_clone(arr2);
    }

    if (!arr2 || !arr2->A) return array_clone(arr1);
    
    struct Array temp_array = array_init(arr1->length + arr2->length);
    if (!temp_array.A) return array_init(ARR_MIN_SIZE); 

    size_t left_index = 0, right_index = 0, temp_index = 0;

    while (left_index < arr1->length && right_index < arr2->length) {
        if (arr1->A[left_index] < arr2->A[right_index]) {
            temp_array.A[temp_index++] = arr1->A[left_index++];
        } else if (arr2->A[right_index] < arr1->A[left_index]) {
            temp_array.A[temp_index++] = arr2->A[right_index++];
        } else {
            temp_array.A[temp_index++] = arr1->A[left_index++];
            right_index++;
        }
    }
    while (left_index < arr1->length)
        temp_array.A[temp_index++] = arr1->A[left_index++];
    while (right_index < arr2->length)
        temp_array.A[temp_index++] = arr2->A[right_index++];
    temp_array.length = temp_index; 
    return temp_array;
}


struct Array array_intersection(const struct Array* arr1, const struct Array* arr2) {
    if (!arr1 || !arr1->A || !arr2 || !arr2->A) {
        return array_init(ARR_MIN_SIZE);
    }

    struct Array temp_array = array_init(arr1->length + arr2->length);
    if (!temp_array.A) return array_init(ARR_MIN_SIZE); 

    size_t left_index = 0, right_index = 0, temp_index = 0;

 
    while (left_index < arr1->length && right_index < arr2->length) {
        if (arr1->A[left_index] == arr2->A[right_index]) {
            temp_array.A[temp_index++] = arr1->A[left_index++];
            right_index++;
        } else if (arr1->A[left_index] < arr2->A[right_index]) {
            left_index++;
        } else {
            right_index++;
        }
    }
    temp_array.length = temp_index;
    return temp_array;
}


struct Array array_difference(const struct Array* arr1, const struct Array* arr2){
    if (!arr1 || !arr1->A) {
        if (!arr2 || !arr2->A) return array_init(ARR_MIN_SIZE);
        return array_clone(arr2);
    }

    if (!arr2 || !arr2->A) return array_clone(arr1);

    struct Array temp_array = array_init(arr1->length + arr2->length);
    if (temp_array.A) return array_init(ARR_MIN_SIZE); 

    size_t left_index = 0, right_index = 0, temp_index = 0;

    if (arr2->length == 0) {
        for (; left_index < arr1->length; left_index++) {
            temp_array.A[left_index] = arr1->A[left_index];
        }
        temp_array.length = arr1->length;
        return temp_array;
    }

    while (left_index < arr1->length && right_index < arr2->length) {
        if (arr1->A[left_index] < arr2->A[right_index]) {
            temp_array.A[temp_index++] = arr1->A[left_index++];
        } else if (arr1->A[left_index] > arr2->A[right_index]) {
            right_index++;
        } else {
            left_index++;
        }
    }

    for (; left_index < arr1->length; left_index++) {
        temp_array.A[temp_index++] = arr1->A[left_index];
    }

    temp_array.length = temp_index;
    temp_array.size = temp_index;

    return temp_array;
}
