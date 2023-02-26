#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/17070
Dp나 DFS 방식으로 모두 풀 수 있는 문제였다.
하지만 이 문제의 2번째 유형인 17069번은 시간 제한이 0.5초라
Dp로 접근해야 한다.
처음에 Dp로 접근했는데 이게 파이프가 모이는 쪽으로 생각한 Dp가 아니라
파이프를 뿌리는 방향으로 생각한 Dp라서 3차원 배열 2개를 쓰게 되었다.
가로인 상태면 사선 상태의 Cnt, 가로 상태의 Cnt 배열에 개수를 넣는 방식이다.
다른 사람의 Dp 풀이는 가로 상태, 세로 상태, 사선 상태의 배열들이 모여서 한 칸을
만드는 방식이라 Cnt 배열만 필요하고 Pip배열이 필요없다.
사실 내 방식에서 Pip을 빼고 그 부분을 Cnt로 바꾸면 되는 것이였다.
괜히 복잡하게 생각해서 상태를 나눈다고 파이프 상태 Pip 배열을 생성했는데.. 
Cnt가 채워지면서 자동으로 체크되는 부분이라 용량 낭비였다.
이 문제를 통해 Dp에 대한 문제 접근 속도를 늘려간다.
*/

int N, Map[33][33];
long long Cnt[33][33][3];
bool Pip[33][33][3];

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> Map[i][j];
	Pip[0][1][0] = 1; Cnt[0][1][0] = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (Map[i][j])
				continue;
			bool stat[3] = { 0,0,0 };
			if (j + 1 < N && !Map[i][j + 1])
				stat[0] = 1;
			if (j + 1 < N && i + 1 < N && !Map[i + 1][j + 1] && !Map[i][j + 1] && !Map[i + 1][j])
				stat[1] = 1;
			if (i + 1 < N && !Map[i + 1][j])
				stat[2] = 1;
			for (int k = 0; k < 3; k++) {
				if (Pip[i][j][k]) {
					if (stat[0] && k != 2) {
						Cnt[i][j + 1][0] += Cnt[i][j][k];
						Pip[i][j + 1][0] = 1;
					}
					if (stat[1]) {
						Cnt[i + 1][j + 1][1] += Cnt[i][j][k];
						Pip[i + 1][j + 1][1] = 1;
					}
					if (stat[2] && k) {
						Cnt[i + 1][j][2] += Cnt[i][j][k];
						Pip[i + 1][j][2] = 1;
					}
				}
			}
		}
	}
	N--;
	cout << Cnt[N][N][0] + Cnt[N][N][1] + Cnt[N][N][2];
}

/*
// DFS 방식... 느리다. 16칸이면 2의 16승이라 1초 안에 계산이 가능은 하다.

int N, Map[17][17], Ans;

void DFS(int x, int y, int state) {
	if (x == N - 1 && y == N - 1) {
		Ans++;
		return;
	}
	if (!state) {
		if (x + 1 < N && !Map[y][x + 1]) {
			DFS(x + 1, y, 0);
		}
		if (x + 1 < N && y + 1 < N && !Map[y + 1][x + 1] && !Map[y][x + 1] && !Map[y + 1][x]) {
			DFS(x + 1, y + 1, 1);
		}
	}
	else if (state == 1) {
		if (x + 1 < N && !Map[y][x + 1]) {
			DFS(x + 1, y, 0);
		}
		if (x + 1 < N && y + 1 < N && !Map[y + 1][x + 1] && !Map[y][x + 1] && !Map[y + 1][x]) {
			DFS(x + 1, y + 1, 1);
		}
		if (y + 1 < N && !Map[y + 1][x]) {
			DFS(x, y + 1, 2);
		}
	}
	else {
		if (y + 1 < N && !Map[y + 1][x]) {
			DFS(x, y + 1, 2);
		}
		if (x + 1 < N && y + 1 < N && !Map[y + 1][x + 1] && !Map[y][x + 1] && !Map[y + 1][x]) {
			DFS(x + 1, y + 1, 1);
		}
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> Map[i][j];
	DFS(1, 0, 0);
	cout << Ans;
}
*/