#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2588
숫자의 각 자리 수를 뽑아내면 된다.
*/

int main() 
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int N, M;
	cin >> N >> M;
	cout << N * (M % 10) << '\n' << N * (M % 100 - M % 10) / 10 << '\n' << N * (M - M % 100) / 100 << '\n' << M * N;
}
