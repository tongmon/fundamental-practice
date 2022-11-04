#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1261
BFS 응용 문제이다.
보통 BFS 응용 문제에서는 기존 BFS에서 그냥 큐를 쓰게 되는 것과 달리 deque, 우선순위 큐가 사용된다.
이 문제도 보통의 응용문제와 같이 덱, 우선순위 큐를 사용해서 풀 수 있다.
기존 BFS는 모든 노드를 탐색해야 하기에 그냥 규칙이 없는 큐를 사용하게 되는데 이러면 답 도출이 안된다.
그냥 시작점에서 끝점까지의 최단거리는 구할 수 있겠지만 어떤 가중치가 붙게 되면 이 가중치에 대한 최대, 최소는 구하지 못한다.
즉 노드를 재방문 해야 되는 경우가 있기 때문에 가중치에 대한 고려를 하지 못한다.
그러면 DFS로 완전 탐색을 진행하게 되면 될까? 이 경우 맵에서 가능한 모든 경우의 수가 다 나오기 때문에 가능은 하다.
근데 시간복잡도가 100 x 100 맵으로 가게 되면 미쳐날뛴다.... 어떤 중간에 중단하는 조건을 붙이더라도 1초안에 계산할 수 없다.
그렇다면 다시 해결법으로 돌아와서 우선순위 큐는 항상 최대 or 최소가 맨 위에 위치하기에 가중치를 고려할 수 있다.
목표 지점에 다다르면 결과가 위에서 자동으로 튀어 나와주기 때문이다. 
게다가 자신이 원하는 가중치에 가까운 녀석들이 맨위에 맨날 올라와 있고 이 녀석들만 고려하기에 시간도 안걸린다.
덱은 우선 순위 큐와 비슷한데 얘도 목표 가중치에 가까운 녀석들은 항상 front에 위치해 있다.
물론 이렇게 만드려면 삽입시에 고려를 해야하는데 front의 가중치보다 큰 녀석들은 뒤로 back에 넣는다.
front 가중치와 이동 후에도 같은 녀석들은 front에 넣는다. 이를 반복하면 우선 순위 큐와 비슷한 효과를 가지게 되고 답이 도출된다.
단, deque 사용시 주의 점은 가중치가 일정하게 증가하는 경우만 된다. 어떤 때는 100, 어떤 때는 2 이렇게 불규칙성을 띄면 편하게 우선순위 큐 사용해라
시작 점에서 어떤 노드던 최대, 최소 가중치 값이 들어가게되는 다익스트라도 사용할 수 있다. 
다익스트라는 자료구조 알고리즘에 나온 방식을 빼다 박기에 설명은 생략한다.
이 문제를 풀면서 BFS를 변형 시키는 문제에 대한 감을 잡아간다.
*/

char Ary[101][101];
short Width, Height, Dir[4][2] = { {-1,0}, {0,-1}, {1,0}, {0,1} }, Count = 0;
bool Visited[101][101];

typedef struct _Ca
{
    char Col, Row; short W;
}Weight;

bool operator>(Weight A, Weight B)
{
    if (A.W > B.W) return true;
    return false;
}

bool is_Vailed(char Col, char Row)
{
    if (0 <= Col && Col < Height && 0 <= Row && Row < Width) return true;
    return false;
}

void BFS_pri() // 우선순위 큐
{
    if (Width == 1 && Height == 1) return;
    priority_queue<Weight, vector<Weight>, greater<Weight>> BFSQ; char bCol, bRow;
    Visited[0][0] = true; BFSQ.push({ 0,0,0 });
    while (BFSQ.empty() == false)
    {
        for (short i = 0; i < 4; i++)
        {
            bCol = BFSQ.top().Col + Dir[i][0]; bRow = BFSQ.top().Row + Dir[i][1];
            if (is_Vailed(bCol, bRow) && Visited[bCol][bRow] == false)
            {
                Visited[bCol][bRow] = true;
                if (bCol == Height - 1 && bRow == Width - 1) { Count = BFSQ.top().W; return; }
                if (Ary[bCol][bRow] == '1') BFSQ.push({ bCol, bRow, BFSQ.top().W + 1 });
                else BFSQ.push({ bCol, bRow, BFSQ.top().W });
            }
        }
        BFSQ.pop();
    }
}

void BFS_deck() // 덱
{
    if (Width == 1 && Height == 1) return;
    deque<Weight> BFSQ; char bCol, bRow; Weight Front;
    Visited[0][0] = true; BFSQ.push_front({ 0,0,0 });
    while (BFSQ.empty() == false)
    {
        Front = BFSQ.front(); BFSQ.pop_front();
        for (short i = 0; i < 4; i++)
        {
            bCol = Front.Col + Dir[i][0]; bRow = Front.Row + Dir[i][1];
            if (is_Vailed(bCol, bRow) && Visited[bCol][bRow] == false)
            {
                Visited[bCol][bRow] = true;
                if (bCol == Height - 1 && bRow == Width - 1) { Count = Front.W; return; }
                if (Ary[bCol][bRow] == '1') BFSQ.push_back({ bCol, bRow, Front.W + 1 });
                else BFSQ.push_front({ bCol, bRow, Front.W });
            }
        }
    }
}

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);   
    cin >> Width >> Height;
    for (int i = 0; i < Height; i++)
    {
        for (int j = 0; j < Width; j++)
        {
            cin >> Ary[i][j];
        }
    }
    BFS_deck(); cout << Count;
}