#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/11053
대표적인 Dp문제 중 하나인 최장 길이 증가 부분 수열을 구하는 문제이다.
O(n*n)의 복잡도가 걸리는 알고리즘에서는 현재 고를 원소에서 그 원소보다 작은 녀석들 중에
가장 여태까지 많이 원소들을 많이 달고 있는 즉, Dp값이 가장 큰 녀석을 선택해 그 뒤에 현재 원소를 달아
Dp = Dp + 1을 해주는 방식이다.
하지만 이 방식은 현재 그 원소 위치 전에 있는 원소들을 모두 검사해야 하기에 비효율 적이다.
그래서 밑의 Count_Min 배열을 이용하여 시간복잡도를 O(n*log(n)) 로 줄이는 방식이 있다.
이 방식은 이중 for문 처럼 보여도 Count_Min 배열만 탐색하기에 더 효율적이다.
이 문제를 통해 기존 값들을 모두 비교하여 현재 최선의 Dp를 찾는 방식에 익숙해져야 한다.
*/

int Ary[1001];
int Dp[1001];

// 이 배열에서 인덱스는 부분 수열의 개수를 나타내고 배열값은 그 길이를 가지는 부분 수열 중 마지막을 장식하는 녀석의 제일 작은 값을 가리킨다.
int Count_Min[1001];

int Dynamic(int Size) // O(n*n)
{
	Dp[0] = 1; 
	int Big = 0;
	for (int i = 1; i < Size; i++)
	{
		int Bigone = 0;
		for (int j = i - 1; j >= 0; j--)
		{
			if (Ary[i] > Ary[j] && Bigone <= Dp[j])
			{
				Bigone = Dp[j];
			}
		}
		Dp[i] = Bigone + 1;
	}
	for (int i = 0; i < Size; i++)
	{
		if (Dp[i] > Big)
		{
			Big = Dp[i];
		}
	}
	return Big;
}

int Dynamic_improved(int Size) // O(n*log(n))
{
	Dp[0] = 1; Count_Min[1] = Ary[0];
	int Maxindex = 1;
	for (int i = 1; i < Size; i++)
	{
		for (int j = 1; j <= Maxindex; j++)
		{
			if (Count_Min[j] >= Ary[i])
			{
				Count_Min[j] = Ary[i]; Dp[i] = j;
				break;
			}
			else if (Maxindex == j)
			{
				Count_Min[++Maxindex] = Ary[i]; Dp[i] = Maxindex;
				break;
			}
		}
	}
	return Maxindex;
}

int main()
{
	int N;
	cin >> N;
	scanf_s("%d", &Ary[0]);
	for (int i = 1; i < N; i++)
	{
		scanf_s(" %d", &Ary[i]);
	}
	cout << Dynamic_improved(N);
}