#include <iostream>
#include <unordered_map>
#include <string>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2186
진짜 존내 어려웠다.... 결국 풀이를 봤지만 어짜피 내 힘으로 풀지 못할 문제였다... 고민 작작하고 좀 더 빨리 볼 걸.... 플레 문제보다 오래걸렸네
일단 처음에 로직을 짜긴했다. visited를 맵으로 구현하고 키를 다녀오게되는 경로가 저장된 string으로 하는 예를 들면 
(0,1) -> (2,1) 이라면 키가 0|1|2|1| 이런식으로 저장이 된다. 이렇게 하고 순회하는데 전달해야되는 정보가 많아서 구조체로 묶어 BFS로 돌릴까
아니면 DFS로 매개변수로 전달할까 고민하다가 그냥 DFS가 편해보여서 DFS로 진행했고 메모리초과로 Fail.....
결국 3시간 삽질하다가 풀이를 봤는데 DP와 DFS 혼합 문제였다!
일단 기존의 visited와 성향이 다르다! 왔던 곳을 또 올 수 있는 문제의 특성을 반영해야 한다.
(0,1) -> (2,1) -> (1,1) -> (2, 2)의 경로로 가서 단어를 완성시킬수 있다고 해보자.
(0,0) -> (0,1) -> (1,1) -> (2, 2)의 경로를 다음 DFS가 처리하려한다.
근데 굳이 (1,1) -> (2,2) 이 중복되는 곳을 거쳐야 할까? Dp의 메모제이션을 사용하면 그럴 필요가 없다.
따라서 이 Visited[i][j][k]의 배열은 어떤 격자 i, j를 선택하고 그 때가 목표 단어의 k번째를 탐색하게 되면 거기서 뻗어나갈 수 있는 경우의 가지 수가 저장된다.
이렇게 뻗어나가는 가지수를 알아야하는 경우에 재귀함수가 복귀하면서 DP가 저장되기 때문에 DFS 함수는 값을 반환하게 된다.
이러한 테크닉과 사고방식을 기억하자.
그리고 일단 격자 모양에서 DP 배열을 만들 경우에 Dp[][][?] 이러한 모양을 구상해보자.
DFS와 Dp가 혼합된 문제 유형이 처음이였는데 이 해답을 통해 감을 조금 잡았다...
*/

#pragma warning(disable:4996)

int Width, Height, Jump, Count = 0, Dir[4][2] = { {1, 0},{0, -1},{0, 1},{-1, 0} };
string Target;
int Visited[101][101][81];
char Board[101][101];

bool is_Vailed(int Col, int Row)
{
    if (0 <= Col && Col < Height && 0 <= Row && Row < Width)
    {
        return true;
    }
    return false;
}

int DFS(int Col, int Row, int Num)
{
    if (Target.size() == Num) return 1;
    if (Visited[Col][Row][Num] != -1) return Visited[Col][Row][Num];
    int bCol, bRow; 
    Visited[Col][Row][Num] = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 1; j < Jump + 1; j++)
        {
            bCol = Col + Dir[i][0] * j; bRow = Row + Dir[i][1] * j;
            if (is_Vailed(bCol, bRow) == true && Board[bCol][bRow] == Target[Num])
            {
                Visited[Col][Row][Num] = Visited[Col][Row][Num] + DFS(bCol, bRow, Num + 1);
            }
        }
    }
    return Visited[Col][Row][Num];
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> Height >> Width >> Jump;
    for (int i = 0; i < Height; i++)
    {
        for (int j = 0; j < Width; j++)
        {
            cin >> Board[i][j];
        }
    }
    cin >> Target; memset(Visited, -1, sizeof(Visited));
    for (int i = 0; i < Height; i++)
    {
        for (int j = 0; j < Width; j++)
        {
            if (Target.front() == Board[i][j])
            {               
                Count = Count + DFS(i, j, 1);
            }
        }
    }
    cout << Count;
}