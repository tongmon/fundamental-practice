#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "mylib.h"

unsigned int factorial(unsigned int n) {
    return n <= 1 ? n : n * factorial(n - 1);
}

TEST_CASE("Factorials are computed", "[factorial]") {
    REQUIRE(factorial(1) == 1);
    REQUIRE(factorial(2) == 2);
    REQUIRE(factorial(3) == 6);
    REQUIRE(factorial(10) == 3628800);
}