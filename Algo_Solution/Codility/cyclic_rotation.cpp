#include <bits/stdc++.h>
using namespace std;

/*
https://app.codility.com/programmers/lessons/2-arrays/cyclic_rotation/
덱으로 배열을 회전하면 O(1)에 가능하다.
물론 덱 특성상 메모리 소모는 커지겠지만...
*/

vector<int> solution(vector<int>& A, int K)
{
	deque<int> a(A.begin(), A.end());
	for (int i = 0; i < K && a.size(); i++)
		a.push_front(a.back()), a.pop_back();
	return vector<int>(a.begin(), a.end());
}