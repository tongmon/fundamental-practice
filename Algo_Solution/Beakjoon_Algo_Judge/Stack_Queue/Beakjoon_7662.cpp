#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/7662
이중 우선순위 큐 문제이다.
오름 힙, 내림 힙 두 가지를 사용하여 풀게 된다.
힙은 맨 위에 가장 큰 수나 작은 수가 위치하게 자동으로 배열되기에 시간 단축에 있어서 굉장히
유용하다.
이게 힙 두개를 이용하지만 삭제하는 경우 한쪽 힙에서만 지워지기에 다른 쪽 힙에서 이게 지워졌는지 아닌지
알 방도가 필요하다.
그래서 Vis 배열로 이를 체크 해주었다.
나는 만약 실제 832 이런 수가 들어오면 Vis[832] = 832 개수 이런 식으로 방문 배열을 설계했는데
다른 사람 풀이를 보니 실제 들어오는 인덱스 즉 첫번째 들어오는 수가 832면 이를 체크한다면 Vis[0] = true로 저장했더라
이렇게 하기 위해서 결국 큐에도 인덱스와 숫자를 pair로 묶어 집어넣게 된다.
코드 내용은 방문 배열 의미만 바뀔뿐 전혀 바뀌는 것은 없다.
코드가 짧은 풀이도 있는데 multiset을 이용하는 것이다. set이기에 그냥 삽입할 때마다 정렬이 되고 첫번째 iter와 마지막 iter의 하나 전이
크고 작은 수를 항상 가리키고 있기에 편하다.
하지만 힙이 아니고 레드블랙트리라 시간은 꽤 오래걸린다.
*/

#define LL long long

LL T, N, Num;
char Order;
unordered_map<LL, int> Vis;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	Vis.reserve(2000000);
	cin >> T;
	for (LL i = 0; i < T; i++)
	{
		cin >> N;
		priority_queue<LL, vector<LL>, greater<LL>> Small;
		priority_queue<LL> Big;
		for (LL j = 0; j < N; j++)
		{
			cin >> Order >> Num;
			if (Order == 'I') {
				Small.push(Num); Big.push(Num);
				if (Vis.find(Num) == Vis.end())
					Vis[Num] = 1;
				else
					Vis[Num]++;
			}
			else if (Num == -1) {
				if (!Small.empty()) {
					if (Vis[Small.top()] > 0) {
						Vis[Small.top()]--;
						Small.pop();
					}
				}
			}
			else {
				if (!Big.empty()) {
					if (Vis[Big.top()] > 0) {
						Vis[Big.top()]--;
						Big.pop();
					}
				}
			}
			while (!Small.empty() && !Vis[Small.top()]) {
				Small.pop();
			}
			while (!Big.empty() && !Vis[Big.top()]) {
				Big.pop();
			}
		}
		bool Big_ok = 0, Small_ok = 0;
		if (!Big.empty() && Vis[Big.top()])
			Big_ok = 1;
		if (!Small.empty() && Vis[Small.top()])
			Small_ok = 1;
		if (Small_ok && Big_ok)
			cout << Big.top() << ' ' << Small.top() << '\n';
		if (Small_ok && !Big_ok)
			cout << Small.top() << ' ' << Small.top() << '\n';
		if (!Small_ok && Big_ok)
			cout << Big.top() << ' ' << Big.top() << '\n';
		if (!Small_ok && !Big_ok)
			cout << "EMPTY\n";
		Vis.clear();
	}
}