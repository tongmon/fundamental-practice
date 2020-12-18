#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/13913
숨바꼭질 문제 시리즈....
처음에 우선순위큐를 사용하는 줄 알고 사용했다가 빠꾸먹어 시간 날리고
그냥 큐로 바꿨더니 잘 작동하길래 제출했더니 틀렸다고 빠꾸먹고....
Vis[N] = 0 인 경우 (방문이 실제 0인 경우) 를 따지지 않아서 틀리고
범위 설정 잘못해서 또 틀린 삽질의 연속인 문제였다.
일단 우선순위 큐를 사용하지 말아야하는 것은 곱하기 2를 하던 + 1을 하던 - 1을 하던
그냥 모두 똑같은 1초라는 점에서 이를 캐치했어야 했다.
범위를 보면 더하는 경우는 K보다 커질 이유가 없다 K가 커지면 다시 빼줘야하는데 시간낭비가 생겨
계산에서 제외한다.
곱하는 경우는 폭 넓게 100000 이하로 잡하야한다.
초반에 곱한 값이 K 이하가 되게 해야한다로 잡았더니 틀렸습니다가 자꾸 나와서 생각해보니
17 33 이러한 경우, 즉 두배를 하고 34로 K보다 커진 후에 하나를 빼는 것이 최소인 경우를 생각하지 못했다.
그러면 곱한 값이 100000 이상이 되었다가 빼는 것이 더 효과적인 경우가 있을 수 있지 않은가? 라는 의문이 생길 수 있는데
이렇게 값이 큰 경우는 어짜피 K는 100000 이하여서 빼서 두배를 사용하는 경우로 모두 커버가 된다.
*/

#define Cur pair<int, int>

int N, K, Vis[100001];

int BFS() {
	queue<Cur> Q;
	Q.push({ N, 0 }); Vis[N] = -2;
	Cur Top;
	while (!Q.empty()) {
		Top = Q.front(); Q.pop();
		if (K > Top.first && Vis[Top.first + 1] == -1) {
			Vis[Top.first + 1] = Top.first;
			if (Top.first + 1 == K)
				return ++Top.second;
			Q.push({ Top.first + 1, Top.second + 1 });
		}
		if (50000 >= Top.first && Vis[Top.first * 2] == -1) {
			Vis[Top.first * 2] = Top.first;
			if (Top.first * 2 == K)
				return ++Top.second;
			Q.push({ Top.first * 2, Top.second + 1 });
		}
		if (1 <= Top.first && Vis[Top.first - 1] == -1) {
			Vis[Top.first - 1] = Top.first;
			if (Top.first - 1 == K)
				return ++Top.second;
			Q.push({ Top.first - 1, Top.second + 1 });
		}
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	memset(Vis, -1, sizeof(Vis));
	cin >> N >> K;
	if (N == K) {
		cout << "0\n" << K;
		return 0;
	}
	cout << BFS() << '\n';
	int ind = K;
	vector<int> Ans;
	while (ind != -2) {
		Ans.push_back(ind);
		ind = Vis[ind];
	}
	reverse(Ans.begin(), Ans.end());
	for (auto Num : Ans) {
		cout << Num << ' ';
	}
}