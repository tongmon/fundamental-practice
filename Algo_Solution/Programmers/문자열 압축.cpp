#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/60057
문자열 압축 문제.
문제에서 설명한 그대로 구현을 하면 된다.
1로 끊는 경우, 2로 끊는 경우.... 모두 탐색하는 완전 탐색 문제이다.
약간 까다롭다고 하면 끊어 읽을 때 처음과 마지막 부분을 깔끔하게 처리하지 못하면
결과가 이상해질 수 있다는 것 정도.
이 문제는 다른 사람 풀이를 보니 코드를 비약적으로 줄일 수 있는데
끊어 읽는 것을 c++ 라이브러리인 스트링변수.substr(i, j)를 사용해 구현하면 된다.
이 함수 잘 써먹을 수 있도록하자
시간도 더 줄일 수 있는데 문자열 길이의 절반이 넘어가면 비교 의미가 없어진다.
따라서 길이의 절반까지만 탐색하면 된다.
이 문제를 통해 풀이 속도를 높여간다.
*/

int solution(string s) {
	int answer = 100000, Ind = 0, Cnt = 1;
	string A, B, Ans;
	for (int j = 1; j <= s.size(); j++) {
		while (Ind < s.size())
		{
			int k;
			for (k = 0; k < j && Ind < s.size(); k++) {
				A.push_back(s[Ind++]);
			}
			if (k < j && Ind == s.size())
				break;
			if (Ind == k)
				B = A;
			else if (B != A) {
				if (Cnt > 1)
					Ans += to_string(Cnt);
				Ans += B;
				B = A;
				Cnt = 1;
			}
			else
				Cnt++;
			A.clear();
		}
		if (Cnt > 1)
			Ans += to_string(Cnt);
		Ans += B + A;
		answer = min(answer, (int)Ans.size());
		Cnt = 1; Ind = 0;
		A.clear(); B.clear(); Ans.clear();
	}
	return answer;
}