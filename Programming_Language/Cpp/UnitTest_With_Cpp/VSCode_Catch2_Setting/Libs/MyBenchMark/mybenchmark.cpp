#include <cmath>
#include <mybenchmark.h>
#include <vector>

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