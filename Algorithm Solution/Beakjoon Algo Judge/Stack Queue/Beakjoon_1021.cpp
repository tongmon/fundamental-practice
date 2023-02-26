#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1021
큐 문제다.
큐에서 앞에서 빼고 뒤에 넣고, 아니면 뒤에서 빼고 앞에 넣고 이런 방식을
원형 큐 처럼 생각하면 풀기 원활해진다. 
연산 2, 3의 경우를 계산해서 더 적은 연산이 수행되는 연산을 실제로 진행하면 된다.
*/

int M, N, input, two, three, Cnt;
deque<int> List;

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for (int i = 1; i <= N; i++) List.push_back(i);
    for (int i = 0; i < M; i++)
    {
        two = 0; three = 1; int j = 0;
        cin >> input;
        while (List[j] != input) { two++; j++; }
        j = List.size() - 1;
        while (List[j] != input) { three++; j--; }
        j = two;
        while (two < three && j > 0)
        {
            List.push_back(List.front()); List.pop_front(); Cnt++; j--;
        }
        j = three;
        while (two >= three && j > 0)
        {
            List.push_front(List.back()); List.pop_back(); Cnt++; j--;
        }
        List.pop_front();
    }
    cout << Cnt;
}