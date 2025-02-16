#include "stdio.h"

struct Array {
	int A[10];
	int length;
	int size;
};

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
	if((index >= 0) && (index < arr->length)){ 
		for (int i = arr->length; i > index; i--){
			arr->A[i] = arr->A[i - 1]; 
		}
		arr->A[index] = elt;
		arr->length++;	
	}
}


int main(){	
	struct Array arr = {{1, 2, 3, 4, 5}, 5, 10};
	emplace_at(&arr, -3, 0); // 0 1 2 3 4 5 is expected 
	print(arr);

	return 0;			
}	
