#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/5052
문제 유형은 트라이였는데 그냥 해쉬맵으로 풀었다.
접두어라는 조건 때문에 단어를 쌓으면서 해쉬맵에서 조사하면 풀린다.
이 문제를 통해 구현 속도를 늘려간다.
*/

int T, N;
string A, Ans;
unordered_set<string> V;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> N;
		V.clear();
		Ans = "YES\n";
		for (int j = 0; j < N; j++) {
			cin >> A;
			V.insert(A);
		}
		for (auto& k : V) {
			string B;
			if (Ans[0] == 'N') break;
			for (auto& s : k) {
				B += s;
				if (k.size() != B.size() && V.find(B) != V.end()) {
					Ans = "NO\n";
					break;
				}
			}
		}
		cout << Ans;
	}
}