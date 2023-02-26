#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1600
방문 배열을 응용한 너비 탐색 문제이다.
방문 배열을 약간이라도 잘못짜면 큐가 터져 메모리초과가 난다.
이거와 비슷한 유형의 문제인 2206번을 풀어서 이 문제도 비슷한 방식으로 풀게 되었다.
일단 이 문제도 점프 K번을 한 상태에서의 방문과 점프 K-1번을 한 상태... 점프를 안한 상태에서의 방문 배열이 모두 달라야 한다.
서로의 방문 상태가 서로의 이동 경로에 영향을 끼치면 안되기 때문에 점프를 할 때마다 다른 차원으로 이동 시켜 방문을 다루어야 한다.
따라서 Vis[31][201][201] 배열이 선언된다.
이 방문 배열을 활용할 경우 주의해야 하는 점은 Vis[점프 횟수][row][col]이기에
점프 횟수에 따른 방문 구별을 명확하게 해야한다.
예를 들어 점프를 한번 해서 갈 수 있는 곳이 밝혀지면 그 곳을 간다는 표시는 Vis[점프 횟수 + 1][row][col] 이곳에 해주어야 한다.
이렇게 안해주면 메모리 초과가 난다.
이 문제를 통해 이러한 차원 분류 너비 탐색 유형에 대한 접근법을 좀 더 알아간다.
*/

short K, W, H, Dir[12][2] = { {1,0},{0,1},{-1,0},{0,-1},{2,1},{1,2},{1,-2},{-2,1},{-1,2},{2,-1},{-1,-2},{-2,-1} };
bool Map[201][201], Vis[31][201][201];

int BFS()
{
	queue<tuple<short, short, char, int>> Q;
	for (int i = 0; i < 31; i++) Vis[i][0][0] = 1;
	Q.push({ 0,0,0,1 });
	short R, C;
	while (!Q.empty())
	{
		for (int i = 0; i < 12; i++)
		{
			if (i >= 4 && K <= get<2>(Q.front())) break;
			R = get<0>(Q.front()) + Dir[i][0]; C = get<1>(Q.front()) + Dir[i][1];
			if (0 <= R && R < H && 0 <= C && C < W && !Map[R][C])
			{
				if (i < 4 && !Vis[get<2>(Q.front())][R][C])
				{
					Q.push({ R,C,get<2>(Q.front()),get<3>(Q.front()) + 1 });
					Vis[get<2>(Q.front())][R][C] = 1;
				}
				else if (i > 3 && !Vis[get<2>(Q.front()) + 1][R][C])
				{
					Q.push({ R,C,get<2>(Q.front()) + 1,get<3>(Q.front()) + 1 });
					Vis[get<2>(Q.front()) + 1][R][C] = 1;
				}
			}
			if (R == H - 1 && C == W - 1) return get<3>(Q.front());
		}
		Q.pop();
	}
	return -1;
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> K;
	cin >> W >> H;
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			cin >> Map[i][j];
		}
	}
	if (W == 1 && H == 1) cout << 0;
	else cout << BFS();
}