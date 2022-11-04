#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/11967
처음 보는 유형이라 애를 먹었다...
비효율적으로 매번 BFS를 돌리는 문제 유형이라니.... 기억해두어야겠다.
주석처리 해놓은 방식은 우선순위 큐를 이용해 불켜진 순서에 따라 이동가능하게 만들었는데....
왜 자꾸 틀렸습니다라고 나오는지 이해가 아직도 안간다.
시간 있을 때 한번 고민해보자.
정석적인 방식은 그냥 새로 불이 켜질 때마다 BFS를 돌려주는 것이다.
왜 이렇게 비효율적으로 해야하냐면 다른 방도가 딱히 없다.
만약에 (1,1)번방 스위치 키고 밝아진 방 중 하나인 (1,2)번방 키고 밝아진 방 중 하나인 (1,3)번방을 키는데 
(1,3)방에서 킨 방 중에 (2,1)이 속해 (2,1)이 밝아진 상태다. 현재 위치는 (1,3)인데 
BFS에서는 (1,3)에서 (2,1)로 돌아가는 방법이 없기에 (왜냐하면 이미 (2,1)은 큐에 넣는 시기를 놓쳤다.)
처음부터 다시 BFS를 돌려야한다.
이렇게 돌아가서 그 방에 도달하여 그 방 스위치를 켜야하는 상황이 연출되는 이 문제는
어쩔 수 없이 BFS를 불이 새로 켜진 방이 없을 때 까지 계속해서 돌려주어야 한다.
불이 새로 켜진 곳이 있는가 없는가를 알 수 있는 방법은 
BFS마다 초기화되는 불의 켜짐 유무를 담는 상태 배열 Light와 
초기화되지 않고 여태 BFS마다 계속 새로 불 켜짐이 추가되는 Map을 비교하여 
Map에서는 꺼짐상태인데 Light에서 켜짐상태다? 이러면 BFS를 다시 돌려봐야 한다.
새로 켜진 곳이 징검다리 역할을 하여 불 켜짐 영역 확장을 도모할 가능성이 있기 때문에...
이 문제를 풀며 BFS를 계속해서 갱신하여 주는 새로운 너비 탐색 문제 유형에 대해 알아간다.
*/

#define Cord pair<short, short>

short M, N, Cnt = 1, col, row, lcol, lrow, Dir[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };
bool Light[101][101], Vis[101][101], Map[101][101], flag;
vector<Cord> Link[101][101];

int BFS()
{
	for (int i = 1; i <= N; i++)
	{
		memset(Vis[i], 0, sizeof(Vis[i]));
		memset(Light[i], 0, sizeof(Light[i]));
	}
	queue<Cord> Q; Q.push({ 1,1 }); Map[1][1] = Light[1][1] = Vis[1][1] = 1;
	int lup = 1; short R, C;
	while (!Q.empty())
	{
		for (int i = 0; i < Link[Q.front().first][Q.front().second].size(); i++)
		{
			R = Link[Q.front().first][Q.front().second][i].first;
			C = Link[Q.front().first][Q.front().second][i].second;
			if (!Light[R][C]) {
				Light[R][C] = 1; lup++;
				if (Light[R][C] && !Map[R][C]) {
					Map[R][C] = 1; flag = true;
				}
			}
		}
		for (int i = 0; i < 4; i++)
		{
			R = Q.front().first + Dir[i][0];
			C = Q.front().second + Dir[i][1];
			if (0 < R && R <= N && 0 < C && C <= N && Map[R][C] && !Vis[R][C])
			{
				Q.push({ R,C }); Vis[R][C] = 1;
			}
		}
		Q.pop();
	}
	return lup;
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		cin >> row >> col >> lrow >> lcol;
		Link[row][col].push_back({ lrow,lcol });
	}
	do {
		flag = false;
		Cnt = BFS();
	} while (flag);
	cout << Cnt;
}

/*
#define Cord pair<short, short>
#define Cord_2 tuple<short, short, short>

short M, Cnt = 1, N, col, row, lcol, lrow, Dir[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };
short Map[101][101];
bool Light[101][101], Vis[101][101];
vector<Cord> Link[101][101];

void Lightup()
{
	queue<Cord> Q;
	Map[1][1] = 1;
	Q.push({ 1,1 });
	Cord Buf;
	while (!Q.empty())
	{
		for (int i = 0; i < Link[Q.front().first][Q.front().second].size(); i++)
		{
			Buf = Link[Q.front().first][Q.front().second][i];
			if (!Map[Buf.first][Buf.second])
			{
				Map[Buf.first][Buf.second] = Map[Q.front().first][Q.front().second] + 1;
				Q.push(Buf);
			}
		}
		Q.pop();
	}
}

void BFS()
{
	priority_queue<Cord_2, vector<Cord_2>, greater<Cord_2>> Q;
	Q.push({ 1, 1, 1 }); Light[1][1] = Vis[1][1] = 1;
	short R, C, Max = 1; Cord Buf; Cord_2 Top;
	while (!Q.empty())
	{
		Top = Q.top(); Q.pop();
		if (get<0>(Top) > Max + 1) break;
		else Max = max(get<0>(Top), Max);
		for (int i = 0; i < Link[get<1>(Top)][get<2>(Top)].size(); i++)
		{
			Buf = Link[get<1>(Top)][get<2>(Top)][i];
			if (!Light[Buf.first][Buf.second])
			{
				Light[Buf.first][Buf.second] = 1; Cnt++;
			}
		}
		for (int i = 0; i < 4; i++)
		{
			R = get<1>(Top) + Dir[i][0];
			C = get<2>(Top) + Dir[i][1];
			if (0 < R && R <= N && 0 < C && C <= N && !Vis[R][C] && Map[R][C])
			{
				Vis[R][C] = 1; Q.push({ Map[R][C],R,C });
			}
		}
	}
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		cin >> row >> col >> lrow >> lcol;
		Link[row][col].push_back({ lrow,lcol });
	}
	Lightup(); BFS();
	cout << Cnt;
}
*/