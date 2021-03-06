#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12981
영어 끝말잇기 문제.
주어진 단어 리스트를 보며 끝말잇기가 잘 연결되는지, 아니면
틀린 사람의 변위가 어떻게 되는지 알아내는 문제다.
변위를 나타낼 때 현재 순서와 싸이클이 몇번 돌았는지를 이용해서 나타내기에
이 둘을 구하면 된다.
이 둘은 계속 증가하는 순서 번호를 나머지 연산을 하거나 나누면 구할 수 있다.
문자열이 다시 나왔는지 아닌지 확인은 해시맵으로 하게 된다.
이 문제를 통해 구현 속도를 늘려간다.
*/

unordered_set<string> Dic;

vector<int> solution(int n, vector<string> words) {
	int Cycle = 1;
	char Back = words[0].back();
	Dic.insert(words[0]);
	for (int i = 1; i < words.size(); i++)
	{
		if (Back != words[i].front() || Dic.find(words[i]) != Dic.end())
			return { Cycle % n + 1 , Cycle / n + 1 };
		Back = words[i].back();
		Dic.insert(words[i]);
		Cycle++;
	}
	return { 0,0 };
}
