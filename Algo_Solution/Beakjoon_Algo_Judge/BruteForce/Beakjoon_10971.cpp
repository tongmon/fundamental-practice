#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/10971
외판원 순회 문제이다. 
완전 탐색 문제로 접근하여 DFS 비스무리하게 푸는 문제이다.
이 문제는 시간초과가 안나기 위해서 중간에 완전탐색을 끊어주는 조건들이 필요하다.
일단 최솟값을 찾는 문제기에 경로를 진행하다가 기존의 최솟값을 이미 넘어버린 경우의 경로는 그대로 그만둔다.
그리고 끝날때도 안되었는데 도착지에 미리 가버린 경우의 경로도 그만둔다.
위의 조건들을 지키면서 완전탐색을 진행하면 풀리는 문제이다.
이 문제를 풀면서 내가 실수 한게 있는데 visited를 나타내는 배열을 그대로 함수 매개변수로 때려넣은 것이다.
이것 때문에 매우 시간이 느려졌다. 배열을 다른 함수 호출 시마다 복사해서 넣기 때문에 매우 비효율적이다.
이러한 비효율 방식 대신에 기존의 배열을 원상태로 되돌려 놓는 쌍부랄 방식을 사용하니 시간이 1000ms나 단축되었다.
쌍부랄 방식은 
Visited[i] = true;
Travel(Count + 1, i, Sum + Ary[Cur][i], Starter);
Visited[i] = false;
이렇게 순열 알고리즘 처럼 바꾸어서 함수 호출하고 호출이 끝나면 다시 원상태로 되돌려 놓는 것을 말한다. 물론 내가 이름을 지었다;;
이러한 테크닉을 알고 잘 써먹기 바란다.
*/

#pragma warning(disable:4996)

int Size, MIN = 20000000;
int Ary[11][11];
bool Visited[11];

void Travel(int Count, int Cur, int Sum, int Starter)
{
	if ((0 < Count && Count < Size && Cur == Starter) || Sum >= MIN)
	{
		return;
	}
	if (Count == Size && Starter == Cur)
	{
		if (Sum < MIN)
		{
			MIN = Sum;
		}
		return;
	}
	for (int i = 0; i < Size; i++)
	{
		if (Ary[Cur][i] != 0 && Visited[i] == false)
		{
			Visited[i] = true;
			Travel(Count + 1, i, Sum + Ary[Cur][i], Starter);
			Visited[i] = false;
		}
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> Size;
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			cin >> Ary[i][j];
		}
	}
	for (int i = 0; i < Size; i++)
	{
		Travel(0, i, 0, i);
	}
	cout << MIN;
}