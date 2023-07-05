#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2583
탐색 문제이다.
그냥 탐색 하면서 색칠 놀이를 시키는 것이 지루했는지 입력 방식에서 차이를 둔 문제이다.
입력 시에는 오픈지엘에서 마우스 좌표가 화면 좌표랑 달라 변환 했던 방식과 비슷하게
최대 길이에서 현 좌표를 빼면 된다.
이렇게 전체 맵을 사각형으로 덮힌 부분을 1로 아닌 부분을 0으로 해서 0으로 되어있는 부분의 크기를
DFS로 구해가면 해결되는 문제다.
이 문제를 통해 탐색 문제에 대한 감을 높여간다.
*/

short Wid, Hei, Num, Stx, Sty, Enx, Eny, Cur;
char Vis[101][101], Map[101][101], Dir[4][2] = { {1,0}, {0,1}, {-1,0}, {0,-1} };

void DFS(short Row, short Col)
{
	Cur++;
	for (int i = 0; i < 4; i++)
	{
		short R = Row + Dir[i][0], C = Col + Dir[i][1];
		if (0 <= R && R < Hei && 0 <= C && C < Wid && Map[R][C] == Vis[R][C])
		{
			Vis[R][C] = 1; DFS(R, C);
		}
	}
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> Hei >> Wid >> Num;
	vector<int> Ans;
	for (int i = 0; i < Num; i++)
	{
		cin >> Stx >> Sty >> Enx >> Eny;
		for (int k = Hei - Eny; k < Hei - Sty; k++)
		{
			for (int j = Stx; j < Enx; j++)
			{
				Map[k][j] = 1;
			}
		}
	}
	for (int i = 0; i < Hei; i++)
	{
		for (int j = 0; j < Wid; j++)
		{
			Cur = 0;
			if (!Vis[i][j] && !Map[i][j])
			{
				Vis[i][j] = 1; DFS(i, j);
			}
			if (Cur) Ans.push_back(Cur);
		}
	}
	cout << Ans.size() << '\n';
	sort(Ans.begin(), Ans.end());
	for (auto i : Ans) cout << i << ' ';
}