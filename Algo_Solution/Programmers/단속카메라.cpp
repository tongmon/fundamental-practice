#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/42884
단속카메라 문제.
그리디 기법으로 범위를 추려내는 문제다.
그리디는 보통 스택, 정렬 등을 자주 이용하는데 이 문제도 별 다를 것 없이 
특정 조건으로 정렬을 한 뒤에 스택을 이용해서 최적의 해를 추려낸다.
시작되는 순서 별로 정렬을 하고 정렬된 상태에서 앞 부분부터 스택에 넣는다.
이때 범위가 겹치는 부분을 중점으로 보는데 만약 스택에 넣을 범위와 스택 Top 부분의
범위가 겹친다면 top 부분을 빼고 겹치는 부분을 추려서 넣는다.
겹치지 않는다면 생판 다른 동네의 범위이기에 그냥 스택에 넣어준다.
이렇게 하면 최소의 카메라 개수를 유지하면서 놓을 수 있는 범위들이 스택에 담기고
이 범위들은 모두 겹치지 않기 때문에 스택 개수가 최소 카메라 개수가 된다.
이 문제를 통해 그리디 실력을 늘려간다.
*/

bool Cmp(vector<int> &A, vector<int> &B) {
	return A[0] < B[0];
}

int solution(vector<vector<int>> routes) {
	sort(routes.begin(), routes.end(), Cmp);
	stack<pair<int, int>> St;
	pair<int, int> Top;
	St.push({ routes[0][0], routes[0][1] });
	for (int i = 1; i < routes.size(); i++) {
		Top = St.top();
		if (Top.second >= routes[i][0]) {
			St.pop();
			St.push({ routes[i][0], Top.second < routes[i][1] ? Top.second : routes[i][1] });
		}
		else
			St.push({ routes[i][0], routes[i][1] });
	}
	return St.size();
}