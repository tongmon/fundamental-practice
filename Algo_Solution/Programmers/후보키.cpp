#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/42890
후보키 문제
일단 키가 될 수 있는 녀석들을 고른 뒤에 최소성을 만족하는 녀석들을
다시 골라내야 한다.
내가 애를 먹었던 부분은 0,1,2 이렇게 있고 0,2 이렇게 있다면 0,1,2는
최소성이 만족되지 않지만 이게 유효한 키로 측정되는 것이 였다.
이게 왜 이랬냐면 나는 키 길이 순으로 정렬을 하고 012 이러한 문자열이 있다면
02 문자열이 포함되는지 검사를 때렸는데 1이 중간에 껴있는 012는 02와 관련이 없다고
판단하는 것이였다.
이를 나는 개별 문자를 뜯어서 확인했다. 0과 2가 012에 포함되는지....
효율성은 극악이지만 효율성을 묻는 문제는 아니여서 통과는했다.
더 빠르고 좋은 방식은 역시 비트마스킹이다.
비트마스킹을 사용하면 한방에 비교가 끝난다.
밑에는 그 방식으로 내가 다시 짠 풀이이다.
이 문제를 통해 탐색 문제에 대한 스킬을 길러간다.
*/

int Size, Frame = 1 << 10;
vector<int> Sel, Ans;
vector<pair<int,int>> Keys;
unordered_map<string, int> Table;

void Finder(int St, vector<vector<string>>& List) {
	if (St) {
		Table.clear();
		for (auto& A : List) {
			string Str;
			for (auto ind : Sel)
				Str += A[ind] + '|';
			if (Table.find(Str) == Table.end())
				Table[Str] = 0;
			Table[Str]++;
		}
		bool isKey = 1;
		for (auto& A : Table) {
			if (A.second > 1) {
				isKey = 0;
				break;
			}
		}
		if (isKey) {
			int K = Frame;
			for (auto& n : Sel)
				K += 1 << n;
			Keys.push_back({ Sel.size(), K });
		}
	}
	for (int i = St; i < Size; i++)
	{
		Sel.push_back(i);
		Finder(i + 1, List);
		Sel.pop_back();
	}
}

int solution(vector<vector<string>> relation) {
	Size = relation[0].size();
	Finder(0, relation);
	sort(Keys.begin(), Keys.end());
	for (auto& K : Keys) {
		bool isMin = 1;
		for (auto& A : Ans) {
			if ((K.second | A) == K.second) {
				isMin = 0; 
				break;
			}
		}
		if (isMin)
			Ans.push_back(K.second);
	}
	return Ans.size();
}