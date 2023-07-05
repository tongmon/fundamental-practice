#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/6064
그냥 무식하게 구현해서 브루트포스로 탐색하면 시간초과가 발생하는 문제다.
일단 내가 푼 풀이는 X, Y 둘 중에 하나를 더해서 1이 먼저 되는 것을 알아내고
그 만큼 더하는 과정에서 목표치 X, Y를 거치나 확인해본다.
무식하게 1씩 증가 시키는 방식보다 시간이 획기적으로 줄어 X가 1, Y가 1 이렇게 번갈아가면서
더해지기에 최악의 시간을 계산해도 80000번에 연산이 끝나 1초안에 해결이 가능해진다.
다른 사람의 풀이를 보니 수학적으로 접근했다.
<x, y> ---> <k%M, k%N> 이를 이용하는 것이 였다. k는 몇번째인지를 의미한다.
이를 이용하면 X나 Y는 목표치로 고정해두고 예를 들어 X를 고정한다 하면 M씩 더하면 X의 값은 변하지 않으면서 Y만 변하니까
Y가 목표치인지 아닌지 검사해가면 답이 도출된다. M씩 더해가기에 시간복잡도도 빠르다.
탈출을 언제하는지 어떻게 결정하냐면 M과 N의 최소공배수가 마지막 번째를 결정한다고 한다.
이렇게 한 쪽은 고정하면서 다른 쪽의 변화를 검사하는 이러한 방식을 알아두고 써먹자.
이 문제를 통해 효율적인 접근 방식에 대한 지식을 늘려간다.
*/

long long N, M, x, y, T, X, Y, Cnt;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		X = Y = 1, Cnt = 1;
		cin >> M >> N >> x >> y;
		while (true) {
			if (X == 1) {
				long long temp = (Y + x - X) % N;
				if (!temp) temp = N;
				if (temp == y) {
					Cnt += x - X;
					break;
				}
				if (Y + M - X == N) {
					Cnt = -1; break;
				}
			}
			else {
				long long temp = (X + y - Y) % M;
				if (!temp) temp = M;
				if (temp == x) { 
					Cnt += y - Y;
					break; 
				}
				if (X + N - Y == M) {
					Cnt = -1; break;
				}
			}
			if (N - Y > M - X) {
				Cnt += (M - X + 1);
				Y += (M - X + 1); X = 1;
			}
			else {
				Cnt += (N - Y + 1);
				X += (N - Y + 1); Y = 1;
				if (X > M) X = 1;
			}
		}
		cout << Cnt << '\n';
	}
}