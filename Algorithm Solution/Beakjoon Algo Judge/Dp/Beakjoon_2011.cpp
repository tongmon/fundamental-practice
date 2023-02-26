#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
https://www.acmicpc.net/problem/2011
암호코드 문제이다.
언뜻보면 타일 깔기 문제들과 비슷한 피보나치 점화식을 이용하는 문제처럼 보일 수 있지만
매우 많은 예외처리를 필요로 한다...
점화식 자체는 예외를 거르면 Dp[i] = Dp[i - 1] + Dp[i - 2] 피보나치가 맞긴하지만
새로 들어오는 숫자가 0인지 그 뒤의 숫자가 얼마인지 이러한 조건에 따라 점화식이 바뀌어진다.
이 문제를 통해 점화식 세우기와 더불어 많은 예외처리를 할 수 있는 능력을 길러야 한다.
*/

#define Moded 1000000

unsigned long long Dp[5001];

unsigned long long Cod(string Code)
{
	if (Code[0] == '0')
	{
		return 0;
	}
	Dp[0] = 1; Dp[1] = 1;
	for (int i = 2; i <= Code.size(); i++)
	{
		if ('0' == Code[i - 1] && '0' == Code[i - 2]) // 연속으로 두개가 0이면 그런 알파벳은 없다
		{
			return 0;
		}
		else if ('2' < Code[i - 2])
		{
			if ('0' == Code[i - 1]) // 30 같은거 방지
			{
				return 0;
			}
			else // 379 이런거
			{
				Dp[i] = Dp[i - 1];
			}
		}
		else if ('0' < Code[i - 2] && Code[i - 2] <= '2')
		{
			if (Code[i - 2] == '2' && Code[i - 1] > '6') // 27 이런거
			{
				Dp[i] = Dp[i - 1];
			}
			else if (Code[i - 1] == '0') // 20 이런거
			{
				Dp[i] = Dp[i - 2];
			}
			else // 정상범주
			{
				Dp[i] = (Dp[i - 1] + Dp[i - 2]) % Moded;
			}
		}
		else if (Code[i - 2] == '0') // 109 이런거
		{
			Dp[i] = Dp[i - 1];
		}
		else // 110 이런거
		{
			Dp[i] = (Dp[i - 1] + Dp[i - 2]) % Moded;
		}
	}
	return Dp[Code.size()];
}

int main()
{
	string Code;
	cin >> Code;
	cout << Cod(Code);
}