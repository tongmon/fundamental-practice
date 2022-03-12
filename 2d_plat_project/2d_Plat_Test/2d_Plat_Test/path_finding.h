#pragma once

#include <bits/stdc++.h>
#include <unordered_set>

// 좌표 정의
template <typename T>
struct Coordinate
{
	T x;
	T y;
	Coordinate() { x = y = static_cast<T>(0); }
	Coordinate(T&& X, T&& Y) { x = X; y = Y; }
	Coordinate(std::pair<T, T>&& XY) { x = XY.first; y = XY.second; }
	Coordinate(std::initializer_list<T>&& XY) { x = *XY.begin(); y = *(XY.begin() + 1); }
};

// 격자 타입 정의
enum class BlockType : int {
	Space = 0, // 빈공간
	Block = 1, // 막힌 벽
};

// A* 알고리즘, 평면에서만 적용 가능, 중력이 작용하는 플랫포머 게임에서는 이를 응용해야 됨.
void AstarAlgorithm(const std::vector<std::vector<int>>& Map, const Coordinate<int>& StartPoint, const Coordinate<int>& EndPoint, bool EdgeOption = true)
{
	// tuple<int,int,int>에서 get<0>()가 가중치(G+H)인 F 값, get<1>()가 x 좌표, get<2>()가 y 좌표
	int mapWidth = (int)Map[0].size(), mapHeight = (int)Map.size();

	// G는 사선이면 가중치 14를 주고, 직선 방향이면 가중치 10을 준다.
	auto getG = [](const Coordinate<int>& A, const Coordinate<int>& B)->int { return abs(A.x - B.x) && abs(A.y - B.y) ? 14 : 10; };

	// H는 휴리스틱 거리를 사용
	auto getH = [&](const Coordinate<int>& A)->int { return 10 * (abs(A.x - EndPoint.x) + abs(A.y - EndPoint.y)); };

	// is_ValidXY는 주어진 좌표가 올바른지 확인하는 함수
	auto is_ValidXY = [&](const Coordinate<int>& A)->bool {return (A.x >= 0 && A.y >= 0 && A.x < mapWidth&& A.y < mapHeight); };

	// 주어진 시작 좌표나 도착 좌표가 이상할 경우
	if (StartPoint.x < 0 || StartPoint.y < 0 || EndPoint.x < 0 || EndPoint.y < 0
		|| StartPoint.x >= mapWidth || StartPoint.y >= mapHeight || EndPoint.x >= mapWidth || EndPoint.y >= mapHeight
		|| Map[StartPoint.y][StartPoint.x] || Map[EndPoint.y][EndPoint.x]) {
		std::cout << "Plz Set the Start, End Point currectly!\n";
		return;
	}

	// 초기 거리는 매우 크게
	std::vector<std::vector<int>> Dist(mapHeight, std::vector<int>(mapWidth, std::numeric_limits<int>::max()));
	// 경로 역추적 배열은 {-1,-1}로 초기화
	std::vector<std::vector<Coordinate<int>>> TraceBack(mapHeight, std::vector<Coordinate<int>>(mapWidth, { -1,-1 }));
	// 길을 찾았는지 유무
	bool is_FindPath = false;
	// 8 방향, 1~4 방향은 직선 방향, 5~8 방향은 사선 방향
	short Dir[8][2] = { {0,1},{1,0},{0,-1},{-1,0},{1,1},{-1,-1},{1,-1},{-1,1} };
	// 모서리 옵션에 따라 방향 제한, 모서리 옵션이 켜지면 사선 방향으로도 이동이 가능하다고 판단함.
	short DirSize = EdgeOption ? 8 : 4;
	// 우선순위 큐를 통해 열린목록, 닫힌목록 용이하게 관리, 큐의 맨 위에는 G+H 값이 가장 작은 녀석이 위로 온다.
	// 큐에 들어가는 자료구조는 tuple로 { F(G+H), x좌표, y좌표 } 로 구성된다.
	std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, std::greater<std::tuple<int, int, int>>> Q;
	// 초기 거리는 0 으로 설정
	Dist[StartPoint.y][StartPoint.x] = 0;
	// 도착점 까지의 H 값을 구함, 초기엔 이것이 F값이 됨
	int h = getH(StartPoint);
	Q.push({ h, StartPoint.x, StartPoint.y });

	while (!Q.empty())
	{
		int F = get<0>(Q.top());
		int X = get<1>(Q.top());
		int Y = get<2>(Q.top());
		Q.pop();

		// 도착점에 도달했으면 우선순위 큐 탐색을 끝냄
		if (X == EndPoint.x && Y == EndPoint.y) {
			is_FindPath = true;
			break;
		}

		// 현재 거리 가중치를 구함
		int CurG = F - getH({ X,Y });

		// 기록된 거리 가중치보다 크다면 큐에서 다른 녀석을 탐색한다.
		if (CurG > Dist[Y][X])
			continue;

		// 방향을 모두 탐색하면서 F값과 거리 가중치를 기록한다.
		for (int i = 0; i < DirSize; i++)
		{
			int nX = X + Dir[i][0], nY = Y + Dir[i][1];

			// 좌표가 올바른 좌표인지 검사한다. 맵의 값이 1이면 벽으로 인식한다. 0은 길로 인식한다.
			if (!is_ValidXY({ nX, nY }) || Map[Y][X])
				continue;
			int G = CurG + getG({ nX,nY }, { X,Y });

			// 이미 기록된 거리 가중치보다 작은 녀석이 나타났다면 이를 기록하고 큐에 넣는다.
			if (G < Dist[nY][nX]) {
				Dist[nY][nX] = G;
				// 역추적 시에 사용될 부모 좌표를 기록한다.
				TraceBack[nY][nX] = { X,Y };
				Q.push({ G + getH({nX, nY}), nX, nY });
			}
		}
	}

	// 도달할 수 있는 경로가 없는 경우
	if (!is_FindPath) {
		std::cout << "Can't Reach the Goal!\n";
		return;
	}

	// 추적시에는 도착 좌표부터 시작 좌표로 역추적을 하게 된다.
	Coordinate<int> B = EndPoint;
	// 최종 길 좌표가 담기게 되는 deque
	std::deque<Coordinate<int>> Way;
	while (B.x != -1) {
		Way.push_front(B);
		B = TraceBack[B.y][B.x];
	}

	// 실행 결과를 알려주기 위한 로직
	std::vector<std::vector<int>> TraceResult = Map;

	// 시작점과 끝점을 출력에서 제외하려면 활성화
	// Way.pop_back(); Way.pop_front();

	for (const auto& A : Way)
		TraceResult[A.y][A.x] = (int)1e9;
	std::cout << "\nTravel Finished!\n";
	for (const auto& A : TraceResult) {
		for (const auto& B : A) {
			std::string printBrick = ". ";
			if (B == 1) printBrick = "X ";
			else if (B == (int)1e9) printBrick = "+ ";
			std::cout << printBrick;
		}
		std::cout << "\n";
	}
}

// AABB 충돌 검사 내장 직사각형 클래스
// 네 모퉁이의 좌표로 해도 되지만 여기선 중심과 반지름으로 했다.
struct Square {
	Coordinate<float> mCenter; // 사각형의 중심
	Coordinate<float> mHalf; // 사각형의 반지름
	int mType; // 해당 사각형이 길인지 벽돌인지 아니면 다른 사물인지 알 수 있는 타입
	Square() { mCenter = { 0.f,0.f }, mHalf = { 1.f,1.f }; mType = 0; }
	Square(const Coordinate<float>& center, const Coordinate<float>& half, const int& type = 0) { mCenter = center, mHalf = half; mType = type; }
	~Square() {}
	std::pair<float, float> GetLeftTop() { return { mCenter.x - mHalf.x, mCenter.y + mHalf.y }; }
	std::pair<float, float> GetRightBottom() { return { mCenter.x + mHalf.x, mCenter.y - mHalf.y }; }
	bool Overlaps(const Square& A) const {
		return abs(mCenter.x - A.mCenter.x) <= mHalf.x + A.mHalf.x
			&& abs(mCenter.y - A.mCenter.y) <= mHalf.y + A.mHalf.y;
	}
	float GetTop() { return mCenter.y + mHalf.y; }
	float GetBottom() { return mCenter.y - mHalf.y; }
	float GetRight() { return mCenter.x + mHalf.x; }
	float GetLeft() { return mCenter.x - mHalf.x; }
};

class Map {
public:
	int mWidth;
	int mHeight;
	// 맵 시작 사각형 중심
	Coordinate<float> mStMapPoint;
	// 맵의 실제 사각형 정보
	std::vector<std::vector<Square>> mMap;
	Map() { mWidth = mHeight = 0; }

	// startCoordiante -> 맵의 첫 블록 사각형의 중심 좌표
	// squareSize -> 맵 사각형 크기 (한 변 크기, 정사각형이라고 가정)
	// mapInfo -> 맵 정보
	Map(const Coordinate<float>& startCoordiante, const float& squareSize, const std::vector<std::vector<int>>& mapInfo)
	{
		mStMapPoint = startCoordiante;
		mWidth = (int)mapInfo[0].size(), mHeight = (int)mapInfo.size();
		float X = startCoordiante.x, Y = startCoordiante.y;
		mMap.resize(mapInfo.size(), std::vector<Square>(mapInfo[0].size(), Square()));
		for (int i = mHeight - 1; i >= 0; i--) {
			for (int j = 0; j < mWidth; j++) {
				mMap[i][j] = std::move(Square({ X,Y }, { (float)squareSize, (float)squareSize }, mapInfo[i][j]));
				X += squareSize;
			}
			X = startCoordiante.x;
			Y += squareSize;
		}
	}

	// 주어진 좌표가 어느 격자에 속하는지 알아내는 함수
	Coordinate<int> GetMapTileAtPoint(const Coordinate<float>& point)
	{
		return { (int)((point.x - mStMapPoint.x + mMap[0][0].mHalf.x) / (mMap[0][0].mHalf.x * 2)),
		(int)((point.y - mStMapPoint.y + mMap[0][0].mHalf.y) / (mMap[0][0].mHalf.y * 2)) };
	}

	// 주어진 맵 좌표가 어느 화면 좌표에 속하는지 알아내는 함수
	Coordinate<float> GetPointAtMapTile(const Coordinate<int>& point)
	{
		return { mStMapPoint.x + point.x * mMap[0][0].mHalf.x * 2 + mMap[0][0].mHalf.x,
		mStMapPoint.y + point.y * mMap[0][0].mHalf.y * 2 + mMap[0][0].mHalf.y };
	}
};

enum class NodeState : int // 걷기, 점프 등의 행동패턴 삽입
{
	Walk,
	Jump,
	Drop
};

// 노드 정보가 담김
// X,Y 좌표 정보, 점프 속도, 해당 좌표로 이동할때 어떤 행동을 취해야 하는지가 담김
class NodeInfo
{
public:
	// 현재 격자의 인덱스, Map 격자를 해당 인덱스로 접근하기 위해 필요
	int X = 0, Y = 0;
	// 해당 격자에서 어느 속도로 점프를 뛰어야 되는지 알기 위한 점프 속도
	float vX = 0, vY = 0;
	NodeState State;
public:
	NodeInfo() { X = Y = 0; vX = vY = 0; State = NodeState::Walk; }
	NodeInfo(int x, int y, float vx, float vy, int iState) { X = x, Y = y, vX = vx, vY = vy, State = (NodeState)iState; }
	NodeInfo(int x, int y, float vx, float vy, NodeState iState) { X = x, Y = y, vX = vx, vY = vy, State = iState; }
};

// 적이 실제로 갈 수 있는 경로를 나타내는 노드
// Map의 한 블록에서 다른 블록으로 연결되는 여러 지점들이 있을 것이다.
// Map의 한 블록(Square) 당 Node 하나다.
// 따라서 vector<vector<Square>> Map의 격자 크기와 vector<vector<Node>> NodeMap의 격자 크기는 같아야 한다.
// 그리고 예를 들어 Map[1][1]에 대응되는 노드는 NodeMap[1][1]가 되어야 한다.
class Node {
public:
	std::shared_ptr<std::vector<NodeInfo>> mLink;
	Node() { mLink = nullptr; }
	Node(std::shared_ptr<std::vector<NodeInfo>> link) { mLink = link; }
	Node(std::vector<NodeInfo>* link) { mLink.reset(link); }
	void AddNode(const NodeInfo& nodeinfo)
	{
		if (mLink == nullptr)
			mLink.reset(new std::vector<NodeInfo>());
		mLink.get()->push_back(nodeinfo);
	}
	void AddNode(std::pair<int, int> XY, std::pair<float, float>velXY, int State)
	{
		if (mLink == nullptr)
			mLink.reset(new std::vector<NodeInfo>());
		mLink.get()->push_back(NodeInfo(XY.first, XY.second, velXY.first, velXY.second, State));
	}
	void AddNode(std::pair<int, int> XY, std::pair<float, float>velXY, NodeState State)
	{
		if (mLink == nullptr)
			mLink.reset(new std::vector<NodeInfo>());
		mLink.get()->push_back(NodeInfo(XY.first, XY.second, velXY.first, velXY.second, State));
	}
};

// 길찾기를 이용할 생명체
class Creature
{
public:
	float mWidth;
	float mHeight;
	float mMaxXSpeed;
	float mJumpSpeed; // 생명체 점프 속도, 각도와 같이 쓰임
	float mGravity; // 생명체가 받는 중력 수치
};

// 맵에 대응되는 노드를 만들기 위해 필요한 것
// 1. 캐릭터 크기 -> 점프 시에 포물선 충돌 감지 시에 필요
// 2. 캐릭터 점프, 최대 좌우 속도 -> 포물선 함수가 속도에 따라 달라짐, 속도 조절 간격에 따라 연산 속도가 달라질 수 있음.
// 3. 블록 하나 당 크기
// 

// 해당 함수는 x 좌표는 왼쪽에서 오른쪽으로 갈 수록 커지고 y 좌표는 아래에서 위로 갈 수록 커지는 좌표계에서 계산된다.
// 맵의 격자는 y축만 반대로 맵의 가장 밑바닥은 맵의 y 인덱스가 가장 큰 녀석이 대응된다.
void NodeMaker(Map& map, std::vector<std::vector<Node>>& nodeMap, const Creature&& creature)
{
	// 새로운 노드맵을 만들기 위해 노드맵을 초기화해준다.
	nodeMap.clear();
	// 노드맵의 격자 크기를 맵의 격자 크기와 같게 해준다.
	nodeMap.resize(map.mHeight, std::vector<Node>(map.mWidth, Node()));

	// 맵의 정보 따오기
	auto& MapInfo = map.mMap;
	float block_width = MapInfo[0][0].mHalf.x, block_height = MapInfo[0][0].mHalf.y;

	// 맵의 격자를 순회하면서 격자 간의 관계가 어떻게 형성되어 있는지 검사한다.
	for (int i = 0; i < map.mHeight; i++)
	{
		for (int j = 0; j < map.mWidth; j++)
		{
			// 벽인 사각형은 노드가 될 수 없다.
			// 바닥이 없는 경우 노드를 만들 수 없다.
			if (MapInfo[i][j].mType == (int)BlockType::Block || i + 1 >= map.mHeight)
				continue;

			// 생명체 크기에 따라 지면 위, 옆으로 몇 블록을 검사해야 하는지 알기 위함.
			// 생명체는 해당 블록을 밣고 있으며 블록 중간 지점에 위치한다고 가정한다.
			// 예를 들어 블록 하나의 높이 길이가 3이고 생명체 크기가 7이라면 생명체가 서있는 곳에서부터
			// (7 / 3)을 올림한 수인 3, 즉 3블록을 위로 검사해야 한다.
			// left_Edge, right_Edge 캐릭터에 맞닿아 있는 양쪽 끝 지면 블록의 x 인덱스
			int hSize = (int)ceil(creature.mHeight / (block_height * 2)),
				wSize = (int)ceil(creature.mWidth / (block_width * 2));

			// 너비를 검사해야 하는 블록 개수가 짝수면 홀수로 만들어 준다.
			// 예를 들어 4블록을 검사해야 한다면 4블록 크기의 생명체를 해당 블록 정가운데에 세워놓기 위해서는
			// 결국 5블록을 검사해야 한다.
			wSize = wSize % 2 ? wSize : wSize + 1;

			int	left_Edge = j - wSize / 2, right_Edge = j + wSize / 2, x, y;

			// 생명체가 서있을 수 있는 지면이 있으면 해당 x 블록 인덱스가 여기에 담김
			std::unordered_set<int> ground_Index;

			// 생명체가 서있을 수 있는 지면이 존재하는지 검사
			for (x = left_Edge; x <= right_Edge; x++)
			{
				if (MapInfo[i + 1][x].mType == (int)BlockType::Block)
					ground_Index.insert(x);
			}

			// 서 있을 수 있는 지면이 있다면 노드를 생성하기 위한 조건 검사
			if (!ground_Index.empty())
			{
				// 해당 블록이 노드를 만들 수 있는 위치인지를 검사
#pragma region calculate_can_make_node
				// 재사용성을 위해 람다로 구현 (점프 노드 착지 지점 연결하는 경우 다시 사용함)
				// x_index, y_index는 생명체와 맞닿아있는 바닥들 인덱스에서 중점 인덱스의 바로 위 블록의 x, y 인덱스여야 한다...
				// 말로는 설명이 어렵기 때문에 그림으로 보면
				//     0   1   2
				// 0  [-] [-] [-]
				// 1  [-] [-] [-]
				// 2   -   -   -
				// 위에서 [-]는 생명체의 부피이다. 그니까 생명체는 가로 3칸, 세로 2칸의 부피를 가진다.
				// - 는 바닥을 나타낸다.
				// 이러한 상황에서 x_index, y_index는 (1, 1)이다.
				// 짝수는 어떻게 하냐고?
				//     0   1   2
				// 0    [-] [-]
				// 1    [-] [-]
				// 2   -   -   -
				// 위와 같이 보면 된다. 이 상황에서 x_index, y_index는 똑같이 (1, 1)이다.
				auto is_fit = [&](int x_index, int y_index, bool ground_opt = false)->bool
				{
					bool is_Fit = true, has_ground = true;
					int left = x_index - wSize / 2, right = x_index + wSize / 2;

					// 너비로 먼저 돌고 루프 안에서 높이를 계산한다.
					for (x = left; x <= right; x++)
					{
						// 맵의 좌우를 뚫고 검사를 진행할 수 없다.
						if (x < 0 || x >= map.mWidth) {
							is_Fit = false;
							break;
						}

						// 높이 검사
						for (y = y_index; y >= 0 && y > y_index - hSize; y--)
							is_Fit &= MapInfo[y][x].mType == (int)BlockType::Space;

						// 천장을 뚫고 검사를 진행할 수 없다.
						if (y < 0) {
							is_Fit = false;
							break;
						}

						// 바닥 검사 옵션이 켜져있으면 캐릭터 밑의 바닥도 검사함
						if (ground_opt) {
							has_ground &= MapInfo[y_index + 1][x].mType == (int)BlockType::Block;
						}
					}

					return ground_opt ? (is_Fit && has_ground) : is_Fit;
				};

				// 해당 블록에 오브젝트가 서있을 수 없으니 노드도 찍을 수 없고 그냥 넘김
				if (!is_fit(j, i))
					continue;
#pragma endregion

				// 바로 양옆 노드를 연결하기 위한 조건 검사
#pragma region link_side_node

				// 왼쪽 옆 노드 연결 확인
				// 캐릭터의 왼쪽 끝보다 한 칸 더 옆 블록의 맵 인덱스 획득
				int left_end = left_Edge - 1;

				// 생명체 바닥을 볼 때 오른쪽 끝 블록만 블록이 있는 상태인데 왼쪽으로 이동할 곳 바닥이 존재하지 않으면 왼쪽으로 이동할 수 없다.
				// 왼쪽으로 갈 곳이 맵 인덱스를 벗어나도 왼쪽으로 이동할 수 없다.
				bool can_Move_Left = left_end >= 0 && !(ground_Index.size() == 1 && ground_Index.find(j + wSize / 2) != ground_Index.end() && MapInfo[i + 1][left_end].mType == (int)BlockType::Space);

				/*
				for (x = left_end; x >= 0 && x < j && !can_Move_Left; x++)
				{
					if (MapInfo[i + 1][x].mType == (int)BlockType::Block)
						can_Move_Left = true;
				}
				*/

				// 캐릭터의 왼쪽 끝보다 한 칸 더 옆 블록의 위쪽을 검사해 위쪽에 막히는 블록이 있는지 없는지 검사한다.
				for (y = i; y >= 0 && y > i - hSize && can_Move_Left; y--)
					can_Move_Left &= MapInfo[y][left_end].mType == (int)BlockType::Space;
				can_Move_Left &= y >= 0;

				// 왼쪽에 노드 추가
				if (can_Move_Left)
					nodeMap[i][j].AddNode({ left_end,i }, { -creature.mMaxXSpeed,0.f }, (int)NodeState::Walk);

				// 오른쪽 옆 노드 연결 확인
				// 캐릭터의 오른쪽 끝보다 한 칸 더 옆 블록의 맵 인덱스 획득
				int right_end = right_Edge + 1;

				// 생명체 바닥을 볼 때 오른쪽 끝 블록만 블록이 있는 상태인데 왼쪽으로 이동할 곳 바닥이 존재하지 않으면 왼쪽으로 이동할 수 없다.
				// 왼쪽으로 갈 곳이 맵 인덱스를 벗어나도 왼쪽으로 이동할 수 없다.
				bool can_Move_Right = right_end < map.mWidth && !(ground_Index.size() == 1 && ground_Index.find(j - wSize / 2) != ground_Index.end() && MapInfo[i + 1][right_end].mType == (int)BlockType::Space);

				/*
				for (x = right_end; x < map.mWidth && x > j && !can_Move_Right; x--)
				{
					if (MapInfo[i + 1][x].mType == (int)BlockType::Block)
						can_Move_Right = true;
				}
				*/

				// 캐릭터의 오른쪽 끝보다 한 칸 더 옆 블록의 위쪽을 검사해 위쪽에 막히는 블록이 있는지 없는지 검사한다.
				for (y = i; y >= 0 && y > i - hSize && can_Move_Right; y--)
					can_Move_Right &= MapInfo[y][right_end].mType == (int)BlockType::Space;
				can_Move_Right &= y >= 0;

				// 오른쪽에 노드 추가
				if (can_Move_Right)
					nodeMap[i][j].AddNode({ right_end,i }, { creature.mMaxXSpeed,0.f }, (int)NodeState::Walk);

#pragma endregion

				// 떨어질 수 있는 공간에 대한 노드를 연결하기 위한 조건 검사
#pragma region link_fall_node

				// 왼쪽으로 이동할 경우 바닥이 단 한개도 존재하지 않는다면 떨어진다.
				// can_Move_Left에서 왼쪽 이동 노드를 이미 추가했다면 왼쪽으로 떨어질 노드를 볼 필요가 없다.
				bool can_Fall_Left = !can_Move_Left && left_end >= 0 && ground_Index.size() == 1 && ground_Index.find(j + wSize / 2) != ground_Index.end() && MapInfo[i + 1][left_end].mType == (int)BlockType::Space;

				// 바닥 인덱스 초기화
				int bottom_Index = -1;

				// 생명체가 떨어질 공간을 탐색함
				for (y = i + 2; can_Fall_Left && bottom_Index < 0; y++) {
					for (x = left_Edge - 1; x <= right_Edge - 1; x++) {
						// 탐색 도중 생명체를 가로막는 것이 있다면 바로 윗 y 인덱스가 추락 지점이다.
						if (MapInfo[y][x].mType == (int)BlockType::Block) {
							bottom_Index = y - 1;
							break;
						}
					}
				}

				// 추락 노드 추가
				if (can_Fall_Left)
					nodeMap[i][j].AddNode({ left_end,bottom_Index }, { -creature.mMaxXSpeed,0.f }, (int)NodeState::Walk);

				// 오른쪽으로 이동할 경우 바닥이 단 한개도 존재하지 않는다면 떨어진다.
				// can_Move_Right에서 오른쪽 이동 노드를 이미 추가했다면 오른쪽으로 떨어질 노드를 볼 필요가 없다.
				bool can_Fall_Right = !can_Move_Right && right_end < map.mWidth&& ground_Index.size() == 1 && ground_Index.find(j - wSize / 2) != ground_Index.end() && MapInfo[i + 1][right_end].mType == (int)BlockType::Space;

				// 바닥 인덱스 초기화
				bottom_Index = -1;

				// 생명체가 떨어질 공간을 탐색함
				for (y = i + 2; can_Fall_Right && bottom_Index < 0; y++) {
					for (x = left_Edge + 1; x <= right_Edge + 1; x++) {
						// 탐색 도중 생명체를 가로막는 것이 있다면 바로 윗 y 인덱스가 추락 지점이다.
						if (MapInfo[y][x].mType == (int)BlockType::Block) {
							bottom_Index = y - 1;
							break;
						}
					}
				}

				if (can_Fall_Right)
					nodeMap[i][j].AddNode({ right_end,bottom_Index }, { creature.mMaxXSpeed,0.f }, (int)NodeState::Walk);
#pragma endregion

				// 점프해서 갈 수 있는 노드를 연결하기 위한 조건 검사
#pragma region link_jump_node

				// 0 ~ 180도를 특정 각도로 끊어서 생명체가 그 방향으로 힘을 주고 뛴다고 가정한다.
				// 10도씩 끊어서 포물선 레이캐스팅을 할 건지 20도씩 할 건지에 따라 연산 속도가 달라진다.
				// 각도를 세밀하게 쪼개면서 검사할 수록 연산량이 많아진다.
				// 생명체가 주는 힘은 mJumpSpeed로 일정하다고 가정한다.
				// 만약 mJumpSpeed 이하의 힘으로 점프가 가능하다면 mJumpSpeed 이하의 힘으로 뛰는 경우에 대해 검사해야 하기에 연산이 많아진다.

				// 각도 정의, degree_gap인 20도 마다 포물선을 그려 계산하기로 하고 검사 시작 각도는 20도이다.
				int degree, degree_gap = 20, radius_start = 20;

				// 각도를 라디안으로 바꿔주는 람다 함수
				auto deg_to_rad = [](int deg)->float { return (float)(deg * (3.14159265359 / 180.f)); };

				// 각도 검사
				for (degree = radius_start; degree <= 180; degree += degree_gap)
				{
					float x_speed = cosf(deg_to_rad(degree)); // x축 속도는 등속도 운동
					float y_speed = sinf(deg_to_rad(degree)); // y축 속도는 중력에 의해 등가속도 운동을 한다.

					// 생명체의 중심 좌표 획득
					Coordinate<float> center_xy = map.GetPointAtMapTile({ j,i });
					center_xy.y = center_xy.y - block_height + creature.mHeight / 2;

					// 생명체의 충돌을 알기 위한 사각형 생성
					Square creature_sq(center_xy, { creature.mWidth / 2, creature.mHeight / 2 });

					// tick_gap이 너무 크면 프물선 레이캐스팅 정확도가 낮아진다.
					// 레이캐스팅 점 간격이 너무 넓어서 충돌 계산을 해야하는 블록을 건너뛰어버리는 불상사가 발생할 수 있다.
					int tick_gap = 10, tick_start = 10, tick = tick_start;
					std::vector <Coordinate<int>> collide_block;

					// 시간(틱)을 증가시키면서 포물선 레이캐스팅 수행
					while (!collide_block.empty())
					{
						// 생명체의 예전 상태 저장
						Square prev_creature = creature_sq;
						// 생명체의 사각형 중앙 좌표는 점프를 하면서 바뀐다.
						creature_sq.mCenter = { creature_sq.mCenter.x + x_speed * tick, creature_sq.mCenter.y + (y_speed - creature.mGravity * tick) * tick };
						// 캐릭터 중앙과 충돌하는 맵 타일을 구한다.
						Coordinate<int> maptile_xy = map.GetMapTileAtPoint(creature_sq.mCenter);

						// BFS 방식으로 생명체와 맵 블록의 충돌을 계산한다.
						// 큐에는 생명체와 충돌된 맵의 좌표가 들어간다.
						int X[4] = { 1,-1,0,0 }, Y[4] = { 0,0,1,-1 };

						// 속도 때문에 방문 배열은 unordered_set을 사용한다.
						struct coordinate_hash {
							size_t operator()(Coordinate<int> A) const {
								unsigned h = 37;
								h = (h * 54059) ^ (A.x * 76963);
								h = (h * 54059) ^ (A.y * 76963);
								return h;
							}
						};
						struct coordinate_hash_equal {
							bool operator()(const Coordinate<int>& A, const Coordinate<int>& B) const {
								return A.x == B.x && A.y == B.y;
							}
						};
						std::unordered_set<Coordinate<int>, coordinate_hash, coordinate_hash_equal> visited;

						std::queue<Coordinate<int>> bfs_Q;
						bfs_Q.push(maptile_xy);
						while (!bfs_Q.empty())
						{
							Coordinate<int> front = bfs_Q.front();
							bfs_Q.pop();

							for (int u = 0; u < 4; u++) {
								Coordinate<int> cur = { X[u] + front.x, Y[u] + front.y };

								// 생명체와 충돌을 하지도 않으면 그쪽 방향으로 더 탐색할 필요도 없다.
								if (!creature_sq.Overlaps(MapInfo[cur.y][cur.x]))
									continue;

								// 맵과 생명체의 히트박스가 겹침으로 큐에 삽입함.
								if (visited.find(cur) == visited.end()) {
									visited.insert(cur);
									bfs_Q.push(cur);

									// 맵 블록과 생명체가 충돌을 했는데 해당 블록이 벽돌이면 collide_block에 담는다.
									// 여기서 블록이 생명체 옆으로 충돌했는지 위로 충돌했는지 미리 알면 연산 속도 더 빠르게 가능
									if (MapInfo[cur.y][cur.x].mType == (int)BlockType::Block)
										collide_block.push_back(cur);
								}
							}
						}

						bool can_Landing = true;

						// 포물선 레이캐스팅으로 생명체와 충돌한 블록 검사
						for (auto& block : collide_block) {
							// 예전 생물체의 y축 속도를 구한다.
							float prev_y_speed = y_speed - creature.mGravity * (tick - tick_gap);
							// 생명체가 떨어지는 중이고 예전 상태가 부딫혔던 블록 위라면 아래 조건 중에 한개여야 한다.
							if (prev_y_speed < 0 && prev_creature.GetBottom() > MapInfo[block.y][block.x].GetTop()) {
								can_Landing &= (
									// 블록은 생명체 너비 안에 있다.
									(prev_creature.GetLeft() <= MapInfo[block.y][block.x].GetLeft() && MapInfo[block.y][block.x].GetRight() <= prev_creature.GetRight()) ||
									// 블록은 생명체 왼쪽으로 약간 삐져나왔다.
									(MapInfo[block.y][block.x].GetLeft() < prev_creature.GetLeft() && prev_creature.GetLeft() < MapInfo[block.y][block.x].GetRight()) ||
									// 블록은 생명체 오른쪽으로 약간 삐져나왔다.
									(MapInfo[block.y][block.x].GetRight() > prev_creature.GetRight() && prev_creature.GetRight() > MapInfo[block.y][block.x].GetLeft()) ||
									// 블록이 생명체 너비보다 크다.
									(MapInfo[block.y][block.x].GetLeft() < prev_creature.GetLeft() && prev_creature.GetRight() < MapInfo[block.y][block.x].GetRight()));
							}
						}

						// 착지 조건이 갖춰졌다면 노드를 만들어준다.
						if (can_Landing && !collide_block.empty()) {
							Coordinate<int> creature_left_block = map.GetMapTileAtPoint({ creature_sq.GetLeft(), creature_sq.GetBottom() });
							int creature_left_x = creature_left_block.x, creature_y = creature_left_block.y - 1;
							int creature_right_x = map.GetMapTileAtPoint({ creature_sq.GetRight(), creature_sq.GetBottom() }).x;
							int creature_center_x = map.GetMapTileAtPoint(creature_sq.mCenter).x;

							// 첫번째 인자 : 생명체의 중심 x 좌표가 속하는 블록의 x 인덱스와 충돌한 블록과의 거리
							// 두번째 인자 : 충돌한 블록의 x 인덱스
							std::vector<std::pair<int, int>> coordinate_ary;
							coordinate_ary.reserve(creature_right_x - creature_left_x + 1);
							for (x = creature_left_x; x <= creature_right_x; x++)
								coordinate_ary.push_back({ abs(creature_center_x - x), x });
							// 생명체 중심과 가장 가까운 블록부터 조사하게 정렬함
							std::sort(coordinate_ary.begin(), coordinate_ary.end());

							// 좌표 배열을 순회하면서 생명체가 들어갈 수 있는 좌표면 점프 노드 착지 지점에 해당하는 좌표를 확정 짓는다.
							for (const auto& coordinate : coordinate_ary) {
								if (is_fit(coordinate.second, creature_y, true)) {
									x = coordinate.second;
									break;
								}
							}

							// 착지 지점과 가장 가까운 블록의 중심 x, creature_y에 점프 노드를 넣어준다.
							nodeMap[i][j].AddNode({ x, creature_y }, { x_speed, y_speed }, (int)NodeState::Jump);
						}

						tick += tick_gap;
					}
				}

#pragma endregion
			}
		}
	}
}
