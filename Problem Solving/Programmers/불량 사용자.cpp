#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/64064
불량 사용자 문제.
카카오 입사 문제들을 조금 풀어보니까 꼭 해쉬맵 관련된 문제를 내더라.
이 문제도 해쉬맵을 사용해 풀었다.
해쉬맵을 이용하여 불량 사용자 조건을 보고 불량 사용자가 가능한 이름들을
이차원 string 배열에 넣었다.
그런데 중복 제거를 잘해야 한다. 예를 들어 frodo crodo aa 와 crodo frodo aa는
같은 경우이기에 이런 것을 잘 걸러야 한다.
따라서 이를 방지하기 위해 비트마스킹을 이용하여 처리하였다.
비트마스킹을 사용해야 중복을 거르는데 계산 한번으로 끝나기에 시간복잡도가 얼마 걸리지 않는다.
그래서 끝까지 다 세주고 중복되지 않으면 답을 하나 더하면 된다.
이 문제를 통해 구현 속도를 늘려간다.
*/

unordered_map<string, int> Offset, Vis;
unordered_set<int> Check;
int answer, Comp;

void Sel(int N, vector<vector<string>>& List) {
	if (List.size() == N) {
		if (Check.find(Comp) == Check.end()) {
			Check.insert(Comp);
			answer++;
		}
		return;
	}
	for (int i = 0; i < List[N].size(); i++)
	{
		if (!Vis[List[N][i]]) {
			int Nums = 1 << Offset[List[N][i]];
			Comp |= Nums;
			Vis[List[N][i]] = 1;
			Sel(N + 1, List);
			Comp ^= Nums;
			Vis[List[N][i]] = 0;
		}
	}
}

int solution(vector<string> user_id, vector<string> banned_id) {
	vector<vector<string>> Mat(banned_id.size());
	Comp = 1 << 10;
	int z = 0;
	for (auto &str : user_id) {
		Vis[str] = 0;
		Offset[str] = z++;
		int k = 0;
		for (auto& ban : banned_id) {
			if (ban.size() == str.size()) {
				bool Find = 1;
				for (int i = 0; i < ban.size() && Find; i++) {
					if (ban[i] != '*' && ban[i] != str[i])
						Find = 0;
				}
				if (Find)
					Mat[k].push_back(str);
			}
			k++;
		}
	}
	Sel(0, Mat);
	return answer;
}