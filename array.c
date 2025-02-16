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


}
int main(){	
	struct Array arr = {{1, 2, 3, 4, 5}, 5, 10};
	push_back(&arr, 6);
	print(arr);

	return 0;			
}	
