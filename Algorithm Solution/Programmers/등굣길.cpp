#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/42898
등굣길 문제
백준에서 풀어봤던 파이프 격자 문제와 거의 똑같았다.
DFS로 풀 수도 있지만 시간 복잡도가 미쳐돌아간다.
따라서 Dp로 중복되는 결과를 저장하면서 풀어야 한다.
오른쪽, 아래쪽으로만 갈 수 있으니 위, 왼쪽 격자의 결과를 더한 것이
현재 격자의 값이 된다.
이 문제를 통해 Dp 사고방식을 늘려간다.
*/

int Dp[101][101];
bool Map[101][101];

int solution(int m, int n, vector<vector<int>> puddles) {
	int answer = 0;
	for (auto A : puddles)
		Map[A[1]][A[0]] = 1;
	Dp[1][1] = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if ((i == 1 && j == 1) || Map[i][j])
				continue;
			Dp[i][j] = (Dp[i - 1][j] + Dp[i][j - 1]) % 1000000007;
		}
	}
	answer = Dp[n][m];
	return answer;
}