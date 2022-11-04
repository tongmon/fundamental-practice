#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/12851
숨바꼭질 문제 시리즈...
풀다가 방문 배열 짜는 법에 대해서 감이 안잡혀서 결국 힌트를 봤다.
보통의 BFS 문제에서는 큐에 막무가내로 들어가서 메모리가 터지는 것을 방지하기 위해
큐에 삽입을 할 경우에 방문 배열을 On 한다.
근데 이 문제는 여러가지 경우를 모두 따져야하기에 pop하는 경우에 방문을 해야한다.
pop하는 경우에 방문을 하면 문제가 없는게 일단 pop하는 시점 전에 그 pop되는 원소에 담긴
수를 방문하지 못했다는 것은 일단 그 수를 방문하기까지 얻을 수 있는 최소 시간을
못 찾았다는 뜻이기에 추후에도 그 수를 방문할 필요가 없다.
게다가 이렇게 하면 최단 거리이면서 중복되는 수를 방문하는 경우를 허용하면서
쓸데없이 왔다갔다 하는 경우가지 모두 차단된다.
이 문제를 통해 최단 경로를 골라야하지만 최단 경로가 여러개인 경우를 고려할 때
방문을 pop하는 경우에 체크하는 것을 고려해봐야 한다는 것을 알아간다.
*/

using Cord = pair<int, int>;
int N, M, Cnt, Max = 200001;
bool Vis[200001];

int BFS(int St) {
	queue<Cord> Q;
	Q.push({ St, 0 });
	Cord T;
	while (!Q.empty()) {
		T = Q.front(); Q.pop();
		Vis[T.first] = 1;
		if (T.first == M && T.second <= Max) {
			Max = T.second; Cnt++;
		}
		if (Max < T.second)
			return Max;
		int Num[3] = { T.first - 1, T.first + 1, T.first * 2 };
		for (auto& n : Num) {
			if (0 <= n && n < 200001 && !Vis[n])
				Q.push({ n, T.second + 1 });
		}
	}
	return 1;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	BFS(N);
	cout << Max << '\n' << Cnt;
}