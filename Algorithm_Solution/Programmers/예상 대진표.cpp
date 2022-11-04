#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12985
예상 대진표 문제.
시간복잡도를 계산하니 그냥 배열로 뺑뺑이 돌려도 되는 각이 나와서 무식하게 풀었다.
두 배열을 번갈아가면서 배열의 절반씩 담는 방식으로 풀었다.
이는 매우 비효율적이고 효율적인 방식을 생각해보니
3,4 였던 것은 2로 강등, 5,6 였던 것은 3로 강등, 7,8 였던 것은 4으로 강등... 이런 규칙이 있으니
이를 그대로 구현 하면된다. 근데 1까지 강등되면 더이상 내려갈 곳이 없으니 계속 1을 유지해야 한다.
이 문제를 통해 구현속도를 늘려간다.
*/

int solution(int n, int a, int b)
{
	int answer = 0;
	while (a != b) {
		answer++;
		if (a > 1)
			a = a % 2 ? (a + 1) / 2 : a / 2;
		if (b > 1)
			b = b % 2 ? (b + 1) / 2 : b / 2;
	}
	return answer;
}

/*
int solution(int n, int a, int b)
{
	int answer = 0, Ind = 0;
	if (a > b)
		swap(a, b);
	vector<int> Con[2];
	for (int i = 0; i < n; i++)
		Con[Ind].push_back(i + 1);
	while (true) {
		answer++;
		Con[Ind ^ 1].clear();
		for (int i = 0; i < Con[Ind].size(); i += 2)
		{
			if (Con[Ind][i] == a && Con[Ind][i + 1] == b)
				return answer;
			else if (Con[Ind][i] == a || Con[Ind][i] == b)
				Con[Ind ^ 1].push_back(Con[Ind][i]);
			else if (Con[Ind][i + 1] == a || Con[Ind][i + 1] == b)
				Con[Ind ^ 1].push_back(Con[Ind][i + 1]);
			else
				Con[Ind ^ 1].push_back(Con[Ind][i]);
		}
		Ind ^= 1;
	}
	return answer;
}
*/