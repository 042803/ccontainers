#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"

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

struct Array* merge(struct Array* arr1, struct Array* arr2){
	int i, j, k;
	i = 0; j = 0; k = 0; 
	struct Array* temp = (struct Array*)malloc(sizeof(struct Array)); 

	while(i < arr1->length && j < arr2->length){
		if (arr1->A[i] < arr2->A[j]){
			temp->A[k] = arr1->A[i];
			k++;
			i++;
		} else {
			temp->A[k] = arr2->A[j];
			k++;
			j++;
		}
	}
	for (; i < arr1->length; i++){
		temp->A[k] = arr1->A[i];
	}

	for (; j < arr2->length; j++){
		temp->A[k] = arr2->A[j];
	}
	temp->length = arr1->length + arr2->length;
	temp->size = 10;

	return temp;
}

struct Array* un(struct Array* arr1, struct Array* arr2){
	int i, j, k;
	i = 0; j = 0; k = 0; 
	struct Array* temp = (struct Array*)malloc(sizeof(struct Array)); 

	while (i < arr1->length && j < arr2->length){
		if (arr1->A[i] < arr2->A[j]){
			temp->A[k++] = arr1->A[i++];
		} else if (arr2->A[j] < arr1->A[i]){
			temp->A[k++] = arr2->A[j++];
		} else {
			temp->A[k++] = arr1->A[i++];
			j++;
		}
	}
	
	for (; i < arr1->length; i++){
		temp->A[k++] = arr1->A[i];
	}
	for (; j < arr2->length; j++){
		temp->A[k++] = arr2->A[j];
	}
	temp->length = k;
	temp->size = 10;
	
	return temp;
}

struct Array* in(struct Array* arr1, struct Array* arr2){
	int i, j, k;
	i = 0; j = 0; k = 0;
	struct Array* temp = (struct Array*)malloc(sizeof(struct Array));

	while (i < arr1->length && j < arr2->length){
		if (arr1->A[i] == arr2->A[j]){
			temp->A[k++] = arr1->A[i++];
			j++;
		} else if (arr1->A[i] < arr2->A[j]){
			i++;
		} else if (arr2->A[j] < arr1->A[i]){
			j++;
		}
	}
	temp->length = k;
	temp->size = 10;
	return temp;
}

struct Array* dif(struct Array* arr1, struct Array* arr2){
	int i, j, k;
	i = 0; j = 0; k = 0;
	struct Array* temp = (struct Array*)malloc(sizeof(struct Array));

	while (i < arr1->length){
		if (arr1->A[i] < arr2->A[j]){
			temp->A[k++] = arr1->A[i++];
		} else if (arr2->A[j] < arr1->A[i]){
			j++;
		} else {
			i++;
		}
	}
	for (; i < arr1->length; i++){
		temp->A[k++] = arr1->A[i];
	}
	temp->length = k;
	temp->size = 10;
	
	return temp;
	
}


int main(){	
	struct Array arr = {{1, 2, 5, 6, 9}, 5, 10};
	struct Array arr1 = {{1, 3, 5, 7, 9}, 5, 10};
	struct Array *temp;
	temp = dif(&arr, &arr1);
	print(*temp);
	
	return 0;			
}	
