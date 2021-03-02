#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12977
소수 만들기 문제.
주어진 숫자 중에 3개를 골라 그것이 소수인지 아닌지 반별하면 된다.
3개 고르는 방법은 재귀적으로 하던 3중 포문을 돌던 아무렇게나 하면되고
나는 재귀적으로 했고 소수 판정하는 것은 소수 판정법이랑 에라토스테네스의 체가 있는데
둘 다 사용해봤는데 최대 3000까지의 소수를 구하는 것이라 에라토스테네스가 약 35ms 정도 빨랐다.
이 문제를 통해 구현 속도를 늘려간다.
*/

bool Prime[3001] = { 1,1,0, };

void Erathos() {
	for (int i = 4; i < 3001; i += 2)
		Prime[i] = 1;
	for (int i = 3; i <= sqrt(3000); i += 2) {
		if (Prime[i]) continue;
		for (int j = i * i; j < 3001; j += i)
			Prime[j] = 1;
	}
}

bool is_Prime(int Num) {
	if (Num == 1 || (Num != 2 && Num % 2 == 0))
		return false;
	if (Num == 2) return true;
	for (int i = 3; i <= sqrt(Num); i+=2)
	{
		if (Num % i == 0)
			return false;
	}
	return true;
}

void Sel(int St, int *Ans, vector<int> &Con, vector<int> &Nums) {
	if (Con.size() == 3) {
		if (!Prime[Con[0] + Con[1] + Con[2]])
			*Ans += 1;
		/*
		if (is_Prime(Con[0] + Con[1] + Con[2]))
			Ans += 1;
		*/
		return;
	}
	for (int i = St; i < Nums.size(); i++)
	{
		Con.push_back(Nums[i]);
		Sel(i + 1, Ans, Con, Nums);
		Con.pop_back();
	}
}

int solution(vector<int> nums) {
	int answer = 0;
	Erathos();
	vector<int> Con;
	Sel(0, &answer, Con, nums);
	return answer;
}