#pragma once

#include <vector>

using std::vector;

// объявление функций

void swap_args(int *lhs, int *rhs);

int *allocate_1d_array(int size);

int **allocate_2d_array(int num_rows, int num_cols, int init_value);

void deallocate_1d_array(int *arr);

void deallocate_2d_array(int **arr_2d, int num_rows);

bool copy_2d_array(int **arr_2d_source, int **arr_2d_target, int num_rows, int num_cols);

void reverse_array(vector<int> &arr);

void reverse_array(int *arr_begin, int *arr_end);

void print_each_nth_element(int *arr, int size, int n);

