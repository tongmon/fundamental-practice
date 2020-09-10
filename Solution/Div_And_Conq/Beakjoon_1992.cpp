#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1992
분할정복 문제.
다른 사람 풀이에 비해 코드가 약간 늘어졌다.
늘어진 이유는 내가 짠 코드는 4분할을 for문 돌릴때 검사하지만 다른 사람 코드를 보니
left right top bottom 전체를 훍고 저기서 하나라도 다르면 그냥 4분할 때려버리는 방식으로 했더라.
다른 사람 방식이 코드는 더 깔끔해지지만 로직은 내 방식과 같다. 속도도 같고
그래도 간결해져야 생산성이 높아지니 다른 사람 코드처럼 짜도록 노력하자.
이런 유형의 문제는 하나가 분할되면 어짜피 나머지도 분할 되어야하기에 한번에 전체를 검사하고 분할하는 것이 코드가 짧아진다.
이 문제를 통해 분할정복 유형에 대한 감을 좀 더 잡았다.
*/

#pragma warning(disable:4996)

short Ary[65][65];

void Compress(short left, short top, short right, short bottom)
{
    cout << "(";
    int Size = right - left + 1;
    int Windex = left, Hindex = top;
    bool is_Brick = true;
    if (Size == 2)
    {
        for (int i = top; i <= top + 1; i++)
        {
            for (int j = left; j <= left + 1; j++)
            {
                cout << Ary[i][j];
            }
        }
        cout << ")";
        return;
    }
    for (int k = 0; k < 4; k++)
    {
        for (int i = Hindex; i < Hindex + Size / 2; i++)
        {
            for (int j = Windex; j < Windex + Size / 2; j++)
            {
                if (Ary[Hindex][Windex] != Ary[i][j])
                {
                    is_Brick = false;
                    Compress(Windex, Hindex, Windex + Size / 2 - 1, Hindex + Size / 2 - 1);
                    break;
                }
            }
            if (is_Brick == false)
            {
                break;
            }
        }
        if (is_Brick == true)
        {
            cout << Ary[Hindex][Windex];
        }
        Windex = Windex + Size / 2; is_Brick = true;
        if (k == 1)
        {
            Windex = left; Hindex = Hindex + Size / 2;
        }
    }
    cout << ")";
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int N; cin >> N;
    bool Only_one = true;
    string buffer;
    for (int i = 0; i < N; i++)
    {
        cin >> buffer;
        for (int j = 0; j < N; j++)
        {
            Ary[i][j] = (buffer[j] - '0');
            if (Ary[0][0] != Ary[i][j])
            {
                Only_one = false;
            }
        }
    }
    if (Only_one == true)
    {
        cout << Ary[0][0];
    }
    else
    {
        Compress(0, 0, N - 1, N - 1);
    }
}