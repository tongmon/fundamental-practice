#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/5427
첫번째 출발 BFS 탐색 경로가 다른 출발 BFS 탐색 경로에 영향을 주는 문제
첫번째 탐색에서 각 블록마다의 이동 경로를 구하고
이에 따라 두번째 탐색에서 적절히 피해다니면서 경로를 탐색하면 풀리는 문제다.
사실상 4179번 문제에서 테스트 케이스만 많아진 문제라고 볼 수 있다.
4179번을 먼저 풀어서 푸는데 오래걸리진 않았다.
실수를 몇가지 한 것이 있는데 memset에서 크기 조절 잘하자... 확실히 memset이 실수하기 좋은 함수다. 잘보고 이용할 것
이 문제를 통해 BFS 응용력을 길러간다.
*/

int T, Wid, Hei, San[1001][1001], Fire[1001][1001];
char Map[1001][1001], Dir[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };
queue<pair<int, int>> Step, Burn;

int BFS()
{
	int R, C;
	for (int i = 0; i < Hei; i++)
	{
		memset(San[i], 0, sizeof(int) * Wid);
		memset(Fire[i], 0, sizeof(int) * Wid);
	}
	while (!Burn.empty())
	{
		for (int i = 0; i < 4; i++)
		{
			R = Burn.front().first + Dir[i][0]; C = Burn.front().second + Dir[i][1];
			if (0 <= R && R < Hei && 0 <= C && C < Wid && Map[R][C] != '#' && !Fire[R][C])
			{
				Fire[R][C] = Fire[Burn.front().first][Burn.front().second] + 1;
				Burn.push({ R,C });
			}
		}
		Burn.pop();
	}
	while (!Step.empty())
	{
		for (int i = 0; i < 4; i++)
		{
			R = Step.front().first + Dir[i][0]; C = Step.front().second + Dir[i][1];
			if (0 > R || R >= Hei || 0 > C || C >= Wid) return ++San[Step.front().first][Step.front().second];
			else if (Map[R][C] == '.' && !San[R][C] && 
				((Fire[R][C] - 1 > San[Step.front().first][Step.front().second]) || !Fire[R][C]))
			{
				San[R][C] = San[Step.front().first][Step.front().second] + 1;
				Step.push({ R,C });
			}
		}
		Step.pop();
	}
	return -1;
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		cin >> Wid >> Hei;
		while (!Step.empty()) Step.pop();
		for (int j = 0; j < Hei; j++)
		{
			for (int k = 0; k < Wid; k++)
			{
				cin >> Map[j][k];
				if (Map[j][k] == '@') {
					Step.push({ j,k }); San[j][k] = 1;
				}
				else if (Map[j][k] == '*') {
					Burn.push({ j,k }); Fire[j][k] = 1;
				}
			}
		}
		int Temp = BFS();
		if (Temp > 0) cout << Temp << '\n';
		else cout << "IMPOSSIBLE\n";
	}
}