#include <catch2/catch_all.hpp>

#include <mymath.h>

// 팩토리얼 함수 테스팅...
// 첫번째 케이스에서 오류라고 Catch2는 판단하여 터미널창에 정보를 띄울 것이다.
TEST_CASE("Factorials are computed", "[factorial]") {
    REQUIRE(factorial(0) == 1);
    REQUIRE(factorial(3) == 6);
    REQUIRE(factorial(10) == 3628800);
}

// 소수 판정 함수 테스팅...
// 두번째 케이스에서 오류라고 Catch2는 판단하여 터미널창에 정보를 띄울 것이다.
TEST_CASE("Primes are computed", "[is_prime]") {
    REQUIRE(is_prime(3) == true);
    REQUIRE(is_prime(4) == false);
    REQUIRE(is_prime(7) == true);
    REQUIRE(is_prime(21341479) == true);
}