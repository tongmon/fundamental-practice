#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/5430
덱을 이용하여 푸는 문제...
덱말고 큐나 머 다른 자료구조 사용하면 모두 타임아웃이다.
그리고 덱을 써도 R연산을 실제로 뒤집으면 타임아웃이다.
그냥 덱은 그냥 놔두고 앞에서 뺄지 뒤에서 뺄지만 바꿔야한다.
숫자 넣는 기본 범위를 < 이거로 써서 0을 제외하게 되어 틀렸는데
이런 실수를 앞으로 줄이자!
*/

int T, N;
bool is_front = true, is_error = false;
string Order, Nums, Output, Number;
deque<int> Ary;

void printer()
{
    if (is_error == true) { cout << "error\n"; is_error = false; return; }
    if (Ary.empty()) { cout << "[]\n"; return; }
    cout << '[';
    if (is_front == true)
    {
        for (int i = 0; i < Ary.size() - 1; i++) cout << Ary[i] << ',';
        cout << Ary.back() << "]\n";
    }
    else
    {
        for (int i = Ary.size() - 1; i > 0; i--) cout << Ary[i] << ',';
        cout << Ary.front() << "]\n";
    }
}

void Mission()
{
    for (int i = 0; i < Order.size(); i++)
    {
        if (Ary.empty() && Order[i] == 'D') { is_error = true; return; }
        if (Order[i] == 'R') { is_front = is_front == true ? false : true; }
        else if (is_front == true) Ary.pop_front();
        else Ary.pop_back();
    }
}

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        cin >> Order; cin >> N; cin >> Nums;
        for (int j = 0; j < Nums.size(); j++)
        {
            if ('0' <= Nums[j] && Nums[j] <= '9') Number.push_back(Nums[j]);
            else if ((Nums[j] == ']' || Nums[j] == ',') && !Number.empty()) { Ary.push_back(stoi(Number)); Number.clear(); }
        }
        Mission();
        printer(); Ary.clear(); is_front = true;
    }
}