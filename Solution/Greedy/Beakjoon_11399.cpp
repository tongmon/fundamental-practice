#include <iostream>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/11399
간단한 그리디 문제다.
각 단계마다 더하게 되는 최선의 시간을 구해주면 되는데
뭐 1 3 4 3 2 이렇게 들어왔다고 하면 아무 가공도 하지 않고 더하면 1 + (1 + 3) + (1 + 3 + 4)... 이렇게 진행이되고
각 더해지는 단계마다 최선이 아니다. 왜냐하면 일단 1 + 3을 더하는 단계에서 말해보면 1 + 3보다는 주어진 수를 더하는 경우에서 1 + 2가 작을 것이다.
그러면 3 보다 뒤에 위치한 2를 앞에 땡겨와서 미리 더해주는 것이 최선의 방법을 만든다.
따라서 각 시간을 더해주는 단계마다 최선으로 작은 수를 더해가면서 진행하게 되려면 오름차순 정렬되어 있어야 한다.
오름차순 정렬하고 더해주면 답이 나온다.
이 문제는 그리디의 정석처럼 알맞은 방법으로 자료 가공하기 + 각 단계마다 최선의 선택으로 최선의 결과 도출하기를 정확하게 따르고 있다.
그리디에서 자료를 가공하는 이유는 그리디는 일단 최선의 선택을 했다하면 뒤를 돌아보지 않는다. 이 뒤를 돌아보지 않는 특성 때문에 앞으로 들어올 자료들의
특성을 미리 알 수가 있어야 최선의 선택이 가능해진다. 이를 가공(ex 정렬)을 통해서 가능하게 해주는 것이다.
이 문제를 풀면서 조금 더 그리디 알고리즘에 대한 감을 익히고 간다.
*/

#pragma warning(disable:4996)

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int N, buffer, Sum = 0; cin >> N;
    vector<int> ATM_time;
    for (int i = 0; i < N; i++)
    {
        cin >> buffer;
        ATM_time.push_back(buffer);
    }
    sort(ATM_time.begin(), ATM_time.end());
    buffer = 0;
    for (int i = 0; i < N; i++)
    {
        buffer = buffer + ATM_time[i];
        Sum = Sum + buffer;
    }
    cout << Sum;
}