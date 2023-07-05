#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/67256
키패드 위치를 넣어놓고 거리 측정을 하면 되는 문제다.
이 문제를 통해 구현속도를 늘려간다.
*/

int A[10][2] = { {1,3} }, L[2] = { 0,3 }, R[2] = { 2,3 };
string answer = "";

int dist(int* A, int* B) {
	return abs(A[0] - B[0]) + abs(A[1] - B[1]);
}

void Ans(char a, int i) {
	if (a == 'R') {
		answer += 'R';
		R[0] = A[i][0]; R[1] = A[i][1];
		return;
	}
	answer += 'L';
	L[0] = A[i][0]; L[1] = A[i][1];
}

string solution(vector<int> numbers, string hand) {
	for (int i = 0; i < 3; i++) {
		for (int j = 1; j < 4; j++) {
			A[i * 3 + j][0] = j - 1;
			A[i * 3 + j][1] = i;
		}
	}
	for (auto& n : numbers) {
		if (n == 3 || n == 6 || n == 9) {
			Ans('R', n);
		}
		else if (n == 1 || n == 4 || n == 7) {
			Ans('L', n);
		}
		else {
			int l = dist(A[n], L), r = dist(A[n], R);
			if (l == r) {
				Ans(toupper(hand[0]), n);
			}
			else {
				l > r ? Ans('R', n) : Ans('L', n);
			}
		}
	}
	return answer;
}