#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/14501
백트래킹 문제지만 다이나믹 프로그램으로 풀 수도 있다.
일단 나는 15일이 최대라 그냥 완전탐색으로 돌렸다.
백트래킹으로 풀게되면 O(n*n) 복잡도가 걸리지만
Dp로 풀게되면 O(n)으로 그냥 끝난다!
점화식은 밑과 같이 짜여진다.
1) 일을 했을 때 (현재 날짜 + 해당 상담 기간이 전체 일 수를 초과하면 안된다.)
DP[현재 날짜 + 해당 상담 기간] = max(DP[현재 날짜 + 해당 상담 기간], DP[현재 날짜] + 해당 상담 수익)
2) 일을 안했을 때
DP[다음날] = max(DP[다음날], DP[현재 날짜])
이렇게 현재 날짜를 계속해서 늘려가면서 DP를 갱신해준다면 O(n)으로 연산이 끝난다.
이 문제를 통해 동적계획법에 대한 접근 사고를 길러간다.
*/

int N, day, cost, Max = 0;
vector<pair<int, int>> St;

void Chosen(int Cur, int earn, int back) {
	if (Cur >= N) {
		int temp = Cur == N ? earn : earn - back;
		Max = max(Max, temp);
		return;
	}
	for (int i = Cur; i < N; i++) {
		Chosen(i + St[i].first, earn + St[i].second, St[i].second);
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> day >> cost;
		St.push_back({ day, cost });
	}
	Chosen(0, 0, 0);
	cout << Max;
}