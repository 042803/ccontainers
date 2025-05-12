#include "../include/array.h"
#include "../include/math.h"

int array_avg(const struct Array* arr){
    if (!arr || !arr->A){
        return -1; 
    }
    if (arr->length == 0) {
        fprintf(stderr, "array is empty\n");
        return -1; 
    }

    int avg = 0; 
    for (size_t index = 0; index < arr->length; index++){
    	avg += arr->A[index]; 
    }
    return avg / arr->length; 
}

bool array_is_sorted(const struct Array* arr){
    if (!arr || !arr->A){
        return false;
    }
    if (arr->length == 0 || arr->length == 1){
    	return true;
    } else {
    	for (size_t index = 0; index < arr->length - 2; index++){
            if (arr->A[index] > arr->A[index + 1]){
    	    return false;
	    }
	}
    }
    return true;
}


int array_max(const struct Array* arr){
    if (!arr || !arr->A){
        return -1; 
    }
    if (arr->length == 0) {
        fprintf(stderr, "array is empty\n");
        return -1; 
    }
    int max = arr->A[0];
    for (size_t index = 1; index < arr->length; index++){
    	if (arr->A[index] > max){
    	    max = arr->A[index];
    	}
    }
    return max;
}
				
int array_min(const struct Array* arr){
    if (!arr || !arr->A){
        return -1;
    }
    if (arr->length == 0) {
        fprintf(stderr, "array is empty\n");
        return -1; 
    }
    int min = arr->A[0];
    for (size_t index = 1; index < arr->length; index++){
    	if (arr->A[index] < min){
    		min = arr->A[index];
    	}
    }
    return min;
}
