#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/64062
징검다리 건너기 문제.
초반에 반복문 돌면서 풀려했으나 시간 복잡도가 너무 커져서 방향을 Dp 쪽으로
틀어봤다. Dp라고 하기엔 애매한데 해당 Dp에는 그 곳까지 도달할 수 있는
사람 수가 들어간다.
이를 구하기 위해서는 k번 뒤에 까지 즉, 점프해서 현재 징검다리 위치까지 올 수 있는 곳들의
값을 봐야되는데 이 값들 중에서 가장 큰 Dp값의 사람들은 현재 징검다리까지 올 수가 있다.
근데 현재 징검다리가 버틸 수 있는 사람 수가 더 작다면? 그 징검다리까지 올 수 있는 사람은
그 징검다리의 현재 stones[] 배열의 값일 것이다. 이를 고려하면 풀리는데
시간 복잡도를 줄이기 위해서 set을 사용했다.
프로그래머스가 c++ 지원이 이상한데 원래 erase(값) 하면 해당 값이 지워져야 하는데 여기서는
굳이 find로 반복자 찾고 erase로 지워야 지워진다.
이 문제로 구현속도를 늘려간다.
*/

int Dp[200001];
multiset<int> Max;

int solution(vector<int> stones, int k) {
	int answer = 0;
	for (int i = 0; i < stones.size(); i++)
	{
		if (i < k)
			Dp[i] = stones[i];
		else {
			auto iter = Max.end();
			iter--;
			Dp[i] = min(*iter, stones[i]);
			Max.erase(Max.find(Dp[i - k]));
		}
		Max.insert(Dp[i]);
	}
	for (int j = 0; j < k; j++)
		answer = max(Dp[stones.size() - 1 - j], answer);
	return answer;
}