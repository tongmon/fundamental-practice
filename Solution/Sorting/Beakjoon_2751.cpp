#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
https://www.acmicpc.net/problem/2751
간단한 정렬문제인줄 알았지만....
사실 간단한 정렬문제는 맞다.
이 문제를 통해 얻은 교훈은 컴퓨터 계산 시간이 오래 걸릴 것 같은 문제들은
입출력을 할 때 cin, cout 대신에 printf, scanf 등을 사용해야 된다는 것이다.
훨씬 빠르다. 훠어어어얼씨이이인
*/

int main()
{
	int N, buffer;
	priority_queue<int, vector<int>, greater<int>> Heap;
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		scanf_s("%d", &buffer); Heap.push(buffer);
	}
	for (int i = 0; i < N; i++)
	{
		printf("%d\n", Heap.top());
		Heap.pop();
	}
}