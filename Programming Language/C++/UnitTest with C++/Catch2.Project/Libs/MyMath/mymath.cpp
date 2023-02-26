#include <cmath>
#include <mymath.h>

// 해당 팩토리얼 함수는 0인 경우 잘못된 값을 반환함
unsigned int factorial(unsigned int n) {
    return n <= 1 ? n : n * factorial(n - 1);

    // 밑은 올바른 구현
    // return n <= 1 ? 1 : n * factorial(n - 1);
}

// 해당 소수 판정 함수는 짝수를 소수로 판단함
bool is_prime(int n) {
    if (n <= 1)
        return false;

    if (!(n % 2))
        return true;

    // 밑은 올바른 구현
    // if (!(n % 2))
    //     return n == 2;

    for (int i = 3; i <= sqrt(n); i += 2)
        if (!(n % i))
            return false;
    return true;
}