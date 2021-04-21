#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/17679
프렌즈4블록 문제.
인덱스 조절이 까다로운 문제였다.
일단 배열이 블록 지우기 힘들게 string 형으로 가로로 줘서 이걸 deque에서 받아 세웠다.
그리고 바뀔 블록 검사하면서 바뀔 녀석이면 + 표시 해두고 이 녀석들을 erase로 지우면서
배열을 바꾸어 나갔다.
이게 쉬울줄 알았는데 erase시에 각 격자 크기가 변동되어서 이걸 다 따져줘야했던 것이 좀
귀찮게 만들었다.
이 문제를 통해 구현속도를 늘려간다.
*/

int Dir[4][2] = { {0,0},{1,-1},{0,-1},{1,0} };
deque<deque<char>> Map;
deque<char> A;

int solution(int m, int n, vector<string> board) {
	int answer = 0, Keep = 1;
	for (int j = 0; j < board[0].size(); j++) {
		Map.push_back(A);
		for (int i = 0; i < board.size(); i++)
			Map[j].push_front(board[i][j]);
	}
	while (Keep) {
		Keep = 0;
		vector<pair<int, int>> del;
		for (int j = 0; j < Map.size() - 1; j++) {
			for (int i = Map[j].size() - 1; i > 0; i--) {
				bool quad = 1;
				for (int k = 1; k < 4 && quad; k++) {
					if (0 > i + Dir[k][1] || i + Dir[k][1] >= Map[j + Dir[k][0]].size()
						|| 0 > j + Dir[k][0] || j + Dir[k][0] >= Map.size()
						|| Map[j][i] != Map[j + Dir[k][0]][i + Dir[k][1]])
						quad = 0;
				}
				for (int k = 0; k < 4 && quad; k++)
					del.push_back({ i + Dir[k][1], j + Dir[k][0] });
			}
		}
		for (auto& a : del)
			Map[a.second][a.first] = '+';
		for (int i = 0; i < Map.size(); i++) {
			for (int j = 0; j < Map[i].size(); j++) {
				if (Map[i][j] == '+') {
					answer++;
					Map[i].erase(Map[i].begin() + j--);
					Keep = 1;
				}
			}
		}
	}
	return answer;
}