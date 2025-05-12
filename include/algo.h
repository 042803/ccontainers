#ifndef ALGO_H
#define ALGO_H

#include "array.h"
#include "comparators.h"

void merge_sort(struct Array* arr);
void quick_sort(struct Array* arr);
void merge_sort_cmp(struct Array* arr, comparator_fn cmp);
void quick_sort_cmp(struct Array* arr, comparator_fn cmp);
void array_reverse(struct Array* arr);
int shift(struct Array* arr);

#endif
