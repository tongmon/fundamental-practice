#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1915
가장 큰 정사각형을 찾는 문제.
브루트 포스 방식으로 풀려하면 n * n * (N - n) * (M - n) 
여기서 n은 정사각형 한변의 길이이고 위와 같은 짓을 1부터 목표 N, M 까지
진행해야 하니 시간복잡도가 답이 없다.
따라서 Dp로 접근했다.
초반에 곰곰히 생각하다가 정사각형이라는 것에 착안하여 모서리를 생각하고 
점화식을 짰다.
일단 모서리를 기점으로 이중포문이 돌아가는데 해당 모서리가 0인 경우 사각형도
아니기에 Pass한다.
모서리 값이 1이면? 그 모서리 위, 옆, 대각선(왼,위)을 보는데 여기서 0이 하나라도
나오면 일단 정사각형 탈락, 0이 하나도 안나왔다면 그간 쌓아놓은 정사각형의 한변의
길이가 Dp배열에 기록이 되어있을 것이고 그 길이 중에서 가장 작은 녀석을 택하고 +1을 기록한다.
왜 작은놈이냐면 위쪽이 3인데 옆쪽은 2이면 2를 택해야지 정상적으로 만들 수 있는 정사각형의
변 길이가 나오지 3을 택하고 변의 길이 4를 기록하면 실제 정사각형 길이 4는 만들 수 없는데 Dp 배열에
기록이 된다.
아무튼 이러한 점화식을 돌리면서 가장 큰 변을 획득하고 넓이를 반환하면 된다.
이 문제를 통해 Dp에 대한 접근법을 더 배워간다.
*/

int N, M, Map[1001][1001], Dp[1001][1001], Ans;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			char a; cin >> a;
			Map[i][j] = a - '0';
		}
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			if (!Map[i][j])
				continue;
			int X[3] = { j - 1,j - 1,j }, Y[3] = { i,i - 1,i - 1 }, Min = 2001;
			bool flag = 1;
			for (int k = 0; k < 3 && flag; k++)
			{
				if (0 <= X[k] && X[k] < M && 0 <= Y[k] && Y[k] < N)
					Min = min(Min, Dp[Y[k]][X[k]]);
				else 
					flag = 0;
			}
			if (!flag)
				Dp[i][j] = 1;
			else
				Dp[i][j] = Min + 1;
			Ans = max(Ans, Dp[i][j]);
		}
	cout << Ans * Ans;
}