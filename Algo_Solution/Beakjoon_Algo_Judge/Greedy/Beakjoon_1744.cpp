#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1744
무난한 그리디 문제다.
일단 원소를 정제하고 그 정제한 틀 안에서 최선의 수를 뽑는 기본 그리디 형태를 취하고 있다.
여기서 정제는 정렬이 이용된다.
일단 곱하기가 들어가고 음수가 원소로 위치할 수 있으니 이를 고려해야한다.
일단 양수와 음수는 서로 곱하거나 더해봤자 작아지기만 할 뿐 이득이 없다. 이들을 서로 떨어트려 정렬하자.
양수는 내림차순으로 정렬하고 음수는 오름차순으로 정렬한다.
양수는 내림차순인게 묶어서 곱하는 경우가 큰수끼리 곱할 수록 커지기에 당연하고 음수는 오름차순인 이유는
절댓값이 큰 음수끼리 곱해야 큰 수를 획득할 수 있기 때문이다.
이렇게 정제하는 방법이 정의가 되었는데 주의할 점은 0을 어떻게 하냐이다.
0은 음수쪽에 들어가야 한다. -100과 0뿐인 배열이 주어지면 0 * -100을 하여 음수를 소멸시켜 더 큰값을 얻을 수 있기 때문이다.
이 문제를 통해 그리디를 체계적으로 푸는 능력이 조금이나마 생긴 것 같다.
골드4로 약간 어려울 수 있는 문제인데 처음부터 "정제하고 매 순간 최선을 집는다" 라는 생각을 가지고 푸니 짧은 시간만에 풀렸다.
앞으로 이 처럼 문제 접근시에 유형에 알맞은 생각을 할 수 있는 능력을 더 기르도록 하자
*/

#pragma warning(disable:4996)

vector<short> Ary_plus;
vector<short> Ary_minus;
int Sum = 0;

void Greedy(vector<short>* A)
{
    int index = 0;
    while (index < A->size() - 1)
    {
        if (A->at(index) + A->at(index + 1) < A->at(index) * A->at(index + 1))
        {
            Sum = Sum + A->at(index) * A->at(index + 1);
            index = index + 2;
        }
        else
        {
            Sum = Sum + A->at(index); index++;
        }
    }
    if (index == A->size() - 1)
    {
        Sum = Sum + A->back();
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int N, input; cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> input;
        if (input > 0)
        {
            Ary_plus.push_back(input);
        }
        else
        {
            Ary_minus.push_back(input);
        }
    }
    sort(Ary_plus.begin(), Ary_plus.end(), greater<int>());
    sort(Ary_minus.begin(), Ary_minus.end());
    if (Ary_plus.empty() == false)
    {
        Greedy(&Ary_plus);
    }
    if (Ary_minus.empty() == false)
    {
        Greedy(&Ary_minus);
    }
    cout << Sum;
}