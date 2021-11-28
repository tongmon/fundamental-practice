#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12919
서울에서 김서방 찾기 문제.
배열 순회로 찾을 수 있지만 간략하게 find를 사용했다.
iterator를 int로 변환하려면 처음 begin() iterator를 빼면 된다는 것을 알자. 
*/

string solution(vector<string> S) {
	return "김서방은 " + to_string(find(S.begin(), S.end(), "Kim") - S.begin()) + "에 있다";
}