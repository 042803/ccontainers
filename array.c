#include "stdio.h"

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
int main(){	
	struct Array arr = {{1, 2, 3, 4, 5}, 5, 10};;
	print(arr);
	int test = avg(arr);
	printf("\n%d", test);
	
	return 0;			
}	
