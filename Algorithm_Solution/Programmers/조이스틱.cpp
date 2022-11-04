#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/42860
���̽�ƽ ����.
Ǯ��� �ణ �ð��� �ɷȴµ� �׸��� ��������.
�������� ù���ڶ�� ���� ��������� ��� ���� �򰥷ȴ�.
��, ��� ������ �븶�� �ٽ� A���� �����ϱ� ������
�̸� ���̽�ƽ�� ��,�Ϸ� �����̴� ��쿡 ��� �̵� ����� ���س��� �� �ִ�.
�� ����� ��, �� �̵��� ����� ������ ���� �����̴�.
�� �������� BBBAAAABB �̷� ��찰�� �̵��� ��ġ�� ���� A�� �ִ��� ���ؼ�
�ܾ���� ��� �ٲپ��ִ� �̵��� �ʿ��� ����� ���ؾ� �Ѵ�.
�� �̵������ ���� A�� �ƴ� �ܾ���� �ε����� ��Ƶδ� �迭�� ��Ƶΰ�
ù ������ 0���� �����ؼ� ������ �� �� �ִ� ���ε� ���� ����� ���� �׸���������
�����ؼ� ��� ��󰬴�. ���� ���õǸ� ���� �������� ���õ� �ε����� �ȴ�.
�̷��� �ϸ� ������ �̵������ ��������.
�� ������ ���� �׸��� ������ ���� �Ƿ��� ��������.
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