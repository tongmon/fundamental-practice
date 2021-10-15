#include <bits/stdc++.h>
using namespace std;

// A* 알고리즘, 평면에서만 적용 가능, 중력이 작용하는 플랫포머 게임에서는 이를 응용해야 됨.
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

// AABB 충돌 검사 내장 사각형 클래스
// 네 모퉁이의 좌표로 해도 되지만 여기선 중심과 반지름으로 했다.
// 해당 사각형이 벽돌인지 길인지 타입을 나타내는 변수도 추가했다.
class Square {
public:
	pair<float, float> mCenter;
	pair<float, float> mHalf;
	int mType;

	Square() { mCenter = { 0,0 }, mHalf = { 1,1 }; }
	Square(const pair<float, float>& center, const pair<float, float>& half, const int& type) { mCenter = center, mHalf = half; mType = type; }
	~Square() {}
	bool Overlaps(const Square& A) const {
		return abs(mCenter.first - A.mCenter.first) <= mHalf.first + A.mHalf.first
			&& abs(mCenter.second - A.mCenter.second) <= mHalf.second + A.mHalf.second;
	}
};

class Map {
public:
	int mWidth;
	int mHeight;
	vector<vector<Square>> mMap; // 맵의 실제 좌표 정보
	Map() {}
	Map(const pair<float, float>& startCoordiante, const int& squareSize, const vector<vector<int>>& mapInfo)
	{
		mWidth = mapInfo[0].size(), mHeight = mapInfo.size();
		int X = startCoordiante.first, Y = startCoordiante.second;
		mMap.resize(mapInfo.size(), vector<Square>(mapInfo[0].size(), Square()));
		for (int i = mHeight - 1; i >= 0; i--) {
			for (int j = 0; j < mWidth; j++) {
				mMap[i][j] = move(Square({ X,Y }, { squareSize, squareSize }, mapInfo[i][j]));
				X += squareSize;
			}
			X = startCoordiante.first;
			Y += squareSize;
		}
	}
};

// 적이 실제로 갈 수 있는 경로를 나타내는 노드
// vector<vector<Node>> NodeMap 이런 방식으로 사용 
class Node {
public:
	enum class NodeState : int // 행동패턴 삽입
	{
		Walk,
		Jump,
		Drop
	};

	// 노드 정보가 담김, X,Y 좌표 정보 + 해당 좌표로 이동할때 어떤 행동을 취해야 하는지가 담김
	// 만약 점프를 한다면 그에 따른 적절한 속도가 필요함
	class NodeInfo
	{
		int X = 0, Y = 0, vX = (int)2e9, vY = (int)2e9;
		NodeState State;
	public:
		NodeInfo(int x, int y, int vx, int vy, int iState) { X = x, Y = y, vX = vx, vY = vy, State = (NodeState)iState; }
	};
	shared_ptr<vector<NodeInfo>> mLink;
	Node() { mLink = nullptr; }
	Node(shared_ptr<vector<NodeInfo>> link) { mLink = make_shared<vector<NodeInfo>>(link.get()); }
	void AddNode(const NodeInfo& nodeinfo)
	{
		if (mLink == nullptr)
			mLink = make_shared<vector<NodeInfo>>(new vector<NodeInfo>());
		mLink.get()->push_back(nodeinfo);
	}
	void AddNode(pair<int,int> XY, pair<int,int>velXY, int State)
	{
		if (mLink == nullptr)
			mLink = make_shared<vector<NodeInfo>>(new vector<NodeInfo>());
		mLink.get()->push_back(NodeInfo(XY.first, XY.second, velXY.first, velXY.second, State));
	}
};

// 노드 만들기 위해 필요한 것
// 1. 캐릭터 크기 -> 점프 시에 포물선 충돌 감지 시에 필요
// 2. 캐릭터 점프, 최대 좌우 속도 -> 포물선 함수가 속도에 따라 달라짐, 속도 조절 간격에 따라 연산 속도가 달라질 수 있음.
// 3. 블록 하나 당 크기
// 

void NodeMaker(const Map& Map, const pair<int, int>& StartPoint, const pair<int, int>& EndPoint,
	const pair<float, float>& ObjHalfSize, vector<vector<Node>>& NodeMap)
{
	NodeMap.clear();
	NodeMap.resize(Map.mHeight, vector<Node>(Map.mWidth, Node()));
	
	const auto& MapInfo = Map.mMap;
	for (int i = 0; i < Map.mHeight; i++)
	{
		for (int j = 0; j < Map.mWidth; j++)
		{
			// 벽인 사각형은 노드가 될 수 없다.
			if (MapInfo[i][j].mType == 1)
				continue;

			// 지면이 존재하면 검사
			if (i + 1 < Map.mHeight && MapInfo[i + 1][j].mType == 1) {

				// 적 캐릭터 크기가 들어갈 수 있는 공간이 있는지 천장 검사
				float X = MapInfo[i][j].mCenter.first, Y = MapInfo[i][j].mCenter.second + MapInfo[i][j].mHalf.second + 0.2f;
				int Size = (int)ceil(ObjHalfSize.second * 2 / (float)MapInfo[i][j].mHalf.first), k; // Size는 블록 몇 개 검사해야하는지 크기
				bool is_Fit = true;

				// 해당 블록에 오브젝트가 들어갈 수 있는지 크기 검사
				for (k = i; k >= 0 && k >= i - Size; k--)
					is_Fit &= MapInfo[k][j].mType != 1;
				is_Fit = k >= 0 ? is_Fit : false; // k가 음수라는 것은 천장을 넘어섰다는 것이므로 false로 만들어 줌
				if (!is_Fit) continue; // 해당 블록에 오브젝트가 서있을 수 없으니 노드도 찍을 수 없고 그냥 넘김

				// 적 캐릭터(오브젝트)가 좌, 우로 움직이는 경우 캐릭터 키에 걸리는 낮은 블록이 있어 그 곳으로 바로 걸어갈 수 없는 경우 계산 
				is_Fit = true;
				for (k = i; k >= 0 && k >= i - Size; k--)
					is_Fit &= MapInfo[k][j - 1].mType != 1;
				is_Fit = k >= 0 ? is_Fit : false;
				if (is_Fit) {
					int p = i;
					// 내려가는 곳에는 제한없이 이동이 가능할 것임, 낙뎀 같은 페널티가 있다면 for문 조정 필요
					for (; p < Map.mHeight; p++) if (MapInfo[p][j - 1].mType == 1) break;
					if (p < Map.mHeight)
						NodeMap[i][j].AddNode({ j,i }, {2e9,2e9}, 0);
				}

				

			}
		}
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
	vector<vector<int>> PlatformerMap = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
		{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0},
		{0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};

	AstarAlgorithm(Map, { 1,1 }, { 17,17 }, false);
}