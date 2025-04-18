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
void free_arr(struct Array* arr);
void print(struct Array arr);
void push_back(struct Array* arr, int elt);
void emplace_at(struct Array* arr, int index, int elt);

// things to work on later
int remove_at(struct Array* arr, int index);
int linear_search(struct Array* arr, int key);
int binary_search(struct Array arr, int key);
int get(struct Array arr, int index);
void set(struct Array* arr, int index, int elt);
int max(struct Array arr);
int min(struct Array arr);
int avg(struct Array arr);
void reverse(struct Array* arr);
int shift(struct Array* arr);
bool is_sorted(struct Array arr);
struct Array* merge(struct Array* arr1, struct Array* arr2);
struct Array* un(struct Array* arr1, struct Array* arr2);
struct Array* in(struct Array* arr1, struct Array* arr2);
struct Array* dif(struct Array* arr1, struct Array* arr2);

#endif
