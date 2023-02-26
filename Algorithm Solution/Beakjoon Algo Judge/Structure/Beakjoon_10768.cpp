#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/10768
달(월)의 크기를 비교하기 쉬운 방법은 M * 31 + D
라는 것을 알면 풀기 쉽다.
*/

int main() 
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int M, D, N;
	cin >> M >> D;
	N = M * 31 + D;
	if (N == 80)
		cout << "Special";
	else
		cout << (80 < N ? "After" : "Before");
}