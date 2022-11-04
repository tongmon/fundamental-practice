#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/11000
방 배치에 관한 그리디 문제이다.
일단 방 배치 관련 문제는 정렬 + 우선순위 큐를 이용하는데
이 때 정렬 순서가 중요하다.
문제 유형에 따라서 회의 시작 시간을 기준으로 정렬해야 할 수도 아니면
회의 종료 시간을 기준으로 정렬해야 할 수도 있기에 잘 생각하여 풀어야 한다.
해당 유형은 최소 배치할 수 있는 방의 개수를 구해야 하기에 시작 시간 기준으로 정렬해야 한다.
그리고 종료 시각은 우선순위 큐에 넣어준다.
예를 들어 시작 1 끝 3 이고 시작 2 끝 4 가 다음에 온다면 시작 2 ~ 끝 3 이렇게 겹치기에
회의실이 두 개 필요하다. 이렇게 겹치면 우선순위 큐에 끝 시각을 넣어준다.
시작 1 끝 3 이고 시작 3 끝 4 이렇게 들어오면 겹치지 않기 때문에 강의실 한개로도 충분하다.
따라서 우선순위 큐에 있는 끝 시각 3을 빼고 끝 시각 4를 새로 넣어준다. 이게 가능한 이유는
시작 시간을 기준으로 정렬했기에 다음에 들어올 일들은 모두 시작 3보다 큰 녀석들이라는 것이 보장되어 있기 때문이다.
따라서 시작 1 끝 3 이러한 강의를 더이상 고려할 필요가 없기 때문에 우선순위 큐에서 완전히 제거해도 되는 것이다.
이 문제를 통해 방 배치 문제에 익숙해져 간다.
*/

int N, s, t, Ans = 1;
vector<pair<int, int>> C;
priority_queue<int, vector<int>, greater<int>> Q;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> s >> t;
		C.push_back({ s,t });
	}
	sort(C.begin(), C.end());
	Q.push(C[0].second);
	for (int i = 1; i < N; i++) {
		while (!Q.empty() && Q.top() <= C[i].first)
			Q.pop();
		Q.push(C[i].second);
		Ans = max(Ans, (int)Q.size());
	}
	cout << Ans;
}