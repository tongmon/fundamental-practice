#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1436
완전탐색문제...
처음에 효율적으로 짜볼라고 별짓을 다해봤지만 생각나는 것이 없어서
그냥 1씩 증가시켜가며 스트링 변환후에 666을 찾는 기법을 사용하였더니 시간초과 안나고
맞아버렸다... 애초에 깊게 접근하지 않아도 되는 문제였다니...
다른 사람 풀이를 보니 더 효율적인 접근 방식이 있었다.
1000의 나머지가 666이면 되는 것!!!! 이러면 문자열에서 666을 찾는 단계가 없어지니
더 빨라진다. 밑 풀이의 Convert가 내 풀이고 Convert_2는 다른 사람 풀이를 참고해 만든 풀이이다.
숫자열 중 N자리 연속된 어떤 수를 찾으려면 0이 N개 달린 10배수를 나누어 주면 된다는 것을 기억하자.
사실 당연한 것인데 빨리 생각이 안났다;;
*/

long long X;

bool Convert(int N) {
	string A = to_string(N);
	if (A.find("666") == string::npos) {
		return false;
	}
	X = N;
	return true;
}

bool Convert_2(int N) {
	int Buf = N;
	while (Buf > 0) {
		if (Buf % 1000 == 666) {
			X = N; return true;
		}
		Buf /= 10;
	}
	return false;
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int N, K = 666; cin >> N; 
	while (N > 0) {
		if (Convert(K)) N--;
		K++;
	}
	cout << X;
}