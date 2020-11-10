#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/10026
탐색 문제 중에 색깔 칠하는 놀이를 약간 변형한 문제다.
일단 색맹과 일반인의 색칠 구분이 좀 달라서 서로 다른 배열을 기준으로 색칠한다.
색을 칠할 때는 현재 가리키는 블록과 같은 색만 칠해나가고 Vis 방문 배열에 표시한다.
위의 두 아이디어를 이용하면 원활히 문제가 풀릴 것이다.
다른 사람 풀이를 보니 나와 별 다른건 없고 대신 R,G,B가 적힌 맵을 걍 하나로 하고
색약 넓이 탐색 바로 전에 R을 G로 바꿔주는 방식을 택했다.
나보다 메모리는 안쓰겠지만 시간이 느려질 것이다.
이 문제를 통해 탐색 문제 푸는 속도를 더 빠르게 만들어 나간다.
*/

int Size, Bsize, Nsize;
char Blind[101][101], Norm[101][101], Dir[4][2] = { {0,1}, {1,0}, {-1,0}, {0,-1} }, In;
bool VisB[101][101], VisN[101][101];

void BFS(char Co, bool Vis[][101] , char Ary[][101], pair<short, short> A)
{
	queue<pair<short, short>> Q;
	Vis[A.first][A.second] = 1; Q.push(A);
	short C, R;
	while (!Q.empty())
	{
		for (int i = 0; i < 4; i++)
		{
			R = Q.front().first + Dir[i][0]; C = Q.front().second + Dir[i][1];
			if (0 <= R && R < Size && 0 <= C && C < Size && Co == Ary[R][C] && !Vis[R][C])
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
			cin >> In; Norm[i][j] = In;
			if (In == 'R' || In == 'G') Blind[i][j] = 'M';
			else Blind[i][j] = 'B';
		}
	}
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			if (!VisB[i][j]) {
				BFS(Blind[i][j], VisB, Blind, { i,j }); Bsize++;
			}
			if (!VisN[i][j]) {
				BFS(Norm[i][j], VisN, Norm, { i,j }); Nsize++;
			}
		}
	}
	cout << Nsize << ' ' << Bsize;
}