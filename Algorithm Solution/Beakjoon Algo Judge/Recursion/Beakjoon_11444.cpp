#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/11444
피보나치 행렬을 구하는 방법이 나는 O(N)이 끝인줄 알았다...
이 문제를 풀고나서 행렬로 O(logN)에 가능하다는 것을 깨달았다.
[ 1, 1 ]
[ 1, 0 ]
위 행렬을 거듭제곱하면 피보나치 수를 획득할 수 있다.
거듭제곱이기에 재귀를 통해 시간복잡도를 획기적으로 줄일 수가 있고
엄청나게 큰 수들도 감당이 가능하다.
이 문제를 통해 피보나치 사전지식을 배웠다.
*/

using ll = long long;

struct Mat {
	ll M[2][2] = { {0,0}, {0,0} };
};

ll N;
Mat f = { 1,1,1,0 };

Mat mult(Mat& a, Mat& b) {
	Mat c;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++) {
				c.M[i][j] += a.M[i][k] * b.M[k][j];
				c.M[i][j] %= 1000000007;
			}
	return c;
}

Mat fib(ll n) {
	if (n == 1) {
		return f;
	}
	if (n % 2) {
		Mat a = fib((n - 1) / 2), b = mult(a, a);
		return mult(b, f);
	}
	Mat a = fib(n / 2);
	return mult(a, a);
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	cout << fib(N).M[0][1];
}