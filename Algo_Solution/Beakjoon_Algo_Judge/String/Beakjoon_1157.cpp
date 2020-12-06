/*
https://www.acmicpc.net/problem/1157
대소문자 내리고 올리는 것을 간단하게 해주는 함수
toupper() tolower() 를 잘 알아가자
*/

string In;
unordered_map<char, int> A;

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> In;
	int Max = 0, cnt = 0; char b;
	for (auto s : In) {
		s = toupper(s);
		if (A.find(s) == A.end())
			A[s] = 1;
		else
			A[s] += 1;
		Max = max(Max, A[s]);
	}
	for (auto num : A) {
		if (num.second == Max) {
			cnt++; b = num.first;
		}
	}
	if (cnt != 1) cout << '?';
	else cout << b;
}