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