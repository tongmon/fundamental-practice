#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1016
처음에 무작정 짜보고 제출했는데 맞긴했다?!
시간제한이 2초이고 내 코드의 시간복잡도가 답이 안나오는데
통과된건 좀 의외였다.... 물론 속도는 300ms로 개느렸다.
처음에 푼 코드는 그냥 제곱 수를 뽑는데 문제는 4를 뽑으면
나중에 나오는 16 36 이러한 제곱수들을 걸러줘야 한다는 것이다.
짜피 이 녀석들도 제곱수이긴 하지만 4의 배수이기에 얘네들을
실제 범위 내에서 또 나누는 것은 의미가 없다.
그래서 이렇게 필요한 제곱수들만 선별해 주는 곳에서
이중포문이 들어가는데 조건에 따라 포문 한번이 건너 뛰어질 수도 있어서
시간복잡도 계산이 난해했고...
아무튼 다음에 뽑은 제곱수들로 범위 내의 수들을 걸러준다.
그리고 개수를 세주면 되는데 내 풀이가 시간이 오래걸려서 다른 사람의 풀이를 보니
나와의 차이는 그냥 다른 사람은 set, 벡터 이런 stl을 최소화하면서
배열로 풀어나갔다.
아마 set에 숫자들을 삽입하면서 속도차이가 생긴 것 같다.
원래 Ex가 해쉬맵이였지만 이를 bool로 바꿔주니 128ms로 시간이 줄긴했다.
*/

using ll = long long;
ll Min, Max;
vector<ll> sqNum;
unordered_set<ll> Nums;
bool Ex[1000001];

void GetSQ() {
	ll Size = sqrtl(Max);
	for (ll i = 2; i <= Size; i++) {
		if (Ex[i])
			continue;
		sqNum.push_back(i * i);
		for (ll j = i * i; j <= Size; j += i) {
			Ex[j] = 1;
		}
	}
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> Min >> Max;
	Nums.reserve(1000100);
	sqNum.reserve(1000100);
	for (ll i = Min; i <= Max; i++)
		Nums.insert(i);
	GetSQ();
	for (auto SQ : sqNum) {
		ll A = Min / SQ;
		if (!(Max / SQ))
			break;
		ll i = A * SQ;
		for (ll i = A * SQ; i <= Max; i += SQ) {
			if (Nums.find(i) == Nums.end())
				continue;
			Nums.erase(i);
		}
	}
	cout << Nums.size();
}