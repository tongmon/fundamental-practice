#include <iostream>
#include <cstring>
#include <string>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/9019
문제를 푸는 구조를 떠올리기는 쉬우나... 시간초과와 틀림의 고통이 큰 문제다.
틀림의 고통은 L과 R의 연산에서 찾아온다.
일단 1에 L연산을 취하면 10이 되어야한다. 1이 아니라!!!
1에 R연산을 취하면 1000이 된다.... 이러한 실수를 하지 말아야하고
시간초과를 해결하는 부분에서 많은 착오가 있었다.
초반에는 덱을 이용하여 L과 R연산을 구현하였고 이는 연산시에 for문이 한번 더 돌아 많은 시간이 걸린다.
이를 없애기 위해 한번에 연산가능한 수식으로 바꾸었다.
그리고 visit 배열을 테스트 케이스 마다 초기화 할 경우에도 visit 배열의 값이 변한 녀석들을 따로 저장한 다음에
그 저장된 녀석들만 초기화 해주는 방식을 사용하였다. 
또 BFS에서 종료점을 검색할 때 보통은 코드를 간결하게 하기 위해 큐에서 원소를 빼서 볼 경우에 검사를 하는데
이 문제는 시간이 빡빡하여 큐에 원소를 삽입할 경우에 확인한다.
이러니 문제가 풀렸다.
다른 사람 풀이를 보니... 역시나 내 풀이는 비효율의 극치였다... 
아직 밑의 내 풀이에서 최적화를 할 껀덕지가 많이 남아있다.
일단 LR연산 자체를 그냥 통틀어서 식 하나로 퉁칠 수가 있었다.
일단 L연산 : curNum = (num % 1000) * 10 + num / 1000;
R연산 : curNum = (num % 10) * 1000 + (num / 10);
그리고 나는 Visited 배열에 string 형으로 DSLR 명령들을 차곡차곡 쌓아가는 방식으로 풀었는데
Visited 배열에 부모값을 넣어 부모로 거슬러 올라가는 방식으로 출력하는 방법이 있었다.
마치 유니온 파인드를 쓰는 것과 같은 이 방법을 사용하면 초기화시에 오버헤드가 줄어들고 코드까지 간결해진다!
최적화가 모두 완료된 풀이방법으로 다시 풀었다. 2188ms에서 740ms로 비약적으로 속도가 상승했다.
다른 사람 풀이를 보면서 보고 느끼게된 테크닉들을 잘 사용하기 바란다.
*/

#pragma warning(disable:4996)

int Visited[10000];
char Order[10000];
string Output;

void BFS_improved(int start, int end)
{
    if (start == end) return;
    queue<int> BFSQ; int buffer, Front;
    BFSQ.push(start); Visited[start] = -2;
    while (BFSQ.empty() == false)
    {
        Front = BFSQ.front();
        buffer = (Front * 2) % 10000;
        if (Visited[buffer] == -1)
        {
            Visited[buffer] = Front; BFSQ.push(buffer);
            Order[buffer] = 'D';
            if (buffer == end) return;
        }
        buffer = Front <= 0 ? 9999 : Front - 1;
        if (Visited[buffer] == -1)
        {
            Visited[buffer] = Front; BFSQ.push(buffer);
            Order[buffer] = 'S';
            if (buffer == end) return;
        }
        buffer = (Front % 1000) * 10 + Front / 1000;
        if (Visited[buffer] == -1)
        {
            Visited[buffer] = Front; BFSQ.push(buffer);
            Order[buffer] = 'L';
            if (buffer == end) return;
        }
        buffer = (Front % 10) * 1000 + Front / 10;
        if (Visited[buffer] == -1)
        {
            Visited[buffer] = Front; BFSQ.push(buffer);
            Order[buffer] = 'R';
            if (buffer == end) return;
        }
        BFSQ.pop();
    }
    return;
}

void Print(int End)
{
    int index = End;
    while (Visited[index] != -2)
    {
        Output.push_back(Order[index]);
        index = Visited[index];
    }
    reverse(Output.begin(), Output.end());
    cout << Output << "\n";
    Output.clear();
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T, start, end; cin >> T;
    memset(Visited, -1, 10000 * sizeof(int));
    for (int i = 0; i < T; i++)
    {
        cin >> start >> end;
        BFS_improved(start, end);
        Print(end);
        memset(Visited, -1, 10000 * sizeof(int));
    }
}

/*
// 최적화 진행 전 비효율적인 풀이
string Visited[10000];
vector<int> Clear_index;

int D(int Num)
{
    return (Num * 2) % 10000;
}

int S(int Num)
{
    if (Num == 0) return 9999;
    return Num - 1;
}

void LR(int Num, int *Left, int *Right)
{
    if (Num == 0)
    {
        *Left = 0; *Right = 0; return;
    }
    int Count = 0, front = 0, back = 0, Origin = Num, Ten = 1;
    while (Num > 0)
    {
        if (Num == Origin) back = Num % 10;
        front = Num % 10;
        Count++;
        Num = Num / 10;
        Ten = Ten * 10;
    }
    if (Count < 4)
    {
        *Left = Origin * 10;
        *Right = (10000 * back + Origin - back) / 10; return;
    }
    *Left = (Origin - front * Ten / 10) * 10 + front;
    *Right = (Origin - back + Ten * back) / 10;
}

void BFS(int start, int end)
{
    if (start == end) return;
    queue<int> BFSQ; int buffer, Front, Left, Right;
    BFSQ.push(start);
    while (BFSQ.empty() == false)
    {
        Front = BFSQ.front();
        if (Visited[buffer = D(Front)].empty() == true && start != buffer)
        {
            Visited[buffer] = Visited[Front] + 'D'; BFSQ.push(buffer); Clear_index.push_back(buffer);
            if (buffer == end) return;
        }
        if (Visited[buffer = S(Front)].empty() == true && start != buffer)
        {
            Visited[buffer] = Visited[Front] + 'S'; BFSQ.push(buffer); Clear_index.push_back(buffer);
            if (buffer == end) return;
        }
        LR(Front, &Left, &Right);
        if (Visited[buffer = Left].empty() == true && start != buffer)
        {
            Visited[buffer] = Visited[Front] + 'L'; BFSQ.push(buffer); Clear_index.push_back(buffer);
            if (buffer == end) return;
        }
        if (Visited[buffer = Right].empty() == true && start != buffer)
        {
            Visited[buffer] = Visited[Front] + 'R'; BFSQ.push(buffer); Clear_index.push_back(buffer);
            if (buffer == end) return;
        }
        BFSQ.pop();
    }
    return;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T, start, end; cin >> T;
    vector<string> Result;
    for (int i = 0; i < T; i++)
    {
        cin >> start >> end;
        BFS(start, end);
        Result.push_back(Visited[end]);
        for (int i = 0; i < Clear_index.size(); i++)
        {
            Visited[Clear_index[i]].clear();
        }
        Clear_index.clear();
    }
    for (int i = 0; i < T; i++)
    {
        cout << Result[i] << '\n';
    }
}
*/