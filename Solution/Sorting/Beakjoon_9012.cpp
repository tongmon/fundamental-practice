#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <algorithm>
using namespace std;

#pragma warning(disable:4996)

/*
https://www.acmicpc.net/problem/9012
스택을 이용한 괄호 문제이다.
학교 수업에서도 귀에 박히도록 들었지만 한번 더 설명해보면
( 이면 push하고 ) 이면 pop해야 한다. 스택이 비었는데 pop하려 하거나 괄호들을 모두 검사했는데 찌꺼기 괄호가 남으면 NO다.
*/

int main()
{
	int N, index = 0;
	cin >> N;
	vector<string> Result;
	stack<char> Storage;
	char buffer[51];
	for (int i = 0; i < N; i++)
	{
		scanf("%s", buffer);
		index = 0; bool is_not_right = false;
		while (buffer[index] != '\0')
		{
			if (buffer[index] == '(')
			{
				Storage.push('(');
			}
			else if (buffer[index] == ')')
			{
				if (Storage.empty() == true)
				{
					Result.push_back("NO"); is_not_right = true;
					break;
				}
				else
				{
					Storage.pop();
				}
			}
			index++;
		}
		if (Storage.empty() == false)
		{
			Result.push_back("NO"); is_not_right = true;
		}
		if (is_not_right == false)
		{
			Result.push_back("YES");
		}
		while (Storage.empty() == false)
		{
			Storage.pop();
		}
	}
	for (int i = 0; i < Result.size(); i++)
	{
		printf("%s\n", Result[i].c_str());
	}
}