#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2638
문제를 유심히 읽지를 않고 대충대충 넘겨서... 결국 힌트를 보고 풀었다.
중요한 조건인 '가장자리가 무조건 공기이다' 라는 조건을 읽지를 않았다....
내가 처음에 접근을 한 방식은 치즈를 중심으로 탐색이 진행되는데
가장자리는 무조건 공기이기 때문에 공기를 중심으로 DFS를 통해 계속 맵을 
확장해 나가는 풀이가 훨씬 짜기 쉽고 효율적이다.
일단 치즈가 두면 이상 공기와 접촉했는지 아닌지는 탐색을 통해
그 블록을 몇번 터치하는지를 보면 된다.
공기를 지났다면 -1로 체크를 하고 치즈를 지났다면 그 블록의 수를 하나 증가 시킨다.
결국 1이 였던 치즈블록이 3 이상이 되면 공기와 2면 이상 접촉되었다는 뜻이므로
그 블록은 공기와 같은 0으로 변한다.
때로는 문제를 반대로 생각하는 습관을 들이자. 
예전에 자각하고 있던 건데 오래되어서 감을 잃었다보다.
이 문제를 통해 반대로 생각하는 습관의 중요성을 알고 간다.
*/

int Map[101][101], N, M, Dir[4][2] = { {1,0},{0,1},{0,-1},{-1,0} }, Ans;

int Meltdown() {
	int Cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (Map[i][j] == 1 || Map[i][j] == 2) {
				Map[i][j] = 1;
				Cnt++;
			}
			else Map[i][j] = 0;
		}
	}
	return Cnt;
}

void DFS(int x, int y) {
	Map[x][y] = -1;
	for (int i = 0; i < 4; i++) {
		int bx = x + Dir[i][0], by = y + Dir[i][1];
		if (0 <= bx && bx < N && 0 <= by && by < M) {
			if (Map[bx][by] > 0) 
				Map[bx][by]++;
			else if (!Map[bx][by])
				DFS(bx, by);
		}
	}
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> Map[i][j];
	while (Meltdown()) {
		DFS(0, 0);
		Ans++;
	}
	cout << Ans;
}