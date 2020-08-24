#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

/*
https://www.acmicpc.net/problem/1699
제곱수의 합 문제이다.
언뜻 보면 점화식이 Dp[i] = Dp[k * k] + Dp[i - (k * k)] 이렇게
i와 가장 가까운 제곱수는 1개이니 제일 작으니까 가까운 제곱수의 Dp와 i에서 그 제곱수를 뺀 Dp를
더하면 답이라고 생각할 수가 있다.
하지만 위와 같이 점화식을 짜면 41과 같은 수들에서 답을 구하지 못한다.
41은 16 + 25로 표현이 가능하지만 위와 같은 점화식에서는 36 + 4 + 1로 만들어 버린다.
따라서 자신보다 작은 제곱수들을 찾아가면서 제일 작은 것이 무엇인지 탐색해야 한다.
이 문제를 통해 "Dp[n]은 n 이전 Dp들의 어떤 속성을 가지고 있어야 할까?"라는 사고방식을 길러야 한다.
*/

int Dp[100001];

bool is_SquareNum(int num) // 제곱수 유무 확인
{
	double Dnumber = sqrt(num);
	if (Dnumber == (int)Dnumber)
	{
		return true;
	}
	return false;
}

int MinComb(int Size)
{
	Dp[1] = 1; Dp[2] = 2; Dp[3] = 3;
	for (int i = 4; i <= Size; i++)
	{
		if (is_SquareNum(i) == true)
		{
			Dp[i] = 1;
		}
		else
		{
			int k = sqrt(i), Min = Dp[i - (k * k)];
			for (int j = k - 1; j > 0; j--)
			{
				if (Min == 1)
				{
					break;
				}
				if (Min > Dp[i - j * j])
				{
					Min = Dp[i - j * j];
				}
			}
			Dp[i] = 1 + Min;
		}
	}
	return Dp[Size];
}

int main()
{
	int N;
	cin >> N;
	cout << MinComb(N);
}