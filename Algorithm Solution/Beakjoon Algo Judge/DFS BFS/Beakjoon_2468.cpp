#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2468
탐색 문제지만 3중 포문이 돌아서 시간초과가 나느냐를 따져봐야하는 문제다.
3중 포문이 돌아도 시간초과는 안난다. 제일 커봐야 100 * 100 * (100 + 알파) 인데 
1초에 평균 1억번 계산이 돈다는 것을 생각해보면 가능한 수치였다.
따라서 이 문제는 그냥 탐색 색칠 놀이 문제인데 특정 수 이상의 수를 가진 블록만 색칠한다라는
약간의 아이디어 변형이 섞인 문제라고 할 수 있겠다.
그리고 한가지 실수하지 말하야 하는게 비가 안내리는 경우도 있기에 높이 0을 넘는 블록들 제거하는 경우도 따져줘야 한다.
이 문제를 통해 BFS 변형 문제에 대한 감을 높여간다.
*/

int Mcnt, Ccnt;
short Size, Map[101][101], Max, Dir[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };
bool Vis[101][101];

void BFS(short lvl, short row, short col)
{
	queue<pair<short, short>> Q;
	Q.push({ row, col }); Vis[row][col] = 1;
	short R, C;
	while (!Q.empty())
	{
		for (int i = 0; i < 4; i++)
		{
			R = Q.front().first + Dir[i][0]; C = Q.front().second + Dir[i][1];
			if (0 <= R && R < Size && 0 <= C && C < Size && lvl < Map[R][C] && !Vis[R][C])
			{
				Q.push({ R,C }); Vis[R][C] = 1;
			}
		}
		Q.pop();
	}
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> Size;
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			cin >> Map[i][j];
			Max = max(Max, Map[i][j]);
		}
	}
	for (int i = 0; i <= Max; i++)
	{
		Ccnt = 0;
		for (int k = 0; k < Size; k++) memset(Vis[k], 0, sizeof(bool) * Size);
		for (int k = 0; k < Size; k++)
		{
			for (int j = 0; j < Size; j++)
			{
				if (!Vis[k][j] && i < Map[k][j]) {
					Ccnt++; BFS(i, k, j);
				}
			}
		}
		if (Ccnt > Mcnt) Mcnt = Ccnt;		
	}
	cout << Mcnt;
}