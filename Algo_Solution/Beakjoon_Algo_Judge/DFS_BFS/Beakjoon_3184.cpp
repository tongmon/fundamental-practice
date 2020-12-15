#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/3184
그래프 탐색 문제다.
오랜만에 이 유형을 풀어서 그런지 구현 도중에 잦은 실수가 있었는데
이를 고쳐야한다.
*/

int W, H, Dir[4][2] = { {0,1},{1,0},{-1,0},{0,-1} }, wCnt, sCnt;
char Map[251][251];
bool vis[251][251];

void DFS(int h, int w, int *wol, int *she) {
	if (Map[h][w] == 'v')
		*wol += 1;
	else if (Map[h][w] == 'o')
		*she += 1;
	for (int i = 0; i < 4; i++)
	{
		int hei = h + Dir[i][0], wid = w + Dir[i][1];
		if (0 <= hei && hei < H && 0 <= wid && wid < W 
			&& !vis[hei][wid] && Map[hei][wid] != '#') {
			vis[hei][wid] = 1;
			DFS(hei, wid, wol, she);
		}
	}
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> H >> W;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> Map[i][j];
		}
	}
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (!vis[i][j] && Map[i][j] != '#') {
				int wol = 0, she = 0;
				vis[i][j] = 1;
				DFS(i, j, &wol, &she);
				if (wol < she)
					sCnt += she;
				else 
					wCnt += wol;
			}
		}
	}
	cout << sCnt << ' ' << wCnt;
}