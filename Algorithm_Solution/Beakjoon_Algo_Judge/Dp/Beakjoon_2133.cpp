#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2133
타일 채우기 문제이다.
기존의 타일 채우기 문제처럼 풀되 몇 가지 조건이 추가 된다.
핵심은 ㄱ모양이나 ㅢ 모양으로 n번째가 시작하게 되면 그에 따른 개수를 세주어야 한다.
이런 문제는 Dp문제여서 점화식 세우는 것도 중요하지만 특히 이 문제는 점화식을 구축할 때
n번째 항의 특징을 잘 살펴 그것을 이용할 줄 알아야 한다.
즉 새로운 케이스를 잘 찾는 능력을 길러야 한다.
*/

int Dp[31];

int Fill(int Size)
{
	Dp[0] = 1; Dp[1] = 0; Dp[2] = 3;
	for (int i = 3; i <= Size; i++)
	{
		if (i % 2 != 0)
		{
			Dp[i] = 0;
		}
		else
		{
			Dp[i] = 3 * Dp[i - 2];
			for (int k = 4; i - k >= 0; k = k + 2)
			{
				Dp[i] = Dp[i] + 2 * Dp[i - k];
			}
		}
	}
	return Dp[Size];
}

int main()
{
	int N;
	cin >> N;
	cout << Fill(N);
}