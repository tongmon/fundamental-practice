#include <bits/stdc++.h>
using namespace std;

/*
// A* 알고리즘, 평면에서만 적용 가능, 중력이 작용하는 플랫포머 게임에서는 이를 응용해야 됨.
void AstarAlgorithm(const vector<vector<int>>& Map, const pair<int, int>& StartPoint, const pair<int, int>& EndPoint, bool EdgeOption = true)
{
	// pair<int,int>에서 first가 x 좌표, second가 y 좌표
	// tuple<int,int,int>에서 get<0>()가 가중치(G+H)인 F 값, get<1>()가 x 좌표, get<2>()가 y 좌표

	int mapWidth = Map[0].size(), mapHeight = Map.size();

	auto getG = [](const pair<int, int>& A, const pair<int, int>& B)->int {return abs(A.first - B.first) && abs(A.second - B.second) ? 14 : 10; };

	auto getH = [&](const pair<int, int>& A)->int {return 10 * (abs(A.first - EndPoint.first) + abs(A.second - EndPoint.second)); };

	auto is_ValidXY = [&](const pair<int, int>& A)->bool {return (A.first >= 0 && A.second >= 0 && A.first < mapWidth&& A.second < mapHeight); };

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
*/

// AABB 충돌 검사 내장 사각형 클래스
// 네 모퉁이의 좌표로 해도 되지만 여기선 중심과 반지름으로 했다.
// 해당 사각형이 벽돌인지 길인지 타입을 나타내는 변수도 추가했다.
class Square {
public:
	pair<float, float> mCenter;
	pair<float, float> mHalf;
	int mType;

	Square() { mCenter = { 0.f,0.f }, mHalf = { 1.f,1.f }; }
	Square(const pair<float, float>& center, const pair<float, float>& half, const int& type) { mCenter = center, mHalf = half; mType = type; }
	~Square() {}
	pair<float, float> GetLeftTop() { return { mCenter.first - mHalf.first, mCenter.second + mHalf.second }; }
	pair<float, float> GetRightBottom() { return { mCenter.first + mHalf.first, mCenter.second - mHalf.second }; }
	bool Overlaps(const Square& A) const {
		return abs(mCenter.first - A.mCenter.first) <= mHalf.first + A.mHalf.first
			&& abs(mCenter.second - A.mCenter.second) <= mHalf.second + A.mHalf.second;
	}
};

class Map {
public:
	int mWidth;
	int mHeight;
	pair<float, float> mstMapPoint;
	vector<vector<Square>> mMap; // 맵의 실제 좌표 정보
	Map() { mWidth = mHeight = 0; }
	Map(const pair<float, float>& startCoordiante, const int& squareSize, const vector<vector<int>>& mapInfo) // 일단 맵의 격자는 정사각형이라고 가정하고 수행
	{
		mstMapPoint = startCoordiante;
		mWidth = mapInfo[0].size(), mHeight = mapInfo.size();
		float X = startCoordiante.first, Y = startCoordiante.second;
		mMap.resize(mapInfo.size(), vector<Square>(mapInfo[0].size(), Square()));
		for (int i = mHeight - 1; i >= 0; i--) {
			for (int j = 0; j < mWidth; j++) {
				mMap[i][j] = move(Square({ X,Y }, { (float)squareSize, (float)squareSize }, mapInfo[i][j]));
				X += squareSize;
			}
			X = startCoordiante.first;
			Y += squareSize;
		}
	}
	pair<int, int> GetMapTileAtPoint(const pair<float, float>& point) {
		return { (int)((point.first - mstMapPoint.first + mMap[0][0].mHalf.first) / (mMap[0][0].mHalf.first * 2)),
		(int)((point.second - mstMapPoint.second + mMap[0][0].mHalf.second) / (mMap[0][0].mHalf.second * 2)) };
	}
};


// 적이 실제로 갈 수 있는 경로를 나타내는 노드
// vector<vector<Node>> NodeMap 이런 방식으로 사용 
class Node {
public:
	enum class NodeState : int // 걷기, 점프 등의 행동패턴 삽입
	{
		Walk,
		Jump,
		Drop
	};

	// 노드 정보가 담김, X,Y 좌표 정보 + 해당 좌표로 이동할때 어떤 행동을 취해야 하는지가 담김
	// 만약 점프를 한다면 그에 따른 적절한 속도가 필요함
	class NodeInfo
	{
	public:
		int X = 0, Y = 0;
		float vX = 2e9, vY = 2e9;
		NodeState State;
	public:
		NodeInfo(int x, int y, float vx, float vy, int iState) { X = x, Y = y, vX = vx, vY = vy, State = (NodeState)iState; }
		NodeInfo(int x, int y, float vx, float vy, NodeState iState) { X = x, Y = y, vX = vx, vY = vy, State = iState; }
	};
	shared_ptr<vector<NodeInfo>> mLink;
	Node() { mLink = nullptr; }
	Node(shared_ptr<vector<NodeInfo>> link) { mLink = link; }
	Node(vector<NodeInfo>* link) { mLink = make_shared<vector<NodeInfo>>(*link); }
	void AddNode(const NodeInfo& nodeinfo)
	{
		if (mLink == nullptr)
			mLink = make_shared<vector<NodeInfo>>(*(new vector<NodeInfo>()));
		mLink.get()->push_back(nodeinfo);
	}
	void AddNode(pair<int, int> XY, pair<int, int>velXY, int State)
	{
		if (mLink == nullptr)
			mLink = make_shared<vector<NodeInfo>>(*(new vector<NodeInfo>()));
		mLink.get()->push_back(NodeInfo(XY.first, XY.second, velXY.first, velXY.second, State));
	}
	void AddNode(pair<int, int> XY, pair<int, int>velXY, NodeState State)
	{
		if (mLink == nullptr)
			mLink = make_shared<vector<NodeInfo>>(*(new vector<NodeInfo>()));
		mLink.get()->push_back(NodeInfo(XY.first, XY.second, velXY.first, velXY.second, State));
	}
};

// 노드 만들기 위해 필요한 것
// 1. 캐릭터 크기 -> 점프 시에 포물선 충돌 감지 시에 필요
// 2. 캐릭터 점프, 최대 좌우 속도 -> 포물선 함수가 속도에 따라 달라짐, 속도 조절 간격에 따라 연산 속도가 달라질 수 있음.
// 3. 블록 하나 당 크기
// 

void NodeMaker(Map& Map, const pair<float, float>& ObjHalfSize, const pair<float, float>& MaxSpeed, float Gravity, vector<vector<Node>>& NodeMap)
{
	NodeMap.clear();
	NodeMap.resize(Map.mHeight, vector<Node>(Map.mWidth, Node()));

	auto& MapInfo = Map.mMap;
	for (int i = 0; i < Map.mHeight; i++)
	{
		for (int j = 0; j < Map.mWidth; j++)
		{
			// 벽인 사각형은 노드가 될 수 없다.
			if (MapInfo[i][j].mType == 1)
				continue;

			// 지면이 존재하면 검사
			if (i + 1 < Map.mHeight && MapInfo[i + 1][j].mType == 1) {

				// 적 캐릭터 크기가 들어갈 수 있는 공간이 있는지 검사
				float X = MapInfo[i][j].mCenter.first, Y = MapInfo[i][j].mCenter.second + MapInfo[i][j].mHalf.second + 0.2f;
				int hSize = (int)ceil(ObjHalfSize.second * 2 / (float)MapInfo[i][j].mHalf.second),
					wSize = (int)ceil(ObjHalfSize.first * 2 / (float)MapInfo[i][j].mHalf.first), k; // hSize, wSize는 물건 크기에 따라 높이, 너비 블록 몇 개 검사해야하는지 크기
				bool is_Fit = true;

				// 해당 블록에 오브젝트가 들어갈 수 있는지 크기 검사
				for (k = i; k >= 0 && k > i - hSize; k--)
					is_Fit &= MapInfo[k][j].mType != 1;
				is_Fit = k >= 0 ? is_Fit : false; // k가 음수라는 것은 천장을 넘어섰다는 것이므로 false로 만들어 줌
				if (!is_Fit) continue; // 해당 블록에 오브젝트가 서있을 수 없으니 노드도 찍을 수 없고 그냥 넘김

				// 적 캐릭터(오브젝트)가 좌, 우로 움직이는 경우 캐릭터 키에 걸리는 낮은 블록이 있어 그 곳으로 바로 걸어갈 수 없는 경우 계산
				auto ObjHeightCalculation = [&](bool is_Left)->int {
					if ((is_Left && j - 1 < 0) || (!is_Left && Map.mWidth <= j + 1))
						return -1;
					int t = is_Left ? j - 1 : j + 1;
					is_Fit = true;
					for (k = i; k >= 0 && k > i - hSize; k--)
						is_Fit &= MapInfo[k][t].mType != 1;
					is_Fit = k >= 0 ? is_Fit : false;
					if (is_Fit) {
						int p = i + 1;
						// 내려가는 곳에는 제한없이 이동이 가능할 것임, 낙뎀 같은 페널티가 있다면 for문 조정 필요
						for (; p < Map.mHeight; p++) if (MapInfo[p][t].mType == 1) break;

						// 최초 검사된 바닥 블록 한 칸 위 그리고 한칸 좌측 방향에 노드를 만든다.
						if (p < Map.mHeight)
							return p - 1;
						// NodeMap[i][j].AddNode({ t,p - 1 }, { 2e9,2e9 }, (int)Node::NodeState::Walk);
					}
					return -1;
				};

				// 적 캐릭터 크기로 인해 노드가 될 수 있는 곳인지 아닌지 검사
				auto ObjSizeCalculation = [&](bool is_Left)->void {
					int posY = ObjHeightCalculation(is_Left);
					// 적 캐릭터 너비가 길어서 밑으로 떨어질 수 없는 경우 계산
					if (posY != -1) {
						bool is_NodePlace = true;
						if (posY != i) {
							for (int y = i; y <= posY && is_NodePlace; y++) {
								int x = is_Left ? j - 1 : j + 1;
								for (; is_Left && x >= 0 && x > j - 1 - wSize && is_NodePlace; x--) {
									is_NodePlace &= MapInfo[y][x].mType != 1;
								}
								for (; !is_Left && x < Map.mWidth && x < j + 1 + wSize && is_NodePlace; x++) {
									is_NodePlace &= MapInfo[y][x].mType != 1;
								}
								if ((is_Left && x > 0) || (!is_Left && x < Map.mWidth)) is_NodePlace = false;
							}
						}
						if (is_NodePlace)
							NodeMap[i][j].AddNode({ is_Left ? j - 1 : j + 1,posY }, { 2e9,2e9 }, Node::NodeState::Walk);
					}
				};

				// 현재 노드에서 한칸 좌,우측의 경우 판단
				// 물체의 높이와 너비를 모두 고려해야 함
				ObjSizeCalculation(true);
				ObjSizeCalculation(false);

				// 점프 고려
				// 포물선을 그려 충돌 유무 체크
				// x축과 y축 초기 속도와 그 간격을 잘 조절하는 것이 관건이다.
				float xStartSpeed = 1.f, yStartSpeed = 10.f, xSpeedGap = 5.f, ySpeedGap = 5.f, timeGap = 2.f;
				float initX = MapInfo[i][j].GetRightBottom().first, float initY = MapInfo[i][j].mCenter.second;
				for (float xSpeed = xStartSpeed; xSpeed <= MaxSpeed.first; xSpeed += xSpeedGap)
				{
					for (float ySpeed = yStartSpeed; ySpeed < MaxSpeed.second; ySpeed += ySpeedGap)
					{
						float xDist = initX, yDist = initY;
						for (float fTime = 0; fTime < ; fTime += timeGap)
						{
							xDist = fTime * xSpeed;
							yDist = ySpeed * fTime + fTime * fTime / 2.f * Gravity; // 등가속도 운동
							pair<int, int> mapIndex = Map.GetMapTileAtPoint({ xDist ,yDist });
							MapInfo[mapIndex.second][mapIndex.first].Overlaps(Square({ xDist + ObjHalfSize.first, yDist }, ObjHalfSize, 1));
						}
					}
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

	// AstarAlgorithm(Map, { 1,1 }, { 17,17 }, false);
}