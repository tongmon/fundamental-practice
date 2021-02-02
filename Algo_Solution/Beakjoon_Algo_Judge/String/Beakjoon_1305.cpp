#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1305
문제를 보고도 잘 이해가 안가가지고 문제 분류를 봤는데
KMP였다. 근데 KMP를 알긴 아는데 이걸 이 문제에 어케 적용해야 되나
굉장히 막막했다. 국어를 못하는 건지 문제 자체가 뭘 요구하는지
깨닫는데 오래걸렸다.
광고가 aaba 라고 하면 이게 무제한으로 옆으로 붙여져있다.
즉 aabaaabaaabaaaba... 이렇게 되어있는데 광고판 범위가 5라고하면
|aabaa|abaaabaaaba --> a|abaaa|baaabaaaba --> aa|baaab|aaabaaaba
이렇게 광고가 진행이 된다.
여기서 접두사, 접미사가 같은 부분은 중복이 되니 aababaa라고 하면
aa가 양 끝에 겹치니 겹치는 광고를 제외하면 실제 전달되는 광고는 aabab라고 볼 수 있다.
이렇게 kmp에 사용되는 접두사, 접미사를 잘라 푸는 문제다.
왜 이렇게 생각할 수 있냐면 aababaa 여기까지 광고판에 보이는데 만약에 뒤에 aababaa | babaa
이런식으로 붙어있을 수가 있다.
그러면 끝 aa는 첫 aa 와 겹치기 때문에 실제 광고 길이에서 빼주어도 되는 것이다.
이 문제를 통해 KMP 구현을 상기시키고 간다.
*/

vector<int> Dp;
string In;

void Subm() {
	Dp.reserve(In.size());
	Dp.push_back(0); int j = 0;
	for (int i = 1; i < In.size(); i++) {
		while (j > 0 && In[j] != In[i])
			j = Dp[j - 1];
		if (In[j] == In[i])
			Dp.push_back(++j);
		else
			Dp.push_back(0);
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int N;
	cin >> N >> In;
	Subm();
	cout << N - Dp[N - 1];
}