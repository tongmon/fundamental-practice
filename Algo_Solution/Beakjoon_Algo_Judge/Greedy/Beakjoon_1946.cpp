#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1946
사원을 적절히 골라 뽑는 그리디 문제이다.
일단 순위 종류가 2개이기 때문에 고려할 사항을
하나라도 줄이기 위해 둘 중 한 값을 기준으로 정렬한다.
그러면 면접 순위가 높은 사람부터 낮은 사람으로 정렬이 될 것인데
일단 정렬된 값을 순서대로 읽는 다면 면접순위는 볼 필요도 없다.
이미 앞의 녀석은 뒤의 녀석보다 면접 순위가 높거나 같으니까.
따라서 서류 성적만 고려하면 된다.
서류 성적이 앞 녀석의 순위보다 높거나 같다면 탈락은 면한다.
서류 성적의 기준은 현재 녀석의 것이 된다. 왜냐면 앞의 녀석보다
높거나 같기 때문에
만약에 서류 성적이 앞 녀석보다 낮다면 탈락이다.
서류와 면접 성적 모두 낮다는 것이기에
이러한 원리로 값들을 순서대로 읽으면 뽑을 수 있는 최대 사람 수가 나온다.
이 문제를 통해 그리디 문제에 익숙해져간다.
*/

int T, N, A, G;
vector<pair<int, int>> Con;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> T;
	while (T > 0) {
		cin >> N;
		for (int i = 0; i < N; i++) {
			cin >> A >> G;
			Con.push_back({ A,G });
		}
		sort(Con.begin(), Con.end());
		pair<int, int> Top = Con[0];
		int Cnt = 1;
		for (int i = 1; i < N; i++) {
			if (Con[i].second <= Top.second) {
				Top = Con[i]; Cnt++;
			}
		}
		cout << Cnt << '\n';
		Con.clear();
		T--;
	}
}