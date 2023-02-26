#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

// 이론만 듣고 짜본 Red-Black tree이다. 
// 이론만 들어서 놓친 부분이 있는데 바로 노드에 부모 노드 포인터를 넣지 않았다....
// 따라서 상위노드를 찾는 과정에서 탐색을 하게되는데 이때 비효율적이다. (애초에 알았으면... 고치기는 귀찮다.)
// 삽입보다 삭제 구현이 정말 귀찮더라.... 고려할 케이스가 너무 많았다

void randnum(int* num, int size)
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < size; i++)
	{
		*(num + i) = i + 1;
	}
	int tmp, a, b;
	for (int i = 0; i < (size * 2); i++)
	{
		a = rand() % size;
		b = rand() % size;
		if (a != b)
		{
			tmp = *(num + a);
			*(num + a) = *(num + b);
			*(num + b) = tmp;
		}
	}
}

enum { RED, BLACK };

class RBNode
{
	int data;
	short color;
	RBNode* Left, * Right;
public:
	RBNode(int k = 0, short c = RED, RBNode* left = NULL, RBNode* right = NULL)
	{
		data = k; color = c; Left = left; Right = right;
	}
	short getColor() { return color; }
	void setColor(short c) { color = c; }
	int getData() { return data; }
	void setData(int k) { data = k; }
	RBNode* getLeft() { return Left; }
	RBNode* getRight() { return Right; }
	void setLeft(RBNode* p) { Left = p; }
	void setRight(RBNode* p) { Right = p; }
};

class RBTree
{
	RBNode* Root;
	RBNode* NIL; // red-black 트리의 NULL노드
public:
	RBTree(RBNode* p = NULL)
	{
		Root = p; NIL = new RBNode(-1, BLACK, NULL, NULL);
	}
	~RBTree()
	{
		if (Root != NULL)
		{
			DelNode(Root);
		}
		delete NIL;
	}
	RBNode* getRoot() { return Root; }
	int getHeight(RBNode* p);
	void DelNode(RBNode* p);
	RBNode* RightRotation(RBNode* Parent) // 회전축이 Parent
	{
		RBNode* child = Parent->getLeft();
		RBNode* buffer = child->getRight();
		child->setRight(Parent);
		Parent->setLeft(buffer);
		return child;
	}
	RBNode* LeftRotation(RBNode* Parent) // 회전축이 Parent
	{
		RBNode* child = Parent->getRight();
		RBNode* buffer = child->getLeft();
		child->setLeft(Parent);
		Parent->setRight(buffer);
		return child;
	}
	void Insert(int k);
	void Delete(int k);
	void ReAdjust_ins(RBNode* p); // 삽입시 재조정 함수
	void ReAdjust_del(RBNode* Dbnode, RBNode* Parent, RBNode* Brother); // 삭제시 더블블랙 재조정 함수
	void Display(RBNode* p, int lvl = 0);
};

int main()
{
	RBTree Tree;
	int Rand[15]; randnum(Rand, 15);
	cout << "Random Insertion: ";
	for (int i = 0; i < 15; i++)
	{
		Tree.Insert(Rand[i]);
		cout << Rand[i] << " ";
	}
	cout << "\n\n";
	Tree.Display(Tree.getRoot());
	cout << "\n\n\n";
	cout << "Deletion: 3, 10\n" << endl;
	Tree.Delete(3); Tree.Delete(10);
	Tree.Display(Tree.getRoot());
}

int RBTree::getHeight(RBNode* p)
{
	if (p == NULL)
	{
		return 0;
	}
	int L = getHeight(p->getLeft()) + 1;
	int R = getHeight(p->getRight()) + 1;
	int largeone = L >= R ? L : R;
	return largeone;
}

void RBTree::DelNode(RBNode* p)
{
	if (p != NIL)
	{
		DelNode(p->getRight());
		DelNode(p->getLeft());
		delete p;
	}
}

void RBTree::Insert(int k)
{
	if (Root == NULL)
	{
		RBNode* p = new RBNode(k, BLACK, NIL, NIL);
		Root = p; return;
	}
	RBNode* p = Root, * q = NULL;
	while (p != NIL)
	{
		q = p;
		if (p->getData() > k)
		{
			p = p->getLeft();
		}
		else if (p->getData() < k)
		{
			p = p->getRight();
		}
		else // 키가 같다면
		{
			cout << "Key is Overlapped" << endl;
			return;
		}
	}
	p = new RBNode(k, RED, NIL, NIL);
	if (k > q->getData())
	{
		q->setRight(p);
	}
	else
	{
		q->setLeft(p);
	}
	ReAdjust_ins(p);
}

void RBTree::ReAdjust_ins(RBNode* p) // p는 레드임
{
	RBNode* GGpa, * Grandpa, * Uncle, * Parent, * buffer = Root;
	GGpa = Grandpa = Parent = Uncle = NULL; // 증조할부지, 할부지, 부모, 삼촌
	while (buffer != p)
	{
		GGpa = Grandpa;
		Grandpa = Parent;
		Parent = buffer;
		if (buffer->getData() > p->getData())
		{
			buffer = buffer->getLeft();
		}
		else
		{
			buffer = buffer->getRight();
		}
	}
	if (Parent->getColor() == BLACK) return;
	if (Parent == Root) { Parent->setColor(BLACK); return; }
	if (p->getData() > Grandpa->getData())
	{
		Uncle = Grandpa->getLeft();
	}
	else
	{
		Uncle = Grandpa->getRight();
	}
	if (Uncle->getColor() == RED) // 삼촌이 빨간색
	{
		Uncle->setColor(BLACK); Parent->setColor(BLACK);
		if (Grandpa != Root)
		{
			Grandpa->setColor(RED);
			ReAdjust_ins(Grandpa);
		}
		return;
	}
	// 삼촌이 검은색
	if (Grandpa->getData() > p->getData()) // p가 할아버지 왼쪽에 위치
	{
		if (Parent->getData() > p->getData()) // 왼왼
		{
			buffer = RightRotation(Grandpa);
		}
		else // 왼오
		{
			Grandpa->setLeft(LeftRotation(Parent));
			buffer = RightRotation(Grandpa);
		}
	}
	else // p가 할아버지 오른쪽에 위치
	{
		if (Parent->getData() < p->getData()) // 오오
		{
			buffer = LeftRotation(Grandpa);
		}
		else // 오왼
		{
			Grandpa->setRight(RightRotation(Parent));
			buffer = LeftRotation(Grandpa);
		}
	}
	if (Root == Grandpa)
	{
		Root = buffer;
	}
	else if (GGpa->getData() > buffer->getData())
	{
		GGpa->setLeft(buffer);
	}
	else
	{
		GGpa->setRight(buffer);
	}
	buffer->setColor(BLACK);
	buffer->getRight()->setColor(RED);
	buffer->getLeft()->setColor(RED);
}

void RBTree::Delete(int k)
{
	if (Root == NULL)
	{
		cout << "Void Deletion" << endl; return;
	}
	RBNode* p = Root, * q = NULL, * Linked = NULL, * pLinked = NULL, * bLinked = NULL;
	while (p != NIL)
	{
		if (p->getData() > k)
		{
			q = p;
			p = p->getLeft();
		}
		else if (p->getData() < k)
		{
			q = p;
			p = p->getRight();
		}
		else // 키가 같다면
		{
			break;
		}
	}
	if (p == NIL)
	{
		cout << "Can't find the Key" << endl; return;
	}
	if (p->getLeft() == NIL && p->getRight() == NIL) // 잎노드
	{
		if (q == NULL)
		{
			Root = NULL; delete p; return;
		}
		else if (q->getData() > p->getData())
		{
			q->setLeft(NIL); bLinked = q->getRight();
		}
		else
		{
			q->setRight(NIL); bLinked = q->getLeft();
		}
		Linked = NIL;
		pLinked = q;
	}
	else if (p->getLeft() == NIL || p->getRight() == NIL) // 자식이 하나만 있음
	{
		RBNode* son = p->getRight() != NIL ? p->getRight() : p->getLeft();
		if (q == NULL)
		{
			Root = son;
		}
		else if (q->getData() > p->getData())
		{
			q->setLeft(son); bLinked = q->getRight();
		}
		else
		{
			q->setRight(son); bLinked = q->getLeft();
		}
		Linked = son;
		pLinked = q;
	}
	else // 자식이 둘다 있음
	{
		RBNode* succp = p;
		RBNode* succ = p->getLeft();
		while (succ->getRight() != NIL)
		{
			succp = succ;
			succ = succ->getRight();
		}
		if (succp != p)
		{
			succp->setRight(succ->getLeft()); bLinked = succp->getLeft();
		}
		else
		{
			succp->setLeft(succ->getLeft()); bLinked = succp->getRight();
		}
		p->setData(succ->getData());
		if (q == NULL)
		{
			Root = p;
		}
		p = succ;
		Linked = succ->getLeft();
		pLinked = succp;
	}
	if (p->getColor() == RED) // 지우려는 노드가 빨강이면 그냥 종료
	{
		delete p; return;
	}
	delete p;
	// 블랙이면 문제가 된다.
	if (Linked->getColor() == RED) // 지우려는 노드가 블랙이여도 그 노드의 자식이 빨간색이면 그냥 검은색 칠하고 무난하게 종료 때린다.
	{
		Linked->setColor(BLACK); return;
	}
	// 위의 두가지 해당 사항을 모두 피해갔다면 약간 곤란해진다. 이미 검은색을 검은색으로 칠해야하기 때문이다.
	ReAdjust_del(Linked, pLinked, bLinked); // 더블 블랙인 노드를 넘겨준다.
}

void RBTree::ReAdjust_del(RBNode* Dbnode, RBNode* Parent, RBNode* Brother)
{
	if (Dbnode == Root) // 더블 블랙 노드가 루트면 종료
	{
		return;
	}
	RBNode* Grandpa = NULL, * buffer = Root;
	while (buffer != Parent)
	{
		Grandpa = buffer;
		if (buffer->getData() > Parent->getData())
		{
			buffer = buffer->getLeft();
		}
		else
		{
			buffer = buffer->getRight();
		}
	}
	bool is_DB_right = false;
	if (Dbnode != NIL)
	{
		is_DB_right = Dbnode->getData() > Parent->getData() ? true : false;
	}
	else
	{
		is_DB_right = Brother->getData() > Parent->getData() ? false : true;
	}
	if (is_DB_right == true) // 더블 블랙 노드가 오른쪽인 경우
	{
		if (Brother->getColor() == RED) // 형제 노드가 빨간색
		{
			Brother->setColor(BLACK); Parent->setColor(RED);
			if (Grandpa != NULL)
			{
				if (Grandpa->getData() < Parent->getData())
				{
					Grandpa->setRight(RightRotation(Parent));
				}
				else
				{
					Grandpa->setLeft(RightRotation(Parent));
				}
			}
			else
			{
				Root = RightRotation(Parent);
			}
			Brother = Parent->getLeft();
			ReAdjust_del(Dbnode, Parent, Brother); return;
		}
		else // 형제 노드가 검은색
		{
			if (Brother->getRight()->getColor() == BLACK && Brother->getLeft()->getColor() == BLACK) // 형제 자식들이 모두 검은색
			{
				Brother->setColor(RED);
				if (Parent->getColor() == RED)
				{
					Parent->setColor(BLACK); return;
				}
				if (Grandpa != NULL)
				{
					if (Grandpa->getData() > Parent->getData()) // 부모의 형제 얻기
					{
						Brother = Grandpa->getRight();
					}
					else
					{
						Brother = Grandpa->getLeft();
					}
					ReAdjust_del(Parent, Grandpa, Brother); return; // 부모가 검은색이였다면 더블 블랙이므로 다시 재귀적으로 검사
				}
				return;
			}
			else if (Brother->getLeft()->getColor() == BLACK && Brother->getRight()->getColor() == RED)
			{
				Brother->setColor(RED); Brother->getRight()->setColor(BLACK);
				Parent->setLeft(LeftRotation(Brother)); Brother = Parent->getLeft();
				ReAdjust_del(Dbnode, Parent, Brother); return;
			}
			else if (Brother->getLeft()->getColor() == RED)
			{
				Brother->setColor(Parent->getColor()); Parent->setColor(BLACK);
				Brother->getLeft()->setColor(BLACK);
				if (Grandpa != NULL)
				{
					if (Grandpa->getData() < Parent->getData())
					{
						Grandpa->setRight(RightRotation(Parent));
					}
					else
					{
						Grandpa->setLeft(RightRotation(Parent));
					}
				}
				else
				{
					Root = RightRotation(Parent);
				}
				return;
			}
		}
	}
	else // 더블 블랙 노드가 왼쪽인 경우
	{
		if (Brother->getColor() == RED) // 형제 노드가 빨간색
		{
			Brother->setColor(BLACK); Parent->setColor(RED);
			if (Grandpa != NULL)
			{
				if (Grandpa->getData() < Parent->getData())
				{
					Grandpa->setRight(LeftRotation(Parent));
				}
				else
				{
					Grandpa->setLeft(LeftRotation(Parent));
				}
			}
			else
			{
				Root = LeftRotation(Parent);
			}
			Brother = Parent->getRight();
			ReAdjust_del(Dbnode, Parent, Brother); return;
		}
		else // 형제 노드가 검은색
		{
			if (Brother->getRight()->getColor() == BLACK && Brother->getLeft()->getColor() == BLACK) // 형제 자식들이 모두 검은색
			{
				Brother->setColor(RED);
				if (Parent->getColor() == RED)
				{
					Parent->setColor(BLACK); return;
				}
				if (Grandpa != NULL)
				{
					if (Grandpa->getData() > Parent->getData()) // 부모의 형제 얻기
					{
						Brother = Grandpa->getRight();
					}
					else
					{
						Brother = Grandpa->getLeft();
					}
					ReAdjust_del(Parent, Grandpa, Brother); return; // 부모가 검은색이였다면 더블 블랙이므로 다시 재귀적으로 검사
				}
				return;
			}
			else if (Brother->getLeft()->getColor() == RED && Brother->getRight()->getColor() == BLACK)
			{
				Brother->setColor(RED); Brother->getLeft()->setColor(BLACK);
				Parent->setRight(RightRotation(Brother)); Brother = Parent->getRight();
				ReAdjust_del(Dbnode, Parent, Brother); return;
			}
			else if (Brother->getRight()->getColor() == RED)
			{
				Brother->setColor(Parent->getColor()); Parent->setColor(BLACK);
				Brother->getRight()->setColor(BLACK);
				if (Grandpa != NULL)
				{
					if (Grandpa->getData() < Parent->getData())
					{
						Grandpa->setRight(LeftRotation(Parent));
					}
					else
					{
						Grandpa->setLeft(LeftRotation(Parent));
					}
				}
				else
				{
					Root = LeftRotation(Parent);
				}
				return;
			}
		}
	}
}

void RBTree::Display(RBNode* p, int lvl)
{
	if (p == NIL || p == NULL) return;
	Display(p->getRight(), lvl + 1);
	for (int i = 0; i < lvl; i++)
	{
		cout << "      ";
	}
	if (p->getColor() == BLACK)
	{
		cout << "[B]" << p->getData() << endl;
	}
	else
	{
		cout << "[R]" << p->getData() << endl;
	}
	Display(p->getLeft(), lvl + 1);
}