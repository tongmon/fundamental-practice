#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/42888
오픈채팅방 문제.
해쉬맵 활용도를 묻는 문제다.
유저 아이디가 추후에 어떻게 바뀔지 예측할 수 없기 때문에
for문이 두 번 돌면서 한 번은 출력할 값들을 저장해 놓고
두번째 루프에서는 출력할 값에 담긴 고유한 유저 아이디를 가지고
실제 출력할 결과를 담는다.
이 문제를 통해 구현 속도를 늘려간다.
*/

unordered_map<string, string> User;

vector<string> solution(vector<string> record) {
	vector<string> answer;
	vector<pair<string, char>> Con;
	string A[3];
	for (auto& str : record) {
		stringstream In(str);
		In >> A[0] >> A[1] >> A[2];
		if (A[0][0] == 'E') {
			User[A[1]] = A[2];
			Con.push_back({ A[1], 'E' });
		}
		else if (A[0][0] == 'L')
			Con.push_back({ A[1], 'L' });
		else
			User[A[1]] = A[2];
	}
	for (auto& A : Con) {
		string In;
		if (A.second == 'E')
			In += User[A.first] + "님이 들어왔습니다.";
		else if (A.second == 'L')
			In += User[A.first] + "님이 나갔습니다.";
		answer.push_back(In);
	}
	return answer;
}