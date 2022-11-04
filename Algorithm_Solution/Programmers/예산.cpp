#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12982
예산 문제
문제를 똑바로 읽자...
주어진 budget을 꼭 맞게 다 주어야 하는 줄 알고 배낭 문제 비슷하게 접근했다가
괜히 뻘짓했다...
*/

int solution(vector<int> d, int budget) {
	int ans = 0;
	sort(d.begin(), d.end());
	for (auto& n : d) {
		budget -= n;
		ans++;
		if (budget <= 0) break;
	}
	if (budget < 0) ans--;
	return ans;
}