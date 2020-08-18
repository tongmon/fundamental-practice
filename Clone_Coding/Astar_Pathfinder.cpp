#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

// A* 최단 경로 탐색 알고리즘
// 해당 노드에서 다른 노드까지의 모든 최단 경로를 뽑는 다익스트라와 달리
// 특정 노드에서 특정 목적 노드까지의 최단 경로만 뽑아주기에 더 빠르다.
// 게임에서 많이 쓰인다.
// true 모드는 벽 모서리 통과 불가능이고 false는 벽 모서리도 통과하면서 경로를 탐색한다.

#define MID_LEN 128

enum {Path = 0, Wall, Starter, Finish, ShortestWay};

typedef struct _point // 좌표 클래스
{
	int x, y;
}Cord;

class BrickInfo
{
	int F, G, H;
	Cord Cur, Parent;
public:
	BrickInfo(Cord buffer, Cord parent, int g, int h) { Cur = buffer; Parent = parent; G = g; H = h; F = G + H; }
	Cord getCur() { return Cur; }
	Cord getParent() { return Parent; }
	int getF() { return F; }
	int getG() { return G; }
	int getH() { return H; }
	void modInfo(Cord parent, int g) { Parent = parent; G = g; F = G + H; }
};

bool operator<(BrickInfo a, BrickInfo b)
{
	return a.getF() < b.getF();
}

class Matrix
{
	int Width, Height;
	short Map[MID_LEN][MID_LEN];
public:
	Matrix(short map[][MID_LEN], int width, int height)
	{
		Width = width; Height = height;
		for (int i = 0;i < Width;i++)
		{
			for (int j = 0; j < Height; j++)
			{
				Map[i][j] = map[i][j];
			}
		}
	}
	void setMatrix(int col, int row, int val) { Map[row][col] = val; }
	int getWidth() { return Width; }
	int getHeight() { return Height; }
	int getMap(int col, int row) { return Map[row][col]; }
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

class Astar:public Matrix
{
	Cord Start, End;
public:
	Astar(short map[][MID_LEN], int w, int h) : Matrix(map, w, h) {}
	int getG(Cord Cur, Cord a) 
	{
		if (abs(a.x - Cur.x) == 1 && abs(a.y - Cur.y) == 1)
		{
			return 14;
		}
		else if (abs(a.x - Cur.x) == 1 || abs(a.y - Cur.y) == 1)
		{
			return 10;
		}
		else
		{
			cout << "error" << endl; return -1;
		}
	}
	int getH(Cord Cur)
	{
		return 10 * (abs(End.x - Cur.x) + abs(End.y - Cur.y));
	}
	bool is_vailed(int x, int y)
	{
		if (x < 0 || y < 0 || x > getWidth() || y > getHeight())
		{
			return false;
		}
		if (getMap(x, y) == Wall)
		{
			return false;
		}
		return true;
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
					break;
				}
			}
			if (getstart == true && getend == true)
			{
				break;
			}
		}
		if (getstart != true || getend != true)
		{
			return false;
		}
		return true;
	}
	void AstarAlgorithm(bool EdgeOption = true)
	{	
		vector<BrickInfo> Closed;
		vector<BrickInfo> Opened;
		if (setStart() == false)
		{
			cout << "Set the Start, End Point currectly!" << endl; return;
		}
		Cord Cur = Start;
		Closed.push_back(BrickInfo(Start, Cur, 0, 0));
		PushWay(Cur, 0, &Opened, &Closed, EdgeOption);
		while (Opened.size() > 0)
		{
			auto mIter = min_element(Opened.begin(), Opened.end());
			BrickInfo Smallone = *mIter;
			if (Smallone.getCur().x == End.x && Smallone.getCur().y == End.y)
			{
				Closed.push_back(Smallone);
				break;
			}
			Closed.push_back(Smallone);
			Opened.erase(mIter);
			PushWay(Smallone.getCur(), Smallone.getG(), &Opened, &Closed, EdgeOption);
		}
		if (Opened.size() == 0)
		{
			cout << "Can't Find the Way to reach the Point!" << endl; return;
		}
		Cord Track = End;
		while (Track.x != Start.x || Track.y != Start.y)
		{
			for (int j = 0; j < Closed.size(); j++)
			{
				if (Track.x == Closed[j].getCur().x && Track.y == Closed[j].getCur().y)
				{
					if (Track.x != End.x || Track.y != End.y)
					{
						setMatrix(Track.x, Track.y, ShortestWay);
					}
					Track = Closed[j].getParent();
					Closed.erase(Closed.begin() + j);
					break;
				}
			}
		}
		cout << "\nFinished Travel" << endl;
		Display();
	}
	void PushWay(Cord Cur, int CurG, vector<BrickInfo>* Opened, vector<BrickInfo>* Closed, bool Edge)
	{
		bool is_closed[8] = { false, false, false, false, false, false, false, false };
		int is_opened[8] = { -1,-1,-1,-1,-1,-1,-1,-1 };
		Cord buffer[8]; int Gvalue;
		buffer[7].x = Cur.x - 1; buffer[7].y = Cur.y - 1; buffer[0].x = Cur.x; buffer[0].y = Cur.y - 1;
		buffer[1].x = Cur.x + 1; buffer[1].y = Cur.y - 1; buffer[2].x = Cur.x + 1; buffer[2].y = Cur.y;
		buffer[3].x = Cur.x + 1; buffer[3].y = Cur.y + 1; buffer[4].x = Cur.x; buffer[4].y = Cur.y + 1;
		buffer[5].x = Cur.x - 1; buffer[5].y = Cur.y + 1; buffer[6].x = Cur.x - 1; buffer[6].y = Cur.y;
		for (int i = 0; i < Opened->size(); i++)
		{
			int X = Opened->at(i).getCur().x;
			int Y = Opened->at(i).getCur().y;
			for (int j = 0; j < 8; j++)
			{
				if (X == buffer[j].x && Y == buffer[j].y)
				{
					is_opened[j] = i;
					break;
				}
			}
		}
		for (int i = 0; i < Closed->size(); i++)
		{
			int X = Closed->at(i).getCur().x;
			int Y = Closed->at(i).getCur().y;
			for (int j = 0; j < 8; j++)
			{
				if (X == buffer[j].x && Y == buffer[j].y)
				{
					is_closed[j] = true;
					break;
				}
			}
		}
		for (int i = 0; i < 8; i++)
		{
			if (is_vailed(buffer[i].x, buffer[i].y) == true && is_closed[i] == false)
			{
				Gvalue = getG(Cur, buffer[i]);
				if (Edge == true) // 벽 대각선 통과 불가능
				{
					if (i % 2 == 1) // 대각선 블록인 경우
					{
						int back = i - 1, front = (i + 1) % 8;
						if (getMap(buffer[back].x, buffer[back].y) != Wall && getMap(buffer[front].x, buffer[front].y) != Wall)
						{
							if (is_opened[i] != -1 && Opened->at(is_opened[i]).getG() > Gvalue + CurG)
							{
								Opened->at(is_opened[i]).modInfo(Cur, Gvalue + CurG);
							}
							else if (is_opened[i] == -1)
							{
								Opened->push_back(BrickInfo(buffer[i], Cur, Gvalue + CurG, getH(buffer[i])));
							}
						}
					}
					else
					{
						if (is_opened[i] != -1 && Opened->at(is_opened[i]).getG() > Gvalue + CurG)
						{
							Opened->at(is_opened[i]).modInfo(Cur, Gvalue + CurG);
						}
						else if (is_opened[i] == -1)
						{
							Opened->push_back(BrickInfo(buffer[i], Cur, Gvalue + CurG, getH(buffer[i])));
						}
					}
				}
				else if (Edge == false) // 벽 대각선 통과 가능
				{
					if (is_opened[i] != -1 && Opened->at(is_opened[i]).getG() > Gvalue + CurG)
					{
						Opened->at(is_opened[i]).modInfo(Cur, Gvalue + CurG);
					}
					else if (is_opened[i] == -1)
					{
						Opened->push_back(BrickInfo(buffer[i], Cur, Gvalue + CurG, getH(buffer[i])));
					}
				}
			}
		}
	}
};

int main()
{
	short Map[MID_LEN][MID_LEN] =
	{
		{0,0,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
		{0,2,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,1,0,3,0,0},
		{1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};
	Astar PathFinder(Map, 20, 20);
	PathFinder.AstarAlgorithm(true);
}