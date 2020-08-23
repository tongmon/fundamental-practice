#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/11054
11722번, 11053번을 섞어 놓은 문제이다.
오름차순 정렬, 내림차순 정렬을 적절하게 한 후에 합쳐주면 된다.
여기서 주의할 사항은 중복이 되는 원소를 빼주어야 하기에 합치고 -1이 들어간다는 것이다.
이 문제를 통해 여러 Dp배열을 만들고 적절히 합치는 방법을 숙지해야 한다.
*/

int Ary[1001], Dp[1001];
int Dp_Up[1001], Count_Min[1001];
int Dp_Down[1001], Count_Max[1001];

void Dynamic_UP(int start, int end) // 오름차수 부분 수열 Dp 채우기
{
	int Len = 1;
	Count_Min[1] = Ary[0];
	for (int i = start; i <= end; i++)
	{
		for (int j = 1; j <= Len; j++)
		{
			if (Ary[i] <= Count_Min[j])
			{
				Count_Min[j] = Ary[i]; Dp_Up[i] = j; break;
			}
			else if (Len == j)
			{
				Count_Min[++Len] = Ary[i]; Dp_Up[i] = Len; break;
			}
		}
	}
	return;
}

void Dynamic_DOWN(int start, int end) // 내림차수 부분 수열 같지만 오름차수 부분 수열을 거꾸로 시작한 것과 같다.
{
	int Len = 1;
	Count_Max[1] = Ary[end];
	for (int i = end; i >= start; i--)
	{
		for (int j = 1; j <= Len; j++)
		{
			if (Ary[i] <= Count_Max[j])
			{
				Count_Max[j] = Ary[i]; Dp_Down[i] = j; break;
			}
			else if (Len == j)
			{
				Count_Max[++Len] = Ary[i]; Dp_Down[i] = Len; break;
			}
		}
	}
	return;
}

int Bitonic(int Size)
{
	Dynamic_UP(0, Size - 1); Dynamic_DOWN(0, Size - 1);
	Dp[0] = Dp_Up[0] + Dp_Down[0] - 1;
	int Bigone = Dp[0];
	for (int i = 1; i < Size; i++)
	{		
		if (Ary[i] > Ary[i - 1])
		{
			Dp[i] = Dp_Up[i] + Dp_Down[i] - 1;
			if (Bigone < Dp[i])
			{
				Bigone = Dp[i];
			}
		}
	}
	return Bigone;
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
	cout << Bitonic(N);
}