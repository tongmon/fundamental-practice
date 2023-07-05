#include <iostream>
#include <unordered_map>
#include <map>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2251
문제가 헷갈려서 애먹은 문제다....
나는 한 물통이 빌 때까지 다른 물통한테 부은다는 것이 각각 나누어서 이 물통 저 물통 부울 수 있는 줄 알았는데 그게 아니였다.
그냥 a->b, b->c... 이렇게 6가지를 고려해서 BFS든 DFS든 고려해서 설계하면 풀리는 문제였다.
그리고 이게 물병 옮겨다니는걸 방문했다고 표시하기 위해서는 그냥 배열은 사용하기가 힘들어서 map을 이용하였다.
구조체를 맵 키로 사용하려면 연산자 < 를 재정의 해야한다는 것도 잊지 말자!
그리고 다른 사람의 풀이를 봤는데 이렇게 물병 옮겨다니는 걸 표현하기 위해서 이차원 bool 배열을 사용하였다!
물병 두개의 무게가 정해지면 다른 물병 하나의 무게는 알아서 정해져서 이차원 배열이고 어짜피 물병 한개 무게가 커봤자 200이라 용량도 작다.
이러한 기법을 잘 알아두자.
*/

#pragma warning(disable:4996)

typedef struct  _bot
{
    int Bot[3];
}Bottle;

bool operator<(Bottle one, Bottle two)
{
    if (one.Bot[0] == two.Bot[0])
    {
        if (one.Bot[1] == two.Bot[1])
        {
            return one.Bot[2] < two.Bot[2];
        }
        return one.Bot[1] < two.Bot[1];
    }
    return one.Bot[0] < two.Bot[0];
}

vector<int> Result;
map<Bottle, bool> Visited;
int Limit[3];

void BFS()
{
    queue<Bottle> BFSQ; Bottle Temp; int buffer;
    Temp.Bot[0] = 0; Temp.Bot[1] = 0; Temp.Bot[2] = Limit[2];
    BFSQ.push(Temp); Result.push_back(Limit[2]);
    Visited[Temp] = true;
    while (BFSQ.empty() == false)
    { 
        for (int i = 0; i < 3; i++)
        {
            for (int j = 1; j < 3 && BFSQ.front().Bot[i] != 0; j++)
            {
                if (BFSQ.front().Bot[(i + j) % 3] != Limit[(i + j) % 3])
                {
                    Temp = BFSQ.front(); buffer = BFSQ.front().Bot[(i + j) % 3] + BFSQ.front().Bot[i];
                    Temp.Bot[i] = buffer <= Limit[(i + j) % 3] ? 0 : BFSQ.front().Bot[i] - (Limit[(i + j) % 3] - BFSQ.front().Bot[(i + j) % 3]);
                    Temp.Bot[(i + j) % 3] = buffer <= Limit[(i + j) % 3] ? buffer : Limit[(i + j) % 3];
                    if (Visited.find(Temp) == Visited.end())
                    {
                        if (Temp.Bot[0] == 0) { Result.push_back(Temp.Bot[2]); }
                        Visited[Temp] = true; BFSQ.push(Temp);
                    }
                }
            }
        }
        BFSQ.pop();
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> Limit[0] >> Limit[1] >> Limit[2];
    BFS();
    sort(Result.begin(), Result.end());
    for (int i = 0; i < Result.size(); i++)
    {
        cout << Result[i] << " ";
    }
}