#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

#pragma warning(disable:4996)

/*
https://www.acmicpc.net/problem/11004
간단한 정렬문제.
힙 정렬로 했으면 더 빨랐을 듯 하다.
*/

int main()
{
	int N, K;
	long long buffer;
	scanf("%d %d", &N, &K);
	vector<long long> Comp;
	scanf("%lld", &buffer); Comp.push_back(buffer);
	for (int i = 1; i < N; i++)
	{
		scanf(" %lld", &buffer); Comp.push_back(buffer);
	}
	sort(Comp.begin(), Comp.end());
	cout << Comp[K - 1];
}