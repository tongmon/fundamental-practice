#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

#pragma warning(disable:4996)

/*
https://www.acmicpc.net/problem/10989
그냥 정렬 문제 같아보이지만 용량 제한이 무쳤다...
따라서 약간 특이한 정렬방식을 시도해보았다.
이렇게 정렬에 걸리는 시간복잡도는 널널하지만 공간복잡도가 꽉 조여져있는 문제는 아래와 같은 
Count 배열을 선언하여 풀어야 한다. Count 배열의 인덱스는 해당 수를 의미하고 그 내용은 몇번 나왔는지를 알려준다.
예를 들어 Count[111] = 3 이라면 111번이라는 수가 중복되어 3번 나왔다는 것이다.
이 문제를 통해 시간복잡도만 따져볼 것이 아니라 공간복잡도도 따져보는 습관을 기를 수 있어야 한다.
참고로 scanf()를 통해 short형 값을 받을 때는 %hd를 사용하더라.... 이 문제를 통해 처음 알게 되었다.
*/

int Count[10001] = { 0, };

int main()
{
	unsigned int N;
	short buffer;
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		scanf("%hd", &buffer);
		Count[buffer]++;
	}
	for (int i = 0; i < 10001; i++)
	{
		for (int j = 0; j < Count[i]; j++)
		{
			printf("%d\n", i);
		}
	}
}