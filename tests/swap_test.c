#include "../include/array.h"
#include "../src/array.c"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void swap(int*a, int* b);

void test_swap(){
	int a, b;
	
	a = 5;
	b = 10;
	swap(&a, &b);
	CU_ASSERT_EQUAL(a, 10);
	CU_ASSERT_EQUAL(b, 5);
	
	a = 7;
	b = -7;
	swap(&a, &b); 
	CU_ASSERT_EQUAL(a, -7);
	CU_ASSERT_EQUAL(b, 7);

	
 	a = -2;
    	b = -8;
    	swap(&a, &b);
    	CU_ASSERT_EQUAL(a, -8);
    	CU_ASSERT_EQUAL(b, -2);

   	a = 4;
        b = 4;
        swap(&a, &b);
   	CU_ASSERT_EQUAL(a, 4);
  	CU_ASSERT_EQUAL(b, 4);
}

int main(){

	if (CU_initialize_registry() != CUE_SUCCESS) {
        	return CU_get_error();
    	}

    	CU_pSuite suite = CU_add_suite("Swap Test Suite", NULL, NULL);
    	if (suite == NULL) {
        	CU_cleanup_registry();
        	return CU_get_error();
    	}	

    
    	if (CU_add_test(suite, "Test of swap function", test_swap) == NULL) {
        	CU_cleanup_registry();
        	return CU_get_error();
    	}
    
    	CU_basic_set_mode(CU_BRM_VERBOSE);
    	CU_basic_run_tests();
    	CU_cleanup_registry();

    	return CU_get_error();

}

