#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1043
시간복잡도가 너무 널널하여 3중포문으로 완전탐색했다.
이중포문으로 풀기가 힘든 것이 파티가 동시에 열리고 있는 상태라
최후반 파티에 1, 2 가 속해있다고 하고 2가 진실을 안다고 할 경우
그 바로 전 파티에 2, 3 이 속해있으면 3도 진실을 알게되는 것이다.
그 전의 파티까지 계속 영향이 갈 것을 생각해보면 3중 포문이 돌아야 한다는 것을
알 수 있다.
제일 바깥의 루프는 인원수 N번을 돌렸는데 생각을 해보면 최악이 N 이하일 수 밖에 없다.
파티 M개의 2명씩 배정된다면 최대 N번을 돌면 1명만이 진실을 알고 있어도 그 진실이 다른 파티로
퍼지기에 충분하다.
따라서 N번 파티 전체를 순회한다, M번째 파티를 순회한다, 파티 안의 있는 인원을 조사한다.
이러한 3중 루프가 돌면서 진실을 아는 사람을 확장해나간다.
다른 사람의 풀이를 보니 유니온 파인드로 접근했다.
1번 파티: 1 -- 2
2번 파티: 3 -- 5
3번 파티: 2 -- 3 -- 4 에서 입력 받을 때
유니온 파인드를 진행하면 
1 <-- 2 가 처음에 만들어지고
3 <-- 5 가 다음에 만들어지고
1 <-- 2 였던 2가 맨 앞에 있어서 1 <-- 2 <-- 3 <-- 4 가 만들어 지는데 사실상
5의 부모는 3이였고 3의 부모는 1이 되어버려 전체가 진실을 알고 있는 것으로 볼 수 있다.
따라서 진실을 알고 있는 사람과 부모가 같은 파티원 중 다른 사람이 존재한다면 그 파티에서는
거짓말을 할 수가 없는 것이다.
이렇게 집합(파티)로 묶어지고 서로 영향을 끼칠 수 있다면 유니온파인드를 고려해보자.
이 문제를 통해 유니온 파인드에 대한 응용력을 길러간다.
*/

int N, M, nums, a, Ans;
bool Truth[51];
vector<int> Vert[51];

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M >> nums;
	for (int i = 0; i < nums; i++) {
		cin >> a; Truth[a] = 1;
	}
	for (int i = 0; i < M; i++) {
		cin >> nums;
		for (int j = 0; j < nums; j++) {
			cin >> a; Vert[i].push_back(a);
		}
	}
	for (int k = 0; k < N; k++) {
		for (int i = 0; i < M; i++) {
			bool flag = 0;
			for (int j = 0; j < Vert[i].size(); j++) {
				if (Truth[Vert[i][j]]) {
					flag = 1; break;
				}
			}
			for (int j = 0; j < Vert[i].size() && flag; j++) {
				Truth[Vert[i][j]] = 1;
			}
		}
	}
	for (int i = 0; i < M; i++) {
		bool flag = 0;
		for (int j = 0; j < Vert[i].size(); j++) {
			if (Truth[Vert[i][j]]) {
				flag = 1; break;
			}
		}
		if (!flag)
			Ans++;
	}
	cout << Ans;
}