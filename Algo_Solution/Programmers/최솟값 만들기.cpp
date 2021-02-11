#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12941
최솟값 만드는 그리디 문제
하나는 정방향으로 정렬하고 하나는 역순으로 정렬해서
차례 차례 곱해 더하면 된다.
더 설명할 건 없다.
*/

int solution(vector<int> A, vector<int> B)
{
	int answer = 0;

	sort(A.begin(), A.end());
	sort(B.begin(), B.end(), greater<int>());

	for (int i = 0; i < A.size(); i++)
		answer += A[i] * B[i];

	return answer;
}