#include <bits/stdc++.h>
using namespace std;

/*
CodeGround 다이어트 문제.
정렬을 하고 일단 작은 것들을 추려낸 뒤에 큰거 + 작은거 이렇게 더하면 된다.
이 문제를 통해 구현 속도를 늘려간다.
*/

int Answer;

int main()
{
	// ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int T, test_case;
	
	/*
	   키보드가 아니라 freopen("input.txt", "r", stdin); 을 통해 입력을 받음
	   테스트를 해보려면 freopen("input.txt", "r", stdin);의 '//' 주석을 지우거나
	   스탠다드 인풋으로 받기 위한 입력부를 달아줘야 함.
	   실제 제출시에는 이러한 변형을 모두 주석처리 할 것.
	*/

	 // freopen("input.txt", "r", stdin);

	cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{

		Answer = 0;

		// 알고리즘 작성 시작
		int N, K;
		vector<int> A, B;
		cin >> N >> K;
		A.resize(N); B.resize(N);
		for (int i = 0; i < N; i++)
			cin >> A[i];
		for (int i = 0; i < N; i++)
			cin >> B[i];
		sort(A.begin(), A.end());
		sort(B.begin(), B.end());
		for (int i = 0; i < K; i++) {
			Answer = max(Answer, A[i] + B[K - i - 1]);
		}
		// 알고리즘 작성 끝

		cout << "Case #" << test_case + 1 << endl;
		cout << Answer << endl;
	}

	return 0;
}