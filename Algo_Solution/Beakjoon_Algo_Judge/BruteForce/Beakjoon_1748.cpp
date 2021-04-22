#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1748
해당 숫자의 자릿수를 기준으로 수행해야 되는 문제다.
진짜 완전탐색 한다 치고 숫자 1, 2, 3.. 이렇게 가면 시간복잡도가 터지고
자릿수 1개인 숫자 9개, 자릿수 2개인 숫자 90개... 이런식으로 접근한다.
2034를 예로 들면 999까지의 자릿수는 9 + 90 * 2 + 900 * 3 이고
1000 ~ 2034 까지는 4자리씩 더해지는데 이 수들의 개수는 2034 - 1000 + 1 = 1035개이고
최종적으로 9 + 90 * 2 + 900 * 3 + 1035 * 4가 최종적인 답이 된다.
이 문제를 통해 구현 속도를 늘려간다.
*/

int k, Ans, K;
string Num;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> Num; 
	for (int i = 1, n = 1; i < Num.size(); i++, n *= 10)
		k += 9 * n * i;
	if (Num.size() > 1)
		Ans = k + Num.size() * (stoi(Num) - pow(10, Num.size() - 1) + 1);
	else
		Ans = stoi(Num);
	cout << Ans;
}