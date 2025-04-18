#include "../include/array.h"
#include "../include/array_utils.h"

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
        .size = initial_size
    };

    return arr;
}

struct Array init_from_array(const int* values, size_t length) {
    struct Array arr = init(length);
    cpy(arr.A, values, length);
    arr.length = length;
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

void print(const struct Array* arr){
	for (int i = 0; i < arr->length; i++){
		printf("%d ", arr->A[i]);
	}
	printf("\n");
}

// insertion and deletion
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

int binary_search(const struct Array* arr, int key){
	int l = 0; 
	int r = arr->length - 1; 
	while (l <= r){
		int m = (l + r) / 2;
		if (arr->A[m] == key){
			return m; 
		} else if (arr->A[m] < key){
			l = m + 1;
		} else {
			r = m - 1;
		}
	}
	return -1; 
}

// get, set, max, min, avg  
int get(const struct Array* arr, int index){
	if (index < 0 || index >= arr->length){
		return -1; 
	}
	return arr->A[index];
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

void set(struct Array* arr, int index, int elt){
	if (index < 0 || index >= arr->length){
		return; 
	}
	arr->A[index] = elt;
}

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

void quick_sort(struct Array* arr){
    if (arr->length > 1){
        internal_quicksort(arr, 0, arr->length - 1);
    }
}

void merge_sort(struct Array* arr){
    if (arr->length > 1){
        internal_merge_sort(arr, 0, arr->length - 1);
    }
}
