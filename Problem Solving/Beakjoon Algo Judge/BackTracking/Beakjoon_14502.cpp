#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/14502
브루트포스와 탐색 혼합 문제이다.
백준 치킨 배달 문제와 동일하게 선택지 중에서 몇 개를 뽑는 조합에서 다 뽑은 후에
알맞게 DFS나 어떤 처리를 가하는 시뮬레이션 문제라고 볼 수 있다.
일단 내 풀이 길이에서 더 줄일 수 없을까 함수를 찾아본 결과
memcpy라는 배열값 카피해 주는 함수가 있었다.
이러면 굳이 이중포문 안쓰고 이차원배열을 배껴올 수가 있다.
이 문제를 통해 시뮬레이션 문제에 대한 감을 잡아간다.
*/

int N, M, Map[8][8], Snum, numBuf, Clone[8][8], Vis[8][8], Dir[4][2] = { {1,0},{0,1},{-1,0},{0,-1} }, Max;
vector<pair<int,int>> Virus, Safe;
vector<int> sel;

void DFS(int x, int y) {
	int X, Y;
	for (int i = 0; i < 4; i++)
	{
		X = x + Dir[i][0]; Y = y + Dir[i][1];
		if (0 <= X && X < M && 0 <= Y && Y < N && !Vis[Y][X] && Clone[Y][X] != 1) {
			Vis[Y][X] = 1; Clone[Y][X] = 2; numBuf--;
			DFS(X, Y);
		}
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> Map[i][j];
			if (Map[i][j] == 2)
				Virus.push_back({ j,i });
			else if (!Map[i][j]) {
				Safe.push_back({ j,i });
				sel.push_back(0);
			}
		}
	}
	Snum = Safe.size() + Virus.size() - 3;
	for (int i = 0, j = sel.size() - 1; i < 3; i++, j--)
		sel[j] = 1;
	do {
		memset(Vis, 0, sizeof(Vis));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				Clone[i][j] = Map[i][j];
			}
		}
		numBuf = Snum;
		for (int i = 0; i < sel.size(); i++) {
			if (sel[i])
				Clone[Safe[i].second][Safe[i].first] = 1;
		}
		for (auto C : Virus) {
			if (!Vis[C.second][C.first]) {
				Vis[C.second][C.first] = 1;
				numBuf--;
				DFS(C.first, C.second);
			}
		}
		Max = max(numBuf, Max);
	} while (next_permutation(sel.begin(), sel.end()));
	cout << Max;
}