#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1966
큐 문제에서 우선순위 큐를 약간 섞어놓은 문제이다.
현재 큐에 있는 값 중에 가장 큰 중요도에 대한 정보가 필요하기에 입력 받는 족족 우선순위 큐에 중요도를 박아놓으면
편하다. 알아서 중요도 제일 큰 값이 몇인지 알 수 있기 때문
*/

#pragma warning(disable:4996)

typedef struct _doc
{
    int ID, Priority;
}Document;

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int T, File_Num, Target, Import, Count = 0;
    vector<int> Result;
    Document buffer;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        priority_queue<int> Pri; 
        queue<Document> DocQ; 
        Count = 0;
        cin >> File_Num >> Target;
        for (int j = 0; j < File_Num; j++)
        {
            cin >> Import;
            buffer.ID = j; buffer.Priority = Import; 
            Pri.push(Import);
            DocQ.push(buffer);
        }
        while (true)
        {
            if (Pri.top() > DocQ.front().Priority)
            {
                buffer = DocQ.front(); DocQ.pop();
                DocQ.push(buffer);
            }
            else // 인쇄 되는 경우
            {
                if (DocQ.front().ID == Target)
                {
                    break;
                }
                Pri.pop(); DocQ.pop(); Count++;
            }
        }
        Result.push_back(Count + 1);
    }
    for (int i = 0; i < Result.size(); i++)
    {
        cout << Result[i] << "\n";
    }
}