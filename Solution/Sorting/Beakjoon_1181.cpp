#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1181
단어 정렬 문제...
기본적인 정렬 STL 사용방법을 익히고 있는지를 테스트하는 문제다.
정렬 함수 작성시 유의할 점은 모든 케이스를 다 생각해야 한다는 것이다.
머가 크냐? 같냐? 작냐? 같으면 또 다른건 어케 되냐? 이런 것을 생각하면서 짜보자
그리고 string은 대소비교 < 를 이미 지원한다. strcmp 쓸 필요가 없다.
그리고 배열 중복 제거시 사용되는 STL unique()를 알아두자... 굉장히 쓸 곳이 많아 보인다.
*/

int N; string input;
vector<string> Ary;
unordered_map<string, bool> is_Same;

bool Compare(string A, string B)
{
    if (A.size() < B.size()) return true;
    if (A.size() > B.size()) return false;
    if (A < B) return true;
    return false;
}

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> input; 
        if (is_Same.find(input) == is_Same.end())
        {
            Ary.push_back(input); is_Same[input] = true;
        }
    }
    sort(Ary.begin(), Ary.end(), Compare);
    for (int i = 0; i < Ary.size(); i++)
    {
        cout << Ary[i] << '\n';
    }
}