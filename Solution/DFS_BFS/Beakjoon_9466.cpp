#include <iostream>
#include <cstring>
#include <list>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/9466
텀 프로젝트 문제이다. 저번에 풀었던 10451 문제와 유사해보인다.
하지만 문제가 있는데 싸이클의 개수를 세는 것이 아닌 싸이클을 이루지 못하는 떨거지들의 개수를 세는 것이다....
평소 문제에서 싸이클을 구할 경우 visited에 있는 원소를 다시 방문하게 되는 경우로 체크를 했다.
이 문제는 단순히 이런 식으로 풀리지 않는다. 
일단 떨거지들의 개수를 세야 하기에 visited에 true, false 대신에 여태껏 센 정점 개수에 대한 정보가 담긴다.
그리고 다시 같은 visited 배열을 방문하게 되면 전에 기록해놨던 visited배열에 떨거지들 개수에 대한 정보를 얻을수 있다.
근데 여기서도 문제가 있다. 
만약 2 -> 1 -> 3 -> 3 이러한 3만 싸이클이 도는 그래프에서 순차적으로 1부터 DFS로 검사를 할텐데 일단 떨거지 1을 센다.
그리고 2에서 DFS를 검사하게 되면 2, 1이 떨거지가 되는데 값이 2개가 나와야 할 것이 1을 중복으로 세서 3개가 나온다.
이를 해결하려면 예전에 쓰던 visited 초기화는 물론 이미 검사한 graph 배열을 -1 이나 어떤 특정한 수로 검사를 했다는 표시를 해놓아야 한다.
이러한 케이스들을 모두 처리했다면 문제는 풀릴 것이다.
이 문제를 통해 DFS 변형에 대한 많은 정보를 습득할 수 있었다.
일단 방향성 그래프이고 한 정점에서 하나의 선만이 뻗어 나간다면 그래프는 1차원 배열로 표현이 가능하고 이 경우 DFS 내부에서는 for문 돌릴 필요없이
한방에 다음 원소로 이동이 가능하다.
그리고 그래프 순환에서 사용되는 Visited는 bool형으로 쓰일 수도 있지만 더 많은 정보를 담기위해 int형으로 쓰이고 개수에 대한 정보, 아니면 전 정점에 대한 정보
등이 담길 수가 있다.
항상 이러한 변형을 염두해 두고 문제 풀이에 임하자!
밑에는 2가지 방법이 있는데 해보니 반복이 용량으로나 속도로나 모두 효율적이였다.
*/

#pragma warning(disable:4996)

int Graph[100001]; // 확실하게 다시 방문할 일이 없다면 0으로 만들어준다.
int Visited[100001] = { 0, }; // 단순히 방문했다는 것 뿐 아니라 여태껏 센 정점 개수가 담긴다.
int Cnt = 0;

void DFS(int Starter, int Call, vector<int> *track)
{
    Graph[Call] = 0; track->push_back(Starter);
    if (Visited[Starter] == 0)
    {
        if (Graph[Starter] == 0)
        {
            Cnt = Cnt + Visited[Call]; 
            for (int i = 0; i < track->size(); i++)
            {
                Visited[track->at(i)] = 0;
            }
            track->clear();
            return;
        }
        Visited[Starter] = Visited[Call] + 1;
        DFS(Graph[Starter], Starter, track);
    }
    else
    {
        Cnt = Cnt + Visited[Starter] - 1; // 일반적인 사이클
        for (int i = 0; i < track->size(); i++)
        {
            Visited[track->at(i)] = 0;
        }
        track->clear();
    }
}

int main() // DFS로 해결
{
    ios::sync_with_stdio(false); cin.tie(0);
    int T, Vert, Num;
    vector<int> Result, Track;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        cin >> Vert; Cnt = 0;
        for (int j = 1; j <= Vert; j++)
        {
            cin >> Num;
            Graph[j] = Num;
        }
        for (int j = 1; j <= Vert; j++)
        {
            if (Graph[j] != 0)
            {
                DFS(j, 0, &Track);
            }
        }
        Result.push_back(Cnt);
    }
    for (int i = 0; i < Result.size(); i++)
    {
        cout << Result[i] << "\n";
    }
}

/*
int Graph[100001];
int Numbers[100001];

int main() // 반복으로 해결
{
    ios::sync_with_stdio(false); cin.tie(0);
    int T, Vert, Num, buffer, temp, Counter = 0;
    vector<int> Result, Track;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        cin >> Vert; Counter = 0;
        for (int j = 1; j <= Vert; j++)
        {
            cin >> Num;
            Graph[j] = Num;
        }
        for (int j = 1; j <= Vert; j++)
        {
            if (Graph[j] != 0)
            {
                buffer = Graph[j]; Graph[j] = 0;
                Numbers[j] = 1; temp = j; Track.push_back(j);
                while (true)
                {
                    if (Numbers[buffer] != 0)
                    {
                        Counter = Counter + Numbers[buffer] - 1;
                        Graph[buffer] = 0;
                        break;
                    }
                    Numbers[buffer] = Numbers[temp] + 1;
                    temp = buffer; Track.push_back(buffer);
                    buffer = Graph[buffer];
                    if (buffer == 0)
                    {
                        Counter = Counter + Numbers[temp] - 1;
                        break;
                    }
                    Graph[temp] = 0;
                }
                for (int k = 0; k < Track.size(); k++)
                {
                    Numbers[Track[k]] = 0;
                }
                Track.clear();
            }
        }
        Result.push_back(Counter);
    }
    for (int i = 0; i < Result.size(); i++)
    {
        cout << Result[i] << "\n";
    }
}
*/