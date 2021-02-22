#include <catch2/catch.hpp>

#include "tasks.hpp"

SCENARIO("Demo") {

    GIVEN("Pointers to local variables") {
        WHEN("1") {
            THEN("2") {
                int a = 0;
                int b = 5;

                swap_args(&a, &b);

                CHECK(a == 5);
                CHECK(b == 0);
            }
        }
    }
}