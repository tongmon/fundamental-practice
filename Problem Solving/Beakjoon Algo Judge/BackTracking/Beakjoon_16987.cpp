#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/16987
백트래킹 문제지만 주의해야 하는 것이 있다...
현 상태에서 깨진 계란이 없다면 강제로 다음으로 넘어가게 해야한다.
즉 for문에서 다음 재귀로 가는 것이 한 개도 없다면 억지로 cur + 1 상태로 재귀를 돌려야 한다.
이렇게 억지로 다음으로 재귀를 돌려야 하는 문제도 있다는 것을 인지하자.
이 문제를 통해 백트래킹 문제에 대한 감을 익혀간다.
*/

int N, MAX, a, b;
bool flag;
vector<pair<int, int>> Egg;

/*
void DFS(int Cur) // 마지막에 깨진 계란 수를 세서 코드는 깔끔하지만 속도는 느림
{
	flag = false;
	if (Cur == N) {
		int Cnt = 0;
		for (auto Num : Egg) {
			if (Num.first <= 0) Cnt++;
		}
		MAX = max(MAX, Cnt); return;
	}
	if (Egg[Cur].first <= 0) DFS(Cur + 1);
	for (int i = 0; i < Egg.size() && Egg[Cur].first > 0; i++)
	{
		if (Egg[i].first > 0 && i != Cur) {
			int temp1 = Egg[i].first, temp2 = Egg[Cur].first;
			Egg[i].first -= Egg[Cur].second;
			Egg[Cur].first -= Egg[i].second;
			DFS(Cur + 1); flag = true;
			Egg[i].first = temp1; Egg[Cur].first = temp2;
		}
	}
	if (!flag) DFS(Cur + 1);
}
*/

void DFS(int Cur, int Cnt)
{
	flag = false;
	if (Cur == N) {
		MAX = max(MAX, Cnt); return;
	}
	if (Egg[Cur].first <= 0) DFS(Cur + 1, Cnt);
	for (int i = 0; i < Egg.size() && Egg[Cur].first > 0; i++)
	{
		if (Egg[i].first > 0 && i != Cur) {
			int temp1 = Egg[i].first, temp2 = Egg[Cur].first;
			Egg[i].first -= Egg[Cur].second;
			Egg[Cur].first -= Egg[i].second;
			if (Egg[i].first > 0 && Egg[Cur].first > 0) 
				DFS(Cur + 1, Cnt);
			else if ((Egg[i].first > 0 && Egg[Cur].first <= 0)
				|| (Egg[i].first <= 0 && Egg[Cur].first > 0)) 
				DFS(Cur + 1, Cnt + 1);
			else DFS(Cur + 1, Cnt + 2);
			Egg[i].first = temp1; Egg[Cur].first = temp2;
			flag = true;
		}
	}
	if (!flag) DFS(Cur + 1, Cnt);
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> a >> b; Egg.push_back({ a,b });
	}
	DFS(0, 0);
	cout << MAX;
}