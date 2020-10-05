#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/6603
조합 문제이기에 DFS로 접근하여 풀면 된다.
출력시에 벡터를 사용했는데 벡터말고 그냥 출력 배열을 하나 선언하여 인덱스가 Depth인 배열 위치에 값을 넣고 그 배열을 출력하면
pop_back 할 필요가 없어진다.
이러한 기법을 알고 가자!
*/

#pragma warning(disable:4996)

int Ary[50];
vector<int> PrintList;

void DFS(int Size, int Start, int Depth)
{
    if (Depth == 6)
    {
        for (int i = 0; i < Depth; i++)
        {
            cout << PrintList[i] << " ";
        }
        cout << '\n'; return;
    }
    for (int i = Start; i < Size; i++)
    {
        PrintList.push_back(Ary[i]); // 이거 보다 조금이라도 더 효율적으로 접근하려면 그냥 출력 배열(인덱스가 Depth인)에다 넣어버리고 팝 할 필요없는 방식이 있다.
        DFS(Size, i + 1, Depth + 1);
        PrintList.pop_back();
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int input;
    while (true)
    {
        cin >> input; if (input == 0) break;
        for (int i = 0; i < input; i++)
        {
            cin >> Ary[i];
        }
        DFS(input, 0, 0); cout << '\n';
    }
}