#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/14391
완전탐색 문제
*/

int N, M, Max, Vis[4][4];
char A[4][4];
unordered_set<string> V;
string str;

void func(int x, int y) {
	if (y == N) {
		int sum = 0;
		for (int i = 0, u = 0, v = 0; i < str.length(); i += 2) {
			if (str[i] != '9') {
				string num;
				if (v == str[i] - '0') {
					for (int j = u; j <= str[i + 1] - '0'; j++)
						num.push_back(A[j][v]);
				}
				else {
					for (int j = v; j <= str[i] - '0'; j++)
						num.push_back(A[u][j]);
				}
				sum += stoi(num);
			}
			if (v == M - 1) {
				u++; v = 0;
			}
			else
				v++;
		}
		Max = max(sum, Max);
		return;
	}
	if (Vis[y][x]) {
		str += "99";
		x + 1 == M ? func(0, y + 1) : func(x + 1, y);
		str.pop_back();
		str.pop_back();
		return;
	}
	for (int i = x; i < M && !Vis[y][i]; i++) {
		str.push_back(i + '0');
		str.push_back(y + '0');
		if (V.find(str) == V.end()) {
			V.insert(str);
			for (int j = x; j <= i; j++)
				Vis[y][j] = 1;
			x + 1 == M ? func(0, y + 1) : func(x + 1, y);
			for (int j = x; j <= i; j++)
				Vis[y][j] = 0;
		}
		str.pop_back();
		str.pop_back();
	}
	for (int i = y; i < N && !Vis[i][x]; i++) {
		str.push_back(x + '0');
		str.push_back(i + '0');
		if (V.find(str) == V.end()) {
			V.insert(str);
			for (int j = y; j <= i; j++)
				Vis[j][x] = 1;
			x + 1 == M ? func(0, y + 1) : func(x + 1, y);
			for (int j = y; j <= i; j++)
				Vis[j][x] = 0;
		}
		str.pop_back();
		str.pop_back();
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> A[i][j];
	func(0, 0);
	cout << Max;
}