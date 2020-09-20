#include <iostream>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1931
실수를 오지게 남발한 문제.... 물론 끝끝내 풀긴했지만 그리 좋은 풀이는 아닌 것 같다.
일단 문제 자체는 그리디 알고리즘에 매우 충실하고 있어서 매 순간에 최선을 다 해서 시간이 딱딱 맞는 
회의 들을 골라내면 된다.
일단 그리디 알고리즘 자체를 접근하는 방법부터 생각해보자.
일단 회의는 시작 시간, 끝 시간이 존재 한다. 그리고 시작 시간과 끝 시간의 차이도 존재하게 된다.
보통 최선의 수를 고르기 위해선 정렬을 수행하는 것이 기본이다.
왜냐하면 정렬을 하지 않고 최선의 수를 고른다면 N*N의 시간 복잡도가 생기기 때문이다.
이 문제는 다행이 시작 시간으로 정렬하나 끝 시간으로 정렬하나 모두 풀린다. 차이로 정렬할 경우는 안해봐서 모르겠다;;
나는 시작 시간으로 정렬을 했고 풀기는 하였으나 예외 상황이 굉장히 많이 발생하여서 애를 먹었다..
일단 시작 시간 정렬로 푸는 경우는 시작 시간으로 정렬하되 시작 시간이 같으면 끝 시간이 작은 것이 앞에 놓여야 한다.
그리고 이렇게 놓이면 특정한 경우를 제외하고 시작 시간이 같은 놈들 중에서 몇 놈만 뽑힌다. 이유는 밑의 설명을 읽어보면 알게된다. 
이렇게 정렬되어 있는 상황에서 첫 원소는 일단은 무조건 들어가야하는 최선의 시간을 가진 회의가 된다. 
물론 후에 바뀔 수도 있다. 이 바뀌는 조건은 이런 것이다 예를 들어 1,4의 회의가 첫빠따로 정렬이 되어있었는데 다음에 등장한 2,3 회의가 더 매력적이다.
왜냐하면 회의들이 (1,4) (2,3) (3,5) 인 경우를 생각해보면 답이 나온다. 결국 시작이 빠르더라도 끝나는 시간이 겁나 느린 녀석들을 쳐내야 한다. 
일단 이렇게 끝시간을 비교해야 한다는 조건을 알았다.
이러한 상황도 생긴다. (1,1) (1,2) (2,2) 일단 1,1을 진행 한 후에 1,2도 들어가야 한다. 시작 시간으로 정렬을 했기에 같은 시작 시간을 가진 놈들은
엥간하면 같이 공존할 수 없지만 (1,1) (1,1) 이렇게 시작과 끝이 같은 놈들이나 (1,1) (1,2) 이렇게 시작과 끝나고 다음에 끝시간이 큰놈이 나오면 공존이 가능하다.
이러한 예외상황들을 모두 제끼고 정상적으로 끝시간 회의보다 크거나 같은 회의가 나오게되면 예를 들어 (1,2) (2,5) 이러한 경우는 회의에 추가 시키면된다.
위 처럼 복잡한 풀이말고 다른 사람은 간단하게 풀었다.... 바로 끝나는 시간으로 정렬하면 고려할 것이 적어진다.
일단 들어온 회의들을 끝나는 시간으로 정렬하되 끝나는 시간이 같으면 시작 시간이 빠른 녀석이 앞에 위치하게 만든다.
이렇게 정렬이 되면 확정적으로 정렬된 배열 맨 앞부분은 최적의 회의 값이 된다. 첫번째 방식과 다르게 바뀔 일이 없다.
그 다음에 끝난 시간보다 다음 회의 시작시간이 크거나 같은지 확인하고 맞다면 다시 그 회의의 끝나는 시간을 기준으로 다음 회의들을 확인한다.
이렇게 최선의 선택을 계속해서 진행하며 개수를 세면 답이 도출된다. 내가 푼 방법보다 훨씬 간단하고 오류도 적어진다.
이 문제를 통해 그리디한 방법을 접근하고 그에 따른 정렬 방식, 최적화 방식을 정하는 감에 대해 익히고 간다.
*/

#pragma warning(disable:4996)

typedef struct _mapi
{
    unsigned int start = 0, end = 0;
}Confer;

bool operator<(Confer A, Confer B)
{
    if (A.start == B.start)
    {
        return A.end < B.end;
    }
    return A.start < B.start;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    vector<Confer> Sorted, Candiate;
    int N; cin >> N;
    Confer buffer;
    for (int i = 0; i < N; i++)
    {
        cin >> buffer.start >> buffer.end;
        Sorted.push_back(buffer);
    }
    sort(Sorted.begin(), Sorted.end());
    Candiate.push_back(Sorted[0]);
    for (int i = 1; i < N; i++)
    {
        if (Candiate.back().start == Sorted[i].start)
        {
            if (Sorted[i].start == Sorted[i].end) // 시작하자마자 끝나는 경우
            {
                Candiate.push_back(Sorted[i]);
            }
            else if(Sorted[i].end > Candiate.back().end)
            {
                if (Candiate.back().start == Candiate.back().end)
                {
                    // 시작하자마자 끝나는 경우가 바로 전 회의였고 그래서 이번엔 시작하자마자 끝나지 않는 회의가 들어가게 된다.
                    Candiate.push_back(Sorted[i]);
                }
            }
        }
        else if (Candiate.back().start != Sorted[i].start)
        {
            if (Candiate.back().end <= Sorted[i].start)
            {
                Candiate.push_back(Sorted[i]);
            }
            else // 바뀌는 경우
            {
                if (Sorted[i].end < Candiate.back().end)
                {
                    Candiate.pop_back();
                    Candiate.push_back(Sorted[i]);
                }
            }
        }
    }
    cout << Candiate.size();
}