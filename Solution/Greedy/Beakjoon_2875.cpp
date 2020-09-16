#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2875
그냥 생각없이 풀어재끼기에는 쉬운 문제다.
일단 나는 확정적인 팀을 만들고 거기서 인턴쉽에 가는 사람을 빼는데 한 팀씩 날려가면서 뺀다.
이게 방법 1이다. N번의 복잡도로 풀린다.
다른 사람의 풀이는 보니 1번의 연산으로 끝나는 방법이 있었다!
일단 여학생을 2로 나눈 값과 남학생 인원 수를 비교한다. 둘 중에 적은 수를 킵한다.
왜 적은 수를 킵하냐면 여기서 확정적으로 만들 수 있는 팀의 개수가 나온다.
여학생 + 남학생 - 인턴쉽 인원을 한 값을 3으로 나눈다. 이 값이 만약 전에 킵한 값보다 크다면 값이 아니다.
이 계산은 여학생 남학생의 비율을 따지지 않고 그냥 빼서 답을 도출하기 때문에 큰 답이 나왔다는 것은 오답이라는 것이다.
하지만 여학생 6 남학생 3 처럼 비율이 맞아지는 경우에는 인턴쉽을 빼는 것이 최선의 답을 도출하게 된다.
왜냐면 기존의 N/2, M 비교에서는 3이라는 최선의 값이 나오지만 (N + M - K) / 3에서는 더 최선의 값이 도출 되기 때문이다.
결국에 (N + M - K) / 3 이 연산은 비율을 따지지 않고 제일 큰 값을 얻어오게 되는 연산이기에 위와 같이 사용된다.
이 문제를 통해 그리디 문제 풀이에 대한 감을 조금 익혔다.
*/

#pragma warning(disable:4996)

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int N, M, K; cin >> N >> M >> K;
    int Teamed = 0;
    while (M > 0 && N > 1)
    {
        M--;
        N = N - 2;
        Teamed++;
    }
    int rest = K - (M + N);
    while (rest > 0 && Teamed > 0)
    {
        Teamed--;
        rest = rest - 3;
    }
    cout << Teamed;
}

/*
// 효율적인 방식
int main()
{
    int N, M, K, team;
    cin >> N >> M >> K;
    team = (min(M, N / 2), (N + M - K) / 3);
    cout << team << "\n";
    return 0;
}
*/