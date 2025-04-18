#include "../include/array.h"
#include "../src/array.c"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <string.h>

void print(struct Array arr);

char* capture_output(void (*func)(struct Array), struct Array arr) {
    static char buffer[100];

    freopen("output.txt", "w", stdout);
    func(arr);
    fflush(stdout);
    freopen("CON", "w", stdout);  

    FILE* file = fopen("output.txt", "r");
    if (file) {
        fgets(buffer, sizeof(buffer), file);
        fclose(file);
    }

    return buffer;
}

void test_print() {
    struct Array arr1 = {{1, 2, 3, 4, 5}, 5, 10};
    struct Array arr2 = {{10, 15, 20, 25, 30}, 5, 10};
    struct Array arr3 = {{-1, -2, -3, -4, -5}, 5, 10};
    struct Array arr4 = {{}, 0, 10};

    
    CU_ASSERT_STRING_EQUAL(capture_output(print, arr1), "1 2 3 4 5 \n");
    CU_ASSERT_STRING_EQUAL(capture_output(print, arr2), "10 15 20 25 30 \n");
    CU_ASSERT_STRING_EQUAL(capture_output(print, arr3), "-1 -2 -3 -4 -5 \n");
    CU_ASSERT_STRING_EQUAL(capture_output(print, arr4), "\n");	    
	
}

int main() {
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    CU_pSuite suite = CU_add_suite("Test Suite", NULL, NULL);
    if (!suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (!CU_add_test(suite, "Test of print function", test_print)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}
