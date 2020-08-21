#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/10844
자릿수에 따른 계단수를 구하는 문제
동적 프로그래밍에서의 저장소를 1차원 배열이라는 틀에 빠져서 생각이 오래걸렸다.
동적 프로그래밍 문제다 싶으면 '자릿수', '끝나는 수', '숫자 종류' 이런 키워드들을 이용하여
Dp 메모제이션을 1차원, 2차원으로 적절히 설정할 수 있도록 하자
*/

#define Moded 1000000000

int Dp[101][10]; // 맨 앞의 수가 j로 끝나고 자릿수가 i인 Dp[i][j] 저장소

int Dynamic(int T)
{
	int sum = 0;
	for (int i = 2; i <= T; i++)
	{
		for (int j = 0; j <= 9; j++)
		{
			if (j == 0)
			{
				Dp[i][j] = Dp[i - 1][j + 1];
			}
			else if (j != 0 && j != 9)
			{
				Dp[i][j] = Dp[i - 1][j + 1] + Dp[i - 1][j - 1];
			}
			else
			{
				Dp[i][j] = Dp[i - 1][j - 1];
			}
			Dp[i][j] = Dp[i][j] % Moded;
		}
	}
	for (int i = 0; i <= 9; i++)
	{
		sum = sum + Dp[T][i];
		sum = sum % Moded;
	}
	return sum;
}

int main()
{
	Dp[1][0] = 0;
	for (int i = 1; i <= 9; i++)
	{
		Dp[1][i] = 1;
	}
	int Len;
	cin >> Len;
	cout << Dynamic(Len);
}