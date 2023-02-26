#include <bits/stdc++.h>
using namespace std;

/*

*/

long long solution(long long n) {
	long long answer = 0;
	long long K = sqrt(n);
	if (K * K == n) {
		answer = (K + 1) * (K + 1);
	}
	else {
		answer = -1;
	}
	return answer;
}