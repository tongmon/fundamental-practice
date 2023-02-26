#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/11403
방향성 그래프 탐색 문제였다.
정점 개수 만큼 DFS를 시행하여 그 점에서 출발하여 특정 점으로 도달할 수 있는지를 판단한다.
따라서 Vis배열을 초기화하면서 진행한다.
이것을 정점 수만큼 모두 시행하면 Ans에 도달 가능 유무가 채워져있게 된다.
문제 유형은 플로이드 와샬이라고 쓰여있는데 굳이 삼중 for문 돌리지 않고 그보다
좀 더 적은 시간복잡도의 가능성이 있는 DFS를 단일 포문 돌려 풀게 되었다.
이 문제로 플로이드 와샬 유형을 살짝 맛봤다.
*/

short Size, Input;
bool Ans[101][101], Vis[101];
vector<short> Vert[101];

void DFS(short Cur, short root)
{
	for (int i = 0; i < Vert[Cur].size(); i++)
	{
		if (!Vis[Vert[Cur][i]]) {
			Ans[root][Vert[Cur][i]] = Ans[Cur][Vert[Cur][i]] = Vis[Vert[Cur][i]] = 1;
			DFS(Vert[Cur][i], root);
		}
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
			cin >> Input; 
			if (Input) Vert[i].push_back(j);
		}
	}
	for (int i = 0; i < Size; i++)
	{
		memset(Vis, 0, sizeof(bool) * Size);
		DFS(i, i);
	}
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			cout << Ans[i][j] << ' ';
		}
		cout << '\n';
	}
}