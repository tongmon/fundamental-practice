#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/67259
경주로 건설 문제.
탐색 시 메모제이션이 필요한 문제다.
블럭이 세로로 온 상태에서 기록하는 것과 가로로 온 상태에서 기록하는 것을
다르게 저장해야 한다.
그래서 거리를 저장하는 배열이 격자 위치만이 아니라 어디에서 왔는지 까지 고려하는 3차원 배열이 되었다.
큐에서는 현재까지 비용, 격자 위치, 가로에서 왔는지 세로에서 왔는지에 대한 정보가 저장되고
이 정보들을 가지고 탐색을 진행하면서 문제가 풀린다.
이 문제를 통해 탐색 문제에 대한 실력을 길러간다.
*/

using Cord = tuple<int, int, int, int>;
int Dir[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };

int solution(vector<vector<int>> board) {
	int Dist[2][26][26], Size = board.size();
	for (int k = 0; k < 2; k++)
		for (int i = 0; i < 26; i++)
			for (int j = 0; j < 26; j++)
				Dist[k][i][j] = 2e9;
	priority_queue<Cord, vector<Cord>, greater<Cord>> Q;
	Dist[0][0][0] = Dist[1][0][0] = 0; Q.push({ 0,0,0,2 });
	while (!Q.empty()) {
		Cord Top = Q.top(); Q.pop();
		if (Dist[get<3>(Top) == 2 ? 0 : get<3>(Top)][get<2>(Top)][get<1>(Top)] < get<0>(Top))
			continue;
		for (int i = 0; i < 4; i++) {
			int X = get<1>(Top) + Dir[i][0], Y = get<2>(Top) + Dir[i][1], Len = 100 + get<0>(Top);
			if (0 <= X && X < Size && 0 <= Y && Y < Size && !board[Y][X]) {
				int is_LR = X - get<1>(Top) ? 1 : 0;
				if (get<3>(Top) == 2 || get<3>(Top) == is_LR) {
					if (Len < Dist[is_LR][Y][X]) {
						Dist[is_LR][Y][X] = Len;
						Q.push({ Len,X,Y,is_LR });
					}
				}
				else if (Len + 500 < Dist[is_LR][Y][X]) {
					Dist[is_LR][Y][X] = Len + 500;
					Q.push({ Len + 500,X,Y,is_LR });
				}
			}
		}
	}
	return min(Dist[0][Size - 1][Size - 1], Dist[1][Size - 1][Size - 1]);
}