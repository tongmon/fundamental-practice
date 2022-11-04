#include <bits/stdc++.h>
using namespace std;

/*
https://app.codility.com/programmers/trainings/9/binary_gap/
앞에서 부터 비트쉬프트를 사용해서 0 개수를 세도 되지만 나는 c++에서 제공하는 bitset을 사용해 순회했다.
*/

int solution(int N)
{
	bitset<32> a(N);
	int p = -1, q = 0, c = 0;
	for (int i = 0; i < 32 && p < 0; i++)
		if (a[i]) p = i;
	for (int i = p; i < 32; i++) {
		if (a[i]) {
			q = max(c, q);
			c = 0;
		}
		else c++;
	}
	return q;
}