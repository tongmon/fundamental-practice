#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1783
병든 나이트 문제이다.
풀고나서 다른 사람 풀이를 보니 그리디 알고리즘으로 풀었다고 하는데...
내가 그리디 알고리즘이 정확히 모르는건지 아니면 이렇게 정해진거 없이 최선의 방법을 찾는 문제를 통틀어서 그리디라고 하는 건지....
그리디에 대해 조금 알아봐야겠다.
아무튼 이 문제는 for문 한개가 필요없이 조건만 따지면 되는 문제다.
일단 나이트는 왼쪽 아래에서 시작한다.
방문 칸이 4개 찍히기 전까지는 이동에 제약이 없고 병든 나이트가 갈 수 있는 데를 가면 된다. 
4개가 찍히고 그 다음을 가는 경우에는 병든 나이트가 갈 수 있는 방법의 종류를 모두 쓴 상태여야 한다.
일단 이러한 조건을 아는 상태에서 나는 높이 제한이 2보다 낮은 경우 제약이 생기는 것을 발견했다.
그래서 높이가 2와 나머지인 것으로 분리했다.
높이가 2보다 낮고 1보다 크다면 일단 방문 블록 개수가 4보단 클 수 없다. 모든 이동 방식을 쓰지 못한다.
모든 이동 방식을 쓰려면 높이가 적어도 3이상이여야 한다.
아무튼 높이가 2인 경우 생각해보고 그림에서 경로를 찍어보면 밑과 같은 코드가 나온다.
그리고 높이가 3 이상이면 모든 이동 방식을 쓸 수가 있는데 이 때 모든 이동방식을 쓰게되는 최소 너비수는 7이다.
이것도 그림으로 그려보면 알 수 있다.
그래서 7보다 크면 이동방식에 제약이 없기 때문에 위로 2칸(아니면 아래로 2칸) 옆 1칸의 이동 방식으로 옆으로 계속 한 칸씩 알뜰하게 갈 수 있기 때문에
5 + (Width - 7) 이러한 식이 나오게 된다.
나머지 조건들은 모두 이동 방식에 제약이 있을 경우니 이것도 그림을 그려서 생각해보면 답이 나온다.
아무튼 이러한 유형의 문제가 그리디 유형이라는 것을 알아간다.
*/

#pragma warning(disable:4996)

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    unsigned int Width, Height; cin >> Height >> Width;
    if (Height <= 2) // 높이가 2 이하이면
    {
        if (Height == 1)
        {
            cout << 1;
        }
        else if (Width >= 7)
        {
            cout << 4;
        }
        else
        {
            cout << (Width - 1) / 2 + 1;
        }
    }
    else
    {
        if (Width <= 4)
        {
            cout << Width;
        }
        else if (Width == 5 || Width == 6)
        {
            cout << 4;
        }
        else if (7 <= Width)
        {
            cout << 5 + (Width - 7);
        }
    }
}