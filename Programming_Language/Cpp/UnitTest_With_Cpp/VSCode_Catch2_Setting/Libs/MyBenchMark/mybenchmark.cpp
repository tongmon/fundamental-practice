#include <cmath>
#include <mybenchmark.h>
#include <vector>

// 일반적인 소수 판별 함수
bool is_prime_01(unsigned int n) {
    if (n <= 1)
        return false;
    if (!(n % 2))
        return n == 2;
    for (int i = 3; i <= sqrt(n); i += 2)
        if (!(n % i))
            return false;
    return true;
}

// 에라토스테네스의 체를 이용한 소수 판별 함수
// 다수의 소수 판별을 진행할 때 효과적임, 첫 계산시 is_prime_01 함수보다 느림
bool is_prime_02(unsigned int n, unsigned int max) {
    static std::vector<bool> primes;

    if (primes.size() < max) {
        primes.resize(max + 1);
        primes[0] = primes[1] = true;
        primes[2] = false;
        for (int i = 4; i <= max; i += 2)
            primes[i] = true;
        for (int i = 3; i <= sqrt(max); i += 2) {
            if (primes[i])
                continue;
            for (int j = i * i; j <= max; j += i)
                primes[j] = true;
        }
    }
    return !primes[n];
}