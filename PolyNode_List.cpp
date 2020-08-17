#include <iostream>
#include <string>
using namespace std;

class PolyList;

class PolyNode
{
	friend class PolyList;
private:
	int coef;
	int exp;
	PolyNode* next;
	PolyNode(int c, int e) :coef(c), exp(e) { next = NULL; }
};

class PolyList
{
	friend PolyList* operator+(PolyList&, PolyList&);
	friend PolyList* operator-(PolyList&, PolyList&);
	friend PolyList* operator*(PolyList&, PolyList&);
private:
	PolyNode* head, * tail;
public:
	PolyList() { head = tail = NULL; }
	~PolyList() 
	{
		if (head != NULL)
		{
			PolyNode* p = head;
			while (head != NULL)
			{
				p = head;
				head = head->next;
				delete p;
			}
		}
	}
	int GetCoef(PolyNode* p) { return p->coef; }
	int GetExp(PolyNode* p) { return p->exp; }
	int RetCoef(int exp);
	PolyNode* MoveNext(PolyNode* p) { return p->next; }
	void Attach(int coef, int exp);
	void Insfirst(int coef, int exp);
	void del(PolyNode* p);
	void SortExp();
	void Display();
};

int main()
{
	PolyList one;
	PolyList two;
	PolyList* Result;
	one.Attach(2, 3);
	one.Attach(1, 1);
	one.SortExp();
	one.Display();
	two.Attach(1, 3);
	two.Attach(2, 4);
	two.SortExp();
	two.Display();
	Result = one * two;
	Result->Display();
}

PolyList* operator+(PolyList& A, PolyList& B)
{
	PolyList* Result = new PolyList;
	PolyNode* p = A.head;
	PolyNode* q = B.head;
	int coef, exp;

	while (p != NULL && q != NULL)
	{
		if (A.GetExp(p) == B.GetExp(q))
		{
			coef = A.GetCoef(p) + B.GetCoef(q);
			exp = A.GetExp(p);
			if (coef != 0)
			{
				Result->Attach(coef, exp);
			}
			p = A.MoveNext(p); q = B.MoveNext(q);
		}
		else if (A.GetExp(p) > B.GetExp(q))
		{
			if (A.GetCoef(p) != 0)
			{
				Result->Attach(A.GetCoef(p), A.GetExp(p));
			}
			p = A.MoveNext(p);
		}
		else
		{
			if (B.GetCoef(q) != 0)
			{
				Result->Attach(B.GetCoef(q), B.GetExp(q));
			}
			q = B.MoveNext(q);
		}
	}
	while (p != NULL)
	{
		coef = A.GetCoef(p);
		exp = A.GetExp(p);
		Result->Attach(coef, exp);
		p = A.MoveNext(p);
	}
	while (q != NULL)
	{
		coef = B.GetCoef(q);
		exp = B.GetExp(q);
		Result->Attach(coef, exp);
		q = B.MoveNext(q);
	}
	return Result;
}

/*
PolyList* operator*(PolyList& A, PolyList& B)
{
	int size = 0;
	PolyNode* p = A.head;
	while (p != NULL)
	{
		size++;
		p = A.MoveNext(p);
	}
	PolyList* poly = new PolyList[size];
	PolyList* Result = new PolyList;
	p = A.head;
	for (int i = 0; i < size; i++)
	{
		PolyNode* q = B.head;
		while (q != NULL)
		{
			poly[i].Attach(B.GetCoef(q) * A.GetCoef(p), B.GetExp(q) + A.GetExp(p));
			q = B.MoveNext(q);
		}
		p = A.MoveNext(p);
		poly[i].SortExp();
	}
	for (int i = 0; i < size; i++)
	{
		Result = *Result + poly[i];
	}
	return Result;
}
*/

PolyList* operator*(PolyList& A, PolyList& B)
{
	PolyNode* p = A.head;
	PolyList* Result = new PolyList;
	while(p != NULL)
	{
		PolyNode* q = B.head;
		PolyList* poly = new PolyList;
		while (q != NULL)
		{
			poly->Attach(B.GetCoef(q) * A.GetCoef(p), B.GetExp(q) + A.GetExp(p));
			q = B.MoveNext(q);
		}
		p = A.MoveNext(p);
		poly->SortExp();
		Result = *Result + *poly;
		delete poly;
	}
	return Result;
}


PolyList* operator-(PolyList& A, PolyList& B)
{
	PolyList* Result = new PolyList;
	PolyNode* p = A.head;
	PolyNode* q = B.head;
	int coef, exp;

	while (p != NULL && q != NULL)
	{
		if (A.GetExp(p) == B.GetExp(q)) // 지수가 같을 경우
		{
			coef = A.GetCoef(p) - B.GetCoef(q); // 계수를 서로 빼준다.
			exp = A.GetExp(p);
			if (coef != 0) // 계수가 0이면 넣을 이유 없다.
			{
				Result->Attach(coef, exp);
			}
			p = A.MoveNext(p); q = B.MoveNext(q);
		}
		else if (A.GetExp(p) > B.GetExp(q)) // A 지수가 더 크면
		{
			if (A.GetCoef(p) != 0) // 계수가 0이면 넣을 이유 없다.
			{
				Result->Attach(A.GetCoef(p), A.GetExp(p));
			}
			p = A.MoveNext(p);
		}
		else // B 지수가 더 크면
		{
			if (B.GetCoef(q) != 0) // 계수가 0이면 넣을 이유 없다.
			{
				Result->Attach(-B.GetCoef(q), B.GetExp(q));
				// A-B인데 A식에서 빼주게 되는 B식과 같은 지수를 가지는 항이 없으면 B의 계수는 -가 붙는다.
			}
			q = B.MoveNext(q);
		}
	}
	while (p != NULL) // A에 남아있는 노드들 삽입
	{
		coef = A.GetCoef(p);
		exp = A.GetExp(p);
		Result->Attach(coef, exp);
		p = A.MoveNext(p);
	}
	while (q != NULL) // B에 남아있는 노드들 삽입
	{
		coef = -B.GetCoef(q); // B에 남아있는 노드들은 계수에 -가 붙어서 삽입된다.
		exp = B.GetExp(q);
		Result->Attach(coef, exp);
		q = B.MoveNext(q);
	}
	return Result;
}

void PolyList::Attach(int coef, int exp)
{
	PolyNode* p = new PolyNode(coef, exp);
	if (head == NULL)
	{
		head = p;
		tail = p;
		return;
	}
	tail->next = p;
	tail = p;
}

void PolyList::Insfirst(int c, int e)
{
	PolyNode* p = new PolyNode(c, e); // c와 e를 계수와 지수로 가지는 노드 생성
	if (head == NULL) // 리스트가 비어있으면
	{
		head = p;
		tail = p;
		return;
	}
	p->next = head;
	head = p;
}

int PolyList::RetCoef(int e)
{
	PolyNode* p = head;
	while (p != NULL)
	{
		if (GetExp(p) == e) // 포인트된 노드의 지수와 e와 같다면
		{
			return GetCoef(p); // 포인트된 노드의 계수를 반환
		}
		p = p->next;
	}
	cout << "Can't find matched Exp" << endl; // 일치하는 지수를 못찾았으면
	return 0;
}

void PolyList::Display()
{
	PolyNode* ptr;
	ptr = head;
	if (ptr == NULL)
	{
		cout << "list is empty" << endl;
		return;
	}
	while (ptr != NULL)
	{
		if (ptr == head)
		{
			cout << " " << GetCoef(ptr) << "x^" << GetExp(ptr) << " ";
		}
		else if (GetCoef(ptr) > 0)
		{
			cout << "+";
			cout << " " << GetCoef(ptr) << "x^" << GetExp(ptr) << " ";
		}
		else
		{
			cout << "-";
			cout << " " << -GetCoef(ptr) << "x^" << GetExp(ptr) << " ";
		}
		ptr = ptr->next;
	}
	cout << endl;
}

void PolyList::SortExp()
{
	if (head == tail)
	{
		return;
	}
	PolyList A;
	while (head != NULL) // 같은거 합치기
	{
		PolyNode* p = head->next;
		PolyNode* q = head;
		int rexp = q->exp;
		int rcoef = q->coef;
		while (p != NULL)
		{
			q = p;
			p = p->next;
			if (rexp == q->exp)
			{
				rcoef = rcoef + q->coef;
				del(q);
			}
		}
		if (rcoef != 0)
		{
			A.Attach(rcoef, rexp);
		}
		if (head != NULL)
		{
			del(head);
		}
	}
	while (A.head != NULL) // 큰 놈부터 정렬
	{
		PolyNode* p = A.head;
		PolyNode* q = p;
		int bigexp = p->exp;
		while (p != NULL)
		{
			if (bigexp < p->exp)
			{
				q = p;
				bigexp = q->exp;
			}
			p = p->next;
		}
		Attach(q->coef, q->exp);
		A.del(q);
	}
}

void PolyList::del(PolyNode* p)
{
	if (p == NULL)
	{
		cout << "NULL Deletion" << endl;
		return;
	}
	if (head == tail)
	{
		head = tail = NULL;
		delete p;
		return;
	}
	if (p == head)
	{
		head = head->next;
		delete p;
		return;
	}
	PolyNode* q = head;
	while (q->next != p)
	{
		q = q->next;
	}
	if (p == tail)
	{
		q->next = NULL;
		tail = q;
		delete p;
		return;
	}
	q->next = p->next;
	delete p;
	return;
}