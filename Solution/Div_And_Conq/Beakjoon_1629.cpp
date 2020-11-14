#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1629
실제 C에서 pow 연산이 어떻게 돌아가는지 안다면 풀 수 있는 문제이다.
하지만 수가 너무 커질 수 있어서 나머지 연산을 쓰게 되는데 이 때 문제가 생긴다....
문제에서 주어진 최대 수의 크기는 int 범위 내에서 이루어지는데
이때 int형 최대 범위인 2,147,483,647와 2,147,483,647를 곱하면 오버플로우가 생겨 답이 이상해진다.
따라서 입력부터 함수 내의 변수를 long long으로 선언하고 곱해질 때마다 나머지 연산을 수행해주어야 한다.
long long에서 2,147,483,647와 2,147,483,647를 곱하는 경우 한번은 오버플로우가 생기지 않고 버텨주기에 가능한 방식이다.
그리고 이러한 분할 정복으로 단순한 for문의 루프를 비약적으로 줄이는 이러한 기법을 잘 기억하고 써먹자.
이 문제를 통해 분할 정복의 다양한 유형에 대한 접근법을 익혀간다.
*/

#define LLL unsigned long long

LLL A, B, C;

LLL Pow(LLL N, LLL K)
{
	if (K == 0) return 1;
	if (K == 1) return N % C;
	if (K % 2 == 0)
	{
		LLL Buf = Pow(N, K / 2);
		return (Buf * Buf) % C;
	}
	LLL Buf = Pow(N, (K - 1) / 2);
	return (((N * Buf) % C) * Buf) % C;
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> A >> B >> C;
	cout << Pow(A, B);
}