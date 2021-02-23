#include <catch2/catch.hpp>

#include "tasks.hpp"

TEST_CASE("swap_args testcase") {

    SECTION("swap forth and back stack variables") {

        int a = GENERATE(range(-10, 10, 3));
        int b = GENERATE(range(-10, 10, 3));

        const int a_copy = a;
        const int b_copy = b;

        swap_args(&a, &b);  // swap

        CHECK(a == b_copy);
        CHECK(b == a_copy);

        swap_args(&a, &b);  // swap back

        CHECK(a == a_copy);
        CHECK(b == b_copy);
    }

    SECTION("swap forth and back heap variables") {

        int *a = new int{GENERATE(range(-10, 10, 3))};
        int *b = new int{GENERATE(range(-10, 10, 3))};

        const int a_copy = *a;
        const int b_copy = *b;

        swap_args(a, b);

        CHECK(*a == b_copy);
        CHECK(*b == a_copy);

        swap_args(a, b);

        CHECK(*a == a_copy);
        CHECK(*b == b_copy);

        delete a;
        delete b;
    }
}

TEST_CASE("allocate_2d_array testcase") {

    SECTION("allocate 2d array of valid dimensions") {

        const int num_rows = GENERATE(take(5, random(1, 10)));
        const int num_cols = GENERATE(take(5, random(1, 10)));
        const int init_value = GENERATE(values({-1, 0, 1}));

        int **arr = allocate_2d_array(num_rows, num_cols, init_value);

        REQUIRE(arr != nullptr);

        for (int row_index = 0; row_index < num_rows; row_index++) {
            REQUIRE(arr[row_index] != nullptr);

            for (int col_index = 0; col_index < num_cols; col_index++) {
                CHECK(arr[row_index][col_index] == init_value);
            }
        }

        // cleanup
        for (int row_index = 0; row_index < num_rows; row_index++) {
            delete[] arr[row_index];
        }

        delete[] arr;
    }

    SECTION("allocate 2d array of invalid dimensions") {

        SECTION("invalid number of rows") {
            const int num_rows = GENERATE(values({-5, -1, 0}));
            const int num_cols = GENERATE(take(5, random(1, 10)));
            const int init_value = GENERATE(values({-1, 0, 1}));

            int **arr = allocate_2d_array(num_rows, num_cols, init_value);

            REQUIRE(arr == nullptr);
        }

        SECTION("invalid number of columns") {
            const int num_rows = GENERATE(take(5, random(1, 10)));
            const int num_cols = GENERATE(values({-5, -1, 0}));
            const int init_value = GENERATE(values({-1, 0, 1}));

            int **arr = allocate_2d_array(num_rows, num_cols, init_value);

            REQUIRE(arr == nullptr);
        }
    }
}

