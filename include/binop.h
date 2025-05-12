#ifndef BINOP_H
#define BINOP_H

#include "array.h"

void append(struct Array* dst, const struct Array* src); 
struct Array array_difference(const struct Array* arr1, const struct Array* arr2);
struct Array array_intersection(const struct Array* arr1, const struct Array* arr2);
struct Array array_merge(const struct Array* arr1, const struct Array* arr2);
struct Array array_union(const struct Array* arr1, const struct Array* arr2);

#endif




