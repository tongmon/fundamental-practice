#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/9205
BFS 문제인데 거리 계산하는 곳에서 실수할 여지가 많은 문제다.
난 처음에 50을 나누어 맥주병이 몇개 드는지를 계산했지만
이러면 1020와 같이 맥주병 다 먹고 20미터 더 가서 옴짝달싹 못하는 상황이 생길 수 있다.
이런 상황을 고려해서 거리 차이가 1000 이하라고 명시를 하는 방식을 사용해야 한다.
그리고 방문 배열을 처음에 해쉬맵으로 했는데 Pair를 해쉬맵에 적합하게 해싱을 따로 정의해줘야 했다...
그래서 그냥 O(1)은 아니지만 map을 사용했다. 이 점 기억하자.
BFS 문제를 보고 바로 풀 수 있도록 더 연습해야겠다.
*/

#define Cord pair<int, int>

int T, N, x, y;
Cord St;
map<Cord, bool> Vis;
vector<Cord> Con;

bool BFS() {
	queue<Cord> Q; Q.push(St);
	Cord Fro;
	while (!Q.empty()) {
		Fro = Q.front();
		for (int i = 0; i < Con.size(); i++)
		{
			int Bot = abs(Fro.first - Con[i].first) + abs(Fro.second - Con[i].second);
			if (Bot <= 1000 && !Vis[Con[i]]) {
				Q.push(Con[i]); Vis[Con[i]] = true;
				if (Con.back() == Con[i]) return true;
			}
		}
		Q.pop();
	}
	return false;
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		cin >> N;
		cin >> x >> y;
		St = { x,y };
		for (int j = 0; j <= N; j++)
		{
			cin >> x >> y;
			Con.push_back({ x,y });
			Vis[{x, y}] = false;
		}
		if (BFS()) cout << "happy\n";
		else cout << "sad\n";
		Vis.clear(); Con.clear();
	}
}