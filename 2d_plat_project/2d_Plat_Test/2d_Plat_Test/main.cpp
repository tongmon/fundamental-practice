#include <bits/stdc++.h>
using namespace std;

// olc ���ӿ��� ��� �� ������ ���� https://community.onelonecoder.com/2020/05/20/how-to-attribute-credit-cite-the-olcpixelgameengine/
// ���� �������� ���� ����

// A* �˰���, ��鿡���� ���� ����, �߷��� �ۿ��ϴ� �÷����� ���ӿ����� �̸� �����ؾ� ��.
void AstarAlgorithm(const vector<vector<int>>& Map, const pair<int, int>& StartPoint, const pair<int, int>& EndPoint, bool EdgeOption = true)
{
	// pair<int,int>���� first�� x ��ǥ, second�� y ��ǥ
	// tuple<int,int,int>���� get<0>()�� ����ġ(G+H)�� F ��, get<1>()�� x ��ǥ, get<2>()�� y ��ǥ
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
	vector<vector<int>> Dist(mapHeight, vector<int>(mapWidth, (int)2e9)); // �ʱ� �Ÿ��� �ſ� ũ��
	vector<vector<pair<int, int>>> TraceBack(mapHeight, vector<pair<int, int>>(mapWidth, { -1,-1 })); // ��� ������ �迭�� {-1,-1}�� �ʱ�ȭ
	bool is_FindPath = false; // ���� ã�Ҵ��� ����
	short Dir[8][2] = { {0,1},{1,0},{0,-1},{-1,0},{1,1},{-1,-1},{1,-1},{-1,1} }; // 8 ����
	short DirSize = EdgeOption ? 8 : 4; // �𼭸� �ɼǿ� ���� ���� ����
	priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> Q; // �켱���� ť�� ���� �������, ������� �����ϰ� ����
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
	// Way.pop_back(); Way.pop_front(); // �������� ������ ��¿��� �����Ϸ��� Ȱ��ȭ
	for (const auto& A : Way)
		TraceResult[A.second][A.first] = (int)1e9;
	cout << "\nTravel Finished!\n" << endl;
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

// AABB �浹 �˻� ���� �簢�� Ŭ����
// �� �������� ��ǥ�� �ص� ������ ���⼱ �߽ɰ� ���������� �ߴ�.
// �ش� �簢���� �������� ������ Ÿ���� ��Ÿ���� ������ �߰��ߴ�.
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
	pair<float, float> mstMapPoint; // �� ���� �簢�� �߽�
	vector<vector<Square>> mMap; // ���� ���� ��ǥ ����
	Map() { mWidth = mHeight = 0; }
	// startCoordiante -> ���� ù ��� �簢���� �߽� ��ǥ
	// squareSize -> �� �簢�� ũ�� (�� �� ũ��, ���簢���̶�� ����)
	// mapInfo -> �� ����
	Map(const pair<float, float>& startCoordiante, const float& squareSize, const vector<vector<int>>& mapInfo) // �ϴ� ���� ���ڴ� ���簢���̶�� �����ϰ� ����
	{
		mstMapPoint = startCoordiante;
		mWidth = (int)mapInfo[0].size(), mHeight = (int)mapInfo.size();
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


// ���� ������ �� �� �ִ� ��θ� ��Ÿ���� ���
// vector<vector<Node>> NodeMap �̷� ������� ��� 
class Node {
public:
	enum class NodeState : int // �ȱ�, ���� ���� �ൿ���� ����
	{
		Walk,
		Jump,
		Drop
	};

	// ��� ������ ���, X,Y ��ǥ ���� + �ش� ��ǥ�� �̵��Ҷ� � �ൿ�� ���ؾ� �ϴ����� ���
	// ���� ������ �Ѵٸ� �׿� ���� ������ �ӵ��� �ʿ���(vx, vy)
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
	Node(vector<NodeInfo>* link) { mLink.reset(link); }
	void AddNode(const NodeInfo& nodeinfo)
	{
		if (mLink == nullptr)
			mLink = make_shared<vector<NodeInfo>>(*(new vector<NodeInfo>()));
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

// ��� ����� ���� �ʿ��� ��
// 1. ĳ���� ũ�� -> ���� �ÿ� ������ �浹 ���� �ÿ� �ʿ�
// 2. ĳ���� ����, �ִ� �¿� �ӵ� -> ������ �Լ��� �ӵ��� ���� �޶���, �ӵ� ���� ���ݿ� ���� ���� �ӵ��� �޶��� �� ����.
// 3. ��� �ϳ� �� ũ��
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
						for (float fTime = 0; fTime < 1/* �ٽ� ���� */; fTime += timeGap)
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