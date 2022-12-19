#include <catch2/catch_all.hpp>
#include <mybenchmark.h>

TEST_CASE("Prime Checking with is_prime_01") {
    BENCHMARK("Prime 20") { return is_prime_01(20); };
    BENCHMARK("Prime 3103") { return is_prime_01(3103); };
    BENCHMARK("Prime 21341479") { return is_prime_01(21341479); };
    BENCHMARK("Prime 429496709") { return is_prime_01(429496709); };
}

TEST_CASE("Prime Checking with is_prime_02") {
    BENCHMARK("Prime 20") { return is_prime_02(20); };
    BENCHMARK("Prime 3103") { return is_prime_02(3103); };
    BENCHMARK("Prime 21341479") { return is_prime_02(21341479); };
    BENCHMARK("Prime 429496709") { return is_prime_02(429496709); };
}