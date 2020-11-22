#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/7569
시작 점이 여러개라 BFS로 접근해야 했던 문제이다.
기존 BFS 탐색 문제에서 약간 다른 점이라면 3차원 상에서 탐색을 하기에
들러줘야하는 방향이 6방향이라는 점이다....
이 점만 유의하면 어렵지 않게 풀 수 있다.
*/

short Dir[6][3] = { {0,0,1},{0,1,0},{1,0,0},{0,0,-1},{0,-1,0},{-1,0,0} };
short Height, Width, Depth, Map[101][101][101], Input, B_zero;
int Vis[101][101][101], MAX = 1;
queue<tuple<short, short, short>> Q;

bool is_OK(short Row, short Col, short Dep)
{
	if (0 <= Row && Row < Height && 0 <= Col && Col < Width 
		&& 0 <= Dep && Dep < Depth && Map[Dep][Row][Col] == 0) return true;
	return false;
}

void BFS()
{
	short X, Y, Z;
	while (!Q.empty())
	{
		for (int i = 0; i < 6; i++)
		{
			Z = get<0>(Q.front()) + Dir[i][0]; Y = get<1>(Q.front()) + Dir[i][1]; X = get<2>(Q.front()) + Dir[i][2];
			if (is_OK(Y, X, Z) && Vis[Z][Y][X] == 0)
			{
				Q.push({ Z,Y,X }); Vis[Z][Y][X] = Vis[get<0>(Q.front())][get<1>(Q.front())][get<2>(Q.front())] + 1;
				MAX = max(MAX, Vis[Z][Y][X]); Map[Z][Y][X] = 1; B_zero--;
			}
		}
		Q.pop();
	}
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> Width >> Height >> Depth;
	for (int k = 0; k < Depth; k++)
	{
		for (int i = 0; i < Height; i++)
		{
			for (int j = 0; j < Width; j++)
			{
				cin >> Input;
				Map[k][i][j] = Input;
				if (Input == 1) { Q.push({ k, i, j }); Vis[k][i][j] = 1; }
				if (Input == 0) B_zero++;
			}
		}
	}
	BFS(); 
	if (B_zero != 0) cout << - 1;
	else cout << MAX - 1;
}