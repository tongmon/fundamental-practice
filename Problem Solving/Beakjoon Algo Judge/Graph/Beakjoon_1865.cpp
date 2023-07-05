#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1865
음의 가중치 = 벨만 포드 라는 것을 알게 해준 문제...
다익스트라로 아무리 해보려 했는데 반례가 너무 많아 접근이 힘들었다.
벨만 포드 알고리즘은 처음 접해보는 것이라 매우 많이 제출하고 또 틀리고... 계속 반복했다.
벨만 포드 알고리즘은 기존 플로이드, 다익스트라와 다르게 간선을 기준으로 계산이 진행된다.
다익스트라는 그리디적이게 항상 최소인 정점에 대해서 연결된 녀석들만 갱신해 나가서
정점별로 값을 저장해놓는 것이 맞다.
하지만 벨만 포드는 음수인 간선, 즉 음수 싸이클을 찾아내는 것이 목적으로 모든 간선을 돌면서 
N-1번 Dist 거리 배열을 갱신하고 N번째에 다시 한번 더 갱신해봐서 만약에 또 갱신이 되었다면
그건 음수 싸이클이 존재해서 무한으로 작아질 수 있는 경로를 생성할 수가 있는 뜻이 된다.
갱신하면서 계속해서 작은 값만을 찾아 가는 것이니 N번을 돌고나면
올바른 최단 경로가 나오거나 아니면 음수 싸이클이 있어서 정확한 최단 경로를 판단하지 못하거나
둘 중 하나의 결과가 도출된다.
이 벨만 포드를 이용하여 이 문제를 정-직하게 풀면 밑과 같은 코드가 되고 이는 148ms가 걸린다.
이를 더 빠르게 풀 수가 있다.
이 문제는 출발점이 지정되지 않아서 음수 싸이클만 존재하면 된다.
벨만 포드가 거리를 갱신해 나가는 원리를 생각해보면 INF라는 것은 두 정점이 단절되어 있다는 의미를 뜻하는데
어짜피 초반 Dist 배열을 어떤 것으로 초기화를 하던 갱신해 나가면서 최솟값으로 고정되거나
음수 싸이클이 존재하면 계속해서 내려갈 것이다.
따라서 밑 코드에서 Dist[From] != INF 를 빼고 단 한번의 벨만 포드를 돌리면
음수 싸이클 유무가 도출된다.
이렇게 풀면 24ms가 나온다.
이 문제를 통해 벨만 포드 알고리즘을 알고 써먹을 수 있는 능력을 약간이나마 길러간다.
*/

int T, N, M, W, a, b, c, INF = 9000000;
vector<tuple<int, int, int>> Edge;

bool Bellman(int St) {
    vector<int> Dist(N + 1, INF);
    Dist[St] = 0;
    bool Changed = 1;
    for (int i = 1; i <= N && Changed; i++) {
        Changed = 0;
        for (auto e : Edge) {
            int From = get<0>(e), To = get<1>(e), Wei = get<2>(e);
            if (Dist[From] != INF && Dist[To] > Dist[From] + Wei) {
                Dist[To] = Dist[From] + Wei;
                Changed = 1;
            }
        }
        if (Changed && i == N)
            return 1;
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
	for (int q = 0; q < T; q++)
	{
        Edge.clear();
        cin >> N >> M >> W;
        for (int i = 0; i < M; i++) {
            cin >> a >> b >> c;
            Edge.push_back({ a,b,c });
            Edge.push_back({ b,a,c });
        }
        for (int i = 0; i < W; i++) {
            cin >> a >> b >> c;
            Edge.push_back({ a,b,-c });
        }
        bool ans = 0;
        for (int i = 1; i <= N && !ans; i++)
            ans = Bellman(i);
        cout << (ans ? "YES\n" : "NO\n");
	}
}