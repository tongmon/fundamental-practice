#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12952
풀면서 굉장히 애를 먹은 문제다.
사고방식을 바꾸어야 했다.
백트래킹이라고 생각이 들었지만 계속해서 이중 포문을 통해 좌표를 선택해 나가는
방식으로 접근하니까 시간초과도 나고 중복되는 결과로 인해 오답도 도출되었다.
결국 힌트를 봤는데 백트래킹에서 거의 모두 쓰이는 깊이 변수는 재귀가 진행되면서
자동으로 증가하는데 이를 이용하는 것이였다....
어짜피 퀸들은 같은 x,y에 있지를 못하니 자동으로 늘려주는 깊이를 이용해
x나 y를 자동으로 증가시키면 이중포문에서 단일 포문으로 바뀌고
이렇게 되면서 중복되는 값에 대해 고려할 필요가 없다.
Cr1, Cr2 배열은 사선에 있는 좌표들은 모두 (A, B)라면 A-B나 A+B한 값이 둘 중 하나라도 같다는 것을
이용한 사선 거르기용 배열이다.
이 문제를 통해 백트래킹에서 자동으로 증가하는 깊이 인자를 이용할 수도 있다는 것을 알아간다.
*/

int ans;
bool X[15], Y[15];
unordered_map<int, bool> Cr1, Cr2;

void NQ(int dep, int n) {
	if (dep == n) {
		ans++;
		return;
	}
	for (int i = 0; i < n; i++) {
		if (X[i] || Y[dep] || Cr1[i - dep] || Cr2[i + dep])
			continue;
		X[i] = Y[dep] = Cr1[i - dep] = Cr2[i + dep] = 1;
		NQ(dep + 1, n);
		X[i] = Y[dep] = Cr1[i - dep] = Cr2[i + dep] = 0;
	}
}

int solution(int n) {
	for (int i = -15; i < 30; i++)
		Cr1[i] = Cr2[i] = 0;
	NQ(0, n);
	return ans;
}