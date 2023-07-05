#include <bits/stdc++.h>
using namespace std;

/*
https://app.codility.com/programmers/trainings/4/first_unique/
문제 사이트가 약간 이상한게 삼항연산자 인식을 못한다...
암튼 밑의 코드에서 삼항연산자 부분을 if else 문으로 풀어쓰면 정답 처리가 된다;;
해쉬맵을 이용하여 구현하면 쉽게 풀리는 배열 중복 판단 문제다.
*/

int solution(vector<int>& A)
{
	unordered_map<int, int> v;
	int a = 2e9;
	for (int i = 0; i < A.size(); i++)
		v[A[i]] = v.find(A[i]) != v.end() ? -1 : i;
	for (auto& u : v) {
		if (u.second >= 0 && a > u.second)
			a = u.second;
	}
	return a == 2e9 ? -1 : A[a];
}