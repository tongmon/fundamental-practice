#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/6593
기존 탐색 문제와 달라진 점은 3차원이라는 점이다.
그 외에는 별 다를 것 없이 BFS나 DFS로 탐색을 하면서 Vis에 경로 수 세겨가면서
초기화 잘해가면서 풀게 된다면 풀 수 있다.
이 문제를 통해 탐색 문제를 푸는 속도를 줄여간다.
*/

int Wid, Hei, Dep;
char Map[31][31][31], Dir[6][3] = { {1,0,0},{0,1,0},{0,0,1},{-1,0,0},{0,-1,0},{0,0,-1} };
int Vis[31][31][31];
queue<tuple<short, short, short>> Q;

int BFS()
{
	int D, R, C;
	while (!Q.empty())
	{
		for (int i = 0; i < 6; i++)
		{
			D = get<0>(Q.front()) + Dir[i][0];
			R = get<1>(Q.front()) + Dir[i][1];
			C = get<2>(Q.front()) + Dir[i][2];
			if (0 <= D && D < Dep && 0 <= R && R < Hei && 0 <= C && C < Wid && !Vis[D][R][C])
			{
				if (Map[D][R][C] == 'E') return Vis[get<0>(Q.front())][get<1>(Q.front())][get<2>(Q.front())];
				else if (Map[D][R][C] == '.')
				{
					Q.push({ D,R,C });
					Vis[D][R][C] = Vis[get<0>(Q.front())][get<1>(Q.front())][get<2>(Q.front())] + 1;
				}
			}
		}
		Q.pop();
	}
	return -1;
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	while (true)
	{
		cin >> Dep >> Hei >> Wid;
		if (!Dep) break;
		while (!Q.empty()) Q.pop();
		for (int i = 0; i < Dep; i++)
		{
			for (int j = 0; j < Hei; j++) memset(Vis[i][j], 0, sizeof(int) * Wid);
		}
		for (int i = 0; i < Dep; i++)
		{
			for (int j = 0; j < Hei; j++)
			{
				for (int k = 0; k < Wid; k++)
				{
					cin >> Map[i][j][k];
					if (Map[i][j][k] == 'S')
					{
						Q.push({ i,j,k }); Vis[i][j][k] = 1;
					}
				}
			}
		}
		int Temp = BFS();
		if (Temp != -1) cout << "Escaped in " << Temp << " minute(s).\n";
		else cout << "Trapped!\n";
	}
}