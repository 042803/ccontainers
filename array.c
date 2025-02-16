#include "stdio.h"
#include "stdbool.h"

// testing from feat branch
struct Array {
	int A[10];
	int length;
	int size;
};

void swap(int* a, int* b){
	int temp = *a; 
	*a = *b; 
	*b = temp; 
}

void print(struct Array arr){
	for (int i = 0; i < arr.length; i++){
		printf("%d ", arr.A[i]);
	}
}

void push_back(struct Array* arr, int elt){
	if (arr->length < arr->size){
		arr->A[arr->length] = elt; 
		arr->length++;
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

int pop_back(struct Array* arr, int index){
	int temp = arr->A[index];
	if (index >= 0 && index < arr->length){
		for (int i = index; i < arr->length - 1; i++){
			arr->A[i] = arr->A[i + 1];
		}	
	}		
	arr->length--; 
	return temp; 
}

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

int get(struct Array arr, int index){
	if (index < 0 || index > arr.length){
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

void reverse(struct Array* arr){
	for (int i = 0, j = arr->length - 1; i <= j; i++, j--){
		swap(&arr->A[i], &arr->A[j]);
	}
}


int shift(struct Array* arr){
	for (int i = 0; i < arr->length; i++){
		arr->A[i] = arr->A[i + 1];
	}

}

bool is_sorted(struct Array arr){
	for (int i = 0; i < arr.length - 2; i++){
		if (arr.A[i] > arr.A[i + 1]){
			return false;
		}
	}
	return true;
}


// merge, append, concat, compare, copy and set operations

/*
struct Array union(struct Array arr1, struct Array arr2){
	if (!(is_sorted(arr1)) || !(is_sorted(arr2))){
		return;
	}
	int i, j, k;
	while (i < arr->length){
		for (i = 0; i < arr1->length; i++){
			if (i 
		}
	}
}
*/
int main(){	
	struct Array arr = {{1, 2, 3, 4, 5, 6}, 6, 10};
	struct Array arr1 = {{1, 10,  2, 3, 4, 5, 6}, 7, 10};
	bool test = is_sorted(arr);
	bool test_2 = is_sorted(arr1);
	printf("\n%d\n%d", test, test_2);
	
	return 0;			
}	
