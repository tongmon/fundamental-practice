#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/9461
파도반 수열 문제이다.
기존에 Dp문제를 풀어왔다면 문제의 그림을 그려가면서 쉽게 점화식을 구하는 것이 가능하다.
재밌는 점은 점화식이 2개가 나온다.
그림을 그려가면서 얻을 수 있는 점화식은 Dp[i] = Dp[i - 1] + Dp[i - 5] 이와 같고
결과값들을 나열하면서 점화식을 세워보면 Dp[i] = Dp[i - 2] + Dp[i - 3] 이러한 식도 나온다.
*/

unsigned long long Dp[101];

unsigned long long Tri(int Size)
{
	Dp[1] = 1; Dp[2] = 1; Dp[3] = 1;
	Dp[4] = 2; Dp[5] = 2;
	for (int i = 6; i <= Size; i++)
	{
		Dp[i] = Dp[i - 1] + Dp[i - 5];
		// Dp[i] = Dp[i - 2] + Dp[i - 3];
	}
	return Dp[Size];
}

int main()
{
	int T, N;
	vector<unsigned long long> Result;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		cin >> N;
		Result.push_back(Tri(N));
	}
	for (int i = 0; i < Result.size(); i++)
	{
		cout << Result[i] << endl;
	}
}