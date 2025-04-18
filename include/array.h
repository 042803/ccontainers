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
    size_t flagged_count;
};

#define ARR_MIN_SIZE 4

// CORE

bool array_resize(struct Array* arr, size_t new_size);
bool emplace_at(struct Array* arr, int index, int elt);
void fill(struct Array* arr, int elt); 
void free_arr(struct Array* arr);
int get(const struct Array* arr, int index);
struct Array init(size_t initial_size);
struct Array init_from_array(const int* values, size_t length);
void print(const struct Array* arr);
bool push_back(struct Array* arr, int elt);
bool remove_at(struct Array* arr, int index);
void set(struct Array* arr, int index, int elt);
bool shrink(struct Array* arr);

// write and load from file

#endif
