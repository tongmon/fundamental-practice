#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/11727
타일링 문제 2번
문제 1번과 같이 Dp를 이용하는 문제이다.
하노이 탑과 같이 n-1일 경우, n-2일 경우... 등을 생각해서 Dp[n] = Dp[n-1].....
이러한 점화식을 세우는 능력이 필요하다. 물론 중복되는지 꼭 확인하여 제외시켜야한다.
*/

int Dp[1001] = { 0, };

void Pob(int N)
{
	Dp[1] = 1; Dp[2] = 3;
	if (N == 1 || N == 2)
	{
		return;
	}
	int i = 0;
	while (i + 2 != N)
	{
		Dp[i + 3] = Dp[i + 2] + 2 * Dp[i + 1];
		if (Dp[i + 3] > 10007)
		{
			Dp[i + 3] = Dp[i + 3] % 10007;
		}
		i++;
	}
}

int main()
{
	int N;
	cin >> N;
	Pob(N);
	cout << Dp[N];
}