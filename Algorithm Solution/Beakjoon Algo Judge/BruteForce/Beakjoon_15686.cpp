#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/15686
순열, 조합 문제다.
백트래킹 응용버전의 문제인데 푸는데 애를 먹었다....
처음에 맵 형태로 주어져서 최단 거리 구하는 건가? 라는 생각으로 BFS도 짜보고
머 거리 계산해서 정렬도 해보고 했으나 모두 예외를 처리하는데 문제가 생겼다.
그래서 결국 다른 사람의 답을 봤더니 백트래킹으로 치킨집을 최대 M만큼 고르고 거기서
거리를 완전탐색하는 방식으로 풀었다. 그 아이디어로 밑과 같이 구현했다.
참 문제 많이 풀었다고 개인적으로 생각했지만 아직도 너무 부족하다...
이런 문제를 1시간안에 뚝딱 풀 수 있을 정도로 더 정진해야겠다.
문제를 한 유형에 갇혀 사고하지 말고 이렇게 완탐과 백트래킹이 섞인 문제도 풀 수 있게
열린 사고 방식으로 문제에 접근하자.
*/

int N, M, In, Min = 9999;
vector<pair<int, int>> Home, Store;
vector<int> List, Con;

void DFS(int Cur, int Dep) {
	if (Dep == M) {
		int mdist = 0;
		for (auto H : Home) {
			int Dist = 9999, temp;
			for (auto K : Con) {
				temp = abs(H.first - Store[K].first) + abs(H.second - Store[K].second);
				Dist = min(Dist, temp);
			}
			mdist += Dist;
		}
		Min = min(mdist, Min);
		return;
	}
	for (int i = Cur; i < List.size(); i++)
	{
		Con.push_back(List[i]); List.erase(List.begin() + i);
		DFS(i, Dep + 1);
		List.insert(List.begin() + i, Con.back()); Con.pop_back();
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> In;
			if (In == 1)
				Home.push_back({ j, i });
			else if (In == 2)
				Store.push_back({ j, i });
		}
	}
	for (int i = 0; i < Store.size(); i++) {
		List.push_back(i);
	}
	DFS(0, 0); cout << Min;
}