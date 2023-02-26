#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12913
땅따먹기 문제.
위에서 내려오는 Dp 문제다.
같은 열을 지나지 않으면서 내려오는 값들의 최대값을 구하는 문제기에
그대로 현재 상태에서 최대가 될 수 있는 값을 담는 Dp를 구현하면 된다.
추가적으로 이런 유형은 공간복잡도를 1로 줄일 수가 있다.
예전 값 중에서 필요한 것은 바로 전 i-1의 값이기 때문이다.
이 문제를 통해 Dp 구현 속도를 늘려간다.
*/

int Dp[100001][4];

int solution(vector<vector<int> > land)
{
	int answer = 0;
	for (int i = 0; i < 4; i++)
		Dp[0][i] = land[0][i];
	for (int i = 1; i < land.size(); i++)
	{
		Dp[i][0] = max(Dp[i - 1][3], max(Dp[i - 1][1], Dp[i - 1][2])) + land[i][0];
		Dp[i][1] = max(Dp[i - 1][3], max(Dp[i - 1][2], Dp[i - 1][0])) + land[i][1];
		Dp[i][2] = max(Dp[i - 1][3], max(Dp[i - 1][1], Dp[i - 1][0])) + land[i][2];
		Dp[i][3] = max(Dp[i - 1][0], max(Dp[i - 1][1], Dp[i - 1][2])) + land[i][3];
	}
	for (int i = 0; i < 4; i++)
		answer = max(answer, Dp[land.size() - 1][i]);
	return answer;
}