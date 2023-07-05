#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1912
연속합 문제이다.
기존의 풀었던 전형적인 Dp 풀이 방식대로 접근하면 된다.
현재 고를 원소 자체의 값이 큰가? 아니면 그 원소 전의 원소를 더한 것이 큰가? 를 따져보면 된다.
Dp는 n-1번째, n번째 이렇게 나누어서 사고하면 쉽게 접근 가능한 문제가 많다.
*/

int Ary[100001];
int Dp[100001];

int MaxSum(int Size)
{
	Dp[0] = Ary[0]; 
	int Bigone = Dp[0];
	for (int i = 1; i < Size; i++)
	{
		Dp[i] = max(Ary[i], Ary[i] + Dp[i - 1]);
		if (Bigone < Dp[i])
		{
			Bigone = Dp[i];
		}
	}
	return Bigone;
}

int main()
{
	int N;
	cin >> N;
	scanf_s("%d", &Ary[0]);
	for (int i = 1; i < N; i++)
	{
		scanf_s(" %d", &Ary[i]);
	}
	cout << MaxSum(N);
}