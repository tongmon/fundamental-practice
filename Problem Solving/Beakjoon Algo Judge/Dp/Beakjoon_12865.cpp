#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/12865
이 문제를 풀면서 알게 된 사실은 배열 복사 함수인
memcpy가 겁나게 빠르다는 사실이다.
찾아보니 크기 100000까지는 거의 0ms에 복사 때린다!
밑의 내 Dp 풀이도 memcpy를 안쓰고 루프 돌면 최악의 경우가 10억이라
10초가 걸려야 정상인데 문제 제한 시간이 2초인데 20ms로 통과된거 보면
memcpy 덕이 크다.
이 문제는 배낭 문제 유형으로 따로 이 유형 문제 모음집이 있을 정도로 유명하다.
일단 내 풀이부터 설명하자면 중복되는 물건을 넣으면 안되기에 Vis 배열로
체크를 진행한다.
Dp배열은 Dp[무게] = 가치로 진행된다.
가방에 물건을 넣어봤는데 기존의 Dp값보다 더 크면 Vis배열을 갱신하고 그 값들을
즉 Vis[현재 무게][1 ~ 100] 이 녀석들을 복사해서 Vis[물건 넣은 무게][1 ~ 100] 에
넣어준다.
이게 memcpy의 강력함 때문에 풀린 것이지 정석적인 풀이보다 속도가 딸린다.
정석적인 풀이는 이렇게 접근한다.
일단 가방에 넣을 물건들을 앞에 일렬로 깔아놓는다.
첫번째 물건부터 마지막 물건까지 고를지 안고를지 선택 여부를 따지고 이를 Dp에 저장한다.
점화식을 보면 
Dp[여기에 적힌 인덱스 까지의 물건을 배낭에 담을 수 있음][최대 가능 무게] = 최대 가치
위와 같이 구성되고 i,j에 대한 설명은 코드 주석으로 달아놓는다.
이 문제를 통해 배낭 문제 접근 방식을 알아간다.
*/

int N, M, W, V, Bdp[101][100001];
vector<pair<int, int>> Bag;

/*
int Dp[100001], Min = 100001, Ans;
bool Vis[100001][101];

int main() // 방문배열 복사를 통한 배낭 문제
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	while (N > 0) {
		cin >> W >> V;
		Min = min(Min, W);
		Bag.push_back({ W,V });
		N--;
	}
	Dp[M] = 1;
	for (int i = M; i >= Min; i--) {
		if (!Dp[i])
			continue;
		for (int j = 0; j < Bag.size(); j++) {
			if (i - Bag[j].first < 0)
				continue;
			int buf = Dp[i] + Bag[j].second;
			if (Dp[i - Bag[j].first] < buf && !Vis[i][j]) {
				Dp[i - Bag[j].first] = buf;
				Ans = max(Ans, buf);
				memcpy(Vis[i - Bag[j].first], Vis[i], sizeof(Vis[i]));
				Vis[i - Bag[j].first][j] = 1;
			}
		}
	}
	cout << max(Ans - 1, 0);
}
*/

int main() // 정석적인 배낭 Dp 문제 풀이
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	Bag.reserve(N + 1);
	for (int i = 0; i < N; i++) {
		cin >> W >> V;
		Bag[i+1] = { W,V };
	}
	for (int i = 1; i <= N; i++) // 물건 개수 중심으로 돌아감, i번째 물건까지 선택 가능할 때는 의미
	{
		for (int j = 1; j <= M; j++)  // j는 가방의 최대 지원 가능 무게를 의미
		{
			if (j >= Bag[i].first) 
				Bdp[i][j] = max(Bdp[i - 1][j], Bdp[i - 1][j - Bag[i].first] + Bag[i].second);
			else 
				Bdp[i][j] = Bdp[i - 1][j];
		}
	}
	cout << Bdp[N][M];
}