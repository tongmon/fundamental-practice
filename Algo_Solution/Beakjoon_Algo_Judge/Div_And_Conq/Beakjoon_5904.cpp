#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/5904
그냥 문자열을 사용하는 재귀라면 푸는데 수월했겠지만... 이 문제는 
문자열을 그냥 넣어버리면 기하급수적으로 문자가 늘어나 메모리가 터진다.
따라서 몇 번째에 무슨 문자가 있는지만 판단해야 한다.
moo 문자열은 완전 이진 트리 형태를 갖추고 있어서 재귀로 만들어 보자면
전에 만들어 놓았던 녀석들을 가져와서 붙이고 중간에 있는 놈을 붙이고
전에 만들어 놓았던 녀석을 반대편에 붙이면서 계속 진행하면 만들 수 있다.
문자열 개수만 따지기 때문에 사실상 숫자를 더하는 연산이 주가되고
만약에 반대편에 붙인 녀석에서 답이 찾아진다고 판단되면 범위를 좁혀
새로 시작하게 된다.
이렇게 탐색 범위를 좁혀나가는 재귀를 잘 짤 수 있게 많은 문제를 풀어야겠다.
이 문제를 통해 재귀에 대한 감을 잡아나간다.
*/

long long N, K, m = 2, Back;
char Ans;

void Moo(long long Temp)
{
	m++; // o를 붙여야 하니까 중간 부분 1개 추가
	Back = K; K = K + m; // 예전 녀석인 K와 합체
	if (K >= N) // 중간에서 N이 포함되는지 판단
	{
		if (Back + 1 == N) Ans = 'm';
		else Ans = 'o';
		return;
	}
	Back = K; K = K + Temp;
	if (K >= N) // 오른쪽에 붙일 부분에 N이 속하면 처음부터 moo를 만들면서 다시 판단
	{
		m = 2; K = 0; N -= Back; // 여태 붙였던 수 만큼 탐색은 끝났으니 N에 Back을 빼줌
		Moo(0); return;
	}
	Moo(K);
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	Moo(0);
	cout << Ans;
}