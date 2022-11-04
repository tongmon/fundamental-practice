#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

#pragma warning(disable:4996)

/*
https://www.acmicpc.net/problem/11655
ROT13 암호화 문제이다. 
알파벳의 자리를 13자리씩 밀어내 암호코드를 만드는 방식인데 13을 더했을 경우 26자의 알파벳을 벗어나는 경우를
방지하기 위해 % 26 이라는 연산을 취해준다.
이 문제를 통해 % N 연산을 적재적소에 사용하는 법을 익힌다. 
*/


int main()
{
	string buffer;
	string Result;
	getline(cin, buffer);
	for (int i = 0; i < buffer.size(); i++)
	{
		if ('A' <= buffer.at(i) && buffer.at(i) <= 'Z')
		{
			int Cur = (buffer.at(i) - 'A' + 13) % 26;
			Result.push_back('A' + Cur);
		}
		else if ('a' <= buffer.at(i) && buffer.at(i) <= 'z')
		{
			int Cur = (buffer.at(i) - 'a' + 13) % 26;
			Result.push_back('a' + Cur);
		}
		else
		{
			Result.push_back(buffer.at(i));
		}
	}
	cout << Result;
}