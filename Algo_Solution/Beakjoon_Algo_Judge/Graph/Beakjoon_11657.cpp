#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/11657
벨만 포드 연습하려고 푼 문제.
벨만 포드 알고리즘을 때려넣으면 된다.
주의점은 벨만 포드는 음수 싸이클 검사가 N번째에서 이루어지는데
N번째 까지 거리 배열을 갱신할 때 음수에 대한 제한이 없다.
즉 음수로는 int를 뚫고 long long 범위로 계속 내려갈 수 있다는 것이다.
따라서 음수 방향 언더플로우를 조심해야 한다.
이 문제를 통해 벨만 포드 구현 능력을 키워간다.
*/

long long N, M, a, b, c, INF = 9000000000;
vector<tuple<int, int, int>> Edge;

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> c;
		Edge.push_back({ a,b,c });
	}
	vector<long long> Dist(N + 1, INF); Dist[1] = 0;
	bool is_Ch = 1, ans = 0;
	for (int i = 1; i <= N && is_Ch; i++) {
		is_Ch = 0;
		for (auto &e : Edge) {
			long long buf = get<2>(e) + Dist[get<0>(e)];
			if (Dist[get<0>(e)] != INF && buf < Dist[get<1>(e)]) {
				Dist[get<1>(e)] = buf;
				is_Ch = 1;
			}
		}
		if (i == N && is_Ch)
			ans = 1;
	}
	if (ans)
		cout << "-1\n";
	for (int i = 2; i <= N && !ans; i++)
		cout << (Dist[i] != INF ? Dist[i] : -1) << '\n';
}