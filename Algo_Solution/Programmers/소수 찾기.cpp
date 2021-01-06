#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/42839
소수 찾기 문제
소수 판별법, 에라토스테네스의 체 등을 알고 소수를 알 수가 있어야 하고
단어를 조합하는 모든 경우를 구할 수 있어야 한다.
또한 중복 되는 소수를 세는 것을 피하기 위해 찾았다면 이미 찾았다는 표시를 해야한다.
*/

string Nums, A;
unordered_map<int, bool> Vis;
int answer;

bool is_Prime(int Num) {
    if (Num <= 1)
        return 0;
    if (!(Num % 2)) {
        if (Num == 2)
            return 1;
        return 0;
    }
    for (int i = 3; i <= sqrt(Num); i+=2) {
        if (!(Num % i))
            return 0;
    }
    return 1;
}

void Chosen() {
    if (!A.empty()) {
        int buf = stoi(A);
        if (Vis.find(buf) == Vis.end()) {
            bool flag = is_Prime(buf);
            if (flag)
                answer++;
            Vis[buf] = 1;
        }
    }
    for (int i = 0; i < Nums.size(); i++)
    {
        A.push_back(Nums[i]); Nums.erase(Nums.begin() + i);
        Chosen();
        Nums.insert(Nums.begin() + i, A.back()); A.pop_back();
    }
}

int solution(string numbers) {
    Nums = numbers;
    Chosen();
    return answer;
}