#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/11055
11053번과 똑같지만 길이가 아닌 값의 합을 따진다.
결국 11053번의 O(n*n)이 걸리는 방법에서 bigone을 Ary[i]의 값 합산으로 바꿔주었을 뿐이다.
11053번과 같은 방식으로 고를 원소의 위치보다 아래에 있는 녀석들 중에 자신의 값보다 작고 합산이 가장 큰 녀석을 선발해
Dp값을 채워나간다.
*/

int Ary[1001];
int Dp[1001];

int Dynamic(int Size)
{
	Dp[0] = Ary[0];
	int bigone = 0;
	for (int i = 1; i < Size; i++)
	{
		bigone = 0;
		for (int j = i - 1; j >= 0; j--)
		{
			if (Ary[i] > Ary[j] && bigone < Dp[j])
			{
				bigone = Dp[j];
			}
		}
		Dp[i] = Ary[i] + bigone;
	}
	bigone = 0;
	for (int i = 0; i < Size; i++)
	{
		if (bigone < Dp[i])
		{
			bigone = Dp[i];
		}
	}
	return bigone;
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
	cout << Dynamic(N);
}