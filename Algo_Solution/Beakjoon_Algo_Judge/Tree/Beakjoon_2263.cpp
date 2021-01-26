#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2263
트리 문제여서 역시 재귀 활용도를 물어보는 문제였다.
푸는데 2시간 정도 걸렸다... 실제 코딩 테스트에서 나왔으면
나한테는 킬러 문제였을 것 같다.
일단 초반에 문제를 잘 안읽고 이진 '탐색' 트리 인줄 알아가지고
이진 탐색 트리에서 후위 표기가 들어오면 전위로 바꾸는 것을 생각했다.
예시를 많이 짜봐서 규칙을 알아냈는데 후위 표기식의 맨 뒤의 녀석은 트리의 루트가 명백하다.
최후반에 탐색되니 당연한 사실이다.
그러면 트리 루트 바로 밑의 자식들을 알아내는 것이 관건인데 일단 루트보다 작은 녀석을 찾는다.
작은 녀석이 나오면 그 작은 녀석을 포함한 왼쪽 부분이 해당 트리의 왼쪽 가지 영역이고 그 반대가
트리의 오른쪽 가지 영역이 되는 것이다.
작은 녀석이 나오지 않고 큰 녀석들만 나왔다면 한쪽으로 치우쳐서 생성된 상태의 트리이기에
크기가 작은 것부터 큰 것까지 순서로 전위 저장 배열에 넣어준다. 
그리고 일단 찾은 트리의 루트는 전위 순회에서 가장 먼저 나오게 되므로 전위 저장 배열에 넣어준다.
이를 서브 트리에서도 재귀적으로 왼쪽 --> 오른쪽 순으로 계속 돌리면서 전위 저장 배열에 채워나가면 된다.
이게 이진 탐색 트리에서 적용되는 법칙이고 그냥 이진트리에서도 생각해보면 별 다를 것이 없다.
일단 트리의 중위 순회는 원소들이 정렬되어서 나오게 된다.
이를 이용하여 정렬 순서를 알아내고 비교할 때 똑같이 써먹으면 된다.
이러한 방식으로 문제를 풀었다.
이렇게 표기 순서를 바꾸는 문제는 전위라면 맨 앞이 루트고 후위라면 맨 뒤가 루트가 되는데 이를 기준으로
응용하여 재귀로 푸는 문제가 대부분인 것 같다.
이 문제를 통해 트리를 전위 --> 후위, 후위 --> 전위로 변환하는 문제에 대해 익숙해져 간다.
*/

int N, a, Order[100001];
vector<int> Post, Pre;

void PotoPre(int St, int End) {
	int Small = -1;
	for (int i = End - 1; i >= St && Small < 0; i--) {
		if (Order[Post[End]] > Order[Post[i]])
			Small = i;
	}
	if (Small >= 0) {
		Pre.push_back(Post[End]);
		PotoPre(St, Small);
		PotoPre(Small + 1, End - 1);
		return;
	}
	for (int i = End; i >= St; i--)
		Pre.push_back(Post[i]);
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	Pre.reserve(N); Post.reserve(N);
	for (int i = 0; i < N; i++) {
		cin >> a; Order[a] = i;
	}
	for (int i = 0; i < N; i++) {
		cin >> a; Post.push_back(a);
	}
	PotoPre(0, N - 1);
	for (auto A : Pre)
		cout << A << ' ';
}