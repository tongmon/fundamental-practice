#include <bits/stdc++.h>
using namespace std;

/*
짝수와 홀수 문제.
그냥 나머지 연산으로 풀어도 되지만 N & 1 비트 연산을 해도 된다.
맨 앞 비트가 켜져있으면 이진수는 항상 홀수니...
*/

string solution(int N) {
	return N % 2 ? "Odd" : "Even";
}