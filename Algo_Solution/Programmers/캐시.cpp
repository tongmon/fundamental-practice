#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/17680
캐시 문제.
원래는 LRU 알고리즘은
연결 리스트와 해쉬맵을 같이 써서 푸는 것이 원칙이나
시간복잡도를 계산해보니 덱큐로도 괜찮게 나와서 그냥 이대로 풀었다.
방법을 설명해보면 큐에 어떤 값을 넣어야 하는지 아닌지를 먼저 빠르게 판단
가능해야하는데 이 역할을 해쉬맵이 해결해주고 해쉬맵에 일치하는 문자가 있다면
그 녀석은 캐시에 담겨있는 것이니 해당 캐시에서 해당하는 녀석을 최신 상태로 놓아야한다.
최신 상태는 내 방식에서는 덱의 맨 뒤이고 가장 안쓰이는 녀석은 알아서 맨 앞으로 이동하게 된다.
안쓰이는 녀석들은 캐시 용량 한도가 오면 버려진다.
이 문제를 통해 운영체제 시간에 배웠던 LRU 캐시에 대한 기억을 되살리고 간다.
*/

int solution(int cacheSize, vector<string> cities) {
	if (!cacheSize)
		return cities.size() * 5;
	int answer = 0;
	deque<string> List;
	unordered_set<string> Map;
	for (auto& str : cities) {
		for (auto& c : str)
			c = tolower(c);
		if (Map.find(str) == Map.end()) {
			answer += 5;
			if (List.size() == cacheSize) {
				Map.erase(List.front());
				List.pop_front();
			}
			Map.insert(str);
		}
		else {
			for (int i = 0; i < List.size(); i++) {
				if (List[i] == str) {
					List.erase(List.begin() + i);
					break;
				}
			}
			answer++;
		}
		List.push_back(str);
	}
	return answer;
}