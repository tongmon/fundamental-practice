#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1655
가운데 수에 초점을 계속 유지하는 문제.
가운데 수에 초점을 유지하는데에는 multiset이 정말 유용하다.
multiset에 대한 개념을 알필요가 있는데 4 -> 5 -> 4 -> 4 이러한 순으로 들어온다고 하면
multiset은 선형적으로 보면 이와 같이 정렬된다.
4
4 5
4(old) 4(new) 5
4(첫째) 4(둘째) 4(셋째) 5
이렇게 값이 같은 수라면 새로 들어온 녀석들은 오른쪽에 쌓이게 된다.
이러한 성질과 정렬된 상태를 계속 유지하는 set의 특성을 이용하면 iterator를 적절히 이동하여
중간값을 아주 적은 시간 안에 계속 찾을 수가 있다.
내 방식 말고 최대 힙, 최소 힙을 동시에 사용하는 방식도 있다.

1. 최대 힙의 크기는 최소 힙의 크기와 같거나, 하나 더 크다.
2. 최대 힙의 최대 원소는 최소 힙의 최소 원소보다 작거나 같다.

이러한 규칙을 지키면서 계속 원소를 넣어가면 항상 최대힙의 top은 중간값을 가리킨다.
굉장히 신기하다.... 
이 방식에 대한 설명은 이분이 잘해놓으셨다. https://www.crocus.co.kr/625
이 문제를 통해 가운데 값을 빠르게 찾는 로직에 대해 알아간다.
*/

multiset<int> St;
int N, Num;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> Num;
	St.insert(Num);
	auto iter = St.begin();
	cout << *iter << '\n';
	for (int i = 0; i < N - 1; i++)
	{
		cin >> Num;
		St.insert(Num);
		if (i % 2 == 0) {
			if (Num < *iter) {
				iter--;
			}
		}
		else {
			if (Num >= *iter) {
				iter++;
			}
		}
		cout << *iter << '\n';
	}
}