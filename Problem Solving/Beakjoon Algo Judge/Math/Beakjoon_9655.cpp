#include <iostream>
using namespace std;

/*
https://www.acmicpc.net/problem/9655
먼저 시작하는 사람이 있고 승자가 숫자에 따라 정해져버리는 게임이기에 수학적으로 접근할 수 있다.
일단 1개 아니면 3개 돌을 집을 수 있으니 돌을 최대한 빨리 사라지게 각 사람이 3개씩 집어서 없애버리고 나머지는 3을 나눈 개수가 무조건 나온다.
결과적으로 특정 수를 3으로 나눈 몫하고 나머지를 더한 값에 의해 승자를 예측할 수 있다.
*/

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int N;
	cin >> N;
	cout << ((N / 3 + N % 3) % 2 ? "SK" : "CY");
	return 0;
}