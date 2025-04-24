#ifndef ALGO_H
#define ALGO_H

#include "array.h"
#include "comparators.h"

void merge_sort(struct Array* arr);
void quick_sort(struct Array* arr);
void c_merge_sort(struct Array* arr, comparator_fn cmp);
void c_quick_sort(struct Array* arr, comparator_fn cmp);
void reverse(struct Array* arr);
int shift(struct Array* arr);

#endif
