#include <iostream>   // cout
#include <algorithm>  // copy, fill

#include "tasks.hpp"

// ИСПОЛЬЗОВАНИЕ ЛЮБЫХ ДРУГИХ БИБЛИОТЕК НЕ СОВЕТУЕТСЯ И МОЖЕТ ПОВЛИЯТЬ НА ВАШИ БАЛЛЫ

using std::cout;
using std::fill;
using std::copy;

// Задание 1
void swap_args(int *lhs, int *rhs) {
    if (lhs and rhs) {
        int t = *lhs;
        *lhs = *rhs;
        *rhs = t;
    }

}

// Задание 2
int **allocate_2d_array(int num_rows, int num_cols, int init_value) {
    if ((num_rows < 0) || (num_cols < 0)) {
        return nullptr;
    }
    // Объявление
    int **arr = new int *[num_rows];
    if (num_rows > 0 && num_cols > 0) {
        for (int i = 0; i < num_rows; i++) {
            arr[i] = new int[num_cols];
        }
    } else {
        return nullptr;
    }
    // Заполнение
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            arr[i][j] = init_value;
        }
    }

    return arr;
}

// Задание 3
bool copy_2d_array(int **arr_2d_source, int **arr_2d_target, int num_rows, int num_cols) {
    if ((num_rows > 0) && (num_cols > 0) && (arr_2d_source != nullptr) && (arr_2d_target != nullptr)) {
        for (int i = 0; i < num_rows; i++) {
            for (int j = 0; j < num_cols; j++) {
                arr_2d_target[i][j] = arr_2d_source[i][j];
            }
        }
        return true;
    }
    return false;
}

// Задание 4
void reverse_1d_array(vector<int> &arr) {
    for (int i = 0; i < arr.size() / 2; i++) {
        int t = arr[i];
        arr[i] = arr[arr.size() - i - 1];
        arr[arr.size() - i - 1] = t;
    }

}

// Задание 5
void reverse_1d_array(int *arr_begin, int *arr_end) {
    if ((arr_begin != nullptr) && (arr_end != nullptr)) {
        for (int i = 0; i < (arr_end - arr_begin + 1) / 2; i++) {
            int t = *(arr_begin + i);
            *(arr_begin + i) = *(arr_end - i);
            *(arr_end - i) = t;
        }
    }
}

// Задание 6
int *find_max_element(int *arr, int size) {
    if ((arr != nullptr) && (size > 0)) {
        int *max_value = arr;
        for (int i = 0; i < size; i++) {
            if (*(arr + i) > *max_value) {
                *max_value = *(arr + i);
            }
        }
        return max_value;
    }

    return nullptr;
}

// Задание 7
vector<int> find_odd_numbers(vector<int> &arr) {
    vector<int> my_arr;
    for (int i = 0; i < arr.size(); i++) {
        if (abs(arr[i]) % 2 == 1) {
            my_arr.push_back(arr[i]);
        }
    }
    return my_arr;
}

// Задание 8
vector<int> find_common_elements(vector<int> &arr_a, vector<int> &arr_b) {
    vector<int> my_arr;
    for (int i = 0; i < arr_a.size(); i++) {
        for (int j = 0; j < arr_b.size(); j++) {
            if ((arr_a[i]) == (arr_b[j])) {
                my_arr.push_back(arr_a[i]);
            }
        }
    }
    return my_arr;
}
