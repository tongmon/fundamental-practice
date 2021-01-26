#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12953
N개의 최소공배수
숫자 N개가 주어지고 그 수들의 공통되는 최소공배수를 구하면된다.
어떻게 할까 생각하다가 최대 15개의 수이고 그 수도 100 이하로 작아서
실제 손으로 계산하는 방식처럼 소인수 분해를 해서 풀었다.
근데 비효율적인 것 같아 다른 사람 풀이를 보니 굉장히 깔쌈한 솔루션이 있었다.
걍 a,b,c 이렇게 3개의 수가 있다면 a와 b의 최소공배수 d와 c의 최소공배수를 구하면
3개의 수의 최소공배수가 도출된다.
생각해보면 최소공배수라는게 소인수 분해하여 필요한 만큼의 소인수들만 두 수에서 가져와
곱해 최대로 만드는 것이니... 맞을 수 밖에
이 문제를 통해 최소공배수, 최대공약수, 소수 판정에 대해 복습했다.
*/

/*
// 정석적인 풀이법

int Gcd(int a, int b) {
	int r = a % b;
	if (r == 0)
		return b;
	return Gcd(b, r);
}

int Lcm(int a, int b) {
	return a * b / Gcd(a, b);
}

int solution(vector<int> arr) {
	while (arr.size() != 1) {
		int a = arr.back(), b, Min, Max;
		arr.pop_back();
		b = arr.back();
		arr.pop_back();
		Min = min(a, b);
		Max = max(a, b);
		arr.push_back(Lcm(Max, Min));
	}
	return arr[0];
}
*/

// 처음 소인수분해하여 푼 풀이법

bool Prime[101];
vector<int> P;

void Era() {
	for (int i = 4; i < 101; i += 2)
		Prime[i] = 1;
	for (int i = 3; i <= 10; i += 2)
	{
		if (Prime[i])
			continue;
		for (int j = i * i; j < 101; j += i)
			Prime[j] = 1;
	}
	for (int i = 2; i < 101; i++)
	{
		if (!Prime[i])
			P.push_back(i);
	}
}

int solution(vector<int> arr) {
	int answer = 1;
	Era();
	for (auto prime : P) {
		int Mcnt = 0;
		for (auto num : arr) {
			int N = num, cnt = 0;
			while (N / prime > 0) {
				if (N % prime != 0)
					break;
				N /= prime;
				cnt++;
			}
			Mcnt = max(cnt, Mcnt);
		}
		answer *= pow(prime, Mcnt);
	}
	return answer;
}