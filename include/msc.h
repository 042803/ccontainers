#ifndef MSC_H
#define MSC_H

#include "array.h"
#include <limits.h>

#define FLAGGED INT_MAX
#define SHOULD_COMPACT(arr) ((arr)->flagged_count >= (arr)->length / 4)

void compact(struct Array* arr);
bool equals_not_sorted(struct Array* a, struct Array* b);
bool equals(const struct Array* a, const struct Array* b); 
void pop_flagged(struct Array* arr);
bool remove_value(struct Array* arr, int value); 
struct Array slice(const struct Array* arr, int start, int end); 

#endif 
