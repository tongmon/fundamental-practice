#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/42842
카펫 문제.
적절하게 조건에 맞는 사각형 높이,너비를 구하는 문제다.
속 안에 존재하는 것이 노란색이고 이 노란색을 바탕으로
갈색 블록을 둘러싸면 되는 것이기에 노란색의 형태에 따라
사각형의 높낮이가 좌우된다고 생각하고 노란색을 변형하면서
올바른 사각형을 완전탐색하여 찾는 풀이로 풀었다.
노란색이 한 줄인 경우, 두 줄, 세 줄.... 이렇게
줄을 계속 늘려가면서 갈색블록 개수가 조건과 맞으면 정답이고 아니면
계속 탐색하게 된다.
이 문제를 통해 완전탐색 구현 속도를 늘려간다.
*/

vector<int> solution(int brown, int yellow) {
	vector<int> answer;
	for (int i = 1; i <= yellow / 2 + 1; i++)
	{
		if (yellow % i)
			continue;
		int A = (yellow / i + 2) * 2 + i * 2;
		if (brown == A)
		{
			answer.push_back(yellow / i + 2);
			answer.push_back(i + 2);
			break;
		}
	}
	return answer;
}