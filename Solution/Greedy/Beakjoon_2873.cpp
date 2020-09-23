#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2873
푸는데 존나 오래걸렸다.... 그냥 답 볼껄 시간 쥰내 많이 나갔다....
일단 그리디 알고리즘이라고는 하는데.... 내가 보기엔 이 문제는 구현이 어렵다.
이 문제를 풀면서 구성적 증명법이라는 것을 배웠는데 일단 어떤 것이 맞다면 그게 맞다고 실제로 보이는 것이다.
예를 들어 하늘을 날아다니는 운송수단이 있다고 나는 증명하고 싶다. 구성적 증명법으로 접근하면 그냥 비행기를 만들어서 보여 증명하면 된다.
이게 이 문제에 어떻게 쓰이냐면... 그냥 겁나 그려대면 된다. 겁나 그려대면 3가지 경우로 나뉘는데
일단 첫번째로 행이 홀수인 경우 롤러코스터는 모든 타일을 순회할 수 있으며 방향은 오른쪽 -> 아래 한칸 -> 왼쪽 이렇게 진행한다.
두번째 케이스는 행은 짝수 열이 홀수인 경우이다. 이 경우도 쉽게 아래 -> 오른쪽 한칸 -> 위 이렇게 전체 타일을 순회할 수가 있다.
위 두 케이스는 구현도 쉽고 이해하기도 쉽다.
근데 행과 열이 모두 짝수인 경우가 문제가 된다.
이 경우 시작점을 하얀색으로 잡고 만들어지는 체스판으로 이해하면된다. 일단 하얀색이 최솟점이라도 지울수 없다...
하얀색을 지우면 최소 2개의 검은타일도 같이 날라가야 한다. 그려서 이해하면 쉽다.
반면 검은색 타일은? 한개 지우면 깔끔하게 나머지 타일을 모두 순회하면서 도착점에 도착이 가능하다. 이것도 그려서 이해하면 쉽다;;
따라서 검은색 타일의 값 중에 최솟값을 찾고 그 타일을 지나지 않으면서 모두 순회해야 한다.
여기까지 생각하는 것도 얼마안걸렸는데..... 구현이 엿같아서 오래걸렸다.
구현은 코드를 보면서 이해하는게 쉬우니 설명은 하지 않겠다.
이 문제를 풀면서 일단 그리디를 풀다가 방향성을 못잡겠다면 일단 조건을 나누어야 되겠다라는 생각을 가지게 되었다.
이 문제도 보면 3가지 조건으로 나뉘고 이에 맞추어 구현을 하면되는 문제였다.
물론 조건을 찾지 않고 자료들을 정제하면서 푸는 문제도 있긴하지만 일단 시야가 넓어지면 좋으니 조건 나누기를 염두해두자....
그리고 구현에 대해서도 생각을 해보아야한다.
이게 한칸 한칸 가면서 경로를 생성하는 방식으로 처음에 접근을 했고 이 방식으로 풀리지 않는 반례가 너무 많았다.
최소의 검은색 타일이 존재하는 열 전 까지 그리고 그 후도 행 or 열이 홀수 일때와 마찬가지로 오른쪽 -> 아래 한칸 -> 왼쪽 이렇게 접근이 가능하고
검은색 타일이 존재하는 열에서만 아래, 위로 스캔하면서 특별히 출력해주면 구현도 간단해지고 반례도 없어진다.
이렇게 구현이 복잡해 질 것 같으면 구현시 동일한 부분이 생기는지 다시 고려하며 최소한 동일부를 제외하고 특별한 부분만 구현하게 구현시에도 생각이 많이 필요하다.
요약하자면 구현시에도 그냥 풀었다 싶은 것을 다시 생각해보고 동일한 부분을 제외하며 구현하는 습관을 기르자!
*/

#pragma warning(disable:4996)

int MRow, MCol, Row, Col, Ary[1001][1001];

void StringMaker(string *A, string *B, char Dir_1, char Dir_2, char Dir_3, bool is_Print)
{
    int Border = Dir_1 == 'R' ? Col - 1 : Row - 1;
    for (int i = 0; i < Border; i++)
    {
        A->push_back(Dir_1);
        B->push_back(Dir_2);
    }
    A->push_back(Dir_3);
    B->push_back(Dir_3);
    if (is_Print == false)
    {
        return;
    }
    Border = Dir_1 == 'R' ? Row - 1 : Col - 1;
    for (int i = 0; i < Border; i++) // 출력부
    {
        if (i % 2 == 0)
        {
            cout << *A;
        }
        else
        {
            cout << *B;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int input, Minimum = 1001; 
    cin >> Row >> Col;
    string buffer_1, buffer_2;
    for (int i = 0; i < Row; i++)
    {
        for (int j = 0; j < Col; j++)
        {
            cin >> input;
            Ary[i][j] = input;
            if (i % 2 != j % 2) // 격자마다 체크
            {
                if (input < Minimum)
                {
                    Minimum = input;
                    MRow = i; MCol = j;
                }
            }
        }
    }
    if (Row % 2 == 1)
    {
        StringMaker(&buffer_1, &buffer_2, 'R', 'L', 'D', true);
        buffer_1.pop_back(); cout << buffer_1;
    }
    else if (Col % 2 == 1)
    {
        StringMaker(&buffer_1, &buffer_2, 'D', 'U', 'R', true);
        buffer_1.pop_back(); cout << buffer_1;
    }
    else // 행열이 모두 짝인 경우
    {
        StringMaker(&buffer_1, &buffer_2, 'R', 'L', 'D', false);
        string Find;
        int border = MRow % 2 == 0 ? MRow : MRow - 1; 
        bool status = true;
        for (int i = 0; i < border / 2; i++)
        {
            cout << buffer_1 << buffer_2;
        }
        for (int j = 0; j < Col; j++)
        {
            if (j % 2 == 1)
            {
                if (border == MRow && j == MCol)
                {
                    Find.push_back('R'); status = status == false ? true : false;
                }
                else
                {
                    if (status == true)
                    {
                        Find.push_back('U');
                    }
                    else
                    {
                        Find.push_back('D');
                    }
                    Find.push_back('R');
                }
            }
            else
            {
                if (border + 1 == MRow && j == MCol)
                {
                    Find.push_back('R'); status = status == false ? true : false;
                }
                else
                {
                    if (status == true)
                    {
                        Find.push_back('D');
                    }
                    else
                    {
                        Find.push_back('U');
                    }
                    Find.push_back('R');
                }
            }
        }
        Find.pop_back(); cout << Find;
        if ((Row - border - 2) / 2 != 0)
        {
            cout << 'D';
            for (int i = 0; i < (Row - border - 2) / 2; i++)
            {
                cout << buffer_2;
                if (i != (Row - border - 2) / 2 - 1)
                {
                    cout << buffer_1;
                }
            }
            buffer_1.pop_back(); cout << buffer_1;
        }
    }
}