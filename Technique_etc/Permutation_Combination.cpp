#include <bits/stdc++.h>
using namespace std;

/*
next_permutation을 통한 순열과 조합
재귀를 통한 순열과 조합을 정리해봤다.
next_permutation은 기존의 DFS방식보다 빠르게 짤 수 있다는 장점이 있다.
근데 한 개의 수를 여러번 선택하거나 하는 그런 변형은 가하기 어렵기에
기존의 방식과 섞어서 사용할 줄 알아야 한다.
*/

int Nums = 4; // 순열 개수
int Selection = 3; // 조합 선택 개수

void Permut(vector<int>* Con, vector<int>* List) // 순열
{
	if (List->empty()) {
		for (auto K : *Con) {
			cout << K << ' ';
		}
		cout << '\n'; return;
	}
	//	int back = -1;
	for (int i = 0; i < List->size(); i++)
	{
		//	if (back == List->at(i))
		//	continue;
		Con->push_back(List->at(i)); 
		List->erase(List->begin() + i); // 만약 같은 수를 여러번 택하고 싶다면 지우지 않으면 된다.
		// 같은 수 여러 개가 배열에 포함되어 있다면 back이라는 변수를 선언해 전에 뽑은놈이 지금 뽑으려는 녀석과 같은지 확인한다.
		Permut(Con, List);
		List->insert(List->begin() + i, Con->back()); 
		Con->pop_back();
	}
}

void Combi(int Cur, int Dep, vector<int> *Con, vector<int>* List) // 조합
{
	if (Dep == Selection) {
		for (auto K : *Con) {
			cout << K << ' ';
		}
		cout << '\n'; return;
	}
	for (int i = Cur; i < List->size(); i++)
	{
		Con->push_back(List->at(i));
		List->erase(List->begin() + i);
		Combi(i, Dep + 1, Con, List);
		List->insert(List->begin() + i, Con->back()); 
		Con->pop_back();
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	vector<int> Permu;
	for (int i = 0; i < Nums; i++) {
		Permu.push_back(i + 1);
	}
	cout << Nums << "개의 수 순열\n";
	do {
		for (auto Num : Permu) {
			cout << Num << ' ';
		}
		cout << '\n';
	} while (next_permutation(Permu.begin(), Permu.end()));

	// 재귀를 이용한 순열
	//vector<int> Per;
	//Permut(&Per, &Permu);

	vector<int> sel(Nums, 0); // 조합은 선택배열이 따로 필요
	cout << Nums << "개 중 " << Selection << "개 고르는 조합\n";
	for (int i = 0; i < Selection; i++) // next_permutation은 정렬이 필수적이라 뒤에서 부터 선택할 녀석들을 1로 만든다.
	{
		sel[sel.size() - 1 - i] = 1;
	}
	do {
		for (int i = 0; i < Nums; i++) {
			if (sel[i])
				cout << Permu[i] << ' ';
		}
		cout << '\n';
	} while (next_permutation(sel.begin(), sel.end()));
	
	// 재귀를 이용한 조합
	//vector<int> Com;
	//Combi(0, 0, &Com, &Permu);
}