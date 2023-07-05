#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1074
분할 정복 문제다.
TopDown 방식으로 위에서 부터 4분할로 내려가면서 카운트를 증가시키는 재귀를 돌린다.
사각형 한 변의 크기가 2의 제곱 수이기 때문에 격자 개수를 곱연산으로 적절히 구해 더해나가면서 
크기 2까지 쪼갰으면 목표를 찾고 찾았으면 재귀를 종료하고 개수가 구해지는 방식이다.
이 문제를 통해 분할 정복 문제 접근 속도를 더 빠르게 만들어 나간다.
*/

int N, r, c, Cnt;

void Div(int Len, int Tx, int Ty)
{
	if (Len == 2)
	{
		for (int i = Ty; i < Ty + 2; i++)
		{
			for (int j = Tx; j < Tx + 2; j++)
			{
				if (i == r && j == c) return;
				Cnt++;
			}
		}
	}
	int NLen = Len / 2;
	if (Tx <= c && c < Tx + NLen && Ty <= r && r < Ty + NLen){
		Div(NLen, Tx, Ty); return;
	}
	Cnt += NLen * NLen;
	if (Tx + NLen <= c && c < Tx + Len && Ty <= r && r < Ty + NLen) {
		Div(NLen, Tx + NLen, Ty); return;
	}
	Cnt += NLen * NLen;
	if (Tx <= c && c < Tx + NLen && Ty + NLen <= r && r < Ty + Len) {
		Div(NLen, Tx, Ty + NLen); return;
	}
	Cnt += NLen * NLen;
	Div(NLen, Tx + NLen, Ty + NLen);
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> r >> c;
	Div(pow(2, N), 0, 0);
	cout << Cnt;
}