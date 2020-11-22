#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/7562
기본적인 탐색 문제이다.
기존 4방향 탐색에서 나이트가 갈 수 있는 
8방향으로 달라진 것 외에는 변경점이 없다.
이 문제를 통해 BFS 문제 푸는 시간을 단축해 나간다. 
*/

int T, Size, Stx, Sty, Enx, Eny, Vis[301][301];
short Dir[8][2] = { {2, 1}, {1, 2}, {-1, 2}, {2, -1}, {1, -2}, {-2, 1}, {-2, -1}, {-1, -2} };

int BFS(queue<pair<int, int>> *Q)
{
	int R, C;
	while (!Q->empty())
	{
		if (Q->front().first == Eny && Q->front().second == Enx)
			return Vis[Q->front().first][Q->front().second] - 1;
		for (int i = 0; i < 8; i++)
		{
			R = Q->front().first + Dir[i][0]; C = Q->front().second + Dir[i][1];
			if (0 <= R && R < Size && 0 <= C && C < Size && !Vis[R][C])
			{
				Q->push({ R,C }); Vis[R][C] = Vis[Q->front().first][Q->front().second] + 1;
			}
		}
		Q->pop();
	}
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> T;
	for (int i = 0;i < T;i++)
	{
		queue<pair<int, int>> Q;
		cin >> Size >> Stx >> Sty >> Enx >> Eny;
		Q.push({ Sty, Stx }); Vis[Sty][Stx] = 1;
		cout << BFS(&Q) << '\n';
		for (int i = 0; i < Size; i++) 
			memset(Vis[i], 0, sizeof(int) * Size);
	}
}