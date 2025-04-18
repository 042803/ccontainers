#include "stdio.h"
//#include "../src/array.c"
#include "../include/array.h"
#include "stdlib.h"

// find single missing element in sorted array 

// input 1 2 3 4 5 6 8 9 10 11 12 
// output 7 

// iterative solution O(n)
int sfme(struct Array arr){
	int fdif = arr.A[0];
	int dif; 
	for (int i = 1; i < arr.length; i++){
		dif = arr.A[i] - i;  
		if (fdif < dif){
			return arr.A[i] - 1;
		}
	}
	return -1;
}

// not sorted list lowest and highest elements given
// input 2 1 5 3 6 
// output 4

int nfme(struct Array arr, int low, int high){
	int* temp = (int*)malloc(sizeof(int) * (high +1)); // array of size high 

	for (int i = 0; i < high + 1; i++){
		temp[i] = 0;
	//	printf("storing 0 at position %d\n", i);
	}
	 
	for (int i = 0; i < arr.length; i++){
		temp[arr.A[i]] = 1;
	//	printf("storing 1 at position %d\n", arr.A[i]);
	}

	for (int i = low; i < high + 1; i++){
		if (temp[i] == 0){
	//		printf("comparing temp[%d] with 0\n", i); 
			return i; 
		}
	}
	
	free(temp);
	return -1;
}


// find duplicates in sorted array
// input 1 2 3 4 4 5 6 
// output 4 

int fd(struct Array arr){
	for (int i = 0; i < arr.length - 1; i++){
		if (arr.A[i] == arr.A[i + 1])
		return arr.A[i]; 
	}
	return -1;
}

int ufd(struct Array arr, int low, int high){
	int* temp = (int*)malloc(sizeof(int) * (high + 1));
	for (int i = 0; i < high + 1; i++){
		temp[i] = 0;
		//temp[arr.A[i]] = 1; 
	}
	for (int i = 0; i < arr.length; i++){
		temp[arr.A[i]] += 1;
	}
	for (int i = low; i <= high; i++){
		if (temp[i] > 1){
			return i; 
		}
	}
	free(temp);
	return -1; 
}

// find pair that sums up to key 
// input 1 5 6 8 9 10, key 7 
// output yes 
// input 1 6 8 9 10, key 7
// output no 
int pairing(struct Array arr, int key){
	int i = 0;
	int j = arr.length - 1; 
	while (i < j){
		int sum = arr.A[i] + arr.A[j];
		if (sum == key){
			return 1;
		} else if (sum > key){
			j--;
		} else {
			i++;
		}
	}
	return -1; 
}

// if array is not sorted
int pairing_ns(const struct Array arr, int key, int low, int high){
	int* temp = (int*)malloc(sizeof(int) * (high + 1));
	//set values to zero
	for (int i = 0; i <= high; i++){
		temp[i] = 0;
	}
	// hash
	int index = 0; 
	for (int i = 0; i < arr.length; i++){
		printf("inserting element %d at index %d\n", arr.A[i] - key, i); 
		index = key - arr.A[i]; 
		if (index < 0){
			continue; 
		} else {
			temp[index] = index;
		}
	}

	for (int i = 0; i <= high; i++){
		printf("%d ", temp[i]);
	}
	printf("\n");
	for (int i = 0; i < arr.length; i++){
		if (arr.A[i] == temp[index]){
		printf("comparing element arr[%d] + temp[%d] with key %d\n", i, index, key);
			return 1;
		}
	}
	
	free(temp);
	return -1;
}


int main(){
	struct Array arr = {{7, 2, 5, 10, 9, 2}, 6, 10};
	int temp = pairing_ns(arr, 4, 1, 10);
	printf("%d\n", temp);

	return 0;
}
