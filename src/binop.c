#include "../include/array.h"

struct Array* merge(struct Array* arr1, struct Array* arr2){
	struct Array* temp = (struct Array*)malloc(sizeof(struct Array)); 
	// testing for one empty array case
	
	if (arr1->length == 0 && arr2->length > 0){
		for (int i = 0; i < arr2->length; i++){
			temp->A[i] = arr2->A[i];	
		}
		temp->length = arr2->length;
		return temp;

	} else if (arr2->length == 0 && arr1->length > 0){
		for (int i = 0; i < arr1->length; i++){
			temp->A[i] = arr1->A[i];
		}
		temp->length = arr1->length;
		return temp;
	}
	
	int i, j, k;
	i = 0; j = 0; k = 0; 
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
	// test for emptiness of second array 
	if (arr2->length == 0){
		for (; i < arr1->length; i++){
			temp->A[i] = arr1->A[i];
		}
		temp->length = arr1->length;
		return temp;
	}
	
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
