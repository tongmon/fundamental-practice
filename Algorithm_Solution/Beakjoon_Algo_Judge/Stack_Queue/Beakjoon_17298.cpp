#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/17298
스택을 사용하여 시간복잡도를 줄이는 유형의 문제다.
정렬이 필요하다 싶으면 스택, 우선순위 큐를 한번씩 고려해보는데
스택을 사용해서 푸니 O(n)에 끝났다.
이 문제를 통해 구현속도를 늘려간다.
*/

int N, In;
stack<pair<int, int>> St;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	vector<int> Ans(N);
	for (int i = 0; i < N; i++)	{
		cin >> In;
		while ( !St.empty() && St.top().first < In) {
			Ans[St.top().second] = In;
			St.pop();
		}
		St.push({ In, i });
	}
	while(!St.empty()) {
		Ans[St.top().second] = -1;
		St.pop();
	}
	for (auto& A : Ans)
		cout << A << ' ';
}