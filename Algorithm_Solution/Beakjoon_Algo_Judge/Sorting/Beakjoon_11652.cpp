#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

#pragma warning(disable:4996)

/*
https://www.acmicpc.net/problem/11652
카드 문제이다.
값을 받고 정렬하여 11111...2222....3.... 뭐 이렇게 되어있을 테니 경계값을 따져주어 숫자가 바뀔 때에 count 값 초기화 해주고
또 비교를 반복하는 방식으로 해도 되지만 STL map을 사용하는 방법도 있다.
카드 값이 2의 62승이 최대 값이다 이 많은 수를 인덱스로 가지는 배열을 만들 수는 없으니 map이 적당하다 싶어서 사용했다.
이 문제를 통해 경계값을 비교하는 방식, map 컨테이너를 이용하는 방식을 알아간다.
*/

int main()
{
	long long buffer, SmallestID = 0;
	int N, Cbuffer, BiggestCount = 1;
	map<long long, int> Comp;

	cin >> N;
	scanf("%lld", &buffer);
	Comp[buffer] = 1; SmallestID = buffer;
	for (int i = 1; i < N; i++)
	{
		scanf("%lld", &buffer);
		if (Comp.find(buffer) == Comp.end())
		{
			Comp[buffer] = 1; Cbuffer = 1;
		}
		else
		{
			Cbuffer = ++Comp[buffer];
		}
		if (BiggestCount < Cbuffer)
		{
			SmallestID = buffer;
			BiggestCount = Cbuffer;
		}
		else if (BiggestCount == Cbuffer && SmallestID > buffer)
		{
			SmallestID = buffer;
		}
	}
	cout << SmallestID;
}