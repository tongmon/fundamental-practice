#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2193
이진수 중에 특정한 수인 이친수를 찾는 문제이다.
피보나치로 풀어도 되지만 Dp 능력을 기르기 위해 Dp로 풀었다.
1이 연속해서 나올 수 없으니 1로 끝나는 i 자릿수 이친수는 i-1 자릿수이고 0으로 끝나는 이친수의 값을 가져온다.
0으로 끝나는 i 자릿수 이친수는 i-1 자릿수인 0,1 로 끝나는 이친수의 값을 모두 가져온다. 뭘 하든 상관이 없기 때문.
그리고 초반 뻘짓으로 고생 좀 했는데 만약 로직이 맞았는데 틀렸다고 나온다면 자료형을 검토해봐라
자료형이 작아서 답이 잘려나갔었다....
*/

unsigned long long Dp[91][2];

unsigned long long Dynamic(int T)
{
	Dp[1][0] = 0; Dp[1][1] = 1;
	Dp[2][0] = 1; Dp[2][1] = 0;
	for (int i = 3; i <= T; i++)
	{
		Dp[i][0] = Dp[i - 1][0] + Dp[i - 1][1];
		Dp[i][1] = Dp[i - 1][0];
	}
	unsigned long long sum = Dp[T][0] + Dp[T][1];
	return sum;
}

int main()
{
	int Len;
	cin >> Len;
	cout << Dynamic(Len);
}