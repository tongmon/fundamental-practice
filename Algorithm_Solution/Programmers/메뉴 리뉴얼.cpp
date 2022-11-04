#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/72411
메뉴 리뉴얼 문제.
처음에 문제가 뭘 원하는지 감이 안잡혀서 문제 이해에서 좀 시간이 걸렸다.
국어 실력도 중요하다....
문제를 해석해보니 완전 탐색 문제였다.
한 단어에서 도출이 가능한 모든 경우의 낱개 단어 조합을 구해서
그 개수들을 세어나가면 되는 것이다.
단어도 길이가 최장 10개이기에 모든 경우의 수를 만든다고 해면 1024 언저리일 것이고
이 짓을 20번하고, 또 만들어진 테이블을 탐색하는데 이 탐색을 해당하는 코스 넘버별로
해야하는데 이 코스 넘버의 최대 길이가 10번이니 10 * 20 * 1024 하면 1초 안에 계산하고도
그냥 시간이 남는다.
이 문제를 통해 완전탐색 문제에 대한 감을 늘려간다.
*/

unordered_map<string, int> Table;
string Str;

void Tmaker(int St, string &T)
{
	if (Str.size() >= 2) {
		if (Table.find(Str) == Table.end())
			Table[Str] = 1;
		else
			Table[Str]++;
	}
	for (int i = St; i < T.size(); i++)
	{
		Str.push_back(T[i]);
		Tmaker(i + 1, T);
		Str.pop_back();
	}
}

vector<string> solution(vector<string> orders, vector<int> course) {
	vector<string> answer;
	for (auto A : orders) {
		sort(A.begin(), A.end());
		Tmaker(0, A);
		Str.clear();
	}
	for (auto Num : course) {
		int Max = 2;
		string Mstr;
		for (auto Ta : Table) {
			if (Ta.first.size() == Num && Max <= Ta.second)
				Max = Ta.second;
		}
		for (auto Ta : Table) {
			if (Ta.first.size() == Num && Max == Ta.second)
				answer.push_back(Ta.first);
		}
	}
	sort(answer.begin(), answer.end());
	return answer;
}