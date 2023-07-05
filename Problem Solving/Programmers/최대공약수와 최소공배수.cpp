#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12940
최대공약수, 최소공배수 다시 기억할 겸, 숏코딩 실력 늘릴겸 풀었다.
삼항연산자에서 void를 비교하게 될 때는 void() 이렇게 void형을 쓰면 된다.
*/

int gcd(int n, int m) {
	return m ? gcd(m, n % m) : n;
}

vector<int> solution(int n, int m) {
	m > n ? swap(n, m) : void();
	int k;
	return { k = gcd(n, m), n * m / k };
}