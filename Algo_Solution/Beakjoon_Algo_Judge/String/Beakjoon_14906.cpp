#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/14906
정규식 문제다...
C++로 접근하기 빡센문제다...
왜냐면 C++ 정규식 라이브러리는 Perl에서 지원하는 재귀 정규표현식 (?R)을 지원하지 않기 때문에
몇 가지 꼼수를 써야한다.
재귀 정규식을 지원한다면 스럼프는 ((D|E){1}F+)+G
스림프는 ((A((D|E){1}F+)+GC)|(AB(?R)+C)|(AH)) 이렇게 간단히 끝나지만
이게 안되기에 스림프 검사 시에 주어진 문자열에서 AB와 C를 모두 제거해주어야 한다.
문제는 C를 하나만 지우는 경우 C가 모두 지워지는데 이를 방지하기 위해 C가 하나인 경우도 따로 체크해야 한다.
이 문제를 통해 정규식에 대한 지식이 늘었다.
*/

int N;
string A, C;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	regex P("((D|E){1}F+)+G$"), R("((A((D|E){1}F+)+GC)|(AH))((D|E){1}F+)+G"), U("AB");
	cout << "SLURPYS OUTPUT\n";
	for (int i = 0; i < N; i++) {
		cin >> A;
		if (!regex_search(A, P)) {
			cout << "NO\n";
			continue;
		}
		int l = A.size();
		A = regex_replace(A, U, "");
		C = "";
		for (int j = 0; j < (l - A.size()) / 2; j++)
			C += 'C';
		if (!C.empty()) {
			if (C.size() == 1) {
				for (int k = 0; k < A.size(); k++) {
					if (A[k] == 'C') { 
						A.erase(A.begin() + k); 
						break; 
					}
				}
			}
			else {
				regex Cr(C);
				A = regex_replace(A, Cr, "");
			}
		}
		cout << (regex_match(A, R) ? "YES\n" : "NO\n");
	}
	cout << "END OF OUTPUT\n";
}