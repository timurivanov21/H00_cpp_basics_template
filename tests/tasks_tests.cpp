#include <catch2/catch.hpp>

#include <set>
#include <cmath>
#include <random>
#include <vector>
#include <iterator>
#include <algorithm>

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

        int a = GENERATE(range(-10, 10, 1));
        int b = GENERATE(range(-10, 10, 1));

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

        int *a = new int{GENERATE(range(-10, 10, 1))};
        int *b = new int{GENERATE(range(-10, 10, 1))};

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

    SECTION("swap nullptr variables") {

        int var = GENERATE(range(-10, 10, 2));

        const int var_copy = var;

        swap_args(nullptr, &var);

        CHECK(var == var_copy);

        swap_args(&var, nullptr);

        CHECK(var == var_copy);
    }
}

TEST_CASE("allocate_2d_array testcase") {

    SECTION("allocate 2d array of valid dimensions") {

        const int num_rows = GENERATE(range(1, 10));
        const int num_cols = GENERATE(range(1, 10));

        const int init_value = GENERATE(take(10, random(-100, 100)));

        int **arr = allocate_2d_array(num_rows, num_cols, init_value);

        INFO("Array dimensions: " << num_rows << "x" << num_cols)

        REQUIRE(arr != nullptr);

        for (int row_index = 0; row_index < num_rows; row_index++) {

            INFO("Array at row_index = " << row_index << " is nullptr")

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
            const int num_rows = GENERATE(range(-10, 0));
            const int num_cols = GENERATE(take(100, random(1, 50)));

            const int init_value = GENERATE(values({-1, 0, 1}));

            int **arr = allocate_2d_array(num_rows, num_cols, init_value);

            INFO("Array size is " << num_rows << "x" << num_cols << " with initial value = " << init_value);

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

        const int num_rows = GENERATE(range(1, 10));
        const int num_cols = GENERATE(range(1, 10));

        const auto values = generate_array(num_rows * num_cols, -100, 100);

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

        INFO("Array size is " << num_rows << "x" << num_cols)
        INFO("Source array == nullptr? " << std::boolalpha << (arr == nullptr))
        INFO("Target array == nullptr? " << std::boolalpha << (arr_copy == nullptr))

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

            INFO("Source array == nullptr? " << std::boolalpha << (arr == nullptr))

            CHECK(status == false);

            delete[] arr[0];
            delete[] arr;
        }

        SECTION("nullptr target array") {

            int **arr = nullptr;

            int **arr_copy = new int *[1];
            arr_copy[0] = new int[1]{};

            const bool status = copy_2d_array(arr, arr_copy, 1, 1);

            INFO("Target array == nullptr? " << std::boolalpha << (arr_copy == nullptr))

            CHECK(status == false);

            delete[] arr_copy[0];
            delete[] arr_copy;
        }

        SECTION("invalid array dimensions") {

            const int num_rows = GENERATE(range(-10, 0));
            const int num_cols = GENERATE(range(-10, 0));

            int **arr = new int *[1];
            int **arr_copy = new int *[1];

            arr[0] = new int[1]{};
            arr_copy[0] = new int[1]{};

            const bool status = copy_2d_array(arr, arr_copy, num_rows, num_cols);

            INFO("Array dimensions are " << num_rows << "x" << num_cols)

            CHECK(status == false);

            delete[] arr[0];
            delete[] arr;

            delete[] arr_copy[0];
            delete[] arr_copy;
        }
    }
}

TEST_CASE("reverse_1d_array (vector) testcase") {

    const int size = GENERATE(range(1, 10));

    auto arr = generate_array(size, -100, 100);

    auto arr_copy = arr;

    reverse_1d_array(arr);

    CHECK(arr.size() == arr_copy.size());

    for (int index = 0; index < arr.size(); index++) {
        CHECK(arr[index] == arr_copy[arr_copy.size() - index - 1]);
    }
}

TEST_CASE("reverse_1d_array (pointers) testcase") {

    SECTION("valid array pointers") {

        const int size = GENERATE(range(1, 10));

        auto arr = generate_array(size, -100, 100);
        auto arr_copy = arr;

        reverse_1d_array(arr.data(), arr.data() + size - 1);

        CHECK(arr.size() == arr_copy.size());

        for (int index = 0; index < arr.size(); index++) {
            CHECK(arr[index] == arr_copy[arr_copy.size() - index - 1]);
        }
    }

    SECTION("invalid array pointers") {
        reverse_1d_array(nullptr, nullptr);  // should not fail
    }

}

TEST_CASE("find_max_element testcase") {

    SECTION("passing a valid array") {

        const int size = GENERATE(range(1, 10));
        const int max_index = GENERATE_COPY(take(50, random(0, size - 1)));
        const int max_value = GENERATE(range(-50, 50, 10));

        auto arr = generate_array(size, -100, max_value);

        arr.at(max_index) = max_value;

        int *max_element = find_max_element(arr.data(), arr.size());

        REQUIRE(max_element != nullptr);
        CHECK(*max_element == max_value);
    }

    SECTION("passing nullptr array") {

        const int size = GENERATE(range(0, 10));

        int *max_element = find_max_element(nullptr, size);

        INFO("Array iss nullptr? " << true)

        CHECK(max_element == nullptr);
    }

    SECTION("passing negative array size") {

        const int size = GENERATE(range(-10, 0));

        std::vector<int> arr(3, 0);

        int *max_element = find_max_element(arr.data(), size);

        INFO("Array size is " << size)

        CHECK(max_element == nullptr);
    }
}

TEST_CASE("find_odd_numbers testcase") {
    using Catch::Matchers::Equals;

    const int size = GENERATE(range(1, 50, 3));

    auto arr = generate_array(size, -100, 100);

    auto odd_numbers_ref = std::vector<int>{};
    odd_numbers_ref.reserve(arr.size());

    for (int element: arr) {
        if (std::abs(element) % 2 == 1) {
            odd_numbers_ref.push_back(element);
        }
    }

    const auto odd_numbers = find_odd_numbers(arr);

    CHECK_THAT(odd_numbers, Equals(odd_numbers_ref));
}

TEST_CASE("find_common_elements testcase") {
    using Catch::Matchers::UnorderedEquals;

    const int arr_a_size = GENERATE(range(1, 50, 5));
    const int arr_b_size = GENERATE(range(1, 50, 5));

    auto arr_a = generate_array(arr_a_size, -100, 100);
    auto arr_b = generate_array(arr_b_size, -100, 100);

    auto set_a = std::set<int>(arr_a.begin(), arr_a.end());
    auto set_b = std::set<int>(arr_b.begin(), arr_b.end());

    auto common_elements_ref = std::vector<int>{};
    common_elements_ref.reserve(std::max(set_a.size(), set_b.size()));

    std::set_intersection(set_a.begin(), set_a.end(),
                          set_b.begin(), set_b.end(),
                          std::back_inserter(common_elements_ref));

    const auto common_elements = find_common_elements(arr_a, arr_b);

    // remove duplicates
    const auto common_elements_set = std::set<int>(common_elements.cbegin(), common_elements.cend());

    // convert back to vector
    const auto elements = std::vector<int>(common_elements_set.begin(), common_elements_set.end());

    // check for equality under permutation
    CHECK_THAT(elements, UnorderedEquals(common_elements_ref));
}
