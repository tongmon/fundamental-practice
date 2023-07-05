#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/62048
멀쩡한 사각형 문제.
먼가... 좀 특이하게 풀렸다.
사각형을 그리면서 조금 고민하다가 감이 잡히지 않을 때 누가 머리에 솔루션을
쑤셔넣은듯이 갑자기 생각나서 해봤더니 맞았다.
일단 사각형 가로:세로 비율별로 따져봤더니
1:1 -> 1개 지워짐, 1:2 -> 2개 지워짐, 2:3 -> 4개 지워짐
3:4 -> 6개 지워짐... 여기서 그려보면서 알게 된 것이 비율을 더하고 1개 빼면 지워지는
사각형 개수가 도출된다.
예를 들어 4:5는 4+5 - 1로 8을 예상할 수 있다.
비율 별로 이렇게 도출 되기에 주어진 가로 세로를 최대공약수로 나누어 비율을 알아내고
여기서 빼지는 사각형을 획득하고 나누어진 비율을 곱해 실제 값을 얻어낸다.
약간 직관 능력을 평가하는 문제인 것 같다..
다른 사람의 풀이를 찾아보니 나와 같거나 약간만 달랐다.
이 문제를 통해 직관적인 능력을 길러간다.
*/

using ll = long long;

ll gcd(ll a, ll b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

long long solution(int w, int h) {
	long long answer = 1;
	ll A = w < h ? gcd(h, w) : gcd(w, h);
	ll Gw = w / A, Gh = h / A;
	ll M = Gw + Gh - 1;
	answer = (ll)w * (ll)h - A * M;
	return answer;
}