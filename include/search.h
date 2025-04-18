#ifndef SEARCH_H
#define SEARCH_H

#include "array.h"

int binary_search(const struct Array* arr, int key);
bool contains(const struct Array* arr, int key);
int linear_search(struct Array* arr, int key);

#endif
