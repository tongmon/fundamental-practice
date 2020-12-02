#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/5525
문자열 매칭 문제라 뇌 비우고 KMP 박아버렸다.
정석적인 풀이가 궁금해서 봤는데 연속적으로 나오는 OI를 검사하고
그 개수가 입력받은 N과 같으면 카운트를 센다.
여태껏 세던 OI 개수를 이용해야 하기에 세던 녀석들 중에 꼬리 부분을 자르고
계속 OI를 세나간다. OI가 아니면 세던 것을 모두 버리고 문자열에서 I를 찾아
또 이 짓을 할 명분을 찾는 것.
이 방법이 메모리와 시간 모두 KMP보다 이 문제에서는 절약이다.
이러한 사고력을 기르기 위해 문제를 더 풀어야겠다...
*/

int N, M;
string A = "I", B;
vector<int> lps;

void lps_m() {
	lps.reserve(A.size());
	lps.push_back(0); int j = 0;
	for (int i = 1; i < A.size(); i++)
	{
		while (j > 0 && A[i] != A[j]) {
			j = lps[j - 1];
		}
		if (A[i] == A[j]) lps.push_back(++j);
		else lps.push_back(0);
	}
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M >> B;
	for (int i = 0; i < N; i++) A += "OI";
	lps_m(); int ASize = A.size(), cnt = 0;
	for (int i = 0, j = 0; i < B.size(); i++) {
		while (j > 0 && A[j] != B[i])
		{
			j = lps[j - 1];
		}
		if (A[j] == B[i]) {
			if (j == ASize - 1) {
				j = lps[j]; cnt++;
			}
			else j++;
		}
	}
	cout << cnt;
}

/*
int main() // 정석적인 풀이
{
	cin >> N >> M >> B; int cnt = 0;
	for (int i = 1; i < B.size(); i++)
	{
		int count = 0;
		if (B[i - 1] == 'I')
		{
			while (B[i] == 'O' && B[i + 1] == 'I')
			{
				i += 2; 
				count++; 
				if (count == N) { 
					count--; cnt++; 
				}
			}
		}
	} 
	cout << cnt << '\n';
}
*/