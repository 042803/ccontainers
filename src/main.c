#include "stdio.h"
#include "../include/array.h"

int main(){
	struct Array arr = {{1, 3, 5}, 3, 5};
	struct Array arr2 = {{}, 0,5};
	struct Array* arr3 = dif(&arr, &arr2);
	print(*arr3);
	int temp_length = arr3->length;
	printf("%d\n", temp_length);
	return 0;
}
