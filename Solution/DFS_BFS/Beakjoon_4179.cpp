#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/4179
불이 번지는 경우를 BFS로 생각하고 푸는 문제이다.
일단 지훈과 불이라는 두 개의 시작점이 있으니 BFS를 떠올릴 수 있어야하고
불을 먼저 순회돌리고 이렇게 해서 도출되는 불이 어떤 시간에 어떻게 번졌냐에 대한 정보를 가지고
지훈이를 불을 피해 요리 조리 순회시켜 탈출하면 되는 문제이다.
근데 이렇게 풀고 자꾸 틀리는 경우가 발생했는데 이유는
내가 불이 번지지 않는 경우를 고려하지 않았다...
4 4
###F
#J.#
#..#
#..#
이렇게 불이 번지지 않고 편하게 지훈이가 걸어나갈 수 있는 경우도 고려해야 한다는 사실을 몰랐다....
이러한 반례를 찾아내는 능력을 기를 수 있도록 연습해야 된다.
그리고 이런 류의 출발점이 여러개인데 한 녀석의 경로가 다른 녀석의 경로에 영향을 끼치는 문제들은
이렇게 단계를 나누어 풀어야 한다는 것을 알아가자!
*/

int Height, Width, Dir[4][2] = { {1,0}, {0,1}, {-1,0}, {0,-1} };
char Map[1001][1001];
int Fire[1001][1001], Jihun[1001][1001];
queue<pair<int, int>> Burn, Step;

void BFS_F()
{
	int Row, Col;
	while (!Burn.empty())
	{
		for (int i = 0; i < 4; i++)
		{
			Row = Burn.front().first + Dir[i][0]; Col = Burn.front().second + Dir[i][1];
			if (0 <= Row && Row < Height && 0 <= Col && Col < Width
				&& Map[Row][Col] != '#' && Fire[Row][Col] == 0)
			{
				Burn.push({ Row, Col }); 
				Fire[Row][Col] = Fire[Burn.front().first][Burn.front().second] + 1;
			}
		}
		Burn.pop();
	}
}

int BFS_J()
{
	int Row, Col;
	while (!Step.empty())
	{
		for (int i = 0; i < 4; i++)
		{
			Row = Step.front().first + Dir[i][0]; Col = Step.front().second + Dir[i][1];
			if (0 > Row || Row >= Height || 0 > Col || Col >= Width)
				return Jihun[Step.front().first][Step.front().second];
			if (Map[Row][Col] == '.' && Jihun[Row][Col] == 0
				&& (Jihun[Step.front().first][Step.front().second] + 1 < Fire[Row][Col] || Fire[Row][Col] == 0))
			{
				Step.push({ Row, Col });
				Jihun[Row][Col] = Jihun[Step.front().first][Step.front().second] + 1;
			}
		}
		Step.pop();
	}
	return -2;
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
			if (Map[i][j] == 'J') { Step.push({ i,j }); Jihun[i][j] = 1; }
			if (Map[i][j] == 'F') { Burn.push({ i,j }); Fire[i][j] = 1; }
		}
	}
	BFS_F(); int Temp = BFS_J();
	if (Temp != -2) cout << Temp;
	else cout << "IMPOSSIBLE";
}