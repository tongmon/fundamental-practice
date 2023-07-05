#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/1844
게임 맵 최단거리 문제.
그냥 BFS 때려넣으면 풀리는 문제다.
BFS 기억도 되살릴겸 풀어보았다.
*/

int Vis[101][101], Dir[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };

int solution(vector<vector<int>> maps)
{
	int N = maps[0].size(), M = maps.size();
	queue<vector<int>> Q;
	Q.push({ 0,0,1 });
	Vis[0][0] = 1;
	while (!Q.empty()) {
		int X = Q.front()[0], Y = Q.front()[1], Len = Q.front()[2];
		if (X == N - 1 && Y == M - 1)
			return Len;
		Q.pop();
		for (int i = 0; i < 4; i++) {
			int cX = X + Dir[i][0], cY = Y + Dir[i][1];
			if (0 <= cX && cX < N && 0 <= cY && cY < M && maps[cY][cX] && !Vis[cY][cX]) {
				Vis[cY][cX] = 1;
				Q.push({ cX,cY,Len + 1 });
			}
		}
	}
	return -1;
}