#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2798
간단한 재귀문제, 3중포문 문제
처음에 i+1 대신에 Cur + 1을 BJack에 넘겨주는 실수를 찾느라 시간이 좀 걸렸다. 
*/

vector<int> sto;
int a, b, In, MAX = 0;

void BJack(int Cur, int K, int lvl) {
	if (lvl == 3) {
		MAX = max(MAX, b - K);
		return;
	}
	for (int i = Cur; i < sto.size(); i++)
	{
		if (K - sto[i] >= 0) {
			BJack(i + 1, K - sto[i], lvl + 1);
		}
	}
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> a >> b;
	for (int i = 0; i < a; i++)
	{
		cin >> In;
		sto.push_back(In);
	}
	BJack(0, b, 0);
	cout << MAX;
}