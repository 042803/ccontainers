#ifndef ARRAY_INTERNAL_H
#define ARRAY_INTERNAL_H

#include <stddef.h>
#include "array.h"

// Internal helpers


void cpy(int* dest, const int* src, size_t length);
bool resize_to(struct Array* arr, size_t new_size);
void swap(int* a, int* b);
bool internal_resize(struct Array* arr);
int internal_partition(struct Array* arr, int low, int high);
void internal_quicksort(struct Array* arr, int low, int high);
void internal_merge(struct Array* arr, int low, int mid, int high);
void internal_merge_sort(struct Array* arr, int low, int high);

#endif

