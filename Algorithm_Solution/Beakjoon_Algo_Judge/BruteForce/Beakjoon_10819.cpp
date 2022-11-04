#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/10819
이 문제는 일단 주어진 배열에 있는 정수들의 순서를 적절히 섞는 방법을 알면 쉬운 문제다.
적절히 섞어 모든 수를 계산하는 문제기에 완전탐색 문제다.
순열 알고리즘을 알고, next_permutation 이라는 STL 함수를 알았다면 겁나게 편하게 풀 수 있다.
당연히 나는 둘다 모르고 있는 상태에서 풀었으므로 16ms라는 개느린 속도가 나왔다.....
순열 알고리즘에 대한 자세한 설명은 https://minusi.tistory.com/entry/%EC%88%9C%EC%97%B4-%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98-Permutation-Algorithm
이 분이 굉장히 잘 설명해주셨다.
next_permutation 이 함수를 사용할 때 주의할 점은 오름차순 정렬이 된 상태여야 한다는 것이다. 
순열 알고리즘은 기술 면접에서 물어볼 수도 있으니 이해하고 넘어가자.
스왑 후에 permutation 후에 스왑이 진행되는데 이 때 처음 진행하는 스왑은 그 스왑된 자리를 고정시킨다는 의미로 이해하면 쉽다.
이 문제를 풀면서 순열 알고리즘과 next_permutation 이라는 개꿀 함수를 알아간다.
그리고 완전 탐색과 순열은 밀접한 관계가 있다는 것도 명심하자!
*/

#pragma warning(disable:4996)

list<short> Ary;
int MAX = -1;

void Chose(vector<short> Chosen, list<short> Poped, int choice)
{
	Chosen.push_back(choice);
	if (Chosen.size() == Ary.size())
	{
		int index = 0, Sum = 0;
		while (index < Chosen.size() - 1)
		{
			Sum = Sum + abs(Chosen[index] - Chosen[index + 1]);
			index++;
		}
		if (MAX < Sum)
		{
			MAX = Sum;
		}
		return;
	}
	for (auto iter = Poped.begin(); iter != Poped.end(); iter++)
	{
		if (*iter == choice)
		{
			Poped.erase(iter); break;
		}
	}
	for (auto iter = Poped.begin(); iter != Poped.end(); iter++)
	{
		Chose(Chosen, Poped, *iter);
	}	
}

int main()
{
	int N, input;
	vector<short> buffer;
	cin >> N;
	for (int i = 0;i < N;i++)
	{
		cin >> input;
		Ary.push_back(input);
	}
	for (auto iter = Ary.begin(); iter != Ary.end(); iter++)
	{
		Chose(buffer, Ary, *iter);
	}
	cout << MAX;
}

/*
int main() // next_permutation를 이용한 굉장히 깔쌈한 풀이
{
	int N, input, MAX = -1;
	vector<short> Ary;
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> input;
		Ary.push_back(input);
	}
	sort(Ary.begin(), Ary.end());
	do
	{
		int index = 0, Sum = 0;
		while (index < Ary.size() - 1)
		{
			Sum = Sum + abs(Ary[index] - Ary[index + 1]);
			index++;
		}
		if (MAX < Sum)
		{
			MAX = Sum;
		}
	} while (next_permutation(Ary.begin(), Ary.end()));
	cout << MAX;
}
*/

/*
int Permutation(vector<int>* ary, int Start, int End) // 순열 알고리즘
{
	if (Start == End)
	{
		// 결정된 순열이니 처리할 것을 여기서 처리
		return;
	}
	for (int i = Start; i <= End; i++)
	{
		swap(ary[Start], ary[i]); // 이 때 start 자리에 ary[i]가 위치하면서 고정
		Permutation(ary, Start + 1, End);
		swap(ary[Start], ary[i]); // 원 상태로 복귀
	}
}
*/