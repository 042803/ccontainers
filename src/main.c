#include "stdio.h"
#include "../include/array.h"
#include "../include/array_utils.h"
#include "../include/search.h"
#include "../include/math.h"
#include "../include/binop.h"
#include "../include/msc.h"
#include "../include/algo.h"

int main(){
    struct Array arr1 = init(10);
    for (int i = arr1.size; i > 0; --i){
        push_back(&arr1, i); 
    }    
    print(&arr1);

    quick_sort(&arr1); 
    print(&arr1);


    return 0; 
}
