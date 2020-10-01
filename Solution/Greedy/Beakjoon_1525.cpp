#include <iostream>
#include <unordered_map>
#include <string>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
#include <time.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1525
완전탐색 문제인데 구현이 빡세서 골드2에 있는 것 같다....
일단 BFS로 탐색을 진행하는데 입력이 3x3의 격자식 데이터다.
그런데 32mb의 빡빡한 메모리 제한이 있으므로 편하게 이차원배열을 일차원배열처럼 사용하는 방식을 차용했다.
일단 visited는 해쉬맵으로 만들어 필요한 최소한의 용량만 사용하고 탐색시 배열처럼 한방에 찾고 있게 하였다.
자료형은 어떻게 만들었냐면 string형 10자리로 앞 9자리는 격자를 일차원으로 펼쳐놓은 값들이고 마지막은 0이 있는 자리를 가리키는 익덱스가 char형으로 저장된다.
예를들어
123
456
780
이러한 격자는 1234567808 이렇게 0이 8번째 있다는 사실까지 같이 저장된다.
이러한 변환을 할 때 중요한 점은 좌표를 움직여줄 때 행과 열 인덱스 기준으로 더해지기 때문에 
이차원을 일차원으로 하는 3 * i + j 나 그 반대인 i / 3, j % 3과 같은 변환 연산이 사용된다.
이를 유의하면 문제가 풀린다.
다른 사람의 풀이를 보니 용량을 더 아끼려고 인덱스를 int 형으로 선언하여 풀었는데 이러면 0의 위치를 매번 탐색해야 하기에 속도가 더 느려진다.
내 방식은 용량이 약간 늘어나더라도 속도는 빨라진다.
이 문제를 통해 이차원 <--> 일차원 배열로의 인덱스 변환에 대해 약간 더 익숙해졌다.
*/

#pragma warning(disable:4996)

string Init;
unordered_map<string, char> Visited;
char Dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} }, Index;

bool is_Vailed(char Zcol, char Zrow)
{
    if (0 <= Zcol && Zcol < 3 && 0 <= Zrow && Zrow < 3)
    {
        return true;
    }
    return false;
}

int BFS_string()
{
    string buffer; char Col, Row;
    queue<string> BFSQ; BFSQ.push(Init); Visited[Init] = 0;
    while (BFSQ.empty() == false)
    {
        buffer = BFSQ.front(); Col = (buffer.back() - '0') / 3; Row = (buffer.back() - '0') % 3;
        if (buffer == "1234567808") return Visited["1234567808"];
        for (char i = 0; i < 4; i++)
        {
            if (is_Vailed(Col + Dir[i][0], Row + Dir[i][1]) == true)
            {
                char index = (Col + Dir[i][0]) * 3 + Row + Dir[i][1];
                swap(buffer[buffer.back() - '0'], buffer[index]); buffer.pop_back(); buffer.push_back(index + '0');
                if (Visited.find(buffer) == Visited.end())
                {
                    Visited[buffer] = Visited[BFSQ.front()] + 1; BFSQ.push(buffer);
                }
                buffer.pop_back(); buffer.push_back(BFSQ.front().back()); swap(buffer[buffer.back() - '0'], buffer[index]);
            }
        }
        BFSQ.pop();
    }
    return -1;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    char input;
    for (int i = 0; i < 9; i++)
    {
        cin >> input; Init.push_back(input);
        if (input == '0') Index = i;
    }
    Init.push_back(Index + '0');
    cout << BFS_string();
}