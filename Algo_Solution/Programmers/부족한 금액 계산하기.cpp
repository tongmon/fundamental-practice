#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/82612
부족한 금액 계산하기 문제.
인자는 int로 주어지는데 답은 ll로 나오기에 형변환 해주어야 한다.
*/

using ll = long long;

ll solution(int price, int money, int count) {
	ll answer = 0;
	ll p = price, m = money, c = count;
	for (ll i = 1; i <= c; i++)
		answer += p * i;
	return (money - answer >= 0 ? 0 : answer - m);
}