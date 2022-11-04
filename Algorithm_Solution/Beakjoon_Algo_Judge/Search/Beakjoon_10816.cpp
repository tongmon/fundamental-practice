#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/10816
숫자카드1과 같은 문제지만 이번엔 있는지 유무가 아닌 있으면 그 카드의 개수를 반환해야 한다.
탐색하여 같은 카드가 있을 경우 그 개수를 알려면 2가지 방법이 있다. (일단 탐색은 속도 때문에 기본 이진 탐색을 깔고 간다.)
map을 이용하여 키를 카드의 번호로 하고 개수를 그 값으로 해서 찾으면 map[카드번호]로 반환하는 방법
다른 방법은 어짜피 정렬이 되어 있고 같은 카드 번호가 여러번 나왔다면 그러니까 1 3333 4 이런 식이면 낮은 위치에 있는 3의 인덱스에서 4의 인덱스를 빼주면 
3의 개수가 도출될 것이다. 이것을 해주는 것이 C++ stl에 있는 lower_bound, upper_bound 이다.
lower_bound 는 정렬되어 있는 배열에서 최초로 등장한 지정된 숫자의 인덱스 값을 이진 탐색하여 도출한다. lower_bound(v.begin(), v.end(), num)
upper_bound 는 정렬되어 있는 배열에서 최초로 선택된 숫자에 어긋난 인덱스 값을 반환한다. 1 3 3 4 에서 upper_bound(v.begin(), v.end(), 3)을 하면 숫자4의 위치인 3이 도출된다.
그리고 위 설명에는 bound 함수가 인덱스를 반환하는 것처럼 쓰여있는데 벡터에서 인덱스를 bound 함수로 반환받고 있으면 항상 v.begin()을 빼주어야 한다.
그니까 lower_bound(v.begin(), v.end(), num) - v.begin() 이렇게 써야 인덱스로 반환이 된다.
만약 bound 함수에서 지정된 찾는 값이 없다면 맨 마지막 인덱스가 반환된다.
설명은 https://modoocode.com/298 여기가 자세하다.
map을 쓰는 방식보다 bound함수를 쓰는 방식이 더 효율적이다.
밑의 방식은 내가 풀었던 map을 이용한 방식이다.
이 문제를 통해 bound 쓰는 방법을 익히고 간다.
*/

#pragma warning(disable:4996)

int Card_N = 0;
vector<int> Cards, Result;
map<int, int> Counter;

int is_Card(int N)
{
    int Low = 0, High = Card_N - 1, Mid;
    while (Low <= High)
    {
        Mid = (Low + High) / 2;
        if (Cards[Mid] < N)
        {
            Low = Mid + 1;
        }
        else if (Cards[Mid] > N)
        {
            High = Mid - 1;
        }
        else
        {
            return Counter[N];
        }
    }
    return 0;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int Number, is_Card_N, Number_2 = 10000001;
    cin >> Card_N;
    for (int i = 0; i < Card_N; i++)
    {
        cin >> Number;
        if (Counter.find(Number) == Counter.end())
        {
            Counter[Number] = 1;
        }
        else
        {
            Counter[Number]++;
        }
        Cards.push_back(Number);
    }
    sort(Cards.begin(), Cards.end());
    cin >> is_Card_N;
    for (int i = 0; i < is_Card_N; i++)
    {
        cin >> Number;
        Result.push_back(is_Card(Number));
    }
    for (int i = 0; i < is_Card_N; i++)
    {
        cout << Result[i] << " ";
    }
}