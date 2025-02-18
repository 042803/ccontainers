#include "stdio.h"
#include "../include/array.h"

int main(){
	struct Array arr = {{2, 4, 6, 8}, 4, 10};
	struct Array arr2 = {{1, 3, 5, 7}, 4, 10};
	struct Array* arr3 = merge(&arr, &arr2);
	print(*arr3);
	struct Array arr4 = {{}, 0, 10};
	struct Array* arr5 = merge(&arr, &arr4);
	int temp = arr3->length;
	int temp2 = arr5->length;
	printf("%d\n%d\n", temp, temp2);

	return 0;
}
