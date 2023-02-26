#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/17626
DP문제
제곱수를 따로 담아 이 수들 내에서 현재 수에서 빼 이 
뺀 값 인덱스의 DP값을 확인하여 최소 DP값을 획득하는 문제이다.
처음에 제곱수를 따로 담아놓는 것을 생각하지 못해서 애들 먹었던 문제다.
에라토스테네스의 체로 소수들만 따로 빼놓는 것과 비슷하게 제곱수도 따로 담는다는
생각을 했어야했다.
어떤 특정한 조건의 수들을 다룰 때에는 이렇게 따로 빼서 배열에 담아놓는다는
생각을 항상 해보자
나머지는 DP에 대한 기본 개념을 이용하는 것이기에 딱히 더 설명할 것은 없다.
이 문제를 통해 Dp 문제에 대한 접근 능력을 길러나간다.
*/

int N, DP[50001];
vector<int>sq;

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	DP[1] = 1; DP[2] = 2;
	for (int i = 1; i < 225; ++i) {
		sq.push_back(i * i);
	}
	for (int i = 3; i <= N; ++i) {
		int MIN = 99999;
		for (int j = 0; sq[j] <= i; ++j) {
			int buf = i - sq[j];
			MIN = min(MIN, DP[buf]);
		}
		DP[i] = MIN + 1;
	}
	cout << DP[N];
}