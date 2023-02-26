#include <iostream>
#include <string>
using namespace std;

// 연결 리스트 삽입, 삭제, 방향 바꾸기 구현

class LinkList;

class ListNode
{
	friend class LinkList;
private:
	int info;
	ListNode* next;
	ListNode(int a = '\0', ListNode* p = NULL) :info(a), next(p) {}
};

class LinkList
{
	ListNode* list;
public:
	LinkList() :list(NULL) {}
	LinkList(int a) :list(new ListNode(a, NULL)) {}
	~LinkList()
	{
		if (list != NULL)
		{
			ListNode* delpointer = list;
			while (list != NULL)
			{
				delpointer = list;
				list = list->next;
				delete delpointer;
			}
		}
	}
	int size()
	{
		ListNode* p = list;
		int count = 0;
		while (p != NULL)
		{
			count++;
			p = p->next;
		}
		return count;
	}
	void Insert(int x, ListNode* node);
	void Insert(int x);
	void Delete(int x);
	void display();
	void Reverse();
	int Total();
	int DELAST();
};

int main()
{
	LinkList list;
	list.Insert(12);
	list.Insert(11);
	list.Insert(10);
	list.Insert(9);
	list.Insert(8);
	list.display();
	cout << endl;
	list.Reverse();
	list.display();
}

void LinkList::Insert(int x, ListNode* node)
{
	if (node == NULL)
	{
		ListNode* ptr = new ListNode(x, NULL);
		list = ptr;
		return;
	}
	ListNode* ptr = new ListNode(x, node->next);
	node->next = ptr;
	return;
}

void LinkList::Reverse()
{
	if (size() <= 1)
	{
		return;
	}
	ListNode* cur = list, * cnext = list->next;
	cur->next = NULL;
	while (cnext != NULL)
	{
		ListNode* p = cnext->next;
		cnext->next = cur;
		cur = cnext;
		cnext = p;
	}
	list = cur;
}

void LinkList::Insert(int x)
{
	ListNode* ptr = new ListNode(x, NULL);
	if (list == NULL)
	{
		list = ptr;
		return;
	}
	ptr->next = list;
	list = ptr;
	return;
}

void LinkList::Delete(int x)
{
	if (list == NULL)
	{
		cout << "list is empty" << endl;
		return;
	}
	ListNode* p, * q;
	q = NULL;
	p = list;
	while (p != NULL && p->info != x)
	{
		q = p;
		p = p->next;
	}
	if (p == NULL)
	{
		cout << "Can't find matched char" << endl;
		return;
	}
	if (q == NULL)
	{
		list = list->next;
		delete p;
		return;
	}
	q->next = p->next;
	delete p;
	return;
}

void LinkList::display()
{
	ListNode* p = list;
	cout << "( ";
	while (p)
	{
		cout << p->info;
		if (p = p->next)
		{
			cout << "->";
		}
	}
	cout << " )\0";
}

int LinkList::Total()
{
	if (list == NULL) // 리스트가 비어있다면
	{
		cout << "list is empty" << endl;
		exit(1);
	}
	ListNode* p = list;
	int sum = 0;
	while (p != NULL)
	{
		sum = sum + p->info;
		p = p->next;
	}
	return sum;
}

int LinkList::DELAST()
{
	if (list == NULL) // 리스트가 비어있다면
	{
		cout << "list is empty" << endl;
		exit(1);
	}
	ListNode* p = list;
	ListNode* q = NULL;
	int lastnum = 0;
	if (p->next == NULL) // 리스트에 노드가 한개면
	{
		lastnum = p->info;
		list = NULL;
		delete p;
		return lastnum;
	}
	while (p->next != NULL) // 맨 끝을 지우기에 p->next를 검사한다.
	{
		q = p;
		p = p->next;
	}
	q->next = NULL;
	lastnum = p->info;
	delete p;
	return lastnum;
}