#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/49994
방문 길이 문제.
길이를 따지는 경우에 쌍방을 모두 연결해줘야 하는 것이 중요하다.
이를 처음에 인지를 못해서 계속 틀렸었다.
*/

int V[11][11][4], X, Y, bX, bY, f;

int solution(string dirs) {
	int a = 0, g, b;
	X = Y = 5;
	for (auto& s : dirs) {
		bX = X, bY = Y;
		if (s == 'L') {
			X = max(0, X - 1), g = 0, b = 1;
			f = bX - 1 < 0 ? 1 : 0;
		}
		else if (s == 'R') {
			X = min(10, X + 1), g = 1, b = 0;
			f = bX + 1 > 10 ? 1 : 0;
		}
		else if (s == 'U') {
			Y = min(10, Y + 1), g = 2, b = 3;
			f = bY + 1 > 10 ? 1 : 0;
		}
		else {
			Y = max(0, Y - 1), g = 3, b = 2;
			f = bY - 1 < 0 ? 1 : 0;
		}
		if (f) continue;
		if (!V[Y][X][g] && !V[bY][bX][b]) {
			a++; V[Y][X][g] = V[bY][bX][b] = 1;
		}
	}
	return a;
}