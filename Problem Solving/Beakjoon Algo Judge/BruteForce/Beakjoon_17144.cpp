#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/17144
구현력을 테스트해보는 문제였다.
먼지 확산은 미로찾기에서 쓰이던 방향을 사용해서 문제에 주어진 조건대로
흩뿌리면 된다.
동시에 먼지의 진원지부터 흩뿌리는 것이기에 서로 흩뿌리는 값들이 다른 먼지 지원지에
영향을 끼치면 안되기에 흩뿌려지는 먼지들을 따로 저장해놨다가 다 흩뿌려지는 먼지 값을
구했으면 그 때가서 저장했던 값들을 원래 지면에 있던 먼지에 더해주어야 한다.
그리고 공기청정기 가동을 해야하는데 이건 조금 헷갈리지만 공기청정기 쪽으로
값들을 덮어씌운다는 느낌으로 반목문을 각 방향마다 돌리면 된다.
공기청정기 -1이 덮어씌워지기에 다시 복구시켜야하고 덮어씌워지면서 결과적으로 한칸이 지워져야하므로
공기청정기 바로 옆칸을 0으로 만들어줘야 한다.
이러한 생각을 가지고 구현을 하면 오류없이 문제가 풀린다.
다른 사람 풀이를 보니 공기청정기 순환에 시계 방향, 반시계 방향을 따로 배열로 저장해서
풀었던데 이 방식도 괜찮은 것 같다. 
근데 오히려 이 문제는 하드코딩으로 푸는게 더 짧다....
이 문제를 통해 구현 실력을 늘려간다.
*/

int N, M, T, Map[51][51], Sum[51][51], Cl[2], Dir[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };

void mDust() {
	memset(Sum, 0, sizeof(Sum));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (Map[i][j] == -1 || Map[i][j] < 5)
				continue;
			int Cnt = 0, P = Map[i][j] / 5;
			for (int k = 0; k < 4; k++) {
				int X = Dir[k][0] + j, Y = Dir[k][1] + i;
				if (0 <= X && X < M && 0 <= Y && Y < N && Map[Y][X] != -1) {
					Cnt++; Sum[Y][X] += P;
				}
			}
			Map[i][j] -= P * Cnt;
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (Map[i][j] != -1)
				Map[i][j] += Sum[i][j];
		}
	}
}

void Clean() {
	mDust();
	for (int i = Cl[0] - 1; i >= 0; i--)
		Map[i + 1][0] = Map[i][0];
	for (int i = 1; i < M; i++)
		Map[0][i - 1] = Map[0][i];
	for (int i = 1; i <= Cl[0]; i++)
		Map[i - 1][M - 1] = Map[i][M - 1];
	for (int i = M - 2; i > 0; i--)
		Map[Cl[0]][i + 1] = Map[Cl[0]][i];
	for (int i = Cl[1] + 1; i < N; i++)
		Map[i - 1][0] = Map[i][0];
	for (int i = 1; i < M; i++)
		Map[N - 1][i - 1] = Map[N - 1][i];
	for (int i = N - 2; i >= Cl[1]; i--)
		Map[i + 1][M - 1] = Map[i][M - 1];
	for (int i = M - 2; i > 0; i--)
		Map[Cl[1]][i + 1] = Map[Cl[1]][i];
	Map[Cl[0]][0] = Map[Cl[1]][0] = -1;
	Map[Cl[0]][1] = Map[Cl[1]][1] = 0;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M >> T;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> Map[i][j];
			if (Map[i][j] == -1) {
				if (!Cl[0])
					Cl[0] = i;
				else
					Cl[1] = i;
			}
		}
	}
	while (T > 0) {
		Clean(); T--;
	}
	int Ans = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			Ans += Map[i][j];
	cout << Ans + 2;
}