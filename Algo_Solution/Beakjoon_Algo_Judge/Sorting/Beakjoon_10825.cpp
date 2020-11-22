#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#include <algorithm>
using namespace std;

#pragma warning(disable:4996)

/*
https://www.acmicpc.net/problem/10825
이 문제도 마찬가지로 STL을 잘 활용하여 정렬하면 쉽다.
이 문제에서 유의할 점은 strcmp() 비교를 할 때에 strcmp(a.name, b.name) > 0 이렇게 안하고
strcmp(a.name, b.name) == 1 이나 strcmp(a.name, b.name) >= 0 를 하면 오답 처리 된다는 것이다.
앞으로 이를 유의해서 연산자 오버로딩을 구현하자
이유는 https://www.acmicpc.net/board/view/22947 를 참고해보도록
*/

typedef struct _score
{
	char name[200];
	int local,eng,math;
}Score;

bool operator<(Score a, Score b)
{
	if (a.local == b.local)
	{
		if (a.eng == b.eng && a.math == b.math)
		{
			if (strcmp(a.name, b.name) > 0)
			{
				return true;
			}
			return false;
		}
		if (a.local == b.local && a.eng == b.eng)
		{
			return a.math < b.math;
		}
		return a.eng > b.eng;
	}
	return a.local < b.local;
}

bool operator>(Score a, Score b)
{
	if (a.local == b.local)
	{
		if (a.eng == b.eng && a.math == b.math)
		{
			if (strcmp(a.name, b.name) > 0)
			{
				return true;
			}
			return false;
		}
		if (a.eng == b.eng)
		{
			return a.math > b.math;
		}
		return a.eng < b.eng;
	}
	return a.local > b.local;
}

int main()
{
	int N;
	Score buffer;
	priority_queue<Score, vector<Score>, less<Score>> Heap;
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		scanf("%s", buffer.name); scanf(" %d %d %d", &buffer.local, &buffer.eng, &buffer.math);
		Heap.push(buffer);
	}
	for (int i = 0; i < N; i++)
	{
		printf("%s\n", Heap.top().name);
		Heap.pop();
	}
}