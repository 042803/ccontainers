#include "stdio.h"
#include "../include/vector.h"

int main() {

    struct Array arr = init(5);
    printf("Size : %zu\nLength : %zu\nFlagged Count : %zu\n", arr.size, arr.length, arr.flagged_count);
    
    for (int i = 0; i < arr.size; i++){
        push_back(&arr, i * 7);
    }

    printf("arr : ");
    print(&arr);

    int idx = linear_search(&arr, 28);
    printf("index of 28 is : %d\n", idx);
    
    printf("arr after set_all() : ");
    set_all(&arr, 65);
    print(&arr);
   
    free_arr(&arr);
    
    printf("Finishing properly!\n");
    return 0;
}

