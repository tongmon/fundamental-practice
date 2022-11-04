#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/4358
해쉬맵을 이용하여 개수를 세어 해당 종의 확률을 구해주면 된다.
이 문제를 통해 구현속도를 늘려간다.
*/

map<string, double> V;
string A;
double N;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	getline(cin, A);
	while (!A.empty()) {
		V.find(A) == V.end() ? V[A] = 1 : V[A]++;
		N++;
		getline(cin, A);
	}
	cout.precision(4);
	cout << fixed;
	for (auto& s : V) {
		double k = s.second / N;
		k = round(k * 1e6) / 1e4;
		cout << s.first << ' ' << k << '\n';
	}
}