#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12987
숫자 게임 문제.
그리디 문제다.
A팀의 순서를 B팀이 알고 있기 때문에 A팀이 내는 수에 최선으로 맞받아 치면 된다.
최선으로 맞받아 치는 수를 생각해보면 A가 낸 수보다 큰 수를 내는데 이 차이가
가장 작은 녀석을 내면 된다.
예를 들어 A가 3을 냈는데 B가 가지고 있는 녀석이 4, 5, 6, 7 이거면 4를 내면 가장 최선으로 맞받아 친 것이다.
물론 이는 A, B가 정렬이 되어있는 상태인 경우를 전제한다.
왜냐면 A가 3을 낸 후에 그 다음에 이보다 더 크거나 같은 값을 내는 것이 보장되면
B를 이를 대비해야하고 A를 이기기위한 힘을 아껴야해서 4를 내야하는 것이다.
여기다 최강의 패인 7을 내버리면 뒷감당을 하기 힘들어지는 것이다.
그리고 A가 낸 패보다 작은 녀석들은 그냥 버린다... 점수를 획득하는데 상관도 없기 때문.
이러한 원리로 밑과 같이 작성한 코드가 도출되었다.
이 문제를 통해 그리디 문제 실력을 길러간다.
*/

int solution(vector<int> A, vector<int> B) {
	int answer = 0;
	sort(A.begin(), A.end());
	sort(B.begin(), B.end());
	for (int i = 0, j = 0; i < B.size(); i++)
	{
		if (A[j] < B[i]) {
			answer++;
			j++;
		}
	}
	return answer;
}