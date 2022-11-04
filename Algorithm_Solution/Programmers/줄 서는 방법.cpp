#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12936
줄 서는 방법 문제.
k번째의 순열 찾는 문제인데 next_permutation으로 그냥 돌리면 시간복잡도가
미쳐돌아갈 수 있다.
그래서 한번에 몇 단계를 스킵할 수 있는 수식이 필요하다.
3 1 2 에서 일단 3 이 선택 되었다는 것은 앞 자리 1, 2인 수열은 볼 필요도 없다는 것이고
1, 2 인 녀석들의 개수는 1 인 경우 2개 2인 경우 2개로 총 4개가 스킵된다.
이 것은 1, 2 개수 2개와 2! 이 곱해서 나온 4이다.
따라서 4개 스킵하고 나머지 1, 2 / 2, 1 두 종류 중에 1, 2가 앞서니까 5번째 순열이 3,1,2가 된다.
이러한 방식을 코드로 짜서 풀었다.
fac[N] * i >= Fin 이 부분에서 같은 것도 포함시키는 것은 앞 자리가 2인 순열의 끝자락
즉, 2, 3, 1 이러한 녀석은 4번째인데 이 녀석은 딱 앞자리를 2에서 3으로 스킵하는 구분점 4에 걸친다.
그니까 3으로 시작되는 녀석으로 넘어가는 곳에 걸친다는 것이다.
그래서 같은 것을 포함하지 않고 break하면 그대로 Fin에서 4가 빠져 앞자리가 3이 되어버리는 것이다.
목표 타겟 2, 3, 1의 앞자리는 2인데 불구하고... 따라서 같은 것도 포함해서 break하여 올바른
순열을 만든다.
이 문제를 통해 순열 문제에 대한 실력을 늘려간다.
*/

using ll = long long;
vector<int> answer, Nums;

void FacNum(int N, ll Fin, vector<ll>& fac) {
	if (Nums.size() == 1) {
		answer.push_back(Nums[0]);
		return;
	}
	int i;
	for (i = 0; i < Nums.size(); i++) {
		if (fac[N] * i >= Fin)
			break;
	}
	Fin -= fac[N] * (i - 1);
	answer.push_back(Nums[i - 1]);
	Nums.erase(Nums.begin() + i - 1);
	FacNum(N + 1, Fin, fac);
}

vector<int> solution(int n, long long k) {
	vector<ll> fac(n);
	ll N = 1;
	for (int i = n - 1, j = 1; i >= 0; i--, j++) {
		Nums.push_back(j);
		N *= j;
		fac[i] = N;
	}
	FacNum(1, k, fac);
	return answer;
}