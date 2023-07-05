#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1068
트리 문제
트리 구조를 알맞게 잘 형성하면 순조롭게 진행이 가능하다.
주의할 점은 이진트리가 아닌 그냥 트리이고 0 노드 이외의 노드가
루트 노드가 될 수 있다는 것이다. 이들을 고려하여 코드를 작성하면 된다.
*/

unordered_map<int, vector<int>*> Tree;
int Cnt, finded, root;

void leaf(int node) {
	if (Tree.find(node) == Tree.end() || Tree[node]->empty()) {
		Cnt++; return;
	}
	for (int i = 0; i < Tree[node]->size(); i++) {
		leaf(Tree[node]->at(i));
	}
}

void Del(int Target, int node) {
	if (Tree.find(node) == Tree.end())
		return;
	if (Target == root) {
		cout << 0; exit(0);
	}
	for (int i = 0; i < Tree[node]->size() && !finded; i++)
	{
		if (Target == Tree[node]->at(i)) {
			Tree[node]->erase(Tree[node]->begin() + i);
			finded = 1;
		}
		else
			Del(Target, Tree[node]->at(i));
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int N, del; cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> del;
		vector<int>* A;
		if (del == -1) {
			if (Tree.find(i) == Tree.end()) {
				A = new vector<int>;
				Tree[i] = A;
			}
			root = i;
		}
		else if (Tree.find(del) == Tree.end()) {
			A = new vector<int>;
			Tree[del] = A; Tree[del]->push_back(i);
		}
		else {
			Tree[del]->push_back(i);
		}
	}
	cin >> del; Del(del, root);
	leaf(root); cout << Cnt;
}