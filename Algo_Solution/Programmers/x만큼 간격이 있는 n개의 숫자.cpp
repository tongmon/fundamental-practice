#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12954
x만큼 간격이 있는 n개의 숫자 문제.
람다와 transform을 이용하여 숏코딩해봤다.
transform 함수 주의점은 람다식에 컨테이너 템플릿 인자를 받아야한다는 것이다.
[&](LL k)->LL {return LL(x) + i++ * x; } 이거 대신에
[&]()->LL {return LL(x) + i++ * x; } 이거 쓰면 오류난다.
인자 형이 LL이 아니라 string 같이 쌩뚱맞은 것을 넣어도 오류난다.
인자를 const LL &k, LL &k, LL k 속도 비교해보면 당연히
const LL &k가 가장 빠르다... (LL *k는 오류나서 제외)
*/

using LL = long long;

vector<LL> solution(int x, int n) {
	vector<LL> a(n);
	LL i = 0;
	transform(a.begin(), a.end(), a.begin(), [&](LL &k)->LL {return LL(x) + i++ * x; });
	return a;
}