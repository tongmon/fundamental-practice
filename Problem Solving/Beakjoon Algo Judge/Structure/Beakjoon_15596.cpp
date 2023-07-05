#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/15596
함수 구현 문제...
main 없이 함수만 구현하는 문제가 있길래 풀어봤다.
*/

long long sum(std::vector<int>& a)
{
	long long k = 0;
	for (const auto& n : a)
		k += n;
	return k;
}