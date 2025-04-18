#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

struct Array {
	int *A;
	size_t length;
	size_t size;
};

#define ARR_MIN_SIZE 4




struct Array init(size_t initial_size);
struct Array init_from_array(const int* values, size_t length);
bool array_resize(struct Array* arr, size_t new_size);
bool shrink(struct Array* arr);
void free_arr(struct Array* arr);
void print(const struct Array* arr);
bool push_back(struct Array* arr, int elt);
bool emplace_at(struct Array* arr, int index, int elt);
bool remove_at(struct Array* arr, int index);
int linear_search(struct Array* arr, int key);
int binary_search(const struct Array* arr, int key);
int get(const struct Array* arr, int index);
void set(struct Array* arr, int index, int elt);
int max(const struct Array* arr);
int min(const struct Array* arr);
int avg(const struct Array* arr);
void reverse(struct Array* arr);
int shift(struct Array* arr);
bool is_sorted(const struct Array* arr);
struct Array merge(const struct Array* arr1, const struct Array* arr2);
struct Array un(const struct Array* arr1, const struct Array* arr2);
struct Array in(const struct Array* arr1, const struct Array* arr2);
struct Array dif(const struct Array* arr1, const struct Array* arr2);
void quick_sort(struct Array* arr);
void merge_sort(struct Array* arr);
#endif
