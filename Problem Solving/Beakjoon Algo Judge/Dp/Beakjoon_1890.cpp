#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1890
격자 Dp문제
오른쪽으로 가는 경우와 아래로 가는 경우를 따져주어
해당 칸에 도달할 수 있는 가짓수를 기록해 나가면 된다.
만약 지금 현재 칸으로 도달 가능한 경우의 수가 3가지라고 하면
그 해당 칸에서 오른쪽, 아래쪽 으로 갈 수 있는 칸에
3을 더해주면 된다.
계속해나가면서 마지막 도착지의 Dp 경우의 수를 세주면 그게 답이 된다.
*/

int N, Map[100][100];
long long Cnt[100][100];

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> Map[i][j];
	Cnt[0][0] = 1;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			if (!Map[i][j])
				continue;
			int R = Map[i][j] + j, D = Map[i][j] + i;
			if (R < N)
				Cnt[i][R] += Cnt[i][j];
			if (D < N)
				Cnt[D][j] += Cnt[i][j];
		}
	N--;
	cout << Cnt[N][N];
}