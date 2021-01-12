#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/11660
구간합을 구하는 문제
일반적인 브루트포스 방식으로는 1000억 정도의 시간 복잡도가 나오는데
부분합을 이용하면 1억으로 줄어든다.
계속 누적합을 쌓아가면서 배열에 저장하고 특정 부분의 연속합을 알고 싶다면
Sum[마지막 인덱스] - Sum[처음 인덱스 - 1]을 해주면 된다.
주의점은 처음 인덱스는 즉 Sum[0] = 0 으로 해놓아서 처음부터 끝까지의 연속합을
구할 수 있게 해놓아야 한다.
다른 사람 풀이를 보니 나보다 더 빠른 풀이가 있었는데 애초에 사각형 전체합, 즉 
가로 세로 전체합이 더해진 결과가 Sum에 저장되어 한방에 연속합을 구하는 방식이였다.
사각형 단위로 합이 결정되기에 빼는 것도 left top bottom right 을 고려하여 적절히
블록 단위로 빼주면 한방에 연속합이 구해지니 매우 효율적이다.
이 문제를 통해 구간합 문제에 대해 좀 더 익숙해져 간다.
*/

int N, M, Sum[1025][1025], X1, Y1, X2, Y2, S;

/*
int main() // 초반에 푼 풀이... 세로합만 고려한 부분합 배열로 가로까지 고려할 때 for문이 더 돌게 된다.
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		S = 0;
		for (int j = 1; j <= N; j++) {
			cin >> X1;
			S += X1;
			Sum[i][j] = S;
		}
	}
	for (int i = 0; i < M; i++) {
		cin >> X1 >> Y1 >> X2 >> Y2;
		S = 0;
		for (int j = X1; j <= X2; j++)
			S += Sum[j][Y2] - Sum[j][Y1 - 1];
		cout << S << '\n';
	}
}
*/

int main() // 전체 가로, 세로합이 Sum 배열에 저장되어 격자 범위 연속합이 한번에 구해진다.
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		S = 0;
		for (int j = 1; j <= N; j++) {
			cin >> X1;
			S += X1;
			Sum[i][j] = Sum[i - 1][j] + S;
		}
	}
	for (int i = 0; i < M; i++) {
		cin >> X1 >> Y1 >> X2 >> Y2;
		S = Sum[X2][Y2] + Sum[X1 - 1][Y1 - 1] - Sum[X2][Y1 - 1] - Sum[X1 - 1][Y2];
		cout << S << '\n';
	}
}