#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2293
동전 Dp문제이다.
Dp는 배낭문제와 비슷한 원리로 작동한다.
1,2,3 원 종류 3가지를 써서 6원을 만드는 경우는
1,2원을 사용해서 6원을 만드는 경우와 1,2,3원을 사용해서 3원을 만드는 경우로
나뉠 수 있다.
다시 한번 더 나누어보면 1,2원을 사용하여 6원을 만드는 경우는
1원만 사용하여 6원을 만드는 경우 + 1,2원을 사용하여 4원 만드는 경우로 나뉠 수 있다.
이렇게 계속 나뉘는데 나뉘는 과정에서 중복되는 값이 생기니 Dp를 이용할 수 있는 것이다.
Dp[n][i] = Dp[n-1][i] + Dp[n][i - n번째 동전 종류] 여기서 n은 동전 인덱스를 나타낸다.
근데 여기서 용량제한이 4mb라 이를 지켜줘야한다.
따라서 Dp배열의 2개 라인만이 필요하기에 라인을 번갈아가면서 갈아치우는 방식으로 해결했다.
이 문제를 통해 Dp 문제에 대해 익숙해져간다.
*/

int n, k, In, Dp[2][10001];
vector<short> coin;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> In;
		coin.push_back(In);
	}
	bool flag = 1;
	for (int j = 1; j <= n; j++) {
		flag = flag ? 0 : 1;
		for (int i = 1; i <= k; i++) {
			Dp[flag][i] = Dp[flag ^ 1][i];
			if (i - coin[j - 1] > 0)
				Dp[flag][i] += Dp[flag][i - coin[j - 1]];
			else if (i == coin[j - 1])
				Dp[flag][i] += 1;
		}
	}
	cout << Dp[flag][k];
}