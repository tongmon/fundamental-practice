#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/72412
순위 검색 문제.
구현으로 승부보는 문제 같다.
문제는 완전탐색 문제 같은데 효율성 테스트를 보면
50,000 x 100,000로 2억이 훌쩍 넘어가 일반적인 탐색으로는 답이 안나온다.
따라서 내가 사용한 방법은
해시 테이블을 사용하여 얘를 들어
java backend junior pizza 150 이렇게 정보가 주어지면
여기서 j---, jb--, jbj-, jbjp, -b--, -bj- ... 이렇게 키를 뜯어내고
이 뜯어낸 키들 마다 점수를 넣어두는 것이다.
여기선 150이 각 키에 해당하는 곳에 들어가게 된다.
이렇게 모아두면 탐색할 때 한방에 원하는 조건을 충족하는 점수들을 추릴 수 있다.
처음에 정보 뜯어낼 때 그냥 for문 돌면서 문자를 뜯어냈는데 이게 문자열이 정해져있다 보니
파싱할 때 굉장히 유용한 stringstream 이라는 것을 알아냈다.
사용법은 cout, cin 과 동일하고 cout, cin의 대상이 콘솔화면이라면 얘는 대상이 stringstream 변수가 되는 것이다.
다른 사람의 풀이를 보니 내 풀이에서 조금 더 최적화가 가능했는데
점수를 넣은 후 해시 맵 테이블이 완성된 상태에서 점수를 정렬하는 것이다.
이러면 이진 탐색을 통해 lowwer_bound로 해당 인덱스 구하고 전체 길이에서 빼면 개수를 한방에 획득 할 수 있다.
이 문제를 통해 구현 능력을 길러간다.
*/

unordered_map<string, vector<int>> Table;
vector<int> Emp;
string Buff;

void CodeMaker(int St, string &code, int N) {
	if (Buff.size() == 4) {
		if (Table.find(Buff) == Table.end())
			Table[Buff] = Emp;
		Table[Buff].push_back(N);
		return;
	}
	Buff.push_back(code[St]);
	CodeMaker(St + 1, code, N);
	Buff.pop_back();
	Buff.push_back('-');
	CodeMaker(St + 1, code, N);
	Buff.pop_back();
}

vector<int> solution(vector<string> info, vector<string> query) {
	vector<int> answer;
	string k1, k2, k3, k4, k5, Empty, Code;
	for (auto &str : info) {
		stringstream In(str);
		In >> k1 >> k2 >> k3 >> k4 >> k5;
		Code += k1[0]; Code += k2[0];
		Code += k3[0]; Code += k4[0];
		int N = stoi(k5);
		CodeMaker(0, Code, N);
		Buff.clear();
		Code.clear();
	}
	for (auto &q : query) {
		stringstream In(q);
		In >> k1 >> Empty >> k2 >> Empty >> k3 >> Empty >> k4 >> k5;
		Code += k1[0]; Code += k2[0];
		Code += k3[0]; Code += k4[0];
		int N = stoi(k5), Cnt = 0;
		if (Table.find(Code) != Table.end()) {
			for (auto T : Table[Code]) {
				if (N <= T)
					Cnt++;
			}
		}
		Code.clear();
		answer.push_back(Cnt);
	}
	return answer;
}