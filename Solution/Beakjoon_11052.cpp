#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
https://www.acmicpc.net/problem/11052
카드 구매하기 문제이다.
약간 LIS 문제와 비슷하다.
Dp[i]가 현재 위치가 i일 경우 문제가 요구하는 최선의 방법을 담고있는데
이 Dp[i]를 구하기 위해 예전 최선의 방법들(Dp[i-1]...)도 사용하여 최선 중의 최선을 선별해내는 문제이다.
예를 들어 카드 3장을 구매할 때에 최대로 돈을 버리면서 비싸게 사는 법을 구하려하면 3팩짜리 바로 까는거,
1팩짜리와 2팩짜리, 1팩짜리 3개 까기 이렇게 비교를 해야한다.
근데 Dp로 보자면 1팩짜리 3개 까는 것은 Dp[1] + Dp[2]에서 이미 Dp[2]에 포함 되었을 수 있다.
따라서 최대 비싸게 3팩까기를 Dp로 보면 Dp[3], Dp[2] + Dp[1] 이것만 비교해보면 되는 것이고
이 방식은 더 많이 팩을 까도 같다.
이 문제를 통해 최선의 방법을 저장하는 Dp 점화식을 구하는 사고방식을 길러야 한다.
*/

int Dp[1001];
int Ary[1001];

int Card(int Size)
{
	Dp[1] = Ary[1];
	for (int i = 2; i <= Size; i++)
	{
		int Bigone = Ary[i];
		for (int j = i - 1; j >= i / 2; j--) // i/2인 이유는 3팩을 깐다고 예를 들면 2,1을 비교하고 1,2를 또 비교할 필요는 없기 때문
		{
			if (Bigone < Dp[j] + Dp[i - j])
			{
				Bigone = Dp[j] + Dp[i - j];
			}
		}
		Dp[i] = Bigone;
	}
	return Dp[Size];
}

int main()
{
	int N;
	cin >> N;
	scanf_s("%d", &Ary[1]);
	for (int i = 2; i <= N; i++)
	{
		scanf_s(" %d", &Ary[i]);
	}
	cout << Card(N);
}