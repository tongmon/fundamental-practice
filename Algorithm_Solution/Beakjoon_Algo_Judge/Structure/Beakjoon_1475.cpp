#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1475
배열 이 담는 값 외에도 배열의 인덱스 자체를 활용할 수가 있는데
이 활용 능력을 보는 문제...
배열에 대한 이해가 잘 되어있다면 원활히 풀린다.
*/

string num;
int Ary[10], Max, Index;

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> num;
	for (auto i : num) Ary[i - '0']++;
	for (int i = 0; i < 10; i++)
	{
		if (i != 6 && i != 9)
		{
			Max = max(Max, Ary[i]); Index = i;
		}
	}
	int A = Ary[6] + Ary[9];
	cout << max(Max, abs(A / 2 + A % 2));
}