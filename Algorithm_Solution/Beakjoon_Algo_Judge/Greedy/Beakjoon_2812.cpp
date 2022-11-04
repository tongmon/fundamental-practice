#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2812
스택을 이용한 그리디 문제다.
그리디는 정말 문제에 대한 우선 순위를 찾는 것이 힘든 것 같다.
일단 주어진 숫자를 스택에 넣어간다.
넣다가 현재 넣어져 있는 숫자들이 지금 선택된 숫자보다 작다면 자신보다 큰 숫자가
등장할 때 까지 스택에서 계속해서 숫자를 뺀다.
자기보다 큰 숫자가 등장하거나 스택이 비면 현재 선택된 숫자는 정확히 자신의 자리를 찾게 된 것이다.
이렇게 해서 뺄 수 있는 수만큼 모두 뺐다면 정답이 도출된다.
스택을 이용해서 푸는 그리디 유형을 더 많이 풀어서 익숙해져야겠다.
*/

string A, Ans;
int N, K;

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> K >> A;
	for (auto str : A) {
		while (K && !Ans.empty() && str > Ans.back()) {
			K--; Ans.pop_back();
		}
		Ans.push_back(str);
	}
	for (int i = 0; i < Ans.size() - K; i++)
		cout << Ans[i];
}