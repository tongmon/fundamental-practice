#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

// 최단 경로 탐색 방법
// 다익스트라 알고리즘은 정점 중 한개의 경로만, Floyd는 모든 정점의 경로 최소값을 찾는다.
// Floyd는 track이라는 배열을 추가하면 왔던 길이 어떻게 되는지 추적 할 수가 있다.
// Floyd는 하노이탑과 같이 n-1 작업이 n으로 확장 되면 재귀적으로 해결되는 것과 같은 원리를 따른다.

#define MAX_LEN 256
#define INF 9999

typedef struct _MyStruct // 우선순위 큐에 dist 정보를 넣기 위한 구조체
{
	int index; int dist;
} Distance;

bool operator>(Distance a, Distance b)
{
	return a.dist > b.dist;
}

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
				setEdge(i, j, INF);
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

class WGraphDijkstra : public WGraph
{
	int dist[MAX_LEN];
	bool found[MAX_LEN];
public:
	WGraphDijkstra()
	{
		for (int i = 0; i < MAX_LEN; i++)
		{
			dist[i] = INF;
			found[i] = false;
		}
	}
	void ShortestPath_Q(int starter = 0) // 우선 순위 큐를 이용한 딕스트라 알고리즘
	{
		priority_queue<Distance, vector<Distance>, greater<Distance>> storage;
		for (int i = 0; i < size; i++)
		{
			if (starter != i)
			{
				dist[i] = adj[starter][i];
				Distance buffer; buffer.dist = dist[i]; buffer.index = i;
				storage.push(buffer);
			}
		}
		dist[starter] = 0;
		found[starter] = true;
		while (storage.empty() == false)
		{
			// 제일 거리가 최소인 정점 탐색
			Distance Mini = storage.top(); storage.pop();
			cout << vertices[starter] << "에서 " << vertices[Mini.index] << "까지 최단거리: " << Mini.dist << endl;
			found[Mini.index] = true;
			while (storage.empty() == false)
			{
				storage.pop();
			}
			for (int j = 0; j < size; j++)
			{
				if (found[j] == false)
				{
					dist[j] = min(dist[j], dist[Mini.index] + adj[Mini.index][j]);
					Distance buffer; buffer.dist = dist[j]; buffer.index = j;
					storage.push(buffer);
				}
			}
		}
	}
	void ShortestPath(int starter = 0)
	{
		for (int i = 0; i < size; i++)
		{
			dist[i] = adj[starter][i];
		}
		dist[starter] = 0;
		found[starter] = true;
		for (int i = 0; i < size; i++)
		{
			// 제일 거리가 최소인 정점 탐색
			int Mindex = 0, Mdist = INF;
			for (int j = 0; j < size; j++)
			{
				if (found[j] == false && 0 < dist[j] && dist[j] < Mdist)
				{
					Mdist = dist[j];
					Mindex = j;
				}
			}
			if (Mdist == INF)
			{
				return;
			}
			cout << vertices[starter] << "에서 " << vertices[Mindex] << "까지 최단거리: " << Mdist << endl;
			found[Mindex] = true;
			for (int j = 0; j < size; j++)
			{
				if (found[j] == false)
				{
					dist[j] = min(dist[j], dist[Mindex] + adj[Mindex][j]);
				}
			}
		}
	}
};

class WGraphFloyd :public WGraph // 모든 최단 경로 다 뽑아버리는 Floyd 알고리즘
{
	int dist[MAX_LEN][MAX_LEN];
	int track[MAX_LEN][MAX_LEN]; // 거처가는 중간점 중 도착 바로 전 정점, 중간점이 없다면 -1
public:
	WGraphFloyd() {}
	void Floyd() 
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				track[i][j] = -1;
				dist[i][j] = adj[i][j];
				if (i == j)
				{
					dist[i][j] = 0;
				}
			}
		}
		for (int k = 0; k < size; k++)
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					if (dist[i][j] > dist[i][k] + dist[k][j])
					{
						dist[i][j] = dist[i][k] + dist[k][j];
						track[i][j] = k;
					}
				}
			}
		}
		cout << "	";
		for (int i = 0; i < size; i++)
		{
			cout << vertices[i] << "	";
		}
		cout << endl;
		for (int i = 0; i < size; i++)
		{
			cout << vertices[i] << "	";
			for (int j = 0; j < size; j++)
			{
				cout << dist[i][j] << "	";
			}
			cout << endl;
		}
	}
	void BackTracking(int start, int end)
	{
		int Bindex = track[start][end];
		cout << vertices[end] << " --> ";
		while (Bindex != -1)
		{
			cout << vertices[Bindex] << " --> ";
			Bindex = track[start][Bindex];
		}
		cout << vertices[start];
	}
};

int main()
{
	WGraphDijkstra Dijkstra;
	
	for (int i = 0; i < 7; i++)
	{
		Dijkstra.insertVertex('A' + i);
	}

	Dijkstra.insertEdge(0, 1, 29); Dijkstra.insertEdge(0, 5, 10);
	Dijkstra.insertEdge(1, 2, 16); Dijkstra.insertEdge(1, 6, 15);
	Dijkstra.insertEdge(2, 3, 12); Dijkstra.insertEdge(3, 4, 22);
	Dijkstra.insertEdge(4, 5, 27); Dijkstra.insertEdge(4, 6, 25);
	Dijkstra.insertEdge(3, 6, 18);

	Dijkstra.ShortestPath_Q();
	cout << "\n\n";

	WGraphFloyd Floyd;

	for (int i = 0; i < 7; i++)
	{
		Floyd.insertVertex('A' + i);
	}

	Floyd.insertEdge(0, 1, 29); Floyd.insertEdge(0, 5, 10);
	Floyd.insertEdge(1, 2, 16); Floyd.insertEdge(1, 6, 15);
	Floyd.insertEdge(2, 3, 12); Floyd.insertEdge(3, 4, 22);
	Floyd.insertEdge(4, 5, 27); Floyd.insertEdge(4, 6, 25);
	Floyd.insertEdge(3, 6, 18);

	Floyd.Floyd();
	cout << endl;
	Floyd.BackTracking(0, 4);
}