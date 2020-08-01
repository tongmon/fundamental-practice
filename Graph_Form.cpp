#include <iostream>
using namespace std;

// 그래프는 배열, 연결 리스트들을 이용해 짤 수 있다.
// 각기 다른 장단점이 존재 하니 상황에 맞게 사용할 것.
// DFS 추가

#define MAX_LEN 256

class AdjMatGraph // 그래프 구조 배열로 구현
{
protected:
	int size;
	bool visited[MAX_LEN];
	char vertices[MAX_LEN]; // 정점 이름 한 글자
	unsigned short adj[MAX_LEN][MAX_LEN];
public:
	AdjMatGraph() { reset(); }
	char getVertex(int i) { return vertices[i]; }
	int getEdge(int i, int j) { return adj[i][j]; }
	void setEdge(int i, int j, int val) { adj[i][j] = val; }
	bool is_Empty() { return size == 0; }
	bool is_Full() { return size >= MAX_LEN; }
	void reset()
	{
		size = 0;
		for (int i = 0; i < MAX_LEN; i++)
		{
			for (int j = 0; j < MAX_LEN; j++)
			{
				setEdge(i, j, 0);
			}
			visited[i] = false;
		}
	}
	void insertVertex(char name)
	{
		if (is_Full() == false)
		{
			vertices[size++] = name; return;
		}
		cout << "Current Graph is Full" << endl;
	}
	void insertEdge(int v, int u)
	{
		if (v < size && u < size)
		{
			setEdge(v, u, 1);
			setEdge(u, v, 1);
		}
	}
	void delEdge(int v, int u)
	{
		if (v < size && u < size)
		{
			setEdge(v, u, 0);
			setEdge(u, v, 0);
		}
	}
	void delVertex(char name)
	{
		if (is_Empty() == true)
		{
			cout << "Graph is Empty\n";
			return;
		}
		int num = MAX_LEN;
		for (int i = 0; i < size; i++)
		{
			if (vertices[i] == name)
			{
				num = i;
			}
			if (num <= i)
			{
				vertices[i] = vertices[i + 1];
			}
		}
		if (num == MAX_LEN)
		{
			cout << "Can't find Matched Vertex!" << endl; return;
		}
		if (num != MAX_LEN - 1)
		{
			for (int j = num; j < size; j++) // 한 칸씩 차례대로 땡기기
			{
				for (int i = 0; i < size; i++)
				{
					adj[j][i] = adj[j + 1][i];
				}
				for (int i = 0; i < size; i++)
				{
					adj[i][j] = adj[i][j + 1];
				}
			}
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				setEdge(num, i, 0);
				setEdge(i, num, 0);
			}
		}
		size--;
	}
	void display()
	{
		cout << size << endl;
		for (int i = 0; i < size; i++)
		{
			cout << vertices[i] << " ";
			for (int j = 0; j < size; j++)
			{
				cout << adj[i][j] << " ";
			}
			cout << endl;
		}
	}
	bool is_Linked(int u, int v)
	{
		if (adj[u][v] != 0)
		{
			return true;
		}
		return false;
	}
	void DFS(int ver = 0)
	{
		visited[ver] = true;
		cout << vertices[ver] << "  ";
		for (int i = 0; i < size; i++)
		{
			if (is_Linked(ver, i) == true && visited[i] == false)
			{
				DFS(i);
			}
		}
	}
};

class gNode
{
protected:
	int id;
	gNode* next;
public:
	gNode(int i = -1, gNode* p = NULL)
	{
		id = i; next = p;
	}
	~gNode() { if (next != NULL) delete next; }
	int getId() { return id; }
	gNode* getNext() { return next; }
	void setNext(gNode* p) { next = p; }
};

class AdjListGraph
{
protected:
	int size;
	bool visited[MAX_LEN];
	char vertices[MAX_LEN];
	gNode* adj[MAX_LEN];
public:
	AdjListGraph()
	{
		size = 0; *vertices = NULL; *adj = NULL;
		for (int i = 0; i < MAX_LEN; i++)
		{
			visited[i] = false;
		}
	}
	~AdjListGraph() { reset(); }
	void reset()
	{
		for (int i = 0; i < size; i++)
		{
			if (adj[i] != NULL)
			{
				delete adj[i];
			}
			visited[i] = false;
		}
		size = 0;
	}
	bool is_Empty() { return size == 0; }
	bool is_Full() { return size >= MAX_LEN; }
	char getVertex(int i) { return vertices[i]; }
	void insertVertex(char name)
	{
		if (is_Full() == true)
		{
			cout << "Graph is Full" << endl; return;
		}
		vertices[size] = name;
		adj[size++] = NULL;
	}
	void insertEdge(int u, int v)
	{
		gNode* p = new gNode(v, adj[u]);
		adj[u] = p;
		p = new gNode(u, adj[v]);
		adj[v] = p;
	}
	void display()
	{
		cout << size << endl;
		for (int i = 0; i < size; i++)
		{
			cout << vertices[i] << "	";
			gNode* p = adj[i];
			while (p != NULL)
			{
				cout << getVertex(p->getId()) << "	";
				p = p->getNext();
			}
			cout << endl;
		}
	}
	gNode* adjacent(int v) { return adj[v]; }
	bool is_Linked(int u, int v)
	{
		gNode* p = adj[u];
		while (p != NULL)
		{
			if (v == p->getId())
			{
				return true;
			}
			p = p->getNext();
		}
		return false;
	}
	void DFS(int ver = 0)
	{
		visited[ver] = true;
		cout << vertices[ver] << "  ";
		for (int i = 0; i < size; i++)
		{
			if (is_Linked(ver, i) == true && visited[i] == false)
			{
				DFS(i);
			}
		}
	}
};

int main()
{
	cout << "행렬 배열로 작성된 그래프\n";
	AdjMatGraph g;
	for (int i = 0; i < 4; i++)
	{
		g.insertVertex('A' + i);
	}
	g.insertEdge(0, 1);
	g.insertEdge(0, 3);
	g.insertEdge(1, 2);
	g.insertEdge(1, 3);
	g.insertEdge(2, 3);
	g.display();
	cout << endl;
	cout << "DFS 결과: "; g.DFS();

	cout << "\n\n연결 리스트로 작성된 그래프\n";
	AdjListGraph G;
	for (int i = 0; i < 4; i++)
	{
		G.insertVertex('A' + i);
	}
	G.insertEdge(0, 1);
	G.insertEdge(0, 3);
	G.insertEdge(1, 2);
	G.insertEdge(1, 3);
	G.insertEdge(2, 3);
	G.display();
	cout << endl;
	cout << "DFS 결과: "; G.DFS();
}