#include <bits/stdc++.h>
using namespace std;

void AstarAlgorithm(const vector<vector<int>>&Map, const pair<int,int> &StartPoint, const pair<int, int>& EndPoint, bool EdgeOption = true)
{
	// pair<int,int>에서 first가 x 좌표, second가 y 좌표
	// tuple<int,int,int>에서 get<0>()가 가중치(G+H)인 F 값, get<1>()가 x 좌표, get<2>()가 y 좌표
	
	int mapWidth = Map[0].size(), mapHeight = Map.size();

	auto getG = [](const pair<int, int>& A, const pair<int, int>& B)->int {return abs(A.first - B.first) && abs(A.second - B.second) ? 14 : 10; };

	auto getH = [&](const pair<int, int>& A)->int {return 10 * (abs(A.first - EndPoint.first) + abs(A.second - EndPoint.second)); };

	auto is_ValidXY = [&](const pair<int, int>& A)->bool {return (A.first >= 0 && A.second >= 0 && A.first < mapWidth && A.second < mapHeight); };

	if (StartPoint.first < 0 || StartPoint.second < 0 || EndPoint.first < 0 || EndPoint.second < 0
		|| StartPoint.first >= mapWidth || StartPoint.second >= mapHeight || EndPoint.first >= mapWidth || EndPoint.second >= mapHeight
		|| Map[StartPoint.second][StartPoint.first] || Map[EndPoint.second][EndPoint.first]) {
		cout << "Plz Set the Start, End Point currectly!\n";
		return;
	}

	vector<vector<int>> Dist(mapHeight, vector<int>(mapWidth, (int)2e9)); // 초기 거리는 매우 크게
	vector<vector<pair<int, int>>> TraceBack(mapHeight, vector<pair<int, int>>(mapWidth, { -1,-1 })); // 경로 역추적 배열은 {-1,-1}로 초기화
	bool is_FindPath = false; // 길을 찾았는지 유무
	short Dir[8][2] = { {0,1},{1,0},{0,-1},{-1,0},{1,1},{-1,-1},{1,-1},{-1,1} }; // 8 방향
	short DirSize = EdgeOption ? 8 : 4; // 모서리 옵션에 따라 방향 제한
	priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> Q; // 우선순위 큐를 통해 열린목록, 닫힌목록 용이하게 관리

	Dist[StartPoint.second][StartPoint.first] = 0;
	int h = getH(StartPoint);
	Q.push({ h, StartPoint.first, StartPoint.second });

	while (!Q.empty())
	{
		int F = get<0>(Q.top());
		int X = get<1>(Q.top());
		int Y = get<2>(Q.top());
		Q.pop();

		if (X == EndPoint.first && Y == EndPoint.second) {
			is_FindPath = true;
			break;
		}

		int CurG = F - getH({ X,Y });

		if (CurG > Dist[Y][X])
			continue;

		for (int i = 0; i < DirSize; i++)
		{
			int nX = X + Dir[i][0], nY = Y + Dir[i][1];
			if (!is_ValidXY({ nX,nY }) || Map[Y][X])
				continue;

			int G = CurG + getG({ nX,nY }, { X,Y });

			if (G < Dist[nY][nX]) {
				Dist[nY][nX] = G;
				TraceBack[nY][nX] = { X,Y };
				Q.push({ G + getH({nX,nY}), nX, nY });
			}
		}
	}

	if (!is_FindPath) {
		cout << "Can't Reach the Goal!\n";
		return;
	}

	pair<int, int> B = EndPoint;
	deque<pair<int, int>> Way;
	while (B.first != -1) {
		Way.push_front(B);
		B = TraceBack[B.second][B.first];
	}

	vector<vector<int>> TraceResult = Map;
	// Way.pop_back(); Way.pop_front(); // 시작점과 끝점을 출력에서 제외하려면 활성화
	for (const auto& A : Way)
		TraceResult[A.second][A.first] = (int)1e9;
	cout << "\nFinished Travel!\n" << endl;
	
	for (const auto& A : TraceResult) {
		for (const auto& B : A) {
			string printBrick = ". ";
			if (B == 1) printBrick = "X ";
			else if (B == (int)1e9) printBrick = "+ ";
			cout << printBrick;
		}
		cout << "\n";
	}
}

int main() 
{
	vector<vector<int>> Map = {
		{0,0,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0},
		{0,0,1,0,1,1,1,1,1,0,1,1,1,0,1,0,0,0,0,0},
		{0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,0},
		{0,0,1,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,0,0},
		{0,0,1,0,0,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0},
		{0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0},
		{0,0,1,0,1,0,1,0,0,1,0,0,0,1,0,1,0,1,1,0},
		{0,0,1,0,1,0,1,0,0,1,0,0,0,1,0,1,0,0,0,0},
		{0,0,1,0,1,0,1,0,0,1,0,1,1,1,0,1,1,0,1,0},
		{0,1,1,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0},
		{0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};
	AstarAlgorithm(Map, { 1,1 }, { 17,17 }, false);
}