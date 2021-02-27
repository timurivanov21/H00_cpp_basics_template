#pragma once

#include <vector>

using std::vector;

// объявление функций

// Задание 1
void swap_args(int *lhs, int *rhs);

// Задание 2
int **allocate_2d_array(int num_rows, int num_cols, int init_value);

// Задание 3
bool copy_2d_array(int **arr_2d_source, int **arr_2d_target, int num_rows, int num_cols);

// Задание 4
void reverse_1d_array(vector<int> &arr);

// Задание 5
void reverse_1d_array(int *arr_begin, int *arr_end);

// Задание 6
int *find_max_element(int *arr, int size);

// Задание 7
vector<int> find_odd_numbers(vector<int> &arr);

// Задание 8
vector<int> find_common_elements(vector<int> &arr_a, vector<int> &arr_b);
