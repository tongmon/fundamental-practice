#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1918
데이터구조 수업에 이미 들은 내용이라 쉽게 접근이 가능했다.
문제라면 -, + 가 쌓여 있을 때 *가 들어오면 -,+을 pop하는 것으로 기억하고 있었는데
그 반대로 /, *가 쌓여 있을 때 -,+가 들어오면 /, *를 pop하는 것이였다.... 
그 순서를 반대로 해서 초반에 틀렸다가 뭐가 문제인지 바로잡고 맞았다.
이렇게 어설프게 알고 있던 것을 요번 기회에 리마인딩해서 확실히 기억하고 간다.
*/

string In;
stack<char> A;
unordered_map<char, int> K;

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> In;
	K['('] = 0;
	K['+'] = K['-'] = 1;
	K['*'] = K['/'] = 2;
	A.push('('); In.push_back(')');
	for (auto& str : In) {
		if ('A' <= str && str <= 'Z')
			cout << str;
		else {
			if (str == ')') {
				while (A.top() != '(') {
					cout << A.top();
					A.pop();
				}
				A.pop();
			}
			else if (str == '(' || A.empty() || K[A.top()] < K[str])
				A.push(str);
			else {
				while (!A.empty() && K[A.top()] >= K[str]) {
					cout << A.top();
					A.pop();
				}
				A.push(str);
			}
		}
	}
}