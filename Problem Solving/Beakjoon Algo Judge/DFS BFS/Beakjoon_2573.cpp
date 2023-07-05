#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2573
약간의 생각이 필요했던 탐색 문제이다.
일단 문제에서 주어지는 조건을 최대한 활용해야 시간 초과가 나지 않는다.
문제에서 1이상인 정수가 들어가는 칸은 최대 10000개라고 했기에 이차원 배열 이외에 
매 년이 지날 때마다 0이 아닌 정수가 저장되어 있는 칸이 어디인지 알 수 있는 저장소를 따로 
만들어두어 그 저장소 내에서 탐색을 진행하여 
매 년이 지날 때 마다 모든 이차원 배열을 돌지 않게 해야 속도가 빨라진다는 것을 알 수 있다.
그리고 이 저장소를 매년 탐색하면서 녹아 잠기는 빙산들을 빼주어야 한다.
그리고 이 빙산을 빼줄 때 빠지는 빙산의 좌표를 따로 저장해주어야 하는데 이유는 빙산이 잠겼다고 
그 블록을 바로 0으로 바꾸어 버리면 옆에 있는 빙산이 이 값에 영향을 받아 더 빨리 녹아 없어질 수 있다.
따라서 현재 상태에서 저장된 맵을 수정하지 않고 수정할 놈들만 고른 뒤에 탐색이 끝났다 싶으면
그때부터 따로 맵에 0을 만드는 작업을 해주어야 한다.
이런식으로 진행하며 빙산을 탐색하고 색칠 갯수 세는 로직 돌리면 답이 도출된다.
그리고 그냥 짜면서 보니까 이렇게 짜고 있긴했는데 
큐의 사이즈 만큼 큐를 for문 돌리고 넣은 녀석은 넣고 뺄 녀석은 빼는 이런 기법 먼가 다음에 이용해봐야 겠다.
이 문제를 통해 탐색 응용 문제에 대한 접근 능력을 높여간다.
*/

short Wid, Hei, Map[301][301], Dir[4][2] = { {1,0},{0,1},{-1,0},{0,-1} }, Div;
bool Vis[301][301];
queue <tuple<short, short, short>> Q;
queue <pair<short, short>> Zero;

void DFS(short R, short C)
{
	for (int i = 0; i < 4; i++)
	{
		short r = R + Dir[i][0], c = C + Dir[i][1];
		if (Map[r][c] && !Vis[r][c])
		{
			Vis[r][c] = 1; DFS(r, c);
		}
	}
}

void Color()
{
	short Size = Q.size(), R, C; Div = 0;
	for (int i = 0; i < Hei; i++) memset(Vis[i], 0, sizeof(bool) * Wid);
	for (int i = 0; i < Size; i++)
	{
		R = get<0>(Q.front()); C = get<1>(Q.front());
		if (!Vis[R][C])
		{
			Div++; Vis[R][C] = 1; DFS(R, C);
		}
		Q.push(Q.front()); Q.pop();
	}
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> Hei >> Wid;
	for (int i = 0; i < Hei; i++)
	{
		for (int j = 0; j < Wid; j++)
		{
			cin >> Map[i][j];
			if (Map[i][j]) Q.push({ i,j,0 });
		}
	}
	while (!Q.empty())
	{
		Color();
		if (Div >= 2) { cout << get<2>(Q.front()); return 0; }
		short Size = Q.size(), R, C, Cnt; Div = 0;
		for (int i = 0; i < Size; i++)
		{
			Cnt = 0;
			for (int j = 0; j < 4; j++)
			{
				R = get<0>(Q.front()) + Dir[j][0]; C = get<1>(Q.front()) + Dir[j][1];
				if (!Map[R][C]) Cnt++;
			}
			if (Map[get<0>(Q.front())][get<1>(Q.front())] <= Cnt)
				Zero.push({ get<0>(Q.front()), get<1>(Q.front()) });
			else
			{
				Map[get<0>(Q.front())][get<1>(Q.front())] -= Cnt;
				Q.push({ get<0>(Q.front()),get<1>(Q.front()),get<2>(Q.front()) + 1 });
			}
			Q.pop();
		}
		while (!Zero.empty())
		{
			Map[Zero.front().first][Zero.front().second] = 0;
			Zero.pop();
		}
	}
	cout << 0;
}