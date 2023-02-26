#include <iostream>
using namespace std;

#define SIZE 64
#define TABLE_SIZE 13

int HashFuntion(char *a, int mod)
{
	int r = 0;
	for (int i = 0; i < strlen(a); i++)
	{
		r = r + (int)(a[i] - 80) * i * 19;
	}
	r = r % mod;
	return r;
}


class Record 
{
	char key[SIZE];
	char value[SIZE];
public:
	Record(char* k = NULL, char* v = NULL) 
	{ 
		if (k != NULL && v != NULL)
		{
			setR(k, v);
		}
		reset(); 
	}
	void setR(char* k, char* v) 
	{
		strcpy_s(key, k); 
		strcpy_s(value, v);
	}
	bool is_empty() 
	{
		if (key[0] == '\0')
		{
			return true;
		}
		return false;
	}
	bool equal(char* k) { return strcmp(k, key) == 0; }
	void reset() 
	{ 
		strcpy_s(key, ""); 
		strcpy_s(value, "");
	}
	void display() { cout << "Key: " << key << " Value: " << value << endl; }
	void display_node() { cout << "(Key: " << key << " Value: " << value << ")"; }
};

class HashMap // 해시맵
{
	Record table[TABLE_SIZE];
public:
	HashMap() 
	{
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			table[i].reset();
		}
	}
	void display()
	{
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			cout << "Index: " << i << " ";
			table[i].display();
		}
	}
	void Linearpush(char* key, char* value) // 선형 조사법
	{
		int index = HashFuntion(key, TABLE_SIZE);
		int count = 0, k = index;
		while (count != TABLE_SIZE)
		{
			if (table[k].is_empty() == true)
			{
				table[k].setR(key, value);
				return;
			}
			else if (table[k].equal(key) == true)
			{
				cout << "Key is overlapped!" << endl; return;
			}
			k = (index + (++count)) % TABLE_SIZE;
		}
		cout << "Hashmap is full" << endl;
	}
	Record* LinearSearch(char* key)
	{
		int index = HashFuntion(key, TABLE_SIZE);
		int count = 0, k = index;
		while (count != TABLE_SIZE)
		{
			if (table[k].equal(key) == true)
			{
				cout << "Search Complete! index-> " << k << endl;
				return &table[index];
			}
			k = (index + (++count)) % TABLE_SIZE;
		}
		cout << "Can't find matched element!" << endl;
	}
	void QuadraProb(char* key, char* value) // 이차 조사법
	{
		int index = HashFuntion(key, TABLE_SIZE);
		int count = 0, k = index;
		do
		{
			if (table[k].is_empty() == true)
			{
				table[k].setR(key, value);
				return;
			}
			else if (table[k].equal(key) == true)
			{
				cout << "Key is overlapped!" << endl; return;
			}
			++count;
			k = (index + count * count) % TABLE_SIZE;
		} while (k != index);
		cout << "Hashmap is full" << endl;
	}
	Record* QuadraSearch(char* key)
	{
		int index = HashFuntion(key, TABLE_SIZE);
		int count = 0, k = index;
		do
		{
			if (table[k].equal(key) == true)
			{
				cout << "Search Complete! index-> " << k << endl;
				return &table[index];
			}
			++count;
			k = (index + count * count) % TABLE_SIZE;
		} while (k != index);
		cout << "Can't find matched element!" << endl;
	}
	void DoubleProb(char* key, char* value) // 이중 해싱
	{
		int index = HashFuntion(key, TABLE_SIZE);
		int k = index, count = 0;
		int STEP = 1 + index % 11; // 여기서 11에 해당하는 수는 TABLE_SIZE보다 약간 작은 소수여야 한다.
		do
		{
			if (table[k].is_empty() == true)
			{
				table[k].setR(key, value);
				return;
			}
			else if (table[k].equal(key) == true)
			{
				cout << "Key is overlapped!" << endl; return;
			}
			++count;
			k = (index + STEP * count) % TABLE_SIZE;
		} while (k != index);
	}
	Record* DoubleSearch(char* key)
	{
		int index = HashFuntion(key, TABLE_SIZE);
		int k = index, count = 0;
		int STEP = 1 + index % 11;
		do
		{
			if (table[k].equal(key) == true)
			{
				cout << "Search Complete! index-> " << k << endl;
				return &table[index];
			}
			++count;
			k = (index + STEP * count) % TABLE_SIZE;
		} while (k != index);
		cout << "Can't find matched element!" << endl;
	}
};

class HashNode : public Record
{
	HashNode* next;
public:
	HashNode() :Record() { next = NULL; }
	~HashNode() 
	{
		if (next != NULL)
		{
			delete next;
		}
	}
	HashNode(char* k, char* v, HashNode* p)
	{
		setR(k, v);
		next = p;
	}
	void setNext(HashNode* p) { next = p; }
	HashNode* getNext() { return next; }
};

class HashChainMap // 체이닝 기법
{
	HashNode* Node[TABLE_SIZE];
public:
	HashChainMap() 
	{
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			Node[i] = NULL;
		}
	}
	~HashChainMap()
	{
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			if (Node[i] != NULL)
			{
				delete Node[i];
			}
		}
	}
	void display()
	{
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			cout << "Index: " << i << " ";
			HashNode* p = Node[i];
			if (p != NULL)
			{
				while (p != NULL)
				{
					p->display_node();
					cout << " -> ";
					p = p->getNext();
				}
			}
			cout << "NULL\n";
		}
	}
	void ChainPush(char* key, char* value)
	{
		int index = HashFuntion(key, TABLE_SIZE);
		HashNode* newone = new HashNode(key, value, NULL);
		if (Node[index] != NULL) // 누가 이미 있음
		{
			HashNode* p = Node[index];
			while (p->getNext() != NULL)
			{
				if (p->equal(key) == true) // 중복 검사
				{
					cout << "Key is overlapped!" << endl; return;
				}
				p = p->getNext();
			}
			p->setNext(newone);
		}
		else
		{
			Node[index] = newone;
		}
	}
	HashNode* ChainSearch(char *key)
	{
		int index = HashFuntion(key, TABLE_SIZE);
		HashNode* p = Node[index];
		while (p != NULL)
		{
			if (p->equal(key) == true)
			{
				cout << "Search Complete! index-> " << index << endl;
				return p;
			}
			p = p->getNext();
		}
		cout << "Can't find matched element!" << endl;
		return NULL;
	}
};

int main()
{
	cout << "선형 조사법\n";
	HashMap hash;
	hash.Linearpush("do", "반복");
	hash.Linearpush("if", "분기");
	hash.Linearpush("for", "반복");
	hash.Linearpush("return", "반환");
	hash.display();
	hash.LinearSearch("for");
	cout << "\n\n이차 조사법\n";
	HashMap hash_2;
	hash_2.QuadraProb("do", "반복");
	hash_2.QuadraProb("if", "분기");
	hash_2.QuadraProb("for", "반복");
	hash_2.QuadraProb("return", "반환");
	hash_2.display();
	hash_2.QuadraSearch("for");
	cout << "\n\n이중 해싱\n";
	HashMap hash_3;
	hash_3.DoubleProb("do", "반복");
	hash_3.DoubleProb("if", "분기");
	hash_3.DoubleProb("for", "반복");
	hash_3.DoubleProb("return", "반환");
	hash_3.display();
	hash_3.DoubleSearch("for");
	cout << "\n\n체이닝\n";
	HashChainMap Chain;
	Chain.ChainPush("do", "반복");
	Chain.ChainPush("if", "분기");
	Chain.ChainPush("for", "반복");
	Chain.ChainPush("return", "반환");
	Chain.display();
	Chain.ChainSearch("for");
}