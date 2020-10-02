#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1759
전형적인 DFS 문제로 Total을 정렬하고 그에 따라 한 글자씩 재귀적으로 선택해 나가는 방식으로 풀었다.
처음엔 삼중for문을 돌리던지 하는 개뻘짓을 했었는데 그냥 DFS가 머릿속을 한번 스쳐가지고 DFS로 방향을 틀었다...
3중for문 같은 개뻘짓 조차 생각나지 않도록 좀 더 실력을 길러야겠다.
그리고 일단 순열, 조합 같은 냄새가 문제에서 풍겨져 나온다면 그냥 재귀쓸 생각해라.
그냥 바로 냅다 for문 갈기지 말고....
*/

#pragma warning(disable:4996)

int L, C;
string Total, Buffer;

void DFS(int L, int ConCnt, int VowCnt, int start)
{
    if (L == 0)
    {
        if (ConCnt >= 1 && VowCnt >= 2) cout << Buffer <<'\n';
        return;
    }
    for (int i = start; i < Total.size(); i++)
    {
        Buffer.push_back(Total[i]);
        if (Total[i] == 'a' || Total[i] == 'e' || Total[i] == 'i' || Total[i] == 'o' || Total[i] == 'u') DFS(L - 1, ConCnt + 1, VowCnt, i + 1);
        else DFS(L - 1, ConCnt, VowCnt + 1, i + 1);
        Buffer.pop_back(); 
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> L >> C; 
    char input;
    for (int i = 0; i < C; i++)
    {
        cin >> input;
        Total.push_back(input);
    }
    sort(Total.begin(), Total.end());
    DFS(L, 0, 0, 0);
}