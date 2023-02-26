#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <algorithm>
using namespace std;

#pragma warning(disable:4996)

/*
https://www.acmicpc.net/problem/10799
프로그래머스에도 있던 문제인 쇠막대기 문제이다.
레이져를 쏘는 () 구간은 잘린 쇠막대기 수 만큼 개수에 더해주고 그 외의 ( 는 쇠막대기 스택에 추가, ) 는 쇠막대기 끝이니
막대기 개수를 1개 더 하는 방법으로 풀린다.
스택을 약간 응용하는 방법을 이 문제를 통해 습득할 수 있다.
*/

int main()
{
	int N = 0;
	string buffer;
	stack<char> Storage;
	cin >> buffer;

	for (int i = 0; i < buffer.size(); i++)
	{
		if (buffer.at(i) == '(')
		{
			if (buffer.at(i+1) == ')') // 레이져 쏘기
			{
				N = N + Storage.size(); i++;
			}
			else
			{
				Storage.push('(');
			}
		}
		else
		{
			N = N + 1; Storage.pop();
		}
	}
	cout << N;
}