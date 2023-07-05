#include <iostream>
#include <cstring>
#include <list>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1517
분할정복 유형의 문제였다...
푸는데 족히 2시간 정도 걸렸다. 일단 문제는 버블정렬 할 때의 swap과정 수를 세는 문제인데
이를 그냥 버블정렬 돌려서 카운트하면 시간초과가 난다. O(n*n)을 어떻게든 줄여서 swap의 수를 세야하는 것이다.
O(n*n)보다 작은 정렬들은 퀵, 힙, 합병, 트리 정렬 등이 있지만 swap의 수를 구하기에 적합해 보이는 건 합병정렬이다.
일단 합병정렬은 정렬된 두 부분을 가져와 다시 합쳐나가는 정렬인데 이 정렬된 두 부분을 합치는 과정에서 swap의 수를 셀 수가 있다.
만약 1, 8, 10 / 2, 4, 9 이렇게 있는 것을 합병한다 해보면 처음에 1이 들어가고 swap은 일어나지 않는다.
두번째는 2가 들어가는데 첫번째 정렬된 뭉치에서 남은 수는 8, 10이고 2가 1 다음에 위치하게 된다면 8 ,10 앞에 위치하게 되니까 swap이 두번 생긴거라고 볼 수 있다.
또 4를 넣어도 swap 두번, 8을 넣을 때는 첫번째 뭉치이기에 swap이 생기지 않는다. 9를 넣을 때에는 첫번째 뭉치에 남아있는 10이 한개여서 swap이 한번 생긴다.
10은 swap 없이 들어가게 된다. 이러한 카운팅을 하면 O(nlog(n))의 복잡도로 완료가 된다.
이 문제를 통해 간단해 보이지만 시간복잡도가 빡빡한 경우에 분할정복의 방식을 쓰는 것을 고려해야 겠다는 느낌을 키우고 간다.
*/

#pragma warning(disable:4996)

int Ary[500001] = { 0, };
long long Count = 0;

void MergeSort(int Start, int Mid, int End)
{
    int* BufferAry = new int[End - Start + 2];
    int Backindex = Start, Frontindex = Mid + 1, Bufferindex = 0;
    int Remain = Mid - Backindex + 1;
    while (Backindex <= Mid && Frontindex <= End)
    {
        if (Ary[Backindex] > Ary[Frontindex]) // 얘가 들어갈때 상관이 생긴다.
        {
            BufferAry[Bufferindex++] = Ary[Frontindex++];
            Count = Count + Remain;
        }
        else
        {
            BufferAry[Bufferindex++] = Ary[Backindex++];
        }
        Remain = Mid - Backindex + 1;
    }
    for (; Backindex <= Mid;)
    {
        BufferAry[Bufferindex++] = Ary[Backindex++];
    }
    for (; Frontindex <= End;)
    {
        BufferAry[Bufferindex++] = Ary[Frontindex++];
    }
    for (int i = 0; i < Bufferindex; i++)
    {
        Ary[Start + i] = BufferAry[i];
    }
    delete[]BufferAry;
}

void Merge(int Start, int End)
{
    if (Start >= End)
    {
        return;
    }
    int Mid = (Start + End) / 2;
    Merge(Start, Mid);
    Merge(Mid + 1, End);
    MergeSort(Start, Mid, End);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int N; cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> Ary[i];
    }
    Merge(0, N - 1);
    cout << Count;
}