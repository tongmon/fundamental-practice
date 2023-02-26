#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1107
완전탐색 문제다... 반례가 정말 많아서 까다로웠다.
초반에 완전탐색 접근법을 무시하고 매 자릿수를 확인해서 최적의 자릿수로 채워 넣는 방식으로 풀려했으나
안풀렸다... 너무 반례 케이스가 많아졌기 때문이다. 
일단 내가 풀려는 방식에 반례가 많아 질 것 같다면 완전탐색을 고려해보자.
일단 완전탐색의 기본은 말 그대로 범위가 될 수 있는 원소들을 모두 탐색하는 것이다.
0 ~ 100까지라면 for(int i = 0; i <= 100; i++) 이런식으로 말이다.
완전탐색을 풀면서 느낀 것은 일단 범위를 아는 것이 제일 중요하다.
범위를 알았다면 그 범위 안에 반례가 있는지 알아야 한다. 이 문제도 i가 0이면 결과가 다르게 나오는 반례가 있었다.
이 정도 수순으로 진행된다면 이 수준의 문제는 쉽게 풀 수 있을 것이다.
내 풀이는 난잡해서 간단한 풀이는 https://seol-limit.tistory.com/48 이 분 풀이를 참조하자.
일단 문제에 대해 설명하자면 크게 3가지를 비교해야 한다.
1. 시작 채널이 100이니 100에서 + - 버튼으로 움직여서 도착점에 도착하는 경우
2. 타켓 채널보다 작거나 같은 채널을 숫자 버튼을 눌러서 만들 수 있다면 그 채널을 만들고 + - 버튼으로 움직여서 도착점에 도착하는 경우
3. 2 경우가 반대로 위에서 진행되는 것.
이러한 경우들을 따져 봐야한다.
일단 도착점의 범위가 0 ~ 500000 까지이고 경우 3을 따져봤을 때 최대수는 1000000가 된다. 
1000000가 넘어가면 500000과 1000000의 차이가 500000을 넘어가기에 경우 2와 같이 밑에서 올라오는 녀석을 빼주는 것이 차이가 더 적게 된다.
결과적으로 0 ~ 1000000까지 만들수 있는 채널 수를 모두 구하고 구해질 때 마다 도착 채널과 계속 차이를 구해 차이가 가장 작은 녀석이 답이 될 수 있는 것이다.
이 문제를 풀면서 완전탐색 문제에 관한 접근법을 조금 익혔다.
*/

#pragma warning(disable:4996)

bool Button[10]; // true is broken

int Length(int num)
{
    if (num == 0) return 1;
    int count = 0;
    while (num > 0)
    {
        num = num / 10;
        count++;
    }
    return count;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int N, input, Channel, Channel_d, Channel_u, Max_input = 0;
    bool flag = false;
    cin >> Channel;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> input;
        Button[input] = true;
    }
    for (int i = 9; i >= 0 && N != 10; i--)
    {
        if (Button[i] == false)
        {
            Max_input = i; break;
        }
    }
    Channel_d = Channel_u = Channel;
    while (0 <= Channel_d && N != 10)
    {
        int buffer = Channel_d;
        flag = true;
        if (buffer == 0) 
        {  
            if (Button[0] == true)
            {
                Channel_d--; break;
            }
            else
            {
                break;
            }
        }
        else
        {
            while (buffer > 0)
            {
                int i;
                for (i = 0; i < 10; i++)
                {
                    if (buffer % 10 == i && Button[i] == false)
                    {
                        break;
                    }
                }
                if (i == 10)
                {
                    flag = false;
                    break;
                }
                buffer = buffer / 10;
            }
        }
        if (flag == true) break;
        Channel_d--;
    }
    flag = false;
    while (flag == false && N != 10 && Max_input != 0)
    {
        Channel_u++;
        int buffer = Channel_u;
        flag = true;
        while (buffer > 0)
        {
            int i;
            for (i = 0; i < 10; i++)
            {
                if (buffer % 10 == i && Button[i] == false)
                {
                    break;
                }
            }
            if (i == 10)
            {
                flag = false;
                break;
            }
            buffer = buffer / 10;
        }
    }
    if (Channel_u == Channel) Channel_u = 2000000;
    if (Channel_d < 0 || N == 10) Channel_d = 2000000;
    cout << min(min(abs(100 - Channel), Channel_u - Channel + Length(Channel_u)), abs(Channel - Channel_d) + Length(Channel_d));
}