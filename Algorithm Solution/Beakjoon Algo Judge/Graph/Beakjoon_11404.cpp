#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/11404
플로이드 와샬 알고리즘 문제
플로이드 와샬 알고리즘을 때려박으면 풀린다.
내가 풀면서 실수한 것은 2가지 인데
일단 플로이드 알고리즘은 3중 포문을 돌게 되는데 이때 최상위 루프 (가장 늦게 변화되는 루프) 가 via(거쳐가는 정점)을
나타내야 하는데 이것을 해주지 않았다.
초반에 짤 때 그냥 k나 j를 via로 설정하여 이상한 값이 튀어 나왔다.
꼭 플로이드 짤 때는 루프 i를 via로 설정하자.
그리고 최단 거리는 보통 초기화를 INF 값으로 해주는데 이 값을 너무 작게해서 틀렸습니다가 떳다.
다음부터 이 두가지 유의점을 생각하면서 플로이드 와샬을 짜자
*/

int N, T, a, b, c, Dir[101][101];

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> T;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			Dir[i][j] = 10000001;
	for (int i = 0; i < T; i++) {
		cin >> a >> b >> c;
		Dir[a][b] = min(c, Dir[a][b]);
	}
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			for (int k = 1; k <= N; k++) {
				if (k != j)
					Dir[j][k] = min(Dir[j][k], Dir[j][i] + Dir[i][k]);
			}
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++) {
			if (Dir[i][j] < 10000001)
				cout << Dir[i][j] << ' ';
			else
				cout << "0 ";
		}
		cout << '\n';
	}
}