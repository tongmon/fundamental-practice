#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1448
삼각형을 만드려면 가장 큰 변 길이는 나머지 두 변 길이 합보다 작아야 한다.
정렬을 이용하면 3개의 선택되는 변은 붙어있어야 한다는 것을 알 수 있다.
한 개의 가장 긴 변을 선택하면 나머지 변의 길이들은 클 수록 삼각형이 될 확률이 높아지는데
이 대 긴 변 위치와 붙어있는 녀석들을 선택해도 삼각형이 안만들어 진다면 다른 변을 선택해도 삼각형은
만들어지지 않는다.
이 문제를 통해 구현속도를 늘려간다.
*/

int N, Ans;
vector<int> A;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	A.resize(N);
	for (int i = 0; i < N; i++)
		cin >> A[i];
	sort(A.begin(), A.end(), greater<int>());
	for (int i = 0; i < N; i++) {
		if (i + 2 < N && A[i] < A[i + 1] + A[i + 2]) {
			Ans = A[i] + A[i + 1] + A[i + 2];
			break;
		}
	}
	cout << (Ans ? Ans : -1);
}