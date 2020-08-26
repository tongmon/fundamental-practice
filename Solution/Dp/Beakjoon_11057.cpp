#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/11057
자릿수에 따른 오르막 수를 구하는 문제이다.
예전에 풀었던 10844번 계단 수 구하는 문제와 비슷하여 빠르게 풀 수 있었다.
끝 자리가 0으로 끝나면 자릿 수가 하나 적은 0으로 끝나는 가짓수와 같고,
나머지는 끝 자리가 k로 끝난다면 자릿 수가 하나 적은 k 이하의 가짓수들을 모두 합한 것이 해당 가짓수가 된다.
결국 예를 들어 8로 끝난다면 Dp[i][8] = Dp[i-1][0] + Dp[i-1][1] .... + Dp[i-1][8]과 같다는 것이다.
*/

#define Moded 10007

int Dp[1001][10]; // 맨 앞의 수가 j로 끝나고 자릿수가 i인 Dp[i][j] 저장소

int Dynamic(int T)
{
	int sum = 0;
	for (int i = 0; i <= 9; i++)
	{
		Dp[1][i] = 1;
	}
	for (int i = 2; i <= T; i++)
	{
		Dp[i][0] = Dp[i - 1][0];
		for (int j = 1; j <= 9; j++)
		{
			for (int k = 0; k <= j; k++)
			{
				Dp[i][j] = (Dp[i][j] + Dp[i - 1][k]) % Moded;
			}
		}
	}
	for (int i = 0; i <= 9; i++)
	{
		sum = (sum + Dp[T][i]) % Moded;
	}
	return sum;
}

int main()
{
	int Len;
	cin >> Len;
	cout << Dynamic(Len);
}