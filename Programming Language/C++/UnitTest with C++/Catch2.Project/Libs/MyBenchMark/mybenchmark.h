#ifndef __MYBENCHMARK_H__
#define __MYBENCHMARK_H__

// 일반적인 소수 판별 함수
bool is_prime_01(unsigned int n);

// 에라토스테네스의 체를 이용한 소수 판별 함수
// 다수의 소수 판별을 진행할 때 효과적임, 첫 계산시 is_prime_01 함수보다 느림
bool is_prime_02(unsigned int n, unsigned int max = 500000000);

#endif // __MYBENCHMARK_H__