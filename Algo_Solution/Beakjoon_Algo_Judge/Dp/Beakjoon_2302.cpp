#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2302
피보나치를 사용하는 Dp 문제이다.
일단 좌석 변경이 1234 이러면 1번은 2번으로 밖에, 3번은 2번과 4번으로 가능하다.
좌석을 변경하면 서로의 위치가 바뀌는 것이기에 스왑 개념으로 봐야한다.
그럼 Dp의 기본적인 개념으로 보통 n-1 이하의 수식을 사용해서 n번째 상태가 도출된다.
1234 예를 계속 쓰면
1 --> 한가지
12 --> 12, 21 스왑 한번 두가지
123 --> 123, 213, 132 3가지
123을 잘보면 3을 고정한 경우 원소 2개(1,2)였던 2가지 + 3이 스왑된 경우 원소 1밖에 없는 1가지
이렇게 더해져 3가지가 나오는 것을 알 수 있다.
1234도 보면 원소 3가지인 경우(4고정) + 원소 2가지인 경우(4,3 스왑)으로 5가지가 나온다.
Dp[n-2] + Dp[n-1] = Dp[n] 피보나치이다.
근데 vip 고정 좌석이 경우의 수를 가르기 때문에 12345에서 3이 vip면 Fib(2) * Fib(2)가 된다.
이러한 생각을 통해 문제를 풀 수가 있다.
이 문제를 통해 Dp 문제에 더 익숙해져간다.
*/

int N, M, Ans;
vector<int> R;

int Fib(int N) {
	queue<int> Q({ 1,1 });
	for (int i = 2; i <= N; i++) {
		Q.push(Q.front() + Q.back());
		Q.pop();
	}
	return Q.back();
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> Ans;
		R.push_back(Ans);
	}
	int St = 1; Ans = 1;
	for (auto num : R) {
		Ans *= Fib(num - St);
		St = num + 1;
	}
	N++;
	Ans*= Fib(N - St);
	cout << Ans;
}