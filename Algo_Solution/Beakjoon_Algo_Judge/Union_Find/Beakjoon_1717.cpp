#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1717
유니온 파인드 문제인데 무지성 트리 구조로 짜면 시간초과가 발생한다.
따라서 최적화된 유니온 파인드 트리를 구성해야한다.
트리가 선형 구조에 비슷해 질 수록 트리의 부모를 찾는 시간복잡도는 O(N)에 가까워진다.
이를 줄이려면 트리를 만들거나 부모를 찾는 과정에서 트리를 밑에서 부터 타고 올라오는 경로의 길이를 줄이기 위해
밑에서 부터 거치게 되는 트리의 노드들의 뿌리를 갱신해주어야 한다.
예를 들어 1 -> 3 -> 5 이렇게 뿌리가  5인 트리를 1 -> 5 <- 3 이러한 트리로 계속 변형해주는 것이다.
이렇게 계속해서 갱신하며 트리를 구성하면 높이가 낮은 트리가 유지되게 되고 유니온 파인드를 구축할 때 빨라진다.
*/

vector<int> r, v;

int f(int p) {
	v[0] = p;
	int k = 0;
	while (p != r[p]) {
		p = r[p];
		v[++k] = p;
	}
	for (int i = 0; i < k; i++)
		r[v[i]] = p;
	return p;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int n, m, e, a, b;
	cin >> n >> m;
	r.resize(n + 1); v = r;
	for (int i = 0; i <= n; i++)
		r[i] = i;
	for (int i = 0; i < m; i++) {
		cin >> e >> a >> b;
		a = f(a); b = f(b);
		e ? void(cout << (a == b ? "YES\n" : "NO\n")) : void(r[a] = b);
	}
}