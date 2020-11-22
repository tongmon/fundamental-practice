#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

#pragma warning(disable:4996)

/*
https://www.acmicpc.net/problem/10814
나이순 정렬 문제이다.
평소에 STL을 잘 이용했다면 쉬운 문제다.
이 문제에서 느낀 것은 string을 사용하면 오히려 껄끄러워지는 문제들이 있다는 것이다.
맘편히 char배열로 가는 것도 나쁘지 않다.
*/

typedef struct _ident
{
	int age, id;
	char name[200];
}Apply;

bool operator<(Apply a, Apply b)
{
	if (a.age == b.age)
	{
		return a.id < b.id;
	}
	return a.age < b.age;
}

bool operator>(Apply a, Apply b)
{
	if (a.age == b.age)
	{
		return a.id > b.id;
	}
	return a.age > b.age;
}

int main()
{
	int N;
	Apply buffer;
	priority_queue<Apply, vector<Apply>, greater<Apply>> Heap;
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		buffer.id = i;
		scanf("%d ", &buffer.age); scanf("%s", buffer.name);
		Heap.push(buffer);
	}
	for (int i = 0; i < N; i++)
	{
		printf("%d %s\n", Heap.top().age, Heap.top().name);
		Heap.pop();
	}
}