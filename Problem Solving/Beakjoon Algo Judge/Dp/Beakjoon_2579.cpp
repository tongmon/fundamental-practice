#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2579
계단 오르기 문제이다.
전형적인 Dp문제로 자신의 위치가 n번째라고 생각하고 하위 값들을 어떻게 해야 Dp[n]이 최선의 값이 나올까?
라는 고민을 하면 접근하기 쉽다.
이러한 고민을 할 때에 주의해야 할 점은 초반 값의 선정이다. ex) Dp[0], Dp[1], Dp[2]...
이 계단 오르기 문제는 2156번인 포도주 시식과 약간 유사하다.
*/

int Ary[300];
int Dp[300];

int StairGame(int Size)
{
	Dp[0] = Ary[0]; Dp[1] = Dp[0] + Ary[1]; Dp[2] = max(Ary[0] + Ary[2], Ary[1] + Ary[2]);
	int Bigone = Dp[0];
	for (int i = 3; i < Size; i++)
	{
		Dp[i] = max(Dp[i - 3] + Ary[i - 1] + Ary[i], Dp[i - 2] + Ary[i]);
	}
	return Dp[Size - 1];
}

int main()
{
	int N;
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> Ary[i];
	}
	cout << StairGame(N);
}