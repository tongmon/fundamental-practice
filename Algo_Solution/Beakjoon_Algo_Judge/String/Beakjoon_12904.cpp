#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/12904
거꾸로 생각해야 하는 문제다.
A를 통해 B를 매칭하려 하면 어려워지고 B를 통해 A를 맞추려하면 문제가 확 쉬워진다.
문제가 잘 안 풀린다면 발상의 전환을 한번 해보자.
이 문제를 통해 구현속도를 늘려간다.
*/

string A, B;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> A >> B;
	while (B.size() != A.size()) {
		char K = B.back();
		B.pop_back();
		if (K == 'B')
			reverse(B.begin(), B.end());
	}
	cout << (B == A ? 1 : 0);
}