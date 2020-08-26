#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/9465
품질이 안좋은 스티커 때기 문제이다.
처음 문제 풀때 스티커를 처음 때는 시작점을 어디다 두어야 할지 막막해서 오래걸렸다....
막상해보면 시작점은 처음 한 칸의 2개의 스티커 중 하나라는 것을 알 수 있다.
지그재그로 가서 더 커지는지, 한 칸을 그냥 건너뛰고 선택하는 것이 커지는지 비교를 하는 점화식을 도출해야 한다.
이러한 추상적 개념을 Dp 점화식화 시키는 능력을 더 키워야겠다.
*/

int Board[2][100001];
int Dp[2][100001];


int Sticker(int Size)
{
	Dp[0][0] = Board[0][0]; Dp[1][0] = Board[1][0];
	if (Size > 1)
	{
		Dp[0][1] = Board[1][0] + Board[0][1]; Dp[1][1] = Board[0][0] + Board[1][1];
		for (int i = 2; i < Size; i++)
		{
			Dp[0][i] = Board[0][i] + max(Dp[1][i - 1], Dp[1][i - 2]);
			Dp[1][i] = Board[1][i] + max(Dp[0][i - 1], Dp[0][i - 2]);
		}
	}
	return max(Dp[0][Size - 1], Dp[1][Size - 1]);
}

int main()
{
	int T, N, buffer;
	vector<int> Result;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		cin >> N;
		for (int k = 0; k < 2; k++)
		{
			scanf_s("%d", &Board[k][0]);
			for (int j = 1; j < N; j++)
			{
				scanf_s(" %d", &Board[k][j]);
			}
		}
		Result.push_back(Sticker(N));
	}
	for (int i = 0; i < T; i++)
	{
		cout << Result[i] << endl;
	}
}