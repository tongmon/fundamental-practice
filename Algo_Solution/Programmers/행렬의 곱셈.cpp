#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12949
행렬의 곱셈 문제.
행렬의 곱셈을 구현하면 된다.
별다른 말 할 것이 없다.
*/

vector<vector<int>> solution(vector<vector<int>> arr1, vector<vector<int>> arr2) {
	int Row1 = arr1.size(), Col1 = arr1[0].size(), Row2 = arr2.size(), Col2 = arr2[0].size();
	vector<vector<int>> answer(Row1);
	for (int i = 0; i < Row1; i++)
		answer[i].resize(Col2);
	for (int i = 0; i < Row1; i++)
		for (int j = 0; j < Col2; j++)
			for (int k = 0; k < Col1; k++)
				answer[i][j] += arr1[i][k] * arr2[k][j];
	return answer;
}