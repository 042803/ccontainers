#include "../include/array.h"
#include "../include/array_utils.h"

#define ARRAY_MIN_SIZE 4

void array_resize(struct Array* arr, size_t new_size){
    if (new_size < arr->length){
        fprintf(stderr, "cannot shrink below current length\n");
        return;
    }
    resize_to(arr, new_size);
}

void free_arr(struct Array* arr){
    if (arr->A != NULL){
        free(arr->A);
        arr->A = NULL;
    }
    arr->length = 0;
    arr->size = 0;
}

void print(struct Array arr){
	for (int i = 0; i < arr.length; i++){
		printf("%d ", arr.A[i]);
	}
	printf("\n");
}

// insertion and deletion
void push_back(struct Array* arr, int elt){
	if (arr->length < arr->size){
		arr->A[arr->length] = elt; 
		arr->length++;
        } else {
            
        }
}

void emplace_at(struct Array* arr, int index, int elt){
	if(index >= 0 && index < arr->length){ 
		for (int i = arr->length; i > index; i--){
			arr->A[i] = arr->A[i - 1]; 
		}
		arr->A[index] = elt;
		arr->length++;	
	}
}

int remove_at(struct Array* arr, int index){
	int temp = -1; // return -1 if index is invalid
	if (index >= 0 && index < arr->length){
		temp = arr->A[index];
		for (int i = index; i < arr->length - 1; i++){
			arr->A[i] = arr->A[i + 1];
		}
		arr->length--;
	}
	return temp; 
}

// search operations
int linear_search(struct Array* arr, int key){
	for (int i = 0; i < arr->length; i++){
		if (arr->A[i] == key){
			swap(&arr->A[i], &arr->A[0]);
			return i; 	
		}		
	}       	
	return -1;
}

int binary_search(struct Array arr, int key){
	int l = 0; 
	int r = arr.length - 1; 
	while (l <= r){
		int m = (l + r) / 2;
		if (arr.A[m] == key){
			return m; 
		} else if (arr.A[m] < key){
			l = m + 1;
		} else {
			r = m - 1;
		}
	}
	return -1; 
}

// get, set, max, min, avg  
int get(struct Array arr, int index){
	if (index < 0 || index >= arr.length){
		return -1; 
	}
	return arr.A[index];
}

int max(struct Array arr){
	int max = arr.A[0];
	for (int i = 1; i < arr.length; i++){
		if (arr.A[i] > max){
			max = arr.A[i];
		}
	}
	return max;
}
				
int min(struct Array arr){
	int min = arr.A[0];
	for (int i = 1; i < arr.length; i++){
		if (arr.A[i] < min){
			min = arr.A[i];
		}
	}
	return min;
}

void set(struct Array* arr, int index, int elt){
	if (index < 0 || index >= arr->length){
		return; 
	}
	arr->A[index] = elt;
}

int avg(struct Array arr){
	int avg = 0; 
	for (int i = 0; i < arr.length; i++){
		avg += arr.A[i]; 
	}
	return avg / arr.length; 
}

//reverse and shift
void reverse(struct Array* arr){
	if (arr->length == 0 || arr->length == 1){
		return;
	}
	for (int i = 0, j = arr->length - 1; i <= j; i++, j--){
		swap(&arr->A[i], &arr->A[j]);
	}
}


int shift(struct Array* arr){
	if (arr->length == 0) return -1; 
	int shifted = arr->A[0]; 
	for (int i = 0; i < arr->length; i++){
		arr->A[i] = arr->A[i + 1];
	}
	if (arr->length == arr->size){
		arr->A[arr->length -1] = 0; 
	}
	arr->length--; 
	return shifted;
}

bool is_sorted(struct Array arr){
	if (arr.length == 0 || arr.length == 1){
		return true;
	} else {
		for (int i = 0; i < arr.length - 2; i++){
			if (arr.A[i] > arr.A[i + 1]){
				return false;
			}
		}
	}
}
