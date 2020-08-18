#include <iostream>
#include <cstdio>
using namespace std;

// https://algospot.com/judge/problem/read/FESTIVAL
// 연속으로 공연하는 거니까 묶어서 계산후 최솟값을 찾는다.
// 더 빠르게 하는 방법은 1,2,3 -> 1,2,3,2 -> 1,2,3,2,1 -> 1,2,3,2,1,3 과 같이 가로로 커지게 하면서 계산하는 것이다.
// 밑에는 위 방식과 다른 3개씩, 4개씩, 5개씩.... 묶어나가는 방식이다.
// 10의 -7승 이하의 절대/상대 오차가 있는 답이 정답 처리가 되기에 double로 쓰고 .8f이상을 출력해야 되더라....

double Festival(int* stars, int* cost, int Csize)
{
	int Max_rental = stars[0];
	int Team = stars[1];

	double smallcost = 999, smallone, buffer;
	int gap = Team - 1;
	while (gap != Max_rental)
	{
		smallone = 999999999;
		for (int i = gap; i < Csize; i++)
		{
			buffer = 0;
			for (int j = i - gap; j <= i; j++)
			{
				buffer = buffer + cost[j];
			}
			if (buffer < smallone)
			{
				smallone = buffer;
			}
		}
		buffer = smallone / (gap + 1.0);
		if (smallcost > buffer)
		{
			smallcost = buffer;
		}
		gap++;
	}
	return smallcost;
}

int main()
{
	int Case;
	cin >> Case;

	while (Case > 0)
	{
		int ary[2];
		int cost[1001];
		cin >> ary[0] >> ary[1];
		for (int i = 0; i < ary[0]; i++)
		{
			cin >> cost[i];
		}
		printf("%.101f\n", Festival(ary, cost, ary[0]));
		Case--;
	}
}