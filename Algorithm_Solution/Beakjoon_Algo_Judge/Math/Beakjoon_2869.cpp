#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2869
단순 계산 문제... 끝에 올라가면 내려오지 않기에
미리 빼주는게 관건
*/

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int V, A, B, Ans = 1;
	cin >> A >> B >> V;
	V -= A; 
	Ans += V / (A - B);
	if (!(V % (A - B))) cout << Ans;
	else cout << Ans + 1;
}