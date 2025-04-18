#ifndef MSC_H
#define MSC_H

#include "array.h"

void compact(struct Array* arr);
bool equals_not_sorted(struct Array* a, struct Array* b);
bool equals(const struct Array* a, const struct Array* b); 
void pop_flagged(struct Array* arr);
void remove_elt(struct Array* arr, int elt); 
struct Array slice(const struct Array* arr, int start, int end); 

#endif 
