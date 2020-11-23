#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12899
3진수 문제...
처음엔 시간복잡도 N으로 그냥 포문 돌리면서 증가시키려 했으나 갑자기 번뜩 진수변환이 생각나서
진수변환과 비스무리하게 짰다.
그냥 3진수로 짜면 이상하게 답이 나오니 꼭 3으로 나누어 떨어질 경우 -1을 해주어야 한다.
*/

string solution(int n) {
	string answer = "";
	int ary[3] = { 4,1,2 };
	while (n > 0) {
		answer.push_back(ary[n % 3] + '0');
		if (n % 3 == 0) n = n / 3 - 1;
		else n /= 3;
	}
	reverse(answer.begin(), answer.end());
	return answer;
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cout << solution(10);
}