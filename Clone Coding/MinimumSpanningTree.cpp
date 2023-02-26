#include <iostream>
#include <queue>
#include <vector>
#include <functional>
using namespace std;

// �׷����� ���� �ּ� ���� Ʈ�� ����� ��� 2����
// Kruskal, Prim�� �ִ�.
// kruskal�� ������ �߽����� �������� ���� �� ���� �������� �̾� �����Ѵ�.
// �̶� ����Ŭ ���Ÿ� ���� Union-Find�� �̿�ȴ�.
// Prim�� ���� �߽����� BFS�� ����ϰ� �ʺ�� �а� ���� ������ ���� ���� ������ ���� ���� ���Ѵ�.
// dist��� �迭 �̿�
// �ּ� ���� Ʈ���� ���� ȸ�� ���� ���� ���翡 ���� �̿��

#define MAX_LEN 256
#define INF 9999

typedef struct _Vert
{
	int Weight, v1, v2;
} Vert;

bool operator>(Vert a, Vert b) // greater<Vert>
{
	return a.Weight > b.Weight;
}

bool operator<(Vert a, Vert b) // less<Vert>
{
	return a.Weight < b.Weight;
}

class VertexSets // Union-Find ����
{
	int parent[MAX_LEN];
	int nSets;
public:
	VertexSets(int n) :nSets(n)
	{
		for (int i = 0; i < nSets; i++)
		{
			parent[i] = -1; // �θ� -1�̶�°� �� ������ ��Ʈ�� ���Ѵ�.
		}
	}
	bool is_Root(int u)
	{
		return parent[u] == -1;
	}
	int findSet(int u) // ���� ������ ��Ʈ ��ȯ
	{
		while (parent[u] != -1)
		{
			u = parent[u];
		}
		return u;
	}
	void unionSet(int u, int v)
	{
		parent[u] = v; nSets--;
	}
};

class AdjMatGraph // �׷��� ���� �迭�� ����
{
protected:
	int size;
	bool visited[MAX_LEN];
	char vertices[MAX_LEN]; // ���� �̸� �� ����
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
	void resetV() {
		for (int i = 0; i < size; i++)
		{
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
			for (int j = num; j < size; j++) // �� ĭ�� ���ʴ�� �����
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
	void BFS(int ver = 0)
	{
		queue<int> gBFS;
		visited[ver] = true;
		cout << vertices[ver] << "  ";
		gBFS.push(ver);
		while (gBFS.empty() == false)
		{
			int buffer = gBFS.front(); gBFS.pop();
			for (int i = 0; i < size; i++)
			{
				if (is_Linked(buffer, i) == true && visited[i] == false)
				{
					visited[i] = true;
					gBFS.push(i);
					cout << vertices[i] << "  ";
				}
			}
		}
	}
};

class WGraph :public AdjMatGraph
{
public:
	void insertEdge(int u, int v, int weight)
	{
		if (weight > INF)
		{
			weight = INF;
		}
		setEdge(u, v, weight);
		setEdge(v, u, weight);
	}
	bool hasEdge(int u, int v)
	{
		if (adj[u][v] < INF)
		{
			return true;
		}
		return false;
	}
};

class MinimumSpanningTree :public WGraph
{
public:
	void Kruskal() // ������ �������� �ּ� ��� ���� Ʈ�� ����
	{
		priority_queue<Vert, vector<Vert>, greater<Vert>> Gsort;
		// ��� �ﰢ ��ĸ� ����ȴ�.
		for (int i = 0; i < size - 1; i++)
		{
			for (int j = i; j < size; j++)
			{
				if (0 < adj[i][j] && adj[i][j] < INF)
				{
					Vert buffer; buffer.v1 = i; buffer.v2 = j; buffer.Weight = adj[i][j];
					Gsort.push(buffer);
				}
			}
		}
		VertexSets MST(size);
		int Size = size;
		while (Size != 1)
		{
			Vert buffer = Gsort.top();
			int sub = MST.findSet(buffer.v1);
			int root = MST.findSet(buffer.v2);
			if (sub != root) // �θ� �ٸ��� �� ������ �θ���� Union
			{
				MST.unionSet(sub, root); Size--;
				cout << "����: " << vertices[buffer.v1] << ", " << vertices[buffer.v2] << " ����ġ: " << buffer.Weight << endl;
			}
			Gsort.pop();
		}
	}
	void Prim(int s = 0) // ������ �������� �ּ� ��� ���� Ʈ�� ����
	{
		bool selected[MAX_LEN];
		int dist[MAX_LEN];
		for (int i = 0; i < size; i++)
		{
			selected[i] = false;
			dist[i] = INF;
		}
		dist[s] = 0;
		for (int i = 0; i < size; i++)
		{
			int Mindex = 0, Mdist = INF;
			for (int j = 0; j < size; j++)
			{
				if (Mdist > dist[j] && selected[j] == false)
				{
					Mdist = dist[j];
					Mindex = j;
				}
			}
			if (Mdist == INF)
			{
				return;
			}
			cout << vertices[Mindex] << " ";
			selected[Mindex] = true;
			for (int v = 0; v < size; v++)
			{
				if (selected[v] == false && dist[v] > getEdge(Mindex, v) && 0 < getEdge(Mindex, v))
				{
					dist[v] = adj[Mindex][v];
				}
			}
		}
	}
};

int main()
{
	MinimumSpanningTree MST;

	for (int i = 0; i < 7; i++)
	{
		MST.insertVertex('A' + i);
	}

	MST.insertEdge(0, 1, 29); MST.insertEdge(0, 5, 10);
	MST.insertEdge(1, 2, 16); MST.insertEdge(1, 6, 15);
	MST.insertEdge(2, 3, 12); MST.insertEdge(3, 4, 22);
	MST.insertEdge(4, 5, 27); MST.insertEdge(4, 6, 25);
	MST.insertEdge(3, 6, 18);
	cout << "Kruskal's algorithm\n";
	MST.Kruskal();
	cout << "\n\n";
	cout << "Prim's algorithm\n";
	MST.Prim();
}