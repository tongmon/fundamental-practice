#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/43105
정수 삼각형 문제.
백준에서 풀어봤던 문제인데 약간 다른 식으로 풀어봤다.
위에서 아래로 선택을 하면서 최적의 값이 누적되는 Dp 문제라
용량을 아낄 수가 있어서 2개의 칸을 번갈아가면서 쓰도록 하였다.
이 문제를 통해 구현속도를 늘려간다.
*/

int Dp[2][501];

int solution(vector<vector<int>> triangle) {
	int answer = 0, A = 0;
	Dp[A][1] = triangle[0][0];
	for (int i = 1; i < triangle.size(); i++) {
		auto& L = triangle[i];
		for (int j = 1; j <= i; j++) {
			Dp[A ^ 1][j] = L[j - 1] + max(Dp[A][j], Dp[A][j - 1]);
			Dp[A ^ 1][j + 1] = L[j] + max(Dp[A][j], Dp[A][j + 1]);
		}
		A ^= 1;
	}
	for (auto& An : Dp[A])
		answer = max(An, answer);
	return answer;
}