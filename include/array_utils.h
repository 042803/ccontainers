#ifndef ARRAY_INTERNAL_H
#define ARRAY_INTERNAL_H

#include <stddef.h>
#include "array.h"

// Internal helpers
void cpy(int* dest, const int* src, size_t length);
bool resize_to(struct Array* arr, size_t new_size);
void swap(int* a, int* b);
bool internal_resize(struct Array* arr);

#endif

