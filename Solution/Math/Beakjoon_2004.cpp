#include <iostream>
#include <cstring>
#include <list>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2004
팩토리얼 응용 문제이다.
이 문제는 진짜.... 무친듯이 알고리즘이 조금의 차이로 얼마나 효율성이 갈릴 수 있는지 알려주는 문제다.
일단 예를 N까지의 수들을 모두 곱했을 경우 5의 개수는 몇 개일까?
간단하게 생각해보면 N!을 모두 한 수를 구하고 그 수를 5를 나누어가면서 셀 수 있을 것이다. 근데 N이 엄청 커지면 가능한가?
담을 수 있는 정수형이 없어 불가능하다. 
그리고 엄청난 for문의 루프로 굉장히 느려질 것이다. 이를 해결하려면 트릭이 필요한데 일단 모두 곱한 수를 구할 필요가 없다.
그 자리에서 5로 나누면서 개수를 세주면 되니까. 근데 이것도 이중for문이다. 속도가 느릴 것이다.
더 빠르게 하는 방법이 있다.
일단 어떤 수에서 5를 나누면 그 전에 있던 5배수들의 개수가 모두 찍힌다. 예를 들어 25를 5로 나누면 5가 나오는데 5 10 15 20 25 이렇게 찍힌다.
26도 동일 그럼 25 이하인 5배수들의 5개수는 5개가 끝인가? 아니다. 25는 5가 2개다 총 6이 나와야 한다.
그럼 1개는 어떻게 구할까? 25를 25로 나누면 되는 것이다. 계속해서 큰 수도 똑같이 돌아간다.
624이하의 수들의 5의 개수는 몇개일까? 5로 나누고, 25로 나누고 125로 나누고 625는 624를 넘어가니까 끝.
이 수들을 모두 더해주면 답이 나온다. 정말 천재적이다.....
공부 열심히 하자 경준아
*/

#pragma warning(disable:4996)

unsigned long long Combinatorial(unsigned int N, unsigned int M)
{
    if (N == M || M == 0 || N == 0)
    {
        return 0;
    }
    unsigned long long Nfive = 0, Mfive = 0, NMfive = 0;
    unsigned long long Ntwo = 0, Mtwo = 0, NMtwo = 0;
    for (unsigned long long i = 5; i <= N; i = i * 5) // N까지 수 중에서 5의 배수, 25의 배수, 125의 배수... 들을 찾는 즉 5의 개수를 찾는 방법
    {
        Nfive = Nfive + N / i;
    }
    for (unsigned long long i = 5; i <= M; i = i * 5)
    {
        Mfive = Mfive + M / i;
    }
    for (unsigned long long i = 5; i <= N - M; i = i * 5)
    {
        NMfive = NMfive + (N - M) / i;
    }
    for (unsigned long long i = 2; i <= N; i = i * 2) // 똑같이 2의 개수도 세어준다.
    {
        Ntwo = Ntwo + N / i;
    }
    for (unsigned long long i = 2; i <= M; i = i * 2)
    {
        Mtwo = Mtwo + M / i;
    }
    for (unsigned long long i = 2; i <= N - M; i = i * 2)
    {
        NMtwo = NMtwo + (N - M) / i;
    }
    Nfive = Nfive - Mfive - NMfive; Ntwo = Ntwo - Mtwo - NMtwo;
    return Nfive > Ntwo ? Ntwo : Nfive;
}

int Com(unsigned int N, unsigned int M) // 무식하게 이중포문으로 푸는법.... 시간초과가 난다.
{
    if (N == M || M == 0 || N == 0)
    {
        return 0;
    }
    unsigned int Smallone = N - M > M ? M : N - M;
    unsigned int i = N - Smallone + 1, buffer = i, Nfive = 0, Mfive = 0;
    while (i != N + 1)
    {
        buffer = i;
        while (buffer % 5 == 0)
        {
            Nfive++; buffer = buffer / 5;
        }
        i++;
    }
    i = 1;
    while (i != Smallone + 1)
    {
        buffer = i;
        while (buffer % 5 == 0)
        {
            Mfive++; buffer = buffer / 5;
        }
        i++;
    }
    return Nfive - Mfive;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    unsigned int N, M; 
    cin >> N >> M;
    cout << Combinatorial(N, M);
}