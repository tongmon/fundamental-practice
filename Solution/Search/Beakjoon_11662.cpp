#include <iostream>
#include <cstring>
#include <list>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/11662
정말 골머리를 앓게 만든 문제다.....
아오 생각만해도 빡치네... 내가 짠 코드가 아직도 왜 틀렸는지 모르겠지만
다른 사람 해답을 남긴다.
밑에 나온 방식이 삼분탐색으로 가장 잘 푼 것 같다.
일단 삼분탐색은 미분이 불가능한 볼록함수가 있을 경우 이 함수에서 극솟값, 극대값의 근사치를 구할 경우에 사용된다.
이 문제는 미분이 불가능한 경우가 아니라 굳이 삼분탐색을 쓰지 않고도 풀리지만 삼분탐색이 가장 접근하기 좋은 것 같다.
아무튼 밑의 코드에서는 좌표를 퍼센트로 나누어 각 위치를 알아내고(처음엔 33%, 66% 로 나뉜다.) 각 거리를 구해서 계속 작은 녀석으로 바꾸어 나간다.
이 풀이를 통해 좌표를 퍼센테이지 단위로 더해주는 발상과 삼분탐색을 쓸 수 있는 능력을 약간이나마 기르고 간다.
하.... 정말 어려웠다 ㅠ.ㅠ
*/

double A[2], B[2], C[2], D[2];

typedef struct _cord
{
	long double x, y;
}Cordinate;

Cordinate Min(double a)
{
	Cordinate buffer;
	buffer.x = A[0] + (B[0] - A[0]) * (a / 100);
	buffer.y = A[1] + (B[1] - A[1]) * (a / 100);
	return buffer;
}

Cordinate Gang(double a) 
{
	Cordinate buffer;
	buffer.x = C[0] + (D[0] - C[0]) * (a / 100);
	buffer.y = C[1] + (D[1] - C[1]) * (a / 100);
	return buffer;
}

int main() 
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin >> A[0] >> A[1] >> B[0] >> B[1] >> C[0] >> C[1] >> D[0] >> D[1];

	double FirstP = 0, LastP = 100;
	double Shortest = 2000000000; 

	while (LastP - FirstP >= 0.00000001) // 오차범위는 조금 크게 잡아주었다.
	{ 
		double one = (LastP + FirstP * 2) / 3; // 3분점 중 왼쪽
		double two = (LastP * 2 + FirstP) / 3; // 3분점 중 오른쪽

		Cordinate oneMinho = Min(one); // one % 일 때 민호의 위치
		Cordinate twoMinho = Min(two); // two % 일 때 민호의 위치
		Cordinate oneGangho = Gang(one); // one % 일 때 강호의 위치
		Cordinate twoGangho = Gang(two); // two % 일 때 강호의 위치

		double Plength = pow(oneMinho.x - oneGangho.x, 2) + pow(oneMinho.y - oneGangho.y, 2); // one % 일 때 둘 사이의 거리
		double Qlength = pow(twoMinho.x - twoGangho.x, 2) + pow(twoMinho.y - twoGangho.y, 2); // two % 일 때 둘 사이의 거리

		double ans = (Plength > Qlength ? Qlength : Plength); // Plength, Qlength, Shortest 중 가장 작은 것을 answer에 업데이트한다.
		if (Shortest > ans)
		{
			Shortest = ans;
		}
		if (Plength > Qlength) // 가장 작은 값을 찾아가기에 큰 값이 나온 것을 줄여나간다.
		{
			FirstP = one;
		}
		else
		{
			LastP = two;
		}
	}
	printf("%.10lf", sqrt(Shortest));
	return 0;
}