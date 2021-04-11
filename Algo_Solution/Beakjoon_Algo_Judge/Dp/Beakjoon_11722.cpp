#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/11722
11053번에서 대소비교만 반대로 해주면 풀린다.
따라서 이 문제도 O(n*n), O(n*log(n)) 두 가지 방식이 존재한다.
*/

int Ary[1001];
int Dp[1001];
int Count_Max[1001];

int Dynamic(int Size) // O(n*n)
{
	Dp[0] = 1;
	int Len = 0;
	for (int i = 1; i < Size; i++)
	{
		Len = 0;
		for (int j = i - 1; j >= 0; j--)
		{
			if (Ary[i] < Ary[j] && Len < Dp[j])
			{
				Len = Dp[j];
			}
		}
		Dp[i] = Len + 1;
	}
	Len = 0;
	for (int i = 0; i < Size; i++)
	{
		if (Len < Dp[i])
		{
			Len = Dp[i];
		}
	}
	return Len;
}

int Dynamic_improved(int Size) // O(n*log(n))
{
	Dp[0] = 1; Count_Max[1] = Ary[0];
	int Maxindex = 1;
	for (int i = 1; i < Size; i++)
	{
		for (int j = 1; j <= Maxindex; j++)
		{
			if (Ary[i] >= Count_Max[j])
			{
				Count_Max[j] = Ary[i]; Dp[i] = j;
				break;
			}
			else if (Maxindex == j)
			{
				Count_Max[++Maxindex] = Ary[i]; Dp[i] = Maxindex;
				break;
			}
		}
	}
	return Maxindex;
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
	cout << Dynamic_improved(N);
}

/*
* 7달 후 풀이

int N, Ary[1001], Dp[1001], Ans;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> Ary[i];
	for (int i = 1; i <= N; i++) {
		int M = 0;
		for (int j = 1; j < i; j++)
			if (Ary[j] > Ary[i])
				M = max(M, Dp[j]);
		Dp[i] = 1 + M;
		Ans = max(Ans, Dp[i]);
	}
	cout << Ans;
}
*/