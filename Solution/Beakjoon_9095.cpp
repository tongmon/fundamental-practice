#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/9095
가짓수 더하기 문제
나는 Dp보다는 재귀에 가깝게 풀었다.
Dp로 푸는 경우에 나오게 되는 점화식은 아래와 같다. 예를 들어 4라 하면
1 + (3을 만드는 경우), 2 + (2를 만드는 경우), 3 + (1을 만드는 경우) 이렇게 3개가 나와
한꺼번에 보자면 Dp[i] = Dp[i-1] + Dp[i-2] + Dp[i-3] 이러한 식이 도출된다.
*/

int Dp[11] = { 0, };

void Div(int N, int index)
{
	if (N == 0)
	{
		Dp[index]++; return;
	}
	if (N - 1 >= 0)
	{
		Div(N - 1, index);
	}
	if (N - 2 >= 0)
	{
		Div(N - 2, index);
	}
	if (N - 3 >= 0)
	{
		Div(N - 3, index);
	}
}

int main()
{
	int T, N; vector<int> testCases;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		cin >> N; testCases.push_back(N);
	}
	for (int i = 0; i < T; i++)
	{
		Div(testCases[i], testCases[i]);
	}
	for (int i = 0; i < T; i++)
	{
		cout << Dp[testCases[i]] << endl;
	}
}