#include <catch2/catch.hpp>

#include "tasks.hpp"

TEST_CASE("swap_args testcase") {

    SECTION("swap stack variables") {
        int a = GENERATE(values({-10, -5, 0, 1, 3, 512}));
        int b = GENERATE(values({-11, -3, 0, 2, 7, 361}));

        const int prev_a = a;
        const int prev_b = b;

        swap_args(&a, &b);

        CHECK(a == prev_b);
        CHECK(b == prev_a);
    }
}