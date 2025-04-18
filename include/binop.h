#ifndef BINOP_H
#define BINOP_H

#include "array.h"

void append(struct Array* dst, const struct Array* src); 
struct Array dif(const struct Array* arr1, const struct Array* arr2);
struct Array in(const struct Array* arr1, const struct Array* arr2);
struct Array merge(const struct Array* arr1, const struct Array* arr2);
struct Array un(const struct Array* arr1, const struct Array* arr2);

#endif




