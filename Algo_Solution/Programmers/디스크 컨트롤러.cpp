#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/42627
디스크 컨트롤러 문제.
문제를 보자마자 든 생각은 운영체제에서 배웠던 라운드 로빈이 먼저 떠올랐다.
라운드 로빈을 되새김질하다가 문제를 다시보니 한 번에 하나의 작업만을 건드릴 수
있다는 조건이 붙어서 라운드 로빈으로 푸는 것은 아니였다.
문제를 보아하니 각 작업마다 대기 시간이 짧아야 하니 현재 작업량이 적은 것부터
끝내야 다음 작업의 대기 시간이 잛아진다는 것을 알았다.
현재 가장 작은 상태를 나타내기 좋은 우선순위 큐를 사용하여 풀었다.
시간별로 작업들을 정렬하고 해당 작업이 시작 될 수 있는 시간이면
큐에 해당 작업을 넣어준다.
큐 위에는 현재 작업량이 가장 적은 작업이 올라와 있으므로 그것을 꺼내 작업을 끝내주면 된다.
그만큼 시간은 증가시켜야 된다.
이를 반복하면서 답을 계산해주면 된다.
현재 할 수 있는 작업이 없을 경우에 시간을 하나씩 늘려간다는 것도 잊지 말아야 한다.
이 문제를 통해 우선순위 큐 문제에 대한 감을 키워간다.
*/

using Disc = pair<int, int>;

int solution(vector<vector<int>> jobs) {
	int answer = 0;
	priority_queue<Disc, vector<Disc>, greater<Disc>> Q;
	vector<Disc> List;
	for (auto A : jobs)
		List.push_back({ A[0],A[1] });
	sort(List.begin(), List.end());
	int Time = 0, Ind = 0;
	while (true) {
		for (int i = Ind; i < List.size(); i++)
		{
			if (List[i].first <= Time) {
				Q.push({ List[i].second, List[i].first });
				Ind = i + 1;
			}
			else
				break;
		}
		if (Q.empty() && Ind == List.size())
			break;
		if (!Q.empty()) {
			Disc Top = Q.top(); Q.pop();
			Time += Top.first;
			answer += Time - Top.second;
		}
		else
			Time++;
	}
	return answer / jobs.size();
}