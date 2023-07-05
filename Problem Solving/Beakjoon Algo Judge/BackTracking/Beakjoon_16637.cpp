#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/16637
괄호 추가하기 문제.
괄호 안에는 하나의 연산자만 들어올 수가 있어서 문자열에 주어진
문자들을 3개씩 묶느냐 아니냐로 따져가야 한다.
그니까 1 + 3 * 3 이면 1 + 3을 묶냐 아니냐 이런 것을 따져줘야 한다.
1 + 3을 묶으면 3 * 3을 묶지 못하기에 전에 묶었는지 유무도 따져줘야 한다.
처음에 스택 문제인 줄 알았는데 연산이 왼쪽부터 진행이라 스택도 필요없었다.
다른 사람의 풀이를 보니 묶는 경우를 선택하면서 그때 연산을 해나가는 방식으로
구현을 해서 나보다 코드 길이가 짧아졌다.
반면 나는 선택은 일단 모두 해놓고 마지막에 계산을 진행해서 코드가 늘어졌다.
속도 차이는 없지만 짧게 짠다고 나쁠 건 없다.
이 문제를 통해 완전탐색 구현속도를 늘려간다.
*/

using ll = long long;
ll Max = -2e12, Size;
string str;
vector<char> Op;
vector<ll> Nums;
unordered_set<int> Index;

void Exp(bool Chosen, int Cur)
{
	if (Cur == Op.size() - 1) {
		vector<char> exp;
		vector<ll> N;
		for (int i = 0; i < Op.size(); i++) {
			if (Index.find(i) != Index.end()) {
				if (Op[i] == '+')
					N.push_back(Nums[i] + Nums[i + 1]);
				else if (Op[i] == '-')
					N.push_back(Nums[i] - Nums[i + 1]);
				else
					N.push_back(Nums[i] * Nums[i + 1]);
				exp.push_back(Op[++i]);
			}
			else {
				exp.push_back(Op[i]);
				N.push_back(Nums[i]);
			}
			if (exp.size() && N.size() == 2) {
				ll Sum;
				if (exp[0] == '+')
					Sum = N[0] + N[1];
				else if(exp[0] == '-')
					Sum = N[0] - N[1];
				else
					Sum = N[0] * N[1];
				N.clear();
				N.push_back(Sum);
				exp.erase(exp.begin());
			}
		}
		Max = max(N[0], Max);
		return;
	}
	if (!Chosen) {
		Index.insert(Cur);
		Exp(true, Cur + 1);
		Index.erase(Cur);
	}
	Exp(false, Cur + 1);
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> Size >> str;
	for (int i = 0; i < Size; i++) {
		if (str[i] < '0' || str[i] > '9')
			Op.push_back(str[i]);
		else
			Nums.push_back(str[i] - '0');
	}
	Op.push_back('/');
	Exp(false, 0);
	cout << Max;
}