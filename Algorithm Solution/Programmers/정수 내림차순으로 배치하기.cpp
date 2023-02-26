#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12933
정수 내림차순으로 배치하기 문제.
그냥 구현 문제라 이번에도 람다 연습을 했다.
*/

long long solution(long long n) {
	return stoll([&]()->string {
		multiset<char, greater<char>> b; 
		while (n) { 
			b.insert('0' + n % 10); n /= 10; 
		} 
		return string(b.begin(),b.end()); 
		}()
	);
}