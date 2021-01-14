#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/16953
로직은 그냥 평범한 BFS 최단 경로 문제다.
근데 함정이 있는게 연산 과정에서 long long 으로 연산이 넘어갈 수 있어서
int 형만 쓰면 안되는 문제와 용량의 한계 때문에 Vis배열을 map으로 선언해야하는 문제가 있다.
이 둘을 신경쓰면 맞는데 나는 신경쓰지 않고 대충 갈겼다가 4번이나 틀려버렸다....
앞으로 자료형 크기에 대한 신경을 더 쓰자.
이 문제를 통해 자료형에 대한 실수를 줄여나간다.
*/

int A, B;
unordered_map<int, bool> Vis;

int BFS() {
	queue<pair<long long, int>> Q;
	Q.push({ A,1 }); Vis[A] = 1;
	while (!Q.empty()) {
		long long buf = 2 * Q.front().first;
		if (buf <= B && Vis.find(buf) == Vis.end()) {
			Q.push({ buf, Q.front().second + 1 });
			Vis[buf] = 1;
			if (buf == B)
				return Q.front().second + 1;
		}
		buf = Q.front().first * 10 + 1;
		if (buf <= B && Vis.find(buf) == Vis.end()) {
			Q.push({ buf, Q.front().second + 1 });
			Vis[buf] = 1;
			if (buf == B)
				return Q.front().second + 1;
		}
		Q.pop();
	}
	return -1;
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> A >> B;
	cout << BFS();
}