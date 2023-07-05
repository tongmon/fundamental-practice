#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/10093
쉬운 출력 문제인데 출력초과가 계속 떠서 보아하니...
for문의 i를 int형으로 지정한 문제 때문이였다....
앞으론 이런 형 크기에 관한 실수를 하지 말자!!!
머리에 형 최대 최소 따져보는 습관을 박아두자!
*/

long long A, B;

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> A >> B;
	if (A > B)
	{
		cout << A - B - 1 << '\n';
		for (long long i = B + 1; i < A; i++)
		{
			cout << i << ' ';
		}
	}
	else if (B > A)
	{
		cout << B - A - 1 << '\n';
		for (long long i = A + 1; i < B; i++)
		{
			cout << i << ' ';
		}
	}
	else cout << 0 << '\n';
}