#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/86491
최소직사각형 문제.
가로 세로로 변수가 주어졌지만 돌려 집어 넣을 수 있기에
크기를 일관적으로 만들어줘야 한다.
세로는 큰 것, 가로는 작은 것 이렇게 정리하고 제일 작으면서 모든 명함을 다 넣을 수 있는 크기를
도출하면 된다.
*/

int solution(vector<vector<int>> sizes) {
    int w = 0, h = 0;
    for (auto& n : sizes)
        n[0] < n[1] ? swap(n[0], n[1]) : void();
    for (auto& n : sizes) {
        w = max(n[0], w);
        h = max(n[1], h);
    }
    return w * h;
}