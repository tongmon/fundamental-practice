#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1051
꼭짓점을 비교해 나가는 브루트포스 완탐 문제...
사각형 한 점 잡고 각 꼭짓점 비교해 나가면 풀린다.
*/

int N, M, Map[51][51], Max;
string In;

int Sq(int R, int C)
{
	int Len = 0, Edge = Map[R][C], Ans = 1;
	while (R + Len < N && C + Len < M)
	{
		if (Edge == Map[R + Len][C + Len]
			&& Edge == Map[R][C + Len]
			&& Edge == Map[R + Len][C])
			Ans = Len;
		Len++;
	}
	return (Ans + 1) * (Ans + 1);
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		cin >> In;
		for (int j = 0; j < In.size(); j++)
		{
			Map[i][j] = In[j] - '0';
		}
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < In.size(); j++)
		{
			Max = max(Sq(i, j), Max);
		}
	}
	cout << Max;
}