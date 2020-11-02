#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/6198
스택 문제다.
저번에 송신탑 문제에서 삽질한게 도움이 되었는지 푸는데 큰 어려움이 없었다.
문제가 약간 아리송할 수 있는게 높이가 자신 보다 높은 녀석, 같은 녀석의 옥상은 보지 못한다.
같은 녀석도 보지 못한다는 것이 좀 특이했다.
그리고 Sum 값이 long long이 아니면 오버플로우가 난다는 것도 유의해야 한다.
항상 오버플로우를 고려해보자....
방식은 스택에 받은 녀석을 넣는데 넣기 전에 자신보다 값이 작거나 같은데 스택에 있는 놈들은 뺀다.
남은 원소 수 만큼 Sum 값에 더해준다.
왜냐하면 작은놈들을 모두 거르고 나면 자신보다 큰 녀석들만 스택에 있을 텐데 얘네는 모두 자신을 위에서 쳐다볼 수 있는 녀석들이기에 
이런 녀석들의 수를 Sum에 추가하는 것이다.
그리고 작거나 같은 녀석들은 빼는 이유는 이미 이런 녀석들은 삽입시에 계산이 끝난 상태이기에 빼도 상관이 없다.
이 문제를 통해 스택 활용도를 높여간다.
*/

int N, num;
long long Sum;
stack<int> Height;

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> num;
        while (!Height.empty() && Height.top() <= num) Height.pop();
        Sum = Sum + Height.size();
        Height.push(num);
    }
    cout << Sum;
}