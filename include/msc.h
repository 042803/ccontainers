#ifndef MSC_H
#define MSC_H

#include "array.h"
#include <limits.h>

#define FLAGGED INT_MAX
#define SHOULD_COMPACT(arr) ((arr)->flagged_count >= (arr)->length / 4)

void compact(struct Array* arr);
bool array_equals_not_sorted(struct Array* a, struct Array* b);
bool array_equals(const struct Array* a, const struct Array* b); 
void array_pop_flagged(struct Array* arr);
bool array_remove_value(struct Array* arr, int value); 
struct Array array_slice(const struct Array* arr, int start, int end); 

#endif 
