#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2798
cout 출력 정밀도를 설정하는 cout.precision(숫자) 함수 알고가자
나머지 내용은 그냥 단순 계산
*/

vector<double> sto;

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int N; cin >> N;
	double In, MAX = -1, Avg = 0;
	for (int i = 0; i < N; i++)
	{
		cin >> In; sto.push_back(In);
		MAX = max(MAX, In);
	}
	for (auto Num : sto) {
		Avg += (Num / MAX * 100.0);
	}
	cout.precision(10);
	cout << Avg / (double)N;
}