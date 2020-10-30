#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/5397
키로커 문제...
연결리스트 문제로 보고 리스트를 사용하여 풀었다.
역시 iterator 사용해서 진행하는건 정말 생각이 꼬인다... 연습이 필요하다.
풀고나서 생각보다 시간이 오래걸려서 다른 풀이를 봤더니 스택을 두개 사용하는 풀이가 존재하였다....
한 쪽은 결과 저장 스택 한 쪽은 커서 이동 시를 위한 스택을 두고 처리하는 방식이다.
왼쪽, 오른쪽으로 커서가 이동할 경우 두 스택 중에서 한 스택에서 원소가 빠져 다른 스택으로 집어넣어진다.
빼는 경우는 결과 저장 스택에서 걍 빼버리면 되고 출력시에는 한쪽 스택으로 결과를 몰아서 값을 거꾸로 출력하면 된다.
이 문제를 해결하면서 연결 리스트 사용법에 더 익숙해지고 스택 두개를 이용하는 경우에 대해 배웠다.
*/

int T;
list<char> A;
string input;

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        auto Cur = A.end();
        cin >> input;
        for (int j = 0; j < input.size(); j++)
        {
            if (input[j] == '<')
            {
                if (Cur != A.begin() && !A.empty()) Cur--;
            }
            else if (input[j] == '>')
            {
                if (Cur != A.end() && !A.empty()) Cur++;
            }
            else if (input[j] == '-')
            {
                if (!A.empty() && Cur != A.begin()) { Cur = A.erase(--Cur); }
            }
            else { Cur = A.insert(Cur, input[j]); Cur++; }
        }
        while (!A.empty())
        {
            cout << A.front();
            A.pop_front();
        }
        cout << '\n';
    }
}