#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12980
점프와 순간이동 문제
처음에 BFS 문제인줄 알고 BFS로 접근했는데 시간초과가 자꾸나서
좀 더 생각을 해보니 그리디 문제였다.
그냥 거꾸로 사고하면 된다.
주어진 n을 0으로 만드는데 2로 나누는 것을 우선으로 수행하고
2로 안나누어지는 수인 경우만 1을 빼주면서 배터리를 깎는다.
이 문제를 통해 그리디적인 사고를 길러간다.
*/

int solution(int n)
{
	int ans = 0;
	while (n) {
		if (n % 2 == 0)
			n /= 2;
		else {
			n -= 1;
			ans++;
		}
	}
	return ans;
}