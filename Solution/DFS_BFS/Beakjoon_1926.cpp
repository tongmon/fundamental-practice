#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1926
기본적인 탐색 문제...
탐색에 대한 기본 코드 구조가 머리에 박혀있다면 간단히 풀 수 있다.
워낙 정형화되어 있어 설명할 것도 없다.
*/

int Width, Height, Dir[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
bool Vis[501][501];
int Map[501][501], Max, Cur, Color;

bool is_OK(int Col, int Row)
{
	if (0 <= Col && Col < Width && 0 <= Row && Row < Height && Map[Row][Col]) return true;
	return false;
}

void DFS(int Col, int Row)
{
	Cur++;
	for (int i = 0; i < 4; i++)
	{
		if (is_OK(Col + Dir[i][0], Row + Dir[i][1]) && !Vis[Row + Dir[i][1]][Col + Dir[i][0]])
		{
			Vis[Row + Dir[i][1]][Col + Dir[i][0]] = true; DFS(Col + Dir[i][0], Row + Dir[i][1]);
		}
	}
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> Height >> Width;
	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			cin >> Map[i][j];
		}
	}
	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			if (Map[i][j] == 1 && Vis[i][j] == false)
			{
				Color++; Vis[i][j] = true; Cur = 0;
				DFS(j, i); Max = max(Max, Cur);
			}
		}
	}
	cout << Color << '\n' << Max;
}