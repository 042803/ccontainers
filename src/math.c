#include "../include/array.h"
#include "../include/math.h"

int avg(const struct Array* arr){
    if (arr->length == 0) {
        fprintf(stderr, "array is empty\n");
        return -1; 
    }

    int avg = 0; 
    for (int i = 0; i < arr->length; i++){
    	avg += arr->A[i]; 
    }
    return avg / arr->length; 
}

bool is_sorted(const struct Array* arr){
    if (arr->length == 0 || arr->length == 1){
    	return true;
    } else {
    	for (int i = 0; i < arr->length - 2; i++){
            if (arr->A[i] > arr->A[i + 1]){
    	    return false;
	    }
	}
    }
    return true;
}


int max(const struct Array* arr){
    if (arr->length == 0) {
        fprintf(stderr, "array is empty\n");
        return -1; 
    }
    int max = arr->A[0];
    for (int i = 1; i < arr->length; i++){
    	if (arr->A[i] > max){
    	    max = arr->A[i];
    	}
    }
    return max;
}
				
int min(const struct Array* arr){
    if (arr->length == 0) {
        fprintf(stderr, "array is empty\n");
        return -1; 
    }
    int min = arr->A[0];
    for (int i = 1; i < arr->length; i++){
    	if (arr->A[i] < min){
    		min = arr->A[i];
    	}
    }
    return min;
}
