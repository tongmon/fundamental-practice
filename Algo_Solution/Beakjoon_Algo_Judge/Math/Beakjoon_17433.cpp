#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/17433
합동식 문제다.
합동식 문제인 것을 진작에 알았다면 풀지 않았겠지만 풀고나니 알았다.
부호가 다를 경우와 같을 경우 모두 abs(a-b)를 사용하면 해결이 된다.
예를 들어 93, 7 이면 86이 신비한 수가 되고 -93, 7 인 경우 100이 신비한 수가 되는데
이러한 경우 모두 abs(a-b)로 묶여 해결된다. 이렇게 수들의 차이를 구해서 그 차이값 수들의
최대공약수를 찾으면 답이 된다.
이 문제를 통해 합동식을 복습했다.
*/

int T, k, a, b, p, pb;

int gcd(int a, int b) {
	if (!b) return a;
	return gcd(b, a % b);
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> k >> a;
		pb = 0;
		for (int j = 1; j < k; j++) {
			cin >> b;
			p = abs(a - b);
			pb = gcd(max(p, pb), min(p, pb));
			a = b;
		}
		if (pb)
			cout << pb << '\n';
		else
			cout << "INFINITY\n";
	}
}