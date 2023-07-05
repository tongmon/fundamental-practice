#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/17677
���� Ŭ�����͸� ����
�ؽ��� ��� �ɷ��� ���� ��������.
�ؽ��ʿ� str1���� ������ �༮��, str2���� ������ �༮���� ������ pair�� ���� �����Ѵ�.
pair���� �� ū ���� �������� ���� ���� �������� �ǹ��ϰ� �ȴ�.
��,������ �� �������� �϶���� ���� ����ϸ�ȴ�.
�� ������ ���� �����ӵ��� �÷�����.
*/

unordered_map<string, pair<int, int>> Sets;

int solution(string str1, string str2) {
	int answer = 0, Inter = 0, Uni = 0;
	string Ary[2] = { str1, str2 };
	for (int k = 0; k < 2; k++) {
		for (int i = 0; i < Ary[k].size() - 1; i++) {
			string A;
			A += toupper(Ary[k][i]);
			A += toupper(Ary[k][i + 1]);
			if ('A' <= A[0] && A[0] <= 'Z' && 'A' <= A[1] && A[1] <= 'Z') {
				if (Sets.find(A) == Sets.end())
					!k ? Sets[A].first = 1 : Sets[A].second = 1;
				else
					!k ? Sets[A].first++ : Sets[A].second++;
			}
		}
	}
	for (auto& S : Sets) {
		Uni += max(S.second.second, S.second.first);
		Inter += min(S.second.second, S.second.first);
	}
	if (!Uni) return 65536;
	answer = floor(65536 * float(Inter / (float)Uni));
	return answer;
}