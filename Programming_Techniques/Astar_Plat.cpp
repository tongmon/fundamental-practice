#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

#define MID_LEN 128

enum { Path = 0, Wall, Starter, Finish, ShortestWay };

enum { Walk, Jump, Drop };

typedef struct _point // 좌표 클래스
{
	int x, y;
}Cord;

/*
class BrickInfo
{
	int F, G, H;
	Cord Cur, Parent;
	short State;
public:
	BrickInfo(Cord buffer, Cord parent, int g, int h, short k) { Cur = buffer; Parent = parent; G = g; H = h; F = G + H; State = k; }
	Cord getCur() { return Cur; }
	Cord getParent() { return Parent; }
	int getF() { return F; }
	int getG() { return G; }
	int getH() { return H; }
	void modInfo(Cord parent, int g) { Parent = parent; G = g; F = G + H; }
};
*/

class BrickInfo
{
	int F, G, H;
	int Cur, Parent;
	short State;
public:
	BrickInfo(int buffer, int parent, int g, int h, short k) { Cur = buffer; Parent = parent; G = g; H = h; F = G + H; State = k; }
	int getCur() { return Cur; }
	int getParent() { return Parent; }
	int getF() { return F; }
	int getG() { return G; }
	int getH() { return H; }
	short getState() { return State; }
	void modInfo(int parent, int g, short s) { Parent = parent; G = g; F = G + H; State = s; }
};

bool operator<(BrickInfo a, BrickInfo b)
{
	return a.getF() < b.getF();
}

class Gnode // 가중치는 실제 좌표대로 계산
{
	Cord Mapcord; int id;
	vector<int> Jumplist;
	vector<int> Droplist;
	vector<int> Walklist;
public:
	Gnode(int x = -1, int y = -1) { Mapcord.x = x; Mapcord.y = y; }
	Cord getCord() { return Mapcord; }
	void setCord(int x, int y) { Mapcord.x = x; Mapcord.y = y; }
	void setId(int i) { id = i; }
	int getId() { return id; }
	vector<int>* getJumplist() { return &Jumplist; }
	vector<int>* getDroplist() { return &Droplist; }
	vector<int>* getWalklist() { return &Walklist; }
};

class Matrix
{
	int Width, Height, nodesize;
	short Map[MID_LEN][MID_LEN];
	Gnode Node[MID_LEN];
public:
	Matrix(short map[][MID_LEN], int width, int height, int size)
	{
		Width = width; Height = height;
		for (int i = 0; i < Width; i++)
		{
			for (int j = 0; j < Height; j++)
			{
				Map[i][j] = map[i][j];
			}
		}
		nodesize = size;
		for (int i = 0; i < nodesize; i++)
		{
			Node[i].setId(i);
		}
	}
	void setMatrix(int col, int row, int val) { Map[row][col] = val; }
	int getWidth() { return Width; }
	int getHeight() { return Height; }
	int getNsize() { return nodesize; }
	int getMap(int col, int row) { return Map[row][col]; }
	Gnode* getGnode(int index) { return &Node[index]; }
	void Linknode(int a, int b, int type) // a에서 선이 뻗어 b를 연결
	{
		if (type == Walk)
		{
			getGnode(a)->getWalklist()->push_back(b);
		}
		else if (type == Jump)
		{
			getGnode(a)->getJumplist()->push_back(b);
		}
		else if (type == Drop)
		{
			getGnode(a)->getDroplist()->push_back(b);
		}
	}
	void Display()
	{
		for (int i = 0; i < Width; i++)
		{
			for (int j = 0; j < Height; j++)
			{
				if (Map[i][j] == Wall)
				{
					cout << '@' << "  ";
				}
				else if (Map[i][j] == Starter || Map[i][j] == Finish)
				{
					cout << '#' << "  ";
				}
				else if (Map[i][j] == ShortestWay)
				{
					cout << '+' << "  ";
				}
				else if (Map[i][j] == Path)
				{
					cout << '.' << "  ";
				}
			}
			cout << endl;
		}
	}
};

class Astar_plat :public Matrix
{
	Cord Start, End;
public:
	Astar_plat(short map[][MID_LEN], int w, int h, int s) : Matrix(map, w, h, s) {}
	int getG(Cord Cur, Cord a)
	{
		return abs(a.x - Cur.x) * 5 + abs(a.y - Cur.y) * 10;
	}
	int getH(Cord Cur)
	{
		return abs(End.x - Cur.x) * 5 + abs(End.y - Cur.y) * 10;
	}
	bool setStart()
	{
		bool getstart = false, getend = false;
		for (int i = 0; i < getHeight(); i++)
		{
			for (int j = 0; j < getWidth(); j++)
			{
				if (getMap(j, i) == Starter)
				{
					Start.x = j; Start.y = i;
					getstart = true;
				}
				else if (getMap(j, i) == Finish)
				{
					End.x = j; End.y = i;
					getend = true;
				}
				if (getstart == true && getend == true)
				{
					return true;
				}
			}
		}
		if (getstart != true || getend != true)
		{
			return false;
		}
		return true;
	}
	int getNodeIndex(Cord point)
	{
		for (int i = 0; i < getNsize(); i++)
		{
			if (point.x == getGnode(i)->getCord().x && point.y == getGnode(i)->getCord().y)
			{
				return getGnode(i)->getId();
			}
		}
		return -1;
	}
	void AstarAlgorithm()
	{
		vector<BrickInfo> Result; // 최종 경로 명령 저장
		vector<BrickInfo> Closed;
		vector<BrickInfo> Opened;
		if (setStart() == false)
		{
			cout << "Set the Start, End Point currectly!" << endl; return;
		}
		int Sindex = getNodeIndex(Start);
		int Eindex = getNodeIndex(End);
		Closed.push_back(BrickInfo(Sindex, Sindex, 0, 0, -1));
		Pushway(Sindex, 0, &Opened, &Closed);
		while (Opened.size() > 0)
		{
			auto mIter = min_element(Opened.begin(), Opened.end());
			BrickInfo Smallone = *mIter;
			if (getGnode(Smallone.getCur())->getCord().x == End.x && getGnode(Smallone.getCur())->getCord().y == End.y)
			{
				Closed.push_back(Smallone);
				break;
			}
			Closed.push_back(Smallone);
			Opened.erase(mIter);
			Pushway(Smallone.getCur(), Smallone.getG(), &Opened, &Closed);
		}
		if (Opened.size() == 0)
		{
			cout << "Can't Find the Way to reach the Point!" << endl; return;
		}
		int track = Eindex;
		while (track != Sindex)
		{
			for (int i = 0; i < Closed.size(); i++)
			{
				if (Closed[i].getCur() == track)
				{
					Result.push_back(Closed[i]);
					if (track != Eindex)
					{
						setMatrix(getGnode(track)->getCord().x, getGnode(track)->getCord().y, ShortestWay);
					}
					track = Closed[i].getParent();
					Closed.erase(Closed.begin() + i); break;
				}
			}
		}
		cout << "\nFinished Travel" << endl;
		Display();
		cout << endl;
		cout << "노드" << Sindex << "에서 출발하여 노드" << Eindex << "로 도착하기 까지의 경로" << endl;
		for (int i = Result.size() - 1; i >= 0; i--)
		{
			int Curin = Result[i].getCur(), Parent = Result[i].getParent();
			cout << "노드" << Parent << "에서 노드" << Curin << "로 ";
			if (Result[i].getState() == Walk)
			{
				cout << "걷기" << endl;
			}
			else if (Result[i].getState() == Jump)
			{
				cout << "뛰기" << endl;
			}
			else
			{
				cout << "떨어지기" << endl;
			}
		}
	}
	bool is_Closed(int index, vector<BrickInfo> Closed)
	{
		for (int i = 0; i < Closed.size(); i++)
		{
			if (Closed[i].getCur() == index)
			{
				return true;
			}
		}
		return false;
	}
	int is_Opened(int index, vector<BrickInfo> Opened)
	{
		for (int i = 0; i < Opened.size(); i++)
		{
			if (Opened[i].getCur() == index)
			{
				return i;
			}
		}
		return -1;
	}
	void Pushway(int index, int CurG, vector<BrickInfo>* Opened, vector<BrickInfo>* Closed)
	{
		vector<int> buffer; // 인덱스 저장소
		vector<short> status; // 상태 저장소
		int Gvalue;
		for (int i = 0; i < getGnode(index)->getJumplist()->size(); i++)
		{
			buffer.push_back(getGnode(index)->getJumplist()->at(i));
			status.push_back(Jump);
		}
		for (int i = 0; i < getGnode(index)->getDroplist()->size(); i++)
		{
			buffer.push_back(getGnode(index)->getDroplist()->at(i));
			status.push_back(Drop);
		}
		for (int i = 0; i < getGnode(index)->getWalklist()->size(); i++)
		{
			buffer.push_back(getGnode(index)->getWalklist()->at(i));
			status.push_back(Walk);
		}
		for (int i = 0; i < buffer.size(); i++)
		{
			if (is_Closed(buffer[i], *Closed) == true)
			{
				buffer.erase(buffer.begin() + i);
				status.erase(status.begin() + i--);
			}
		}
		for (int i = 0; i < buffer.size(); i++)
		{
			int Oindex = is_Opened(buffer[i], *Opened);
			Gvalue = getG(getGnode(index)->getCord(), getGnode(buffer[i])->getCord());
			if (Oindex != -1) // 오픈리스트에 존재하면
			{
				if (Opened->at(Oindex).getG() > Gvalue + CurG)
				{
					Opened->at(Oindex).modInfo(index, Gvalue + CurG, status[i]);
				}
			}
			else
			{
				Opened->push_back(BrickInfo(buffer[i], index, Gvalue + CurG, getH(getGnode(buffer[i])->getCord()), status[i]));
			}
		}
	}
};

int main()
{
	short Map[MID_LEN][MID_LEN] =
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};
	short Map_2[MID_LEN][MID_LEN] =
	{
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,3,0,0,0,0,0,0,0},
		{0,1,1,1,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,1,1,1,1,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,2,0}
	};
	Astar_plat tester(Map_2, 10, 10, 23);
	tester.Linknode(0, 1, Walk);
	tester.Linknode(0, 10, Jump);
	tester.Linknode(1, 0, Walk);
	tester.Linknode(1, 2, Walk);
	tester.Linknode(2, 1, Walk);
	tester.Linknode(2, 3, Walk);
	tester.Linknode(3, 2, Walk);
	tester.Linknode(3, 4, Walk);
	tester.Linknode(4, 3, Walk);
	tester.Linknode(4, 5, Walk);
	tester.Linknode(5, 4, Walk);
	tester.Linknode(5, 6, Walk);
	tester.Linknode(6, 5, Walk);
	tester.Linknode(6, 14, Jump);
	tester.Linknode(6, 7, Walk);
	tester.Linknode(7, 6, Walk);
	tester.Linknode(7, 8, Walk);
	tester.Linknode(8, 7, Walk);
	tester.Linknode(8, 9, Walk);
	tester.Linknode(9, 8, Walk);
	tester.Linknode(10, 0, Drop);
	tester.Linknode(10, 11, Walk);
	tester.Linknode(11, 10, Walk);
	tester.Linknode(11, 12, Walk);
	tester.Linknode(12, 13, Walk);
	tester.Linknode(12, 11, Walk);
	tester.Linknode(12, 15, Jump);
	tester.Linknode(13, 12, Walk);
	tester.Linknode(13, 14, Walk);
	tester.Linknode(14, 13, Walk);
	tester.Linknode(14, 6, Drop);
	tester.Linknode(15, 12, Drop);
	tester.Linknode(15, 16, Walk);
	tester.Linknode(15, 22, Jump);
	tester.Linknode(16, 15, Walk);
	tester.Linknode(16, 17, Walk);
	tester.Linknode(17, 16, Walk);
	tester.Linknode(17, 18, Walk);
	tester.Linknode(18, 17, Walk);
	tester.Linknode(18, 19, Walk);
	tester.Linknode(19, 9, Drop);
	tester.Linknode(19, 18, Walk);
	tester.Linknode(22, 15, Drop);
	tester.Linknode(22, 21, Walk);
	tester.Linknode(21, 22, Walk);
	tester.Linknode(21, 20, Walk);
	tester.Linknode(20, 21, Walk);
	tester.Linknode(20, 0, Drop);
	for (int i = 0; i < 10; i++)
	{
		tester.getGnode(i)->setCord(i, 9);
	}
	for (int i = 10; i < 15; i++)
	{
		tester.getGnode(i)->setCord(i - 9, 6);
	}
	for (int i = 15; i < 20; i++)
	{
		tester.getGnode(i)->setCord(i - 11, 3);
	}
	for (int i = 20; i < 23; i++)
	{
		tester.getGnode(i)->setCord(i - 19, 1);
	}
	tester.AstarAlgorithm();
}