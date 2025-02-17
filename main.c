#include "stdio.h"
#include "array.h"

int main(){
	struct Array arr = {{1, 2, 3, 4, 5}, 5, 10};
	struct Array arr2 = {{6, 7, 8, 9, 10}, 5, 10};
	struct Array* arr3 = un(&arr, &arr2);
	print(*arr3);

	return 0;
}
