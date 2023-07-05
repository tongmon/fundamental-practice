#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/4889
스택을 이용한 괄호 처리 문제다.
이전 문제들보다 약간 껄끄러웠던 것은 보통 문제처럼 스택에 담으면서 바로바로 괄호가 올바른지 처리하면 안되고
일단 괄호가 { } 이런 꼴을 1차로 거르고 나머지 경우는 스택에 그냥 박아준다.
그 다음에 스택을 비우면서 연산의 개수가 뭔지 판단한다.
이렇게 두번에 나누어서 검사를 진행하는 것이 내 방식이다.
더 효과적인 풀이도 존재했는데 일단 } 얘는 스택이 비어있는 경우면 { 로 바꾸고 연산을 추가한다.
나머지 케이스는 일반적인 스택 괄호 처리로 진행된다. 
이렇게 진행되면 스택에는 { 이것만 남게 되는데 얘네 중 절반을 } 이걸로 바꾸면 안정적인 괄호가 된다.
따라서 검사 2번 할 것도 없이 그냥 스택의 잔여량을 이용해 최종 답이 도출된다.
이 풀이도 밑에 달아 놓았으니 참고하면 된다.
이 문제를 통해 괄호 문제에 대한 생각을 키워간다.
*/

string Input;
int Onum, Index;
char Top;
stack<char> St;

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	while (true)
	{
		Onum = 0;
		getline(cin, Input);
		if (!Input.empty() && Input[0] == '-') break;
		for (int i = 0; i < Input.size(); i++)
		{
			if (St.empty() || Input[i] == '{') St.push(Input[i]);
			else
			{
				if (St.top() == '{') St.pop();
				else St.push('}');
			}
		}
		while (!St.empty())
		{
			Top = St.top(); St.pop();
			if (Top == '}' && St.top() == '}') Onum++;
			else if (Top == '{' && St.top() == '}') Onum = Onum + 2;
			else Onum++;
			St.pop();
		}
		cout << ++Index << ". " << Onum << '\n';
	}
}

/*
int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	while (true)
	{
		stack<char> St;
		Onum = 0;
		getline(cin, Input);
		if (!Input.empty() && Input[0] == '-') break;
		for (int i = 0; i < Input.size(); i++)
		{
			if (St.empty() && Input[i] == '}') {
				St.push('{'); Onum++;
			}
			else if (!St.empty() && St.top() == '{' && Input[i] == '}') St.pop();
			else St.push('{');
		}
		Onum = Onum + St.size() / 2;
		cout << ++Index << ". " << Onum << '\n';
	}
}
*/