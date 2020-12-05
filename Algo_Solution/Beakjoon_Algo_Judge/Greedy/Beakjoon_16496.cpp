#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/16496
프로그래머스의 https://programmers.co.kr/learn/courses/30/lessons/42746 이 문제와
그냥 똑같은 로직의 문제이다.
근데 웃긴건... 프로그래머스에서 2레벨인데 백준에서 플레다....
근데 모르면 풀기 어려울 것 같긴하다. 나도 프로그래머스에서 손대봐서 접근법이 생각난 문제니까...
이래서 그리디가 어려워지면 난이도가 상당히 올라가나보다.
숫자를 단어로 변환해서 비교하는 이러한 테크닉을 잘 알아가자.
*/

bool Cmp(string A, string B) {
	return A + B > B + A;
}

int N, In;
vector<string> Con;

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> In;
		Con.push_back(to_string(In));
	}
	sort(Con.begin(), Con.end(), Cmp);
	if (Con.front() == "0") {
		cout << 0; return 0;
	}
	for (auto Num : Con) cout << Num;
}