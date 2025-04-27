#include "../include/array.h"
#include "../include/binop.h"
#include "../include/array_utils.h"

void append(struct Array* dst, const struct Array* src){
    if (dst == NULL || src == NULL || dst->A == NULL || src->A == NULL) {
        return;
    }

    if (dst->size < dst->length + src->length){
        if(!resize_to(dst, dst->length + src->length)){
            fprintf(stderr, "memory allocation failed\n");
            return;
        }
    }
    for (int i = 0; i < src->length; ++i){
        dst->A[dst->length++] = src->A[i];
    }
}

struct Array merge(const struct Array* arr1, const struct Array* arr2) {
    struct Array temp = init(arr1->length + arr2->length);

    int i = 0, j = 0, k = 0;
    while (i < arr1->length && j < arr2->length) {
    	if (arr1->A[i] < arr2->A[j]) {
    	    temp.A[k++] = arr1->A[i++];
    	} else {
	    temp.A[k++] = arr2->A[j++];
        }
    }
    while (i < arr1->length) 
    	temp.A[k++] = arr1->A[i++];
    while (j < arr2->length) 
        temp.A[k++] = arr2->A[j++];    
    temp.length = k;
    return temp;
}


struct Array un(const struct Array* arr1, const struct Array* arr2) {
    struct Array temp = init(arr1->length + arr2->length);
    int i = 0, j = 0, k = 0;

    while (i < arr1->length && j < arr2->length) {
        if (arr1->A[i] < arr2->A[j]) {
            temp.A[k++] = arr1->A[i++];
        } else if (arr2->A[j] < arr1->A[i]) {
            temp.A[k++] = arr2->A[j++];
        } else {
            temp.A[k++] = arr1->A[i++];
            j++;
        }
    }
    while (i < arr1->length)
        temp.A[k++] = arr1->A[i++];
    while (j < arr2->length)
        temp.A[k++] = arr2->A[j++];
    temp.length = k; 
    return temp;
}


struct Array in(const struct Array* arr1, const struct Array* arr2) {
    struct Array temp = init(arr1->length < arr2->length ? arr1->length : arr2->length);
    int i = 0, j = 0, k = 0;
    while (i < arr1->length && j < arr2->length) {
        if (arr1->A[i] == arr2->A[j]) {
            temp.A[k++] = arr1->A[i++];
            j++;
        } else if (arr1->A[i] < arr2->A[j]) {
            i++;
        } else {
            j++;
        }
    }
    temp.length = k;
    return temp;
}


struct Array dif(const struct Array* arr1, const struct Array* arr2){
    int i = 0, j = 0, k = 0;
    struct Array temp = init(arr1->length);
    if (arr2->length == 0) {
        for (; i < arr1->length; i++) {
            temp.A[i] = arr1->A[i];
        }
        temp.length = arr1->length;
        return temp;
    }

    while (i < arr1->length && j < arr2->length) {
        if (arr1->A[i] < arr2->A[j]) {
            temp.A[k++] = arr1->A[i++];
        } else if (arr1->A[i] > arr2->A[j]) {
            j++;
        } else {
            i++;
        }
    }

    for (; i < arr1->length; i++) {
        temp.A[k++] = arr1->A[i];
    }

    temp.length = k;
    temp.size = k;

    return temp;
}
