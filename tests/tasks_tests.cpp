#include <catch2/catch.hpp>

#include <random>
#include <vector>

#include "tasks.hpp"

vector<int> generate_array(int size, int start_value, int end_value) {
    std::random_device rand_dev;

    std::vector<int> values(size, 0);

    // generate random values for 2d array
    std::mt19937 rand_engine{rand_dev()};
    std::uniform_int_distribution<int> dist{start_value, end_value};

    for (int &value : values) {
        value = dist(rand_engine);
    }

    return values;
}

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

        const int num_rows = GENERATE(take(10, random(1, 10)));
        const int num_cols = GENERATE(take(10, random(1, 10)));
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
            const int num_cols = GENERATE(take(10, random(1, 10)));
            const int init_value = GENERATE(values({-1, 0, 1}));

            int **arr = allocate_2d_array(num_rows, num_cols, init_value);

            REQUIRE(arr == nullptr);
        }

        SECTION("invalid number of columns") {
            const int num_rows = GENERATE(take(10, random(1, 10)));
            const int num_cols = GENERATE(values({-5, -1, 0}));
            const int init_value = GENERATE(values({-1, 0, 1}));

            int **arr = allocate_2d_array(num_rows, num_cols, init_value);

            REQUIRE(arr == nullptr);
        }
    }
}

TEST_CASE("copy_2d_array testcase") {

    SECTION("copy of valid 2d array") {

        const int num_rows = GENERATE(take(10, random(1, 10)));
        const int num_cols = GENERATE(take(10, random(1, 10)));

        const auto values = generate_array(num_rows * num_cols, -10, 10);

        // init test arrays
        int **arr = new int *[num_rows];
        int **arr_copy = new int *[num_rows];

        int arr_index = 0;

        for (int row_index = 0; row_index < num_rows; row_index++) {

            arr[row_index] = new int[num_cols]{};
            arr_copy[row_index] = new int[num_cols]{};

            for (int col_index = 0; col_index < num_cols; col_index++) {

                arr[row_index][col_index] = values[arr_index];
                arr_index++;
            }
        }

        const bool status = copy_2d_array(arr, arr_copy, num_rows, num_cols);

        CHECK(status == true);

        for (int row_index = 0; row_index < num_rows; row_index++) {
            for (int col_index = 0; col_index < num_cols; col_index++) {

                CHECK(arr[row_index][col_index] == arr_copy[row_index][col_index]);
            }
        }

        // cleanup
        for (int row_index = 0; row_index < num_rows; row_index++) {
            delete[] arr[row_index];
            delete[] arr_copy[row_index];
        }

        delete[] arr;
        delete[] arr_copy;
    }

    SECTION("copy of invalid 2d array") {

        SECTION("nullptr source array") {

            int **arr = new int *[1];
            arr[0] = new int[1]{};

            int **arr_copy = nullptr;

            const bool status = copy_2d_array(arr, arr_copy, 1, 1);

            CHECK(status == false);

            delete[] arr[0];
            delete[] arr;
        }

        SECTION("nullptr target array") {

            int **arr = nullptr;

            int **arr_copy = new int *[1];
            arr_copy[0] = new int[1]{};

            const bool status = copy_2d_array(arr, arr_copy, 1, 1);

            CHECK(status == false);

            delete[] arr_copy[0];
            delete[] arr_copy;
        }
    }
}

TEST_CASE("reverse_1d_array (vector) testcase") {

    const int size = GENERATE(take(100, random(1, 100)));

    auto arr = generate_array(size, -10, 10);

    auto arr_copy = arr;

    reverse_1d_array(arr);

    CHECK(arr.size() == arr_copy.size());

    for (int index = 0; index < arr.size(); index++) {
        CHECK(arr[index] == arr_copy[arr_copy.size() - index - 1]);
    }
}

TEST_CASE("reverse_1d_array (pointers) testcase") {

    const int size = GENERATE(take(100, random(1, 100)));

    auto arr = generate_array(size, -10, 10);
    auto arr_copy = arr;

    reverse_1d_array(arr.data(), arr.data() + size - 1);

    CHECK(arr.size() == arr_copy.size());

    for (int index = 0; index < arr.size(); index++) {
        CHECK(arr[index] == arr_copy[arr_copy.size() - index - 1]);
    }
}

TEST_CASE("find_max_element testcase") {

    SECTION("passing a valid array") {

        const int size = GENERATE(take(3, random(1, 100)));
        const int max_index = GENERATE_COPY(take(3, random(0, size)));

        const int max_value = GENERATE(take(3, random(10, 100)));

        auto arr = generate_array(size, -100, max_value);

        // set max element
        arr[max_index] = max_value;

        int *max_element = find_max_element(arr.data(), arr.size());

        REQUIRE(max_element != nullptr);
        CHECK(*max_element == max_value);
    }

    SECTION("passing nullptr array") {

        int *max_element = find_max_element(nullptr, 10);

        CHECK(max_element == nullptr);
    }

    SECTION("passing negative array size") {

        const int size = GENERATE(values({-100, -10, -1, 0}));

        std::vector<int> arr(3, 0);

        int *max_element = find_max_element(arr.data(), size);

        CHECK(max_element == nullptr);
    }
}

TEST_CASE("find_odd_numbers testcase") {
    using Catch::Matchers::Equals;

    const int size = GENERATE(take(10, random(1, 100)));

    auto arr = generate_array(size, -100, 100);

    auto odd_numbers_ref = std::vector<int>{};
    odd_numbers_ref.reserve(arr.size());

    for (int element: arr) {
        if (element % 2 == 1) {
            odd_numbers_ref.push_back(element);
        }
    }

    const auto odd_numbers = find_odd_numbers(arr);

    CHECK_THAT(odd_numbers, Equals(odd_numbers_ref));
}

