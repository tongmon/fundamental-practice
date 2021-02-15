#include <bits/stdc++.h>
using namespace std;

/*
https://leetcode.com/problems/min-stack/submissions/
스택을 만들어야하는데 스택 내의 최솟값을 항상 뱉을 수 있어야 한다.
처음에는 맵을 이용해서 따로 정렬을 해가면서 최솟값이 저장되는 구조로 짰는데
삭제, 삽입이 O(nlogn)이라 너무 비효율적이다.
따라서 스택에 삽입할 원소, 현재 원소까지의 최솟값 이 두가지를 저장해 놓는 방식을 사용했다.
이러면 삽입, 삭제가 O(1)에 해결이 된다.
스택과 벡터 모두 써봤는데 스택이 10ms나 더 빨랐다.
스택을 사용할 수 있다면 스택을 사용하자.
이 문제를 통해 스택에 대한 숙련도를 늘려간다.
*/

class MinStack {
	stack<pair<int, int>> St;
	long long Min = 21000000000;
public:
	MinStack() {

	}

	void push(int x) {
		if (Min > x)
			Min = x;
		St.push({ x,Min });
	}

	void pop() {
		St.pop();
		if (St.empty())
			Min = 21000000000;
		else
			Min = St.top().second;
	}

	int top() {
		return St.top().first;
	}

	int getMin() {
		return St.top().second;
	}
};

/*
// 처음에 생각나는대로 짜서 제출한 코드... 비효율적이다.
class MinStack {
	vector<int> Ary;
	map<int, int> Con;
public:
	MinStack() {

	}

	void push(int x) {
		Ary.push_back(x);
		if (Con.find(x) == Con.end())
			Con[x] = 1;
		else
			Con[x]++;
	}

	void pop() {
		if (Con[Ary.back()] == 1)
			Con.erase(Ary.back());
		else
			Con[Ary.back()]--;
		Ary.pop_back();
	}

	int top() {
		return Ary.back();
	}

	int getMin() {
		auto iter = Con.begin();
		return (*iter).first;
	}
};
*/