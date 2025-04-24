#ifndef SEARCH_H
#define SEARCH_H

#include "array.h"
#include "comparators.h"

int binary_search(const struct Array* arr, int key);
int c_binary_search(const struct Array* arr, int key, comparator_fn cmp);
bool contains(const struct Array* arr, int key);
bool c_contains(const struct Array* arr, int key, comparator_fn cmp);
int linear_search(struct Array* arr, int key);
int c_linear_search(struct Array* arr, int key, comparator_fn cmp);

#endif
