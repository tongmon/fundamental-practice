#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/18111
문제 조건이 애매해서 자꾸 틀렸습니다 나온 문제...
높이 제한이 256을 초과할 수 없다. 라고 되어있어서 255까지로 했는데 256까지 해야했던 것이다...
문제는 완전탐색 문제로 높이 0부터 256까지 맵 전체를 계속 순회하면 된다.
그러나 다른 사람 풀이 중에 더 빠른 풀이가 있었다.
맵 저장을 이차원으로 할 필요없이 높이별로 나누어 저장하면 이중포문으로 순회가 끝난다!...
문제 풀 때 자료구조를 어떻게 짜야하는지에 대해 더 고민해보는 시간이 필요할 것 같다.
이 문제를 통해 완전탐색 문제에 대한 풀이 속도를 늘려간다.
*/

int N, M, B, H, T = 999999999;
short Map[501][501];

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M >> B;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> Map[i][j];
		}
	}
	for (int i = 0; i <= 256; i++)
	{
		int Block = B, Time = 0;
		for (int k = 0; k < N; k++)
		{
			for (int j = 0; j < M; j++)
			{
				if (Map[k][j] > i) {
					Block += Map[k][j] - i;
					Time += (Map[k][j] - i) * 2;
				}
				else {
					Block -= i - Map[k][j];
					Time += i - Map[k][j];
				}
			}
		}
		if (Block < 0) break;
		if (Time <= T) {
			T = Time; H = max(H, i);
		}
	}
	cout << T << ' ' << H;
}