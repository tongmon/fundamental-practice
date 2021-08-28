#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/64061
크레인 인형뽑기 게임 문제.
요구한데로 구현하면 된다.
나는 배열에서 0인 부분은 필요없기에 다 지우고 시작했다.
*/

int solution(vector<vector<int>> board, vector<int> moves) {
	int a = 0, W = board[0].size(), H = board.size();
	stack<int> S;
	vector<vector<int>> L(W);
	for (int i = 0; i < W; i++) {
		for (int j = H - 1; j >= 0 && board[j][i]; j--) {
			L[i].push_back(board[j][i]);
		}
	}
	for (auto& m : moves) {
		if (!L[--m].empty()) {
			if (!S.empty() && S.top() == L[m].back())
				S.pop(), a += 2;
			else
				S.push(L[m].back());
			L[m].pop_back();
		}
	}
	return a;
}