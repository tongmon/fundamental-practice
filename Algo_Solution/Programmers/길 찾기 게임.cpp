#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/42892
길 찾기 게임 문제.
트리에 관한 문제였다.
이진 탐색 트리를 생성하고 전위, 후위 돌리면 되는 문제다.
노드의 개수도 10000개가 최대라 1초안에 계산이 가능하다.
이진 탐색 트리 생성하는 경우에 노드 삽입 순서가 중요한데
이에 대한 순서는 y값이 높고 x값이 작을 수록 제일 앞으로 오게하면 된다.
그래야 올바른 트리가 형성이 된다.
이 문제를 통해 구현속도를 늘려간다.
*/

class tNode {
public:
	int A[3];
	tNode* L, * R;
	tNode(int x, int y, int ind) { A[0] = x, A[1] = y, A[2] = ind; R = L = NULL; }
};

tNode* Root;
vector<vector<int>> answer, Con;

void Push(int x, int y, int ind) {
	tNode* p = new tNode(x, y, ind), *back, *t;
	if (Root == NULL) {
		Root = p; return;
	}
	back = t = Root;
	while (t != NULL) {
		back = t;
		if (back->A[0] > p->A[0])
			t = back->L;
		else
			t = back->R;
	}
	if (back->A[0] > p->A[0])
		back->L = p;
	else
		back->R = p;
}

void Pre(tNode *t) {
	if (t == NULL) return;
	answer[0].push_back(t->A[2]);
	Pre(t->L);
	Pre(t->R);
}

void Post(tNode* t) {
	if (t == NULL) return;
	Post(t->L);
	Post(t->R);
	answer[1].push_back(t->A[2]);
}

bool Cmp(vector<int> &A, vector<int> &B) {
	if (A[1] == B[1])
		return A[0] < B[0];
	return A[1] > B[1];
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
	answer.resize(2);
	for (int i = 0; i < nodeinfo.size(); i++)
		Con.push_back({ nodeinfo[i][0], nodeinfo[i][1], i + 1 });
	sort(Con.begin(), Con.end(), Cmp);
	for (auto& A : Con)
		Push(A[0], A[1], A[2]);
	Post(Root); Pre(Root);
	return answer;
}