#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/77885
2개 이하로 다른 비트 문제.
비트 연산을 해도 되지만 람다 연습할 겸 십진수 -> 이진수 -> 십진수 
람다함수형으로 풀었다.
*/

using ll = long long;

vector<ll> solution(vector<ll> num) {
	vector<ll> a;
	for (auto& n : num) {
		string b, s = [&]() -> string {
			if (!n) return{ 0 };
			while (n) {
				b += (n % 2);
				n /= 2;
			}
			return { b.rbegin(), b.rend() };
		}();
		int i;
		for (i = s.size() - 1; i >= 0 && s[i]; i--) {}
		if (i < 0) {
			s.insert(s.begin(), 1);
			s[1] = 0;
		}
		else {
			s[i] = 1;
			s[i + 1] = 0;
		}
		a.push_back([&]()->ll {
			ll n = 0, t = 1;
			for (int i = s.size() - 1; i >= 0; i--) {
				n += s[i] * t;
				t *= 2;
			}
			return n;
			}());
	}
	return a;
}