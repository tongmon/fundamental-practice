#include <iostream>
using namespace std;

/*
https://www.acmicpc.net/problem/23971
옆 뒷 자리에 앉으려면 특정 거리를 띄고 앉아야 한다.
5자리인 상황에서 2자리를 띄고 앉아야 한다면 실제로 한명은 3자리를 먹고 있는 것과 같은 효과다.
따라서 일단 5자리에서 3칸씩 몇개를 채울 수 있는지 보려면 5 / 3을 하면 된다.  
3칸씩 채우고 남는 자리가 있을 텐데 이곳은 거리확보가 된 상태이기에 남은 사람 한명이 아무 곳에나 앉아도 된다.
결과적으로 5 / (2 + 1) + (5 % (2 + 1) ? 1 : 0) 와 같은 식이 도출된다.
*/

#define A(x, y) (x / (y + 1) + (x % (y + 1) ? 1 : 0))

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int H, W, M, N;
	cin >> H >> W >> N >> M;
	cout << A(H, N) * A(W, M);
	return 0;
}