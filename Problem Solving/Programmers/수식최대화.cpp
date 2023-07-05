#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/67257
수식 최대화 문제.
수식이 나와서 스택 문제인지 감이 왔고
스택에서 연산자를 사용해서 수식의 연산을 진행하는 방법을
자료구조 시간에 배웠기에 그것을 써먹었다.
단지 다른 점이라면 기존에 -, + , * 에 해당하는 우선순위가 존재했는데
이번엔 이를 뒤바꿔가면서 계산해야 한다는 점이다.
뒤바꾸기위해 next_permutation을 사용하여 좀 더 쉽게 풀 수 있었다.
이 문제를 통해 구현 속도를 늘려간다.
*/

long long solution(string expression) {
	long long Max = -1e18;
	unordered_map<char, int> Pp;
	vector<int> Ch = { '*','+','-' };
	Pp['/'] = 4;
	do {
		expression += '/';
		for (int i = 0; i < 3; i++)
			Pp[Ch[i]] = i;
		stack<char> Op;
		stack<long long> Nums;
		string N;
		for (int i = 0; i < expression.size(); i++) {
			if (('0' > expression[i] || '9' < expression[i]) && !N.empty()) {
				Nums.push(stoi(N));
				N.clear();
				while (!Op.empty() && Pp[expression[i]] >= Pp[Op.top()]) {
					long long A = Nums.top(), B;
					Nums.pop();
					B = Nums.top();
					Nums.pop();
					if (Op.top() == '-')
						Nums.push(B - A);
					else if (Op.top() == '+')
						Nums.push(B + A);
					else
						Nums.push(B * A);
					Op.pop();
				}
				Op.push(expression[i]);
			}
			else
				N.push_back(expression[i]);
		}
		Max = max(Max, abs(Nums.top()));
		expression.pop_back();
	} while (next_permutation(Ch.begin(), Ch.end()));
	return Max;
}