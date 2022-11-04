#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/42860
조이스틱 문제.
풀어보니 약간 시간이 걸렸는데 그리디 문제였다.
시작점이 첫글자라는 말이 명시적으로 없어서 조금 헷갈렸다.
좌, 우로 움직일 대마다 다시 A부터 시작하기 때문에
미리 조이스틱을 상,하로 움직이는 경우에 드는 이동 비용을 구해놓을 수 있다.
이 비용은 좌, 우 이동과 상관이 완전히 없기 때문이다.
그 다음에는 BBBAAAABB 이런 경우같이 이동할 가치가 없는 A를 최대한 피해서
단어들을 모두 바꾸어주는 이동에 필요한 비용을 구해야 한다.
이 이동비용은 나는 A가 아닌 단어들의 인덱스를 모아두는 배열에 담아두고
첫 시작점 0부터 시작해서 다음에 갈 수 있는 곳인데 가장 가까운 곳을 그리디적으로
선택해서 계속 골라갔다. 물론 선택되면 다음 시작점은 선택된 인덱스가 된다.
이렇게 하면 최적의 이동비용이 구해진다.
이 문제를 통해 그리디 문제에 대한 실력을 높여간다.
*/

int solution(string name) {
	int answer = 0;
	vector<int> A;
	for (int i = 0; i < name.size(); i++)
	{
		int Mov = min(name[i] - 'A', 'Z' - name[i] + 1);
		if (Mov) A.push_back(i);
		answer += Mov;
	}
	if (A.empty()) return 0;
	int back = 0;
	for (int j = 0; j < A.size(); j++)
	{
		int Min = 100, Ind = 0;
		for (int i = 0; i < A.size(); i++)
		{
			if (A[i] < 0) continue;
			int K = min(abs(A[i] - back), (int)name.size() - abs(A[i] - back));
			if (Min > K) {
				Min = K;
				Ind = i;
			}
		}
		back = A[Ind];
		A[Ind] = -1;
		answer += Min;
	}
	return answer;
}