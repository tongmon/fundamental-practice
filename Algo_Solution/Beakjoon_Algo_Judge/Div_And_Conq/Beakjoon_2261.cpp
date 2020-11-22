#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2261
아주 유명한 알고리즘인 Closest Pair 알고리즘이다.
밑의 나온 방법은 분할정복 방식이고 다른 한 방식은 스위핑이라는 방식이 존재한다.
나는 해결할 엄두도 안나서 해결책을 보고 구현을 했다.
일단 가장 가까운 두점을 찾는데 있어서 제일 먼저 떠올릴 수 있는 방법은 그냥 브루트 포스로 전체를 다 뒤지는 것이다.
0번 점 잡고 1, 2, 3, 4.... 1번 점 잡고 2, 3, 4... 이렇게 하면 점이 100개만 있어도 미친듯이 느려진다.
이러한 방법 말고 분할정복으로 하면 n log(n) * log(n) 에 해결 가능하다.
들어온 좌표들은 x축 정렬한다.
일단 현재 들어온 좌표들에서 중간에 위치하게 되는 x 좌표로 나눈다.
그니까 점들이 1, 2, 3, 4, 5, 6 의 x좌표를 가진다면 (3 + 4) / 2 = 3을 센터값으로 잡는다.
그리고 재귀적으로 계속 센터를 구해가면서 내려간다...
일단 센터를 잡으면 왼쪽 구간, 중간선, 오른쪽 구간으로 나뉘게 되는데 왼쪽, 오른쪽 구간의 가장 짧은 거리는 재귀적으로 구해진다
이 가운데가 문제이다. 
이 가운데를 거쳐서 거리를 이루는 두 점을 판단하는 것이 문제가 된다.
일단 오른쪽, 왼쪽 구간의 최소 거리를 구했고 이 둘 중의 최소거리 까지 구했다.
그 다음 잡아놨던 가운데 중심축과 x좌표가 얼마나 떨어져 있나 확인한다. 
기존에 구했던 최소거리 보다 적게 떨어져 있다면 이 녀석이 최단 거리를 새롭게 이룰 수 있기 때문에 후보 배열에 넣어둔다.
계속 전체를 검사하면서 후보를 만들어 나간다. 여기서 전체란 분할 정복에서 분할 되어있는 부분의 전체을 말한다.
일단 이렇게 만들어진 후보에 한해서 또 검사가 이루어지는데 이 때 후보들을 y축좌표 순으로 정렬한다.
y축이 제일 작은 녀석부터 검사가 들어가는데 이때는 자신의 y축과 다른 후보들의 y축 차이가 기존에 구해놨던 최소거리보다 작으면
이 두 좌표가 후보들 중에서 새로운 최소거리를 만들수 있기 때문에 기존의 최소거리와 이 두 좌표의 거리를 비교해서 더 작은 값이 최소거리로 들어간다.
이렇게 분할 정복을 계속하다보면 최소거리가 도출된다.
정말 효율적으로 검사를 하는 녀석과 안하는 녀석을 판단하고 거른다.
이렇게 값이 쌍으로 존재하는 경우에는 보통 분할 정복이라는 해결방법이 통한다고 하니 참고하자.
이 문제를 통해 분할 정복을 어떻게 접근해야 하는지 약간 더 알아간다.
좌표 평면이 있다면 반으로 나누어 접근하는 방법을 염두해두자.
*/

#pragma warning(disable:4996)

typedef struct _cord
{
    int x = 0, y = 0;
}Cordinate;

Cordinate Ary[100001];
Cordinate Merge[100001]; // 개선된 방법에서 쓰임, 개선된 방법은 주석처리

unsigned int Dist(Cordinate* A, Cordinate* B)
{
    return (A->x - B->x) * (A->x - B->x) + (A->y - B->y) * (A->y - B->y);
}

bool Compare_X(Cordinate A, Cordinate B) // X좌표 기준으로 정렬
{
    if (A.x == B.x)
    {
        return A.y < B.y;
    }
    return A.x < B.x;
}

bool Compare_Y(Cordinate A, Cordinate B) // Y좌표 기준으로 정렬
{
    if (A.y == B.y)
    {
        return A.x < B.x;
    }
    return A.y < B.y;
}

int Closest_Pair(int Start, int End)
{
    if (End - Start + 1 == 2)
    {
        return Dist(&Ary[Start], &Ary[End]);
    }
    if (End - Start + 1 == 3) // 2개 1개로 분리 할 수는 없기에 3개도 끊어 준다.
    {
        return min(Dist(&Ary[Start], &Ary[Start + 1]), min(Dist(&Ary[Start], &Ary[Start + 2]), Dist(&Ary[Start + 1], &Ary[Start + 2])));
    }

    int Center = (Ary[Start].x + Ary[End].x) / 2; // y축과 평행한 Start부터 End까지의 중심 x좌표
    unsigned int Distance = min(Closest_Pair(Start, (Start + End) / 2), Closest_Pair((Start + End) / 2 + 1, End));
    int Center_Dist = 0, Mid_Size = 0;

    Cordinate* Mid = new Cordinate[End - Start + 2];
    for (int i = Start; i <= End; i++)
    {
        Center_Dist = Center - Ary[i].x;
        if (Center_Dist * Center_Dist < Distance)
        {
            Mid[Mid_Size++] = Ary[i];
        }
    }
    sort(Mid, Mid + Mid_Size, Compare_Y); // 이 부분이 log(n) * log(n)을 만드는 주범이기에 해결하면 속도가 더 빨라진다. 밑의 주석처리한 방식에 해결법이 나와있다.
    for (int i = 0; i < Mid_Size - 1; i++)
    {
        for (int j = i + 1; j < Mid_Size && (Mid[i].y - Mid[j].y) * (Mid[i].y - Mid[j].y) < Distance; j++) // 많아 봤자 최대 6개여서 이중for문이 아닌 N으로 친다.
        {
            Distance = min(Distance, Dist(&Mid[i], &Mid[j]));
        }
    }
    delete[]Mid;
    return Distance;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int N; cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> Ary[i].x >> Ary[i].y;
    }
    sort(Ary, Ary + N, Compare_X);
    cout << Closest_Pair(0, N - 1);
}

/*
int Closest_Pair(int Start, int End)
{
    if (End - Start + 1 == 2)
    {
        sort(Merge + Start, Merge + End + 1, Compare_Y);
        return Dist(&Ary[Start], &Ary[End]);
    }
    if (End - Start + 1 == 3) // 2개 1개로 분리 할 수는 없기에 3개도 끊어 준다.
    {
        sort(Merge + Start, Merge + End + 1, Compare_Y);
        return min(Dist(&Ary[Start], &Ary[Start + 1]), min(Dist(&Ary[Start], &Ary[Start + 2]), Dist(&Ary[Start + 1], &Ary[Start + 2])));
    }

    int Center = (Ary[Start].x + Ary[End].x) / 2; // y축과 평행한 Start부터 End까지의 중심 x좌표
    int Mid = (Start + End) / 2, Sindex = Start, Eindex = Mid + 1, Center_Dist = 0, Mid_Size = 0;
    unsigned int Distance = min(Closest_Pair(Start, Mid), Closest_Pair(Mid + 1, End));
    Cordinate* MidAry = new Cordinate[End - Start + 2];

    // 합병 정렬을 심어 놓아 시간 복잡도 줄임
    while (Sindex <= Mid && Eindex <= End)
    {
        if (Merge[Sindex].y < Merge[Eindex].y)
        {
            MidAry[Mid_Size++] = Merge[Sindex++];
        }
        else
        {
            MidAry[Mid_Size++] = Merge[Eindex++];
        }
    }
    for (; Eindex <= End; Eindex++)
    {
        MidAry[Mid_Size++] = Merge[Eindex];
    }
    for (; Sindex <= Mid; Sindex++)
    {
        MidAry[Mid_Size++] = Merge[Sindex];
    }
    for (int i = 0; i < Mid_Size; i++)
    {
        Merge[i + Start] = MidAry[i];
    }

    Mid_Size = 0;
    for (int i = Start; i <= End; i++)
    {
        Center_Dist = Center - Merge[i].x;
        if (Center_Dist * Center_Dist < Distance)
        {
            MidAry[Mid_Size++] = Merge[i];
        }
    }
    for (int i = 0; i < Mid_Size - 1; i++)
    {
        for (int j = i + 1; j < Mid_Size && (MidAry[i].y - MidAry[j].y) * (MidAry[i].y - MidAry[j].y) < Distance; j++) // 많아 봤자 최대 6개여서 이중for문이 아닌 N으로 친다.
        {
            Distance = min(Distance, Dist(&MidAry[i], &MidAry[j]));
        }
    }
    delete[]MidAry;
    return Distance;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int N; cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> Ary[i].x >> Ary[i].y;
    }
    sort(Ary, Ary + N, Compare_X);
    for (int i = 0; i < N; i++)
    {
        Merge[i] = Ary[i];
    }
    cout << Closest_Pair(0, N - 1);
}
*/