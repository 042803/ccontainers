#ifndef SEARCH_H
#define SEARCH_H

#include "array.h"
#include "comparators.h"

int array_binary_search(const struct Array* arr, int key);
int array_binary_search_cmp(const struct Array* arr, int key, comparator_fn cmp);
bool array_contains(const struct Array* arr, int key);
bool array_contains_cmp(const struct Array* arr, int key, comparator_fn cmp);
int array_linear_search(struct Array* arr, int key);
int array_linear_search_cmp(struct Array* arr, int key, comparator_fn cmp);

#endif
