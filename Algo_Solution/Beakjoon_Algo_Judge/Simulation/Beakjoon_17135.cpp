#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/17135
순열을 이용한 문제다.
최소의 거리를 찾는 부분은 궁수의 범위 안의 값들을 우선순위 큐에 담고 맨 위의
원소들을 참고하는 방식을 사용해였다.
이 문제를 통해 구현 속도를 늘려간다.
*/

using TU = tuple<int, int, int>;
int H, M, D, Ary[16][16], Cnt = 0;

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> H >> M >> D;
	for (int i = 0; i < H; i++)
		for (int j = 0; j < M; j++)
			cin >> Ary[i][j];
	vector<int> Ch(M);
	for (int i = 0; i < M; i++) {
		if (i >= M - 3)
			Ch[i] = 1;
		else
			Ch[i] = 0;
	}
	do {
		int Buf[16][16], Min = 0;
		vector<int> X;
		memcpy(Buf, Ary, sizeof(Ary));
		for (int i = 0; i < Ch.size(); i++)
			if (Ch[i])
				X.push_back(i);
		priority_queue<TU, vector<TU>, greater<TU>> Q[3], P;
		for (int i = H; i > 0; i--) {
			for (int j = i - 1; j >= max(0, i - D); j--) {
				for (int k = 0; k < M; k++) {
					if (Buf[j][k]) {
						for (int p = 0; p < 3; p++) {
							int Di = abs(i - j) + abs(X[p] - k);
							if (Di <= D)
								Q[p].push({ Di, k, j });
						}
					}
				}
			}
			for (int j = 0; j < 3; j++) {
				if (Q[j].empty())
					continue;
				int x = get<1>(Q[j].top()), y = get<2>(Q[j].top());
				if (Buf[y][x]) {
					Buf[y][x] = 0;
					Min++;
				}
				Q[j] = P;
			}
		}
		Cnt = max(Min, Cnt);
	} while (next_permutation(Ch.begin(), Ch.end()));
	cout << Cnt;
}