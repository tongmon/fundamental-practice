#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/17686
파일명 정렬 문제.
나는 왜 자꾸 내 풀이가 틀리나 계속 생각해봤는데 답이 안나와서 질문
게시판을 봤다....
근데 이 문제는 특이하게 안정 정렬을 사용해야 풀린다. 난 계속 퀵 소트가 기본인
sort 함수를 사용해서 안풀리던 것이 였다.
문제에서 힌트를 어떻게 주었냐면 "원래 입력에 주어진 순서를 유지한다" 라고 했다.
난 그래서 인덱스로 또 비교하면 되겠구나라고 생각했고 그렇게 했으나 틀렸다.
이 주어진 순서를 유지한다는 것은 숫자만이 비교 대상인 경우 빨강, 4 와 파랑, 4가 들어오면
그대로 빨강,4 와 파랑,4 를 유지해야 한다는 것이다. 파랑, 4 와 빨강, 4가 되면 안된다.
퀵 소트, 힙 소트는 이게 바뀌고 합병 정렬은 안정 정렬이라 이게 바뀌지 않는다.
합병 정렬을 지원하는 함수 stable_sort가 있고 이를 사용하여 풀게 되었다.
그리고 비교함수 작성시에 무조건 const & 를 붙이는 것을 습관화 하자
이 문제를 통해 stable_sort에 대한 정보를 얻어간다.
*/

int a, b;

bool Cmp(const vector<string> &A, const vector<string> &B) {
	if (A[0] != B[0])
		return A[0] < B[0];
	a = stoi(A[1]); b = stoi(B[1]);
	return a < b;
}

vector<string> solution(vector<string> files) {
	vector<string> answer;
	vector<vector<string>> Con;
	int k = 0;
	for (auto& str : files) {
		vector<string> A(3);
		int i = 0, Cnt = 0;
		while ('0' > str[i] || str[i] > '9')
			A[0] += toupper(str[i++]);
		while ('0' <= str[i] && str[i] <= '9' && Cnt < 5) {
			Cnt++;
			A[1] += str[i++];
		}
		A[2] = to_string(k++);
		Con.push_back(A);
	}
	stable_sort(Con.begin(), Con.end(), Cmp);
	for (auto& K : Con)
		answer.push_back(files[stoi(K[2])]);
	return answer;
}