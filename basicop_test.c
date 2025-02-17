#include "array.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "stdio.h"
#include "string.h"

char* capture_output(void (*func)(struct Array), struct Array arr) {
    	static char buffer[100]; // Buffer to store the output
    	freopen("output.txt", "w", stdout); // Redirect stdout to a file
    	func(arr); // Call the function
    	fflush(stdout); // Flush the output
    	freopen("/dev/tty", "w", stdout); // restore stdout

    	FILE* file = fopen("output.txt", "r");
	fgets(buffer, sizeof(buffer), file);
	fclose(file);

	return buffer;
}

void test_print(){
	struct Array arr1 = {{1, 2, 3, 4, 5}, 5, 10};
	struct Array arr2 = {{10, 15, 20, 25, 30}, 5, 10};
	struct Array arr3 = {{-1, -2, -3, -4, -5}, 5, 10};

	char* output1 = capture_output(print, arr1);
	CU_ASSERT_STRING_EQUAL(output1, "1 2 3 4 5 \n");

	char* output2 = capture_output(print, arr2);
	CU_ASSERT_STRING_EQUAL(output2, "10 15 20 25 30 \n");

	char* output3 = capture_output(print, arr3);
	CU_ASSERT_STRING_EQUAL(output3, "-1 -2 -3 -4 -5 \n");
}

int main(){
	if (CU_initialize_registry() != CUE_SUCCESS){
		return CU_get_error();
	}
	
	CU_pSuite suite = CU_add_suite("Test Suite", NULL, NULL);
	if (suite == NULL){
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (CU_add_test(suite, "Test of print function", test_print) == NULL) {
	        CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();

	return CU_get_error();
}
