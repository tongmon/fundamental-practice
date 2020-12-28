#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1451
직사각형에 관한 완전탐색 문제다.
처음에 점 6개를 조합으로 선택해 계산하는 방식을 떠올렸으나 이는 시간복잡도가 답이 안나온다.
계속 생각해봤더니 테트리스 처럼 직사각형을 딱 딱 맞춰서 3등분 하면 되는 문제였다.
3등분을 딱딱 맞춰 만드는 경우는 세로 3등분, 가로 3등분, 십자가로 4등분 한거에서 적절히 더해 3개로 만드는 4가지 경우
이렇게 나뉘고 이를 모두 탐색하는 것을 구현하면 되는 문제다.
구현할 때 숏코딩에서 애를 먹었다.
결국엔 할 수 있는데 까지 줄여봤다.
이 문제를 통해 완전탐색 문제에 대한 감을 잡아간다.
그리고 앞으로 C++ 쓰는데 #define ll long long 이것보단 using ll = long long; 이렇게 쓰자
*/

#define ll long long

int N, M, Map[101][101], Sum;
ll Max;
char In;

ll Sumed(int xs, int xe, int ys, int ye) {
	ll buf = 0;
	for (int k = xs; k < xe; k++)
		for (int h = ys; h < ye; h++)
			buf += Map[k][h];
	return buf;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> In;
			Map[i][j] = In - '0';
			Sum += Map[i][j];
		}
	}
	for (int i = 0; N > 2 && i < N - 2; i++)
	{
		for (int j = i + 1; j < N - 1; j++)
		{
			ll Num[] = { 0,0,0 };
			Num[0] = Sumed(0, i + 1, 0, M);
			Num[1] = Sumed(i + 1, j + 1, 0, M);
			Num[2] = Sum - Num[1] - Num[0];
			Max = max(Max, Num[0] * Num[1] * Num[2]);
		}
	}
	for (int i = 0; M > 2 && i < M - 2; i++)
	{
		for (int j = i + 1; j < M - 1; j++)
		{
			ll Num[] = { 0,0,0 };
			Num[0] = Sumed(0, N, 0, i + 1);
			Num[1] = Sumed(0, N, i+1, j + 1);
			Num[2] = Sum - Num[1] - Num[0];
			Max = max(Max, Num[0] * Num[1] * Num[2]);
		}
	}
	for (int i = 0; M > 1 && N > 1 && i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			ll Num[] = { 0,0,0,0 };
			Num[0] = Sumed(0, i + 1, 0, j + 1);
			Num[1] = Sumed(0, i + 1, j + 1, M);
			Num[2] = Sumed(i + 1, N, 0, j + 1);
			Num[3] = Sum - Num[0] - Num[1] - Num[2];
			Max = max(Max, (Num[0] + Num[1]) * Num[2] * Num[3]);
			Max = max(Max, (Num[1] + Num[3]) * Num[2] * Num[0]);
			Max = max(Max, (Num[2] + Num[3]) * Num[1] * Num[0]);
			Max = max(Max, (Num[0] + Num[2]) * Num[1] * Num[3]);
		}
	}
	cout << Max;
}