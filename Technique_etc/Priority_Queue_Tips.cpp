#include <bits/stdc++.h>
using namespace std;

/*
우선 순위 큐 비교 연산자 사용에 대한 짧은 팁을 적는다.
길찾기 알고리즘을 짜다보니 단순 구조체 끼리의 비교가 아니라
그 구조체의 값이 가르키는 특정 배열의 값으로 크기가 결정되는
현상이 필요한 경우가 생겼다.
말이 어려운데 풀어쓰자면 맵 격자 2차원 배열 mMap이 있다고 하고
x,y가 들어있는 포인트 자료가 있다고 하면
mMap[a.y][a.x] > mMap[b.y][b.x] 이렇게 비교를 하여 a, b의 우열이 나뉘는 것이
필요한 상황이 있다는 말이다.
그래서 찾아보니 밑에 내가 짜논 코드 같이 하면 된다.
클래스에 특정 중계 자료형을 박고 우선 순위 큐의 비교 연산자로 써주면 된다.
*/

class ComparePFNodeMatrix
{
	vector<int>* mMatrix;

public:
	ComparePFNodeMatrix(vector<int>* Matrix)
	{
		mMatrix = Matrix;
	}
	bool operator()(int a, int b)
	{
		return mMatrix->at(a) < mMatrix->at(b);
	}
};

int main(void)
{
	vector<int> A = { 5,4,3,2,1 };
	priority_queue<int, vector<int>, ComparePFNodeMatrix> *Q;
	Q = new priority_queue<int, vector<int>, ComparePFNodeMatrix>(ComparePFNodeMatrix(&A));
	Q->push(1); Q->push(2);
	while (!Q->empty())
	{
		cout << Q->top() << ' ';
		Q->pop();
	}
	delete Q;
}