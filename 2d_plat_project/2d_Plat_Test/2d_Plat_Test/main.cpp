#include <bits/stdc++.h>
using namespace std;

// olc ���ӿ��� ��� �� ������ ���� https://community.onelonecoder.com/2020/05/20/how-to-attribute-credit-cite-the-olcpixelgameengine/
// ���� ���� ȭ�鿡 olc �ΰ� �ھ��ָ� �Ǵ� ��. �������� ����

// ��ǥ ����
template <typename T>
struct Coordinate
{
	T x;
	T y;
	Coordinate() { x = y = static_cast<T>(0); }
	Coordinate(T&& X, T&& Y) { x = X; y = Y; }
	Coordinate(pair<T, T> &&XY) { x = XY.first; y = XY.second; }
	Coordinate(initializer_list<T> &&XY) { x = *XY.begin(); y = *(XY.begin() + 1); }
};

// ���� Ÿ�� ����
enum class BlockType : int {
	Space = 0, // �����
	Block = 1, // ���� ��
};

// A* �˰���, ��鿡���� ���� ����, �߷��� �ۿ��ϴ� �÷����� ���ӿ����� �̸� �����ؾ� ��.
void AstarAlgorithm(const vector<vector<int>>& Map, const Coordinate<int>& StartPoint, const Coordinate<int>& EndPoint, bool EdgeOption = true)
{
	// tuple<int,int,int>���� get<0>()�� ����ġ(G+H)�� F ��, get<1>()�� x ��ǥ, get<2>()�� y ��ǥ
	int mapWidth = (int)Map[0].size(), mapHeight = (int)Map.size();

	// G�� �缱�̸� ����ġ 14�� �ְ�, ���� �����̸� ����ġ 10�� �ش�.
	auto getG = [](const Coordinate<int>& A, const Coordinate<int>& B)->int { return abs(A.x - B.x) && abs(A.y - B.y) ? 14 : 10; };
	
	// H�� �޸���ƽ �Ÿ��� ���
	auto getH = [&](const Coordinate<int>& A)->int { return 10 * (abs(A.x - EndPoint.x) + abs(A.y - EndPoint.y)); };
	
	// is_ValidXY�� �־��� ��ǥ�� �ùٸ��� Ȯ���ϴ� �Լ�
	auto is_ValidXY = [&](const Coordinate<int>& A)->bool {return (A.x >= 0 && A.y >= 0 && A.x < mapWidth && A.y < mapHeight); };
	
	// �־��� ���� ��ǥ�� ���� ��ǥ�� �̻��� ���
	if (StartPoint.x < 0 || StartPoint.y < 0 || EndPoint.x < 0 || EndPoint.y < 0
		|| StartPoint.x >= mapWidth || StartPoint.y >= mapHeight || EndPoint.x >= mapWidth || EndPoint.y >= mapHeight
		|| Map[StartPoint.y][StartPoint.x] || Map[EndPoint.y][EndPoint.x]) {
		std::cout << "Plz Set the Start, End Point currectly!\n";
		return;
	}

	// �ʱ� �Ÿ��� �ſ� ũ��
	vector<vector<int>> Dist(mapHeight, vector<int>(mapWidth, std::numeric_limits<int>::max()));
	// ��� ������ �迭�� {-1,-1}�� �ʱ�ȭ
	vector<vector<Coordinate<int>>> TraceBack(mapHeight, vector<Coordinate<int>>(mapWidth, { -1,-1 }));
	// ���� ã�Ҵ��� ����
	bool is_FindPath = false; 
	// 8 ����, 1~4 ������ ���� ����, 5~8 ������ �缱 ����
	short Dir[8][2] = { {0,1},{1,0},{0,-1},{-1,0},{1,1},{-1,-1},{1,-1},{-1,1} };
	// �𼭸� �ɼǿ� ���� ���� ����, �𼭸� �ɼ��� ������ �缱 �������ε� �̵��� �����ϴٰ� �Ǵ���.
	short DirSize = EdgeOption ? 8 : 4; 
	// �켱���� ť�� ���� �������, ������� �����ϰ� ����, ť�� �� ������ G+H ���� ���� ���� �༮�� ���� �´�.
	// ť�� ���� �ڷᱸ���� tuple�� { F(G+H), x��ǥ, y��ǥ } �� �����ȴ�.
	priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> Q;
	// �ʱ� �Ÿ��� 0 ���� ����
	Dist[StartPoint.y][StartPoint.x] = 0;
	// ������ ������ H ���� ����, �ʱ⿣ �̰��� F���� ��
	int h = getH(StartPoint);
	Q.push({ h, StartPoint.x, StartPoint.y });

	while (!Q.empty())
	{
		int F = get<0>(Q.top());
		int X = get<1>(Q.top());
		int Y = get<2>(Q.top());
		Q.pop();

		// �������� ���������� �켱���� ť Ž���� ����
		if (X == EndPoint.x && Y == EndPoint.y) {
			is_FindPath = true;
			break;
		}

		// ���� �Ÿ� ����ġ�� ����
		int CurG = F - getH({ X,Y });

		// ��ϵ� �Ÿ� ����ġ���� ũ�ٸ� ť���� �ٸ� �༮�� Ž���Ѵ�.
		if (CurG > Dist[Y][X])
			continue;

		// ������ ��� Ž���ϸ鼭 F���� �Ÿ� ����ġ�� ����Ѵ�.
		for (int i = 0; i < DirSize; i++)
		{
			int nX = X + Dir[i][0], nY = Y + Dir[i][1];

			// ��ǥ�� �ùٸ� ��ǥ���� �˻��Ѵ�. ���� ���� 1�̸� ������ �ν��Ѵ�. 0�� ��� �ν��Ѵ�.
			if (!is_ValidXY({ nX, nY }) || Map[Y][X])
				continue;
			int G = CurG + getG({ nX,nY }, { X,Y });

			// �̹� ��ϵ� �Ÿ� ����ġ���� ���� �༮�� ��Ÿ���ٸ� �̸� ����ϰ� ť�� �ִ´�.
			if (G < Dist[nY][nX]) {
				Dist[nY][nX] = G;
				// ������ �ÿ� ���� �θ� ��ǥ�� ����Ѵ�.
				TraceBack[nY][nX] = { X,Y };
				Q.push({ G + getH({nX, nY}), nX, nY });
			}
		}
	}

	// ������ �� �ִ� ��ΰ� ���� ���
	if (!is_FindPath) {
		std::cout << "Can't Reach the Goal!\n";
		return;
	}

	// �����ÿ��� ���� ��ǥ���� ���� ��ǥ�� �������� �ϰ� �ȴ�.
	Coordinate<int> B = EndPoint;
	// ���� �� ��ǥ�� ���� �Ǵ� deque
	deque<Coordinate<int>> Way;
	while (B.x != -1) {
		Way.push_front(B);
		B = TraceBack[B.y][B.x];
	}

	// ���� ����� �˷��ֱ� ���� ����
	vector<vector<int>> TraceResult = Map;

	// �������� ������ ��¿��� �����Ϸ��� Ȱ��ȭ
	// Way.pop_back(); Way.pop_front();
	
	for (const auto& A : Way)
		TraceResult[A.y][A.x] = (int)1e9;
	std::cout << "\nTravel Finished!\n" << endl;
	for (const auto& A : TraceResult) {
		for (const auto& B : A) {
			string printBrick = ". ";
			if (B == 1) printBrick = "X ";
			else if (B == (int)1e9) printBrick = "+ ";
			std::cout << printBrick;
		}
		std::cout << "\n";
	}
}

// AABB �浹 �˻� ���� ���簢�� Ŭ����
// �� �������� ��ǥ�� �ص� ������ ���⼱ �߽ɰ� ���������� �ߴ�.
struct Square {
	Coordinate<float> mCenter; // �簢���� �߽�
	Coordinate<float> mHalf; // �簢���� ������
	int mType; // �ش� �簢���� ������ �������� �ƴϸ� �ٸ� �繰���� �� �� �ִ� Ÿ��
	Square() { mCenter = { 0.f,0.f }, mHalf = { 1.f,1.f }; }
	Square(const Coordinate<float>& center, const Coordinate<float>& half, const int& type) { mCenter = center, mHalf = half; mType = type; }
	~Square() {}
	pair<float, float> GetLeftTop() { return { mCenter.x - mHalf.x, mCenter.y + mHalf.y }; }
	pair<float, float> GetRightBottom() { return { mCenter.x + mHalf.x, mCenter.y - mHalf.y }; }
	bool Overlaps(const Square& A) const {
		return abs(mCenter.x - A.mCenter.x) <= mHalf.x + A.mHalf.x
			&& abs(mCenter.y - A.mCenter.y) <= mHalf.y + A.mHalf.y;
	}
};

class Map {
public:
	int mWidth;
	int mHeight;
	// �� ���� �簢�� �߽�
	Coordinate<float> mStMapPoint;
	// ���� ���� �簢�� ����
	vector<vector<Square>> mMap;
	Map() { mWidth = mHeight = 0; }
	// startCoordiante -> ���� ù ��� �簢���� �߽� ��ǥ
	// squareSize -> �� �簢�� ũ�� (�� �� ũ��, ���簢���̶�� ����)
	// mapInfo -> �� ����
	Map(const Coordinate<float>& startCoordiante, const float& squareSize, const vector<vector<int>>& mapInfo)
	{
		mStMapPoint = startCoordiante;
		mWidth = (int)mapInfo[0].size(), mHeight = (int)mapInfo.size();
		float X = startCoordiante.x, Y = startCoordiante.y;
		mMap.resize(mapInfo.size(), vector<Square>(mapInfo[0].size(), Square()));
		for (int i = mHeight - 1; i >= 0; i--) {
			for (int j = 0; j < mWidth; j++) {
				mMap[i][j] = move(Square({ X,Y }, { (float)squareSize, (float)squareSize }, mapInfo[i][j]));
				X += squareSize;
			}
			X = startCoordiante.x;
			Y += squareSize;
		}
	}
	// �־��� ��ǥ�� ��� ���ڿ� ���ϴ��� �˾Ƴ��� �Լ�
	Coordinate<int> GetMapTileAtPoint(const Coordinate<float>& point) {
		return { (int)((point.x - mStMapPoint.x + mMap[0][0].mHalf.x) / (mMap[0][0].mHalf.x * 2)),
		(int)((point.y - mStMapPoint.y + mMap[0][0].mHalf.y) / (mMap[0][0].mHalf.y * 2)) };
	}
};

enum class NodeState : int // �ȱ�, ���� ���� �ൿ���� ����
{
	Walk,
	Jump,
	Drop
};

// ��� ������ ���
// X,Y ��ǥ ����, ���� �ӵ�, �ش� ��ǥ�� �̵��Ҷ� � �ൿ�� ���ؾ� �ϴ����� ���
class NodeInfo
{
public:
	// ���� ������ �ε���, Map ���ڸ� �ش� �ε����� �����ϱ� ���� �ʿ�
	int X = 0, Y = 0;
	// �ش� ���ڿ��� ��� �ӵ��� ������ �پ�� �Ǵ��� �˱� ���� ���� �ӵ�
	float vX = 0, vY = 0;
	NodeState State;
public:
	NodeInfo() { X = Y = 0; vX = vY = 0; State = NodeState::Walk; }
	NodeInfo(int x, int y, float vx, float vy, int iState) { X = x, Y = y, vX = vx, vY = vy, State = (NodeState)iState; }
	NodeInfo(int x, int y, float vx, float vy, NodeState iState) { X = x, Y = y, vX = vx, vY = vy, State = iState; }
};

// ���� ������ �� �� �ִ� ��θ� ��Ÿ���� ���
// Map�� �� ��Ͽ��� �ٸ� ������� ����Ǵ� ���� �������� ���� ���̴�.
// Map�� �� ���(Square) �� Node �ϳ���.
// ���� vector<vector<Square>> Map�� ���� ũ��� vector<vector<Node>> NodeMap�� ���� ũ��� ���ƾ� �Ѵ�.
// �׸��� ���� ��� Map[1][1]�� �����Ǵ� ���� NodeMap[1][1]�� �Ǿ�� �Ѵ�.
class Node {
public:
	shared_ptr<vector<NodeInfo>> mLink;
	Node() { mLink = nullptr; }
	Node(shared_ptr<vector<NodeInfo>> link) { mLink = link; }
	Node(vector<NodeInfo>* link) { mLink.reset(link); }
	void AddNode(const NodeInfo& nodeinfo)
	{
		if (mLink == nullptr)
			mLink.reset(new vector<NodeInfo>());
		mLink.get()->push_back(nodeinfo);
	}
	void AddNode(pair<int, int> XY, pair<float, float>velXY, int State)
	{
		if (mLink == nullptr)
			mLink.reset(new vector<NodeInfo>());
		mLink.get()->push_back(NodeInfo(XY.first, XY.second, velXY.first, velXY.second, State));
	}
	void AddNode(pair<int, int> XY, pair<float, float>velXY, NodeState State)
	{
		if (mLink == nullptr)
			mLink.reset(new vector<NodeInfo>());
		mLink.get()->push_back(NodeInfo(XY.first, XY.second, velXY.first, velXY.second, State));
	}
};

// ��ã�⸦ �̿��� ����ü
class Creature
{
public:
	float mWidth;
	float mHeight;
	float mMaxXSpeed;
	float mMaxYSpeed;
};

// �ʿ� �����Ǵ� ��带 ����� ���� �ʿ��� ��
// 1. ĳ���� ũ�� -> ���� �ÿ� ������ �浹 ���� �ÿ� �ʿ�
// 2. ĳ���� ����, �ִ� �¿� �ӵ� -> ������ �Լ��� �ӵ��� ���� �޶���, �ӵ� ���� ���ݿ� ���� ���� �ӵ��� �޶��� �� ����.
// 3. ��� �ϳ� �� ũ��
// 

void NodeMaker(Map& map, vector<vector<Node>>& nodeMap, const Creature && creature, float gravity)
{
	// ���ο� ������ ����� ���� ������ �ʱ�ȭ���ش�.
	nodeMap.clear();
	// ������ ���� ũ�⸦ ���� ���� ũ��� ���� ���ش�.
	nodeMap.resize(map.mHeight, vector<Node>(map.mWidth, Node()));

	// ���� ���ڸ� ��ȸ�ϸ鼭 ���� ���� ���谡 ��� �����Ǿ� �ִ��� �˻��Ѵ�.
	auto& MapInfo = map.mMap;
	for (int i = 0; i < map.mHeight; i++)
	{
		for (int j = 0; j < map.mWidth; j++)
		{
			// ���� �簢���� ��尡 �� �� ����.
			if (MapInfo[i][j].mType == (int)BlockType::Block)
				continue;

			// ������ �����ϸ� �˻�
			if (i + 1 < map.mHeight && MapInfo[i + 1][j].mType == (int)BlockType::Block) 
			{
				// �ش� ����� ��带 ���� �� �ִ� ��ġ������ �˻�
#pragma region calculate_can_make_node
				// ����ü ũ�⿡ ���� ���� ��, ������ �� ����� �˻��ؾ� �ϴ��� �˱� ����.
				// ����ü�� �ش� ����� �P�� ������ ��� �߰� ������ ��ġ�Ѵٰ� �����Ѵ�.
				// ���� ��� ��� �ϳ��� ���� ���̰� 3�̰� ����ü ũ�Ⱑ 7�̶�� ����ü�� ���ִ� ����������
				// (7 / 3)�� �ø��� ���� 3, �� 3����� ���� �˻��ؾ� �Ѵ�.
				int hSize = (int)ceil(creature.mHeight / (MapInfo[i][j].mHalf.y * 2)),
					wSize = (int)ceil(creature.mWidth / (MapInfo[i][j].mHalf.x * 2)),
					x, y;
				bool is_Fit = true;

				// �ʺ� �˻��ؾ� �ϴ� ��� ������ ¦���� Ȧ���� ����� �ش�.
				// ���� ��� 4����� �˻��ؾ� �Ѵٸ� 4��� ũ���� ����ü�� �ش� ��� ������� �������� ���ؼ���
				// �ᱹ 5����� �˻��ؾ� �Ѵ�.
				wSize = wSize % 2 ? wSize : wSize + 1;

				// �ʺ�� ���� ���� ���� �ȿ��� ���̸� ����Ѵ�.
				for (x = j - wSize / 2; x <= j + wSize / 2; x++)
				{
					// ���� �¿츦 �հ� �˻縦 ������ �� ����.
					if (x < 0 || x >= map.mWidth) {
						is_Fit = false;
						break;
					}

					// ���� �˻�
					for (y = i; y >= 0 && y > i - hSize; y--)
						is_Fit &= MapInfo[y][x].mType == (int)BlockType::Space;

					// õ���� �հ� �˻縦 ������ �� ����.
					if(y < 0) {
						is_Fit = false;
						break;
					}
				}
				
				// �ش� ��Ͽ� ������Ʈ�� ������ �� ������ ��嵵 ���� �� ���� �׳� �ѱ�
				if (!is_Fit)
					continue;
#pragma endregion

				// �ٷ� �翷 ��带 �����ϱ� ���� ���� �˻�
#pragma region link_side_node

				// ���� �� ��� ���� Ȯ��
				// ĳ������ ���� ������ �� ĭ �� �� ����� �� �ε��� ȹ��
				int left_end = j - wSize / 2 - 1;
				
				// ĳ���� ���� �� ���� �߾ӱ��� ������ �� ����̶� �ִٸ�
				// �������� �̵��� �� �ִ� ���ɼ��� �ִ�.
				bool can_Move_Left = false;
				for (x = left_end; x >= 0 && x < j && !can_Move_Left; x++)
				{
					if (MapInfo[i + 1][x].mType == (int)BlockType::Block)
						can_Move_Left = true;
				}

				// ĳ������ ���� ������ �� ĭ �� �� ����� ������ �˻��� ���ʿ� ������ ����� �ִ��� ������ �˻��Ѵ�.
				for (y = i; y >= 0 && y > i - hSize && can_Move_Left; y--)
					can_Move_Left &= MapInfo[y][left_end].mType == (int)BlockType::Space;
				can_Move_Left &= y >= 0;

				// ���ʿ� ��� �߰�
				if (can_Move_Left)
					nodeMap[i][j].AddNode({ left_end,i }, { -creature.mMaxXSpeed,0.f }, (int)NodeState::Walk);

				// ������ �� ��� ���� Ȯ��
				// ĳ������ ������ ������ �� ĭ �� �� ����� �� �ε��� ȹ��
				int right_end = j + wSize / 2 + 1;

				// ĳ���� ������ �� ���� �߾ӱ��� ������ �� ����̶� �ִٸ�
				// ���������� �̵��� �� �ִ� ���ɼ��� �ִ�.
				bool can_Move_Right = false;
				for (x = right_end; x < map.mWidth && x > j && !can_Move_Right; x--)
				{
					if (MapInfo[i + 1][x].mType == (int)BlockType::Block)
						can_Move_Right = true;
				}

				// ĳ������ ������ ������ �� ĭ �� �� ����� ������ �˻��� ���ʿ� ������ ����� �ִ��� ������ �˻��Ѵ�.
				for (y = i; y >= 0 && y > i - hSize && can_Move_Right; y--)
					can_Move_Right &= MapInfo[y][right_end].mType == (int)BlockType::Space;
				can_Move_Right &= y >= 0;

				// �����ʿ� ��� �߰�
				if (can_Move_Right)
					nodeMap[i][j].AddNode({ right_end,i }, { creature.mMaxXSpeed,0.f }, (int)NodeState::Walk);

#pragma endregion

				// ������ �� �ִ� ������ ���� ��带 �����ϱ� ���� ���� �˻�
#pragma region link_fall_node


#pragma endregion

				// �����ؼ� �� �� �ִ� ��带 �����ϱ� ���� ���� �˻�
#pragma region link_jump_node
				

#pragma endregion
			}
		}
	}
}

/*
void NodeMaker(Map& Map, vector<vector<Node>>& NodeMap, const pair<float, float>& ObjHalfSize, const pair<float, float>& MaxSpeed, float Gravity)
{
	NodeMap.clear();
	NodeMap.resize(Map.mHeight, vector<Node>(Map.mWidth, Node()));

	auto& MapInfo = Map.mMap;
	for (int i = 0; i < Map.mHeight; i++)
	{
		for (int j = 0; j < Map.mWidth; j++)
		{
			// ���� �簢���� ��尡 �� �� ����.
			if (MapInfo[i][j].mType == 1)
				continue;

			// ������ �����ϸ� �˻�
			if (i + 1 < Map.mHeight && MapInfo[i + 1][j].mType == 1) {

				// �� ĳ���� ũ�Ⱑ �� �� �ִ� ������ �ִ��� �˻�
				float X = MapInfo[i][j].mCenter.first, Y = MapInfo[i][j].mCenter.second + MapInfo[i][j].mHalf.second + 0.2f;
				int hSize = (int)ceil(ObjHalfSize.second * 2 / (float)MapInfo[i][j].mHalf.second),
					wSize = (int)ceil(ObjHalfSize.first * 2 / (float)MapInfo[i][j].mHalf.first), k; // hSize, wSize�� ���� ũ�⿡ ���� ����, �ʺ� ��� �� �� �˻��ؾ��ϴ��� ũ��
				bool is_Fit = true;

				// �ش� ��Ͽ� ������Ʈ�� �� �� �ִ��� ũ�� �˻�
				for (k = i; k >= 0 && k > i - hSize; k--)
					is_Fit &= MapInfo[k][j].mType != 1;
				is_Fit = k >= 0 ? is_Fit : false; // k�� ������� ���� õ���� �Ѿ�ٴ� ���̹Ƿ� false�� ����� ��
				if (!is_Fit) continue; // �ش� ��Ͽ� ������Ʈ�� ������ �� ������ ��嵵 ���� �� ���� �׳� �ѱ�

				// �� ĳ����(������Ʈ)�� ��, ��� �����̴� ��� ĳ���� Ű�� �ɸ��� ���� ����� �־� �� ������ �ٷ� �ɾ �� ���� ��� ���
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
						// �������� ������ ���Ѿ��� �̵��� ������ ����, ���� ���� ���Ƽ�� �ִٸ� for�� ���� �ʿ�
						for (; p < Map.mHeight; p++) if (MapInfo[p][t].mType == 1) break;

						// ���� �˻�� �ٴ� ��� �� ĭ �� �׸��� ��ĭ ���� ���⿡ ��带 �����.
						if (p < Map.mHeight)
							return p - 1;
						// NodeMap[i][j].AddNode({ t,p - 1 }, { 2e9,2e9 }, (int)Node::NodeState::Walk);
					}
					return -1;
				};

				// �� ĳ���� ũ��� ���� ��尡 �� �� �ִ� ������ �ƴ��� �˻�
				auto ObjSizeCalculation = [&](bool is_Left)->void {
					int posY = ObjHeightCalculation(is_Left);
					// �� ĳ���� �ʺ� �� ������ ������ �� ���� ��� ���
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
							NodeMap[i][j].AddNode({ is_Left ? j - 1 : j + 1,posY }, { (float)2e9,(float)2e9 }, Node::NodeState::Walk);
					}
				};

				// ���� ��忡�� ��ĭ ��,������ ��� �Ǵ�
				// ��ü�� ���̿� �ʺ� ��� ����ؾ� ��
				ObjSizeCalculation(true);
				ObjSizeCalculation(false);

				// ���� ���
				// �������� �׷� �浹 ���� üũ
				// x��� y�� �ʱ� �ӵ��� �� ������ �� �����ϴ� ���� �����̴�.
				// 22/02/27 �������... �ٽ� ����
				float xStartSpeed = 1.f, yStartSpeed = 10.f, xSpeedGap = 5.f, ySpeedGap = 5.f, timeGap = 2.f;
				float initX = MapInfo[i][j].GetRightBottom().first, initY = MapInfo[i][j].mCenter.second;
				for (float xSpeed = xStartSpeed; xSpeed <= MaxSpeed.first; xSpeed += xSpeedGap)
				{
					for (float ySpeed = yStartSpeed; ySpeed < MaxSpeed.second; ySpeed += ySpeedGap)
					{
						float xDist = initX, yDist = initY;
						for (float fTime = 0; fTime < 1 // �ٽ� ����
						; fTime += timeGap)
						{
							xDist = fTime * xSpeed;
							yDist = ySpeed * fTime + fTime * fTime / 2.f * Gravity; // ��ӵ� �
							pair<int, int> mapIndex = Map.GetMapTileAtPoint({ xDist ,yDist });
							MapInfo[mapIndex.second][mapIndex.first].Overlaps(Square({ xDist + ObjHalfSize.first, yDist }, ObjHalfSize, 1));
						}
					}
				}
			}
		}
	}
}
*/

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