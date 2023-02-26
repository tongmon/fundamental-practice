#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
https://www.acmicpc.net/problem/11650
좌표 정렬 문제이다.
평소에 STL을 써왔다면 문제 없이 풀 수가 있을 것이다.
이 문제가 헷갈린다면 연산자 재정의에 대한 정보를 다시 익히자
*/

typedef struct _Cord
{
	int x, y;
}Point;

bool operator<(Point a, Point b)
{
	if (a.x == b.x)
	{
		return a.y < b.y;
	}
	return a.x < b.x;
}

bool operator>(Point a, Point b)
{
	if (a.x == b.x)
	{
		return a.y > b.y;
	}
	return a.x > b.x;
}

int main()
{
	int N;
	Point buffer;
	priority_queue<Point, vector<Point>, greater<Point>> Heap;
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		scanf_s("%d %d", &buffer.x, &buffer.y); Heap.push(buffer);
	}
	for (int i = 0; i < N; i++)
	{
		printf("%d %d\n", Heap.top().x, Heap.top().y);
		Heap.pop();
	}
}