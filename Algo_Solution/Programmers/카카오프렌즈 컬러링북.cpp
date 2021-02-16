#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/1829
기본적인 DFS,BFS 문제.
영역 색칠하는 유형을 풀어봤다면 손쉽게 해결가능하다.
프로그래머스가 전역변수 선언시 자동으로 초기화가 안되는 문제들이 있는데
그런 문제들 중에 이 문제가 속해있었다....
Vis배열 초기화 안해서 뻘짓 좀 했다.
*/

bool Vis[101][101];
int Dir[4][2] = { {1,0},{0,1},{-1,0},{0,-1} }, Cnt, M, N;

void DFS(int x, int y, int Col, vector<vector<int>>& Map) {
	Vis[y][x] = 1;
	Cnt++;
	for (int i = 0; i < 4; i++)
	{
		int bx = x + Dir[i][0], by = y + Dir[i][1];
		if (0 <= bx && bx < N && 0 <= by && by < M && !Vis[by][bx] && Map[by][bx] == Col)
			DFS(bx, by, Col, Map);
	}
}

vector<int> solution(int m, int n, vector<vector<int>> picture) {
	vector<int> answer(2);
	answer[0] = answer[1] = 0;
	memset(Vis, 0, sizeof(Vis));
	N = n, M = m;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (picture[i][j] && !Vis[i][j]) {
				Cnt = 0; answer[0]++;
				DFS(j, i, picture[i][j], picture);
				answer[1] = max(Cnt, answer[1]);
			}
		}
	}
	return answer;
}