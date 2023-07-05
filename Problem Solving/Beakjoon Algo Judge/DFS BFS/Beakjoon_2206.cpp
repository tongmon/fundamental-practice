#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2206
BFS 탐색 문제인데 여태껏 풀어보지 못한 유형이였다.
일단 문제 풀이법을 말하기 전에 입력부터 삐걱거렸는데
0110101 이렇게 붙어있는 숫자 입력받을 시에 string으로 추출한 후에
string을 읽으면서 배열에 0,1을 집어넣어라... 그렇게 안하고 Input으로 숫자 받으면
0110101 이걸 받으면 110101 이렇게 저장되고 그냥 입력한번 받고 끝난다.
이 점 유의할 것.
아무튼 다시 풀이법으로 돌아와보면 이 문제는 그냥 BFS를 휘갈겨 푸는 문제가 아니다.
그러면 우선순위 큐나 덱으로 풀 수 있냐? 그것 또한 아니다.
벽을 여러번 부수면서 나아간다면 덱이나 우선순위 큐가 먹히겠지만 이 문제는 단 한번만 벽을 부술 수 있다.
그렇다면 어떻게 풀어야 할까?
Vis배열을 일반적인 문제처럼 이차원 배열로 선언했다고 하자.
만약에 벽을 이미 한번 부순 경로가 다음 차례에 값이 0인 A 부분을 선택한다고 해보자.
벽을 부수지 않고 A 부분을 선택하려하는 경로가 있는데 이미 A 부분은 위에서 선점되어 선택이 불가하다.
만약 벽을 부수지 않은 경로가 바로 그 A블록을 선택해야만 올바른 답이 도출되는 경우라면 답은 계속 틀릴 것이다.
따라서 이 문제는 3차원 Vis배열을 사용해야 한다.
Vis는 이렇게 나타내어 질 것이다. Vis[벽을 이미 부쉈다면 1 아니면 0][row][col]
이러면 일단 벽을 부순 녀석들은 첫 인덱스가 1로 변환되어 벽을 이미 부순 녀석들의 방문 세계에서 계산된다.
이렇게 하면 벽을 부순 녀석들이 아직 벽을 부수지 않은 녀석들의 경로를 방해하지 않으면서 경로가 계산된다.
이렇게 BFS 문제 응용에 Vis배열을 3차원으로 설정하는 방식이 있다는 것을 기억하자!
그리고 이 문제의 Queue는 좌표 2개와 벽을 부쉈는지 여부, Step 수가 묶인 자료구조가 저장되게 된다.
이 문제를 통해 새로운 BFS 응용 문제에 대한 접근법을 배워간다.
*/

bool Vis[2][1001][1001];
queue<tuple<short, short, bool, int>> Q;
short Map[1001][1001], Dir[4][2] = { {1,0},{0,1},{-1,0},{0,-1} }, Hei, Wid;
string Input;

int BFS()
{
	Vis[0][0][0] = Vis[1][0][0] = 1;
	Q.push({ 0,0,0,1 });
	int R, C;
	while (!Q.empty())
	{
		for (int i = 0; i < 4; i++)
		{
			R = get<0>(Q.front()) + Dir[i][0]; C = get<1>(Q.front()) + Dir[i][1];
			if (0 <= R && R < Hei && 0 <= C && C < Wid)
			{
				if (get<2>(Q.front()) && !Map[R][C] && !Vis[1][R][C])
				{
					Q.push({ R,C,1,get<3>(Q.front()) + 1 }); Vis[1][R][C] = 1;
				}
				else if (!get<2>(Q.front()) && !Vis[0][R][C])
				{
					Vis[0][R][C] = 1;
					if (Map[R][C]) Q.push({ R,C,1,get<3>(Q.front()) + 1 });
					else Q.push({ R,C,0,get<3>(Q.front()) + 1 });
				}
			}
			if (R == Hei - 1 && C == Wid - 1) return get<3>(Q.front()) + 1;
		}
		Q.pop();
	}
	return -1;
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> Hei >> Wid;
	for (int i = 0; i < Hei; i++)
	{
		cin >> Input;
		for (int j = 0; j < Wid; j++)
		{
			Map[i][j] = Input[j] - '0';
		}
	}
	if (Hei == 1 && Wid == 1) cout << 1;
	else cout << BFS();
}