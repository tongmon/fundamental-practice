#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12905
가장 큰 정사각형을 찾는 문제.
유명한 Dp 문제이고 전에 백준에서 풀어봤던거라 빠르게 풀었다.
일단 현재 칸이 1로 채워져 있을 때 정사각형이 커질 수가 있으며
현재 칸이 0이면 정사각형이 될 수 없으므로 그냥 건너뛰면 된다.
정사각형이니 뒤, 위, 사선 위뒤가 모두 채워져있으며
이들 중에 가장 작은 값을 계승하여 현재 칸이 가장 작은 값 + 1이
쓰여지고 이 값이 해당 칸의 가장 긴 정사각형 변 길이가 된다.
이 문제를 통해 Dp 실력을 길러간다.
*/

int Dp[1001][1001];

int solution(vector<vector<int>> board)
{
	int answer = 0;
	for (int i = 0; i < board[0].size(); i++) {
		Dp[0][i] = board[0][i];
		answer = max(answer, Dp[0][i]);
	}
	for (int i = 1; i < board.size(); i++) {
		Dp[i][0] = board[i][0];
		answer = max(answer, Dp[i][0]);
	}
	for (int i = 1; i < board.size(); i++)
	{
		for (int j = 1; j < board[0].size(); j++)
		{
			if (Dp[i - 1][j - 1] && Dp[i - 1][j] && Dp[i][j - 1] && board[i][j])
				Dp[i][j] = 1 + min(Dp[i - 1][j - 1], min(Dp[i - 1][j], Dp[i][j - 1]));
			else
				Dp[i][j] = board[i][j];
			answer = max(answer, Dp[i][j]);
		}
	}
	return answer * answer;
}