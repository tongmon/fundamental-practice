#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/16916
KMP �˰������� Ǯ��� �Ѵ�.
��� ����, �ؽ��� �� ����غôµ� �ð� �ʰ��� �޸� �ʰ��� ����.
�� ������ ���� kmp �˰��� ����� �ǻ츮�� ����.
*/

string A, B;

void flps(string* Target, vector<int>* lps)
{
	lps->reserve(Target->size());
	int j = 0; lps->push_back(0);
	for (int i = 1; i < Target->size(); i++) {
		while (j > 0 && Target->at(i) != Target->at(j))
			j = lps->at(j - 1);
		lps->push_back((Target->at(i) == Target->at(j) ? ++j : 0));
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> A >> B;
	vector<int> a;
	flps(&B, &a);
	for (int i = 0, j = 0; i < A.size(); i++) {
		while (j > 0 && A[i] != B[j])
			j = a[j - 1];
		if (A[i] == B[j]) {
			if (j == B.size() - 1) {
				cout << 1; return 0;
			}
			else j++;
		}
	}
	cout << 0;
}