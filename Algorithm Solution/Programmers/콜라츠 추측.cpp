#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12943
콜라츠 추측 문제.
구현하란데로 하면 되는데 int 오버플로우를 유의해야한다.
*/

using ll = long long;

int solution(int p) {
	return [&]()->ll {
		ll k = 0, n = p;
		while (n != 1 && k < 500)
			n = n % 2 ? n * 3 + 1 : n / 2, k++;
		return k < 500 ? k : -1;
	}();
}