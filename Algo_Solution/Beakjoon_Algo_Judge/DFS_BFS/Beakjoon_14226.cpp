#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/14226
bfs 문제인데 방문 배열 설정을 잘해야 한다.
현재 클립 보드의 저장된 값과 현재 출력할 수 있는 이모티콘 수를 모두 고려하여
이차원 배열로 방문 배열을 설정해야 맞을 수 있다.
이 문제를 통해 방문 배열 설정 실력을 길러간다.
*/

int V[2001][2001], N;

using tup = tuple<int, int, int>;

int bfs() {
	queue<tup> Q;
	Q.push({ 0, 1, 0 }); V[1][0] = 1;
	tup T;
	while (!Q.empty()) {
		T = Q.front(); Q.pop();
		if (get<1>(T) == N) break;
		if (!V[get<1>(T)][get<1>(T)]) {
			V[get<1>(T)][get<1>(T)] = 1;
			Q.push({ get<0>(T) + 1,get<1>(T),get<1>(T) });
		}
		int s = get<1>(T) + get<2>(T);
		if (s < 2001 && !V[s][get<2>(T)]) {
			V[s][get<2>(T)] = 1;
			Q.push({ get<0>(T) + 1,s,get<2>(T) });
		}
		s = get<1>(T) - 1;
		if (2 < s && !V[s][get<2>(T)]) {
			V[s][get<2>(T)] = 1;
			Q.push({ get<0>(T) + 1,s,get<2>(T) });
		}
	}
	return get<0>(T);
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	cout << bfs();
}