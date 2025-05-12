#include "stdio.h"
#include "../include/vector.h"

int main() {
    struct Array arr = array_init(10);
    for (int i = 0; i < 10; ++i) push_back(&arr, 18 - i * 2);   
    int idx = array_binary_search_cmp(&arr, 12, cmp_descending);
    bool exists = array_contains_cmp(&arr, 20, cmp_descending);
    
    printf("idx = %d\nexists = %b\n", idx, exists);
    printf("Finishing properly!\n");
    return 0;
}

