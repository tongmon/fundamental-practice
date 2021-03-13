#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/60059
자물쇠와 열쇠 문제.
이차원 배열 회전 + 완전 탐색 + 약간의 꼼수를 요구하는 문제이다.
일단 열쇠를 회전하면서 홈에 맞는지 봐야하는데 홈 크기를 벗어나서도
열쇠를 가져다 댈 수 있다.
그니까 
  ---
  ---
  ---
이러한 열쇠를 4x4 격자 홈에 가져다가 대는 경우
  ****
  **---
  **---
  **---
위와 같이 홈에 댈 수 있다는 것이다.
따라서 이를 구현하기 위해 열쇠 크기 격자가 MxM 이라면 M-1xM-1 울타리를 NxN홈에 둘러쳤다.
그리고 둘러친 격자에 열쇠를 처음 시작점부터 끝까지 회전하면서 가져다가 대보면서 맞는지 아닌지
비교를 했다.
다른 사람 풀이를 봤는데 내가 사용했던 배열 회전보다 공간복잡도와 시간복잡도가 더 효율적인 회전을
사용한 사람이 있었다.
내가 사용한 방식은 버퍼에 결과를 저장하고 그것을 다시 원 값에 복사해서 넣는 것이기에 복사가 진행되어
그닥이다.
그런데 밑의 방식은 복사가 진행되지 않아서 효율적이다.
원리는 배열이 90도 회전하게 되면 풍차돌리기 처럼 각 4개의 원소가 위치를 바꾸는 듯한 패턴이 보이는데
그것을 구현한 것이다.
이 문제를 통해 완전탐색 문제에 대한 실력을 늘려간다.
*/

vector<vector<int>> Lock;
int Hcnt;

/*
// 느린 회전 방식
void Rotate(vector<vector<int>>& Mat) {
	vector<vector<int>> Buf(Mat.size());
	for (int i = 0; i < Mat.size(); i++)
		Buf[i].resize(Mat.size());
	for (int i = 0; i < Mat.size(); i++)
		for (int j = 0; j < Mat.size(); j++) {
			int X = Mat.size() - i - 1, Y = j;
			Buf[Y][X] = Mat[i][j];
		}
	Mat = Buf;
}
*/

void Rotate(vector<vector<int>>& mat) {
	int N = mat.size();
	for (int x = 0; x < N / 2; x++) {
		for (int y = x; y < N - x - 1; y++) {
			int temp = mat[x][y];
			mat[x][y] = mat[y][N - 1 - x];
			mat[y][N - 1 - x] = mat[N - 1 - x][N - 1 - y];
			mat[N - 1 - x][N - 1 - y] = mat[N - 1 - y][x];
			mat[N - 1 - y][x] = temp;
		}
	}
}

bool Comp(int x, int y, vector<vector<int>> &k) {
	int Cnt = 0;
	for (int i = 0; i < k.size(); i++) {
		for (int j = 0; j < k.size(); j++) {
			if ((k[i][j] && Lock[y + i][x + j] == 1)
				|| (!Lock[y + i][x + j] && !k[i][j]))
				return false;
			if (!Lock[y + i][x + j] && k[i][j])
				Cnt++;
		}
	}
	if (Hcnt == Cnt)
		return true;
	return false;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
	int i = 0, Size = lock.size() + 2 * key.size() - 2;
	Lock.resize(Size);
	for (; i < key.size() - 1; i++)
		for (int j = 0; j < Size; j++)
			Lock[i].push_back(3);
	for (int p = 0; p < lock.size(); i++, p++) {
		for (int j = 0; j < key.size() - 1; j++)
			Lock[i].push_back(3);
		for (int z = 0; z < lock.size(); z++) {
			Hcnt = !lock[p][z] ? Hcnt + 1 : Hcnt;
			Lock[i].push_back(lock[p][z]);
		}
		for (int j = 0; j < key.size() - 1; j++)
			Lock[i].push_back(3);
	}
	for (int p = 0; p < key.size() - 1; i++, p++)
		for (int j = 0; j < Size; j++)
			Lock[i].push_back(3);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j <= Lock.size() - key.size(); j++)
			for (int p = 0; p <= Lock.size() - key.size(); p++) {
				if (Comp(p, j, key))
					return true;
			}
		Rotate(key);
	}
	return false;
}