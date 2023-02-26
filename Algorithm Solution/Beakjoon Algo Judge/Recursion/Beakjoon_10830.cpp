#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/10830
행렬 연산과 재귀적인 제곱 풀이를 알고 있으면
원활히 풀 수 있는 문제다.
행렬 연산은 삼중 포문으로 재귀적인 제곱은
짝수인 경우, 홀수인 경우로 나누는데
짝수인 경우는 다시 반절로 나눠 생각하면 되고
홀수는 하나 빼고 반절로 나눠 생각하면 된다.
이 문제를 통해 재귀적인 사고를 길러간다.
*/

using ll = long long;
ll N, B, M[5][5];

void multMat(ll Mat[][5], ll Mat2[][5]) {
	ll R[5][5];
	memset(R, 0, sizeof(R));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				R[i][j] += Mat[i][k] * Mat2[k][j];
				R[i][j] %= 1000;
			}
		}
	}
	memcpy(Mat, R, sizeof(R));
}

void powMat(ll Mat[][5], ll B) {
	if (B == 1)
		return;
	else if (B % 2) {
		ll buf[5][5];
		memcpy(buf, Mat, sizeof(buf));
		powMat(Mat, (B - 1) / 2);
		multMat(Mat, Mat);
		multMat(Mat, buf);
		return;
	}
	powMat(Mat, B / 2);
	multMat(Mat, Mat);
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> B;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> M[i][j];
	powMat(M, B);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cout << M[i][j] % 1000 << ' ';
		cout << '\n';
	}
}