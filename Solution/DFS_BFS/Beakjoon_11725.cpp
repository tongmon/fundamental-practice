#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/11725
트리의 부모 찾기 문제이다.... 문제 해석하는데 대부분의 시간이 걸렸다... 엿같은 문제
내가 문맹인건지 해석이 그렇게 안되더라... 막상 해석하고 나니 기본적인 DFS_BFS 문제였다.
그냥 밑으로 트리 탐색해가면서 각 노드들의 부모를 저장하고 출력하면 되는 문제이다.
해보니 메모리는 DFS가 왕창먹긴 하지만 DFS가 BFS보다 4ms빠르더라..
2가지 방법 모두 밑에 제시하였다.
*/

#pragma warning(disable:4996)

vector<int> Graph[100001];
bool visited[100001];

void Finder_DFS(int Starter, int* Parent)
{
    for (int i = 0; i < Graph[Starter].size(); i++)
    {
        if (visited[Graph[Starter][i]] == false)
        {
            visited[Graph[Starter][i]] = true; Parent[Graph[Starter][i]] = Starter;
            Finder_DFS(Graph[Starter][i], Parent);
        }
    }
}

void Finder_BFS(int *Parent)
{
    visited[1] = true;
    queue<int> BFS_Q;
    BFS_Q.push(1);
    int buffer;
    while (BFS_Q.empty() == false)
    {
        buffer = BFS_Q.front(); BFS_Q.pop();
        for (int i = 0; i < Graph[buffer].size(); i++)
        {
            if (visited[Graph[buffer][i]] == false)
            {
                BFS_Q.push(Graph[buffer][i]); visited[Graph[buffer][i]] = true; Parent[Graph[buffer][i]] = buffer;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int T, Vert_1, Vert_2;
    cin >> T; int* Parent = new int[T + 1];
    for (int i = 1; i < T; i++)
    {
        cin >> Vert_1 >> Vert_2;
        Graph[Vert_1].push_back(Vert_2);
        Graph[Vert_2].push_back(Vert_1);
    }
    memset(visited, false, sizeof(bool) * T);
    Finder_DFS(1, Parent);
    //Finder_BFS(Parent);
    for (int i = 2; i <= T; i++)
    {
        cout << Parent[i] << "\n";
    }
    delete[]Parent;
}