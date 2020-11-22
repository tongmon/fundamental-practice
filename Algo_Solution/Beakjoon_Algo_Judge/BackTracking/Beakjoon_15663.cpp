#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/15663
N과M 백트래킹 문제에서 중복 제거라는 기믹이 필요해 문제를 적어본다.
처음에는 set을 통해 스트링을 통으로 저장하여 중복검사를 하여 풀었는데 12ms가 나왔다.
뭐 느린 편까지는 아니였지만 먼가 다른 방법이 있을 것 같아서 다른 사람 풀이를 보니
전에 선택했던 녀석을 기억해 놓는 방식으로 중복을 허용하지 않았다.
이 방식을 쓰니 8ms가 나오고 메모리도 적게 필요했다.
주석 처리한 풀이법은 내가 처음 푼 것이고 주석이 없는 부분이 좀 더 효율적인 풀이법이다.
정렬이 되어 있어 예전 것을 기억해 놓았다가 중복되면 건너뛰는 이러한 방식을 기억하고 써먹자.
정렬이 되어있다면 탐색도 쉬워지지만 중복검사도 쉬워진다는 것을 기억하자.
이 문제를 통해 중복검사에 대한 테크닉을 길러간다.
*/

int N, M, in;
vector<int> Ary, Out;

void DFS(int Cur)
{
	if (Cur == M) {
		for (auto num : Out) cout << num << ' ';
		cout << '\n'; return;
	}
	int bef = 0;
	for (int i = 0; i < Ary.size(); i++)
	{
		if (bef == Ary[i]) continue;
		bef = Ary[i];
		Out.push_back(Ary[i]); Ary.erase(Ary.begin() + i);
		DFS(Cur + 1);
		Ary.insert(Ary.begin() + i, Out.back()); Out.pop_back();
	}
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	while (N > 0) {
		cin >> in; Ary.push_back(in); N--;
	}
	sort(Ary.begin(), Ary.end()); DFS(0);
}

/*
unordered_set<string> exsist;

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	while (N > 0) {
		cin >> in; Ary.push_back(in); N--;
	}
	sort(Ary.begin(), Ary.end()); 
	string Buf = "";
	do {
		for (int i = 0; i < M; i++)
		{
			Buf = Buf + to_string(Ary[i]); Buf.push_back(' ');
		}
		if (exsist.find(Buf) == exsist.end()) {
			cout << Buf << '\n'; exsist.insert(Buf);
		}
		Buf.clear();
	} while (next_permutation(Ary.begin(), Ary.end()));
}
*/