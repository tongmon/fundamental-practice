#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/60063
블록 이동하기 문제.
문제는 딱 보면 BFS인 것이 눈에 확 보인다.
근데 구현이 귀찮아진다.
이 드론을 회전하는 경우를 고려해야 하는 것도 문제고 드론이 2x1 크기이기에 이에 맞는
Vis 배열 구조를 만들어야 한다.
난 Vis 배열 구조는 2개의 int가 담기는 구조로 만들었는데 각 두개의 좌표는
이차원 --> 일차원화 된 위치가 들어가게 된다. (물론 앞이 작은 것, 뒤가 큰 것)
그리고 회전은 어떻게 숏코딩을 해야할까 고민을 많이했는데도 별다른 방법이 생각나지 않아서
그냥 배열에 회전 가능한 모든 경우를 때려박아서 해결했다.
그 이후에 BFS를 돌려서 정답을 얻어냈다.
이 문제를 통해 BFS 구현 능력을 길러간다
*/

set<pair<int, int>> Vis;
int Size, Dir[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };

bool isOK(int x, int y, vector<vector<int>> &Map) {
	return (0 <= x && x < Size && 0 <= y && y < Size && !Map[y][x]);
}

void Vism(int *A, queue<vector<int>> *Q) {
	for (int i = 0; i < 8; i += 4)
	{
		int Big = A[i + 0] + A[i + 1] * Size, Small = A[i + 2] + A[i + 3] * Size;
		if (Big < Small)
			swap(Big, Small);
		if (Vis.find({ Small,Big }) == Vis.end()) {
			Vis.insert({ Small, Big });
			Q->push({ A[i + 0],A[i + 1],A[i + 2],A[i + 3],A[8] + 1 });
		}
	}
}

int solution(vector<vector<int>> board) {
	int answer = 0; Size = board.size();
	queue<vector<int>> Q;
	Q.push({ 0,0,1,0,0 });
	Vis.insert({ 0,1 });
	while (!Q.empty()) {
		int X1 = Q.front()[0], Y1 = Q.front()[1], X2 = Q.front()[2], Y2 = Q.front()[3], Time = Q.front()[4];
		if ((X1 == Size - 1 && Y1 == Size - 1) || (X2 == Size - 1 && Y2 == Size - 1)) {
			answer = Time;
			break;
		}
		for (int i = 0; i < 4; i++)
		{
			int cX1 = X1 + Dir[i][0], cX2 = X2 + Dir[i][0], cY1 = Y1 + Dir[i][1], cY2 = Y2 + Dir[i][1];
			if (!isOK(cX1, cY1, board) || !isOK(cX2, cY2, board))
				continue;
			int Big = cX1 + cY1 * Size, Small = cX2 + cY2 * Size;
			if (Big < Small) 
				swap(Big, Small);
			if (Vis.find({ Small, Big }) == Vis.end()) {
				Vis.insert({ Small, Big });
				Q.push({ cX1,cY1,cX2,cY2,Time + 1 });
			}
		}
		int pX1 = X1, pY1 = Y1, pX2 = X2, pY2 = Y2;
		if (Y1 > Y2 || X1 > X2) {
			swap(pX1, pX2);
			swap(pY1, pY2);
		}
		if (X1 == X2) {
			if (isOK(pX1 + 1, pY1, board) && isOK(pX2 + 1, pY2, board)) {
				int A[9] = { pX2 + 1, pY2, pX2, pY2, pX1 + 1, pY1, pX1, pY1, Time };
				Vism(A, &Q);
			}
			if (isOK(pX1 - 1, pY1, board) && isOK(pX2 - 1, pY2, board)) {
				int A[9] = { pX2 - 1, pY2, pX2, pY2, pX1 - 1, pY1, pX1, pY1, Time };
				Vism(A, &Q);
			}
		}
		else {
			if (isOK(pX1, pY1 + 1, board) && isOK(pX2, pY2 + 1, board)) {
				int A[9] = { pX2, pY2, pX2, pY2 + 1, pX1, pY1, pX1, pY1 + 1, Time };
				Vism(A, &Q);
			}
			if (isOK(pX1, pY1 - 1, board) && isOK(pX2, pY2 - 1, board)) {
				int A[9] = { pX2, pY2, pX2, pY2 - 1, pX1, pY1, pX1, pY1 - 1, Time };
				Vism(A, &Q);
			}
		}
		Q.pop();
	}
	return answer;
}