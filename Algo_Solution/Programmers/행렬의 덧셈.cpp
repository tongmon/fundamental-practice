#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12950
행렬의 덧셈 문제.
이중 포문으로 그냥 풀린다.
처음에 결과 행렬 배열의 사이즈를 정해놓고 시작하면 숏코딩 가능하다.
*/

using V = vector<int>;

vector<V> solution(vector<V> arr1, vector<V> arr2) {
	int W = arr1[0].size(), H = arr1.size();
	vector<V> a(H, V(W));
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
			a[i][j] = arr1[i][j] + arr2[i][j];
	return a;
}