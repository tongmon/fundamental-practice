#include <bits/stdc++.h>
using namespace std;

/*
https://leetcode.com/problems/minimum-path-sum/
Dp문제
백준에서의 파이프 문제와 같이 위에서 내려오면서 더하는 것과
왼쪽에서 오른쪽으로 가면서 더하는 것 중에 무엇이 더 작아지는지
비교하면서 Dp 값을 저장해 내려오면 되는 문제다.
Dp에서 거의 하는 초반값들을 정할 때는 위에서 내려오면서 더하는 경우는 없기에
옆에서 더해가는 경우만 생각한다.
이 문제를 통해 구현속도를 늘려간다.
*/

int Dp[201][201];

class Solution {
public:
	int minPathSum(vector<vector<int>> grid) {
		int N = grid.size(), M = grid[0].size();
		Dp[0][0] = grid[0][0];
		for (int i = 1; i < M; i++)
			Dp[0][i] = Dp[0][i - 1] + grid[0][i];
		for (int i = 1; i < N; i++) {
			Dp[i][0] = Dp[i - 1][0] + grid[i][0];
			for (int j = 1; j < M; j++)
				Dp[i][j] = min(Dp[i - 1][j], Dp[i][j - 1]) + grid[i][j];
		}
		return Dp[N - 1][M - 1];
	}
};