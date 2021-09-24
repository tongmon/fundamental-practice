#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12935
제일 작은 수 제거하기 문제.
굳이 for문 안돌리고 min_element라는 stl 함수가 있다.
삼항 연산자에서 vector를 반환할 때는 형변환을 고려해야 한다.
arr.empty() ? vector<int>(1, -1) : arr; -> 이거 됨
arr.empty() ? vector<int>{ -1 } : arr; -> 이거 됨
arr.empty() ? { -1 } : arr; -> { -1 } 이 놈이 구조체인지 벡터인지 모름, 벡터여도 int, char 어떤 형 벡터인지 모르기에 에러
*/

vector<int> solution(vector<int> arr) {
	arr.erase(min_element(arr.begin(), arr.end()));
	return arr.empty() ? vector<int>{ -1 } : arr;
}