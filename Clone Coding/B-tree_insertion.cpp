#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

// B-tree 삽입 구현

#define DEGREE 8 // 트리의 차수
#define SIZE 100 // 키 몇개 삽입할건지

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

int ndiv(int a)
{
    if (a == 2)
    {
        return 0;
    }
    if (a % 2 == 0)
    {
        return (a / 2) - 1;
    }
    return a / 2;
}

class Btree; 

class Mnode
{
    friend class Btree;
private:
    int k[DEGREE - 1];
    Mnode* son[DEGREE];
    Mnode* father;
    int numtree;
public:
    Mnode(Mnode* p = NULL, int n = 0) : father(p), numtree(n)
    {
        for (int i = 0; i < DEGREE; i++)
        {
            if (i < DEGREE - 1)
            {
                k[i] = 0;
            }
            son[i] = NULL;
        }
    }
    // 키보다 큰 놈을 만나면 인덱스 반환
    int nodesearch(int key)
    {
        int i;
        for (i = 0; i < numtree - 1; i++)
        {
            if (k[i] >= key)
            {
                break;
            }
        }
        return i;
    }
    // 자신이 몇 번째 자식인지 판단
    int GetIndex()
    {
        Mnode* f = father;
        int i;
        if (f == NULL)
        {
            return -1;
        }
        for (i = 0; i < f->numtree; i++)
        {
            if (f->son[i] == this)
            {
                break;
            }
        }
        return i;
    }
};

class Btree 
{
private:
    Mnode* root;
public:
    Btree() : root(NULL) { }
    ~Btree() { delB(root); }
    Btree(int key) : root(new Mnode(NULL, 2)) { root->k[0] = key; }
    Mnode* Getroot() { return root; }
    Mnode* find(int, int*);
    void insnode(Mnode*, int, int, Mnode*);
    void copy(Mnode*, int, int, Mnode*);
    Mnode* Split(Mnode*, int, int, Mnode*, Mnode*, int*);
    Mnode* insert(int, Mnode*, int);
    void BDisplay(Mnode*, int);
    void Put(int);
    void delB(Mnode*);
};

int main()
{
    int num[SIZE];
    randnum(num, SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        cout << num[i] << " ";
    }
    cout << endl;
    Btree test;
    for (int i = 0; i < SIZE; i++)
    {
        test.Put(num[i]);
    }
    test.BDisplay(test.Getroot(), 0);
}

// 노드가 어디 위치에 들어가야 할지 찾음
Mnode* Btree::find(int key, int* pposition)
{
    int i = 0;
    Mnode* q = NULL;
    Mnode* p = root;
    while (p != NULL)
    {
        i = p->nodesearch(key);
        q = p;
        if (i < p->numtree - 1 && key == p->k[i]) 
        {
            *pposition = i;
            return(p);
        }
        p = p->son[i];
    }
    *pposition = i;
    return(q);
}

// 삽입 함수
void Btree::Put(int a)
{
    if (root == NULL)
    {
        Mnode* ptr = new Mnode(NULL, 2);
        ptr->k[0] = a;
        root = ptr;
        return;
    }
    int pos = 0;
    Mnode* ptr = find(a, &pos);
    insert(a, ptr, pos);
}

// 차수가 다 차지 않은 노드 한칸씩 밀면서 키 삽입
void Btree::insnode(Mnode* nd, int pos, int newkey, Mnode* newnode)
{
    for (int i = nd->numtree - 1; i >= pos + 1; i--)
    {
        nd->son[i + 1] = nd->son[i];
        nd->k[i] = nd->k[i - 1];
    }
    nd->son[pos + 1] = newnode;
    nd->k[pos] = newkey;
    nd->numtree = nd->numtree + 1;
}

// 트리 화면 출력
void Btree::BDisplay(Mnode* p, int depth)
{
    if (p != NULL)
    {
        for (int i = 0; i < p->numtree; i++)
        {
            BDisplay(p->son[i], depth + 1);
            if (i < p->numtree - 1)
            {
                for (int j = 0; j < depth; j++)
                {
                    cout << "  I  ";
                }
                cout << "+[" << p->k[i] << "]" << endl;
            }
        }
    }
}

// 트리를 찢어놓을때 first부터 last까지 복사
void Btree::copy(Mnode* nd1, int first, int last, Mnode* nd2)
{
    int numkeys = last - first + 1;
    if (last < first) // DEGREE가 3, 4일 때 초과 되는 경우가 있다.
    {
        nd2->son[0] = nd1->son[DEGREE - 1];
        nd1->son[DEGREE - 1] = NULL;
        nd2->numtree = 1;
        return;
    }
    for (int i = first, j = 0; j <= numkeys; i++, j++)
    {
        if (j <= numkeys - 1)
        {
            nd2->k[j] = nd1->k[i];
            nd1->k[i] = 0;
        }
        nd2->son[j] = nd1->son[i];
        nd1->son[i] = NULL;
        nd2->numtree = nd2->numtree + 1;
        if (nd2->son[j] != NULL)
        {
            nd2->son[j]->father = nd2;
        }
    }
    return;
}

// 트리 찢어 놓는 함수
Mnode* Btree::Split(Mnode* nd, int pos, int newkey, Mnode* leftnode, Mnode* rightnode, int* midkey)
{
    Mnode *nd2 = new Mnode(NULL, 0);
    int hDegree = ndiv(DEGREE);
    if (pos > hDegree) // newkey가 새롭게 쪼개지는 노드에 들어가는 경우
    {
        copy(nd, hDegree + 1, DEGREE - 2, nd2);
        insnode(nd2, pos - hDegree - 1, newkey, rightnode);
        if (rightnode != NULL)
        {
            rightnode->father = nd2;
        }
        nd->numtree = hDegree + 1;
        *midkey = nd->k[hDegree];
        nd->k[hDegree] = 0;
    }
    else if (pos == hDegree) // newkey가 부모 노드에 들어가는 경우
    {
        copy(nd, hDegree, DEGREE - 2, nd2);
        nd->numtree = hDegree + 1;
        if (rightnode != NULL)
        {
            rightnode->father = nd2;
        }
        nd2->son[0] = rightnode;
        *midkey = newkey;
    }
    else // newkey가 기존 노드에 들어가는 경우
    {
        copy(nd, hDegree, DEGREE - 2, nd2);
        nd->numtree = hDegree + 1;
        insnode(nd, pos, newkey, rightnode);
        nd->numtree = hDegree + 1;
        if (rightnode != NULL)
        {
            rightnode->father = nd;
        }
        *midkey = nd->k[hDegree];
        nd->k[hDegree] = 0;
    }
    // 예전에 찢어진 왼쪽 노드도 적절히 붙여준다.
    if (leftnode != NULL)
    {
        if (pos > hDegree)
        {
            leftnode->father = nd2;
        }
        else if (pos == hDegree)
        {
            leftnode->father = nd;
            nd->son[hDegree] = leftnode;
        }
        else
        {
            leftnode->father = nd;
        }
    }
    return nd2;
}

// 삭제 함수
void Btree::delB(Mnode* p)
{
    if (p != NULL)
    {
        for (int i = 0; i < p->numtree; i++)
        {
            delB(p->son[i]);
        }
        delete p;
    }
}

// find로 찾은 곳에 적절히 삽입
Mnode* Btree::insert(int key, Mnode* s, int position)
{
    Mnode* nd = s;
    Mnode* f = nd->father;
    Mnode* nd2 = NULL;
    Mnode* leftnode = NULL, * rightnode = NULL;
    int newkey = key, pos = position, midkey;
    while (f != NULL && nd->numtree == DEGREE) // 차수가 꽉차버리면 쪼개주어야한다.
    {
        // nd와 nd2로 쪼개고 앞에서 먼저 쪼개진 left, right node를 적절히 연결해줌
        nd2 = Split(nd, pos, newkey, leftnode, rightnode, &midkey);
        pos = nd->GetIndex();
        rightnode = nd2; // 쪼개진 오른쪽 노드 저장
        leftnode = nd; // 쪼개진 왼쪽 노드 저장
        rightnode->father = f;
        nd = f;
        f = nd->father;
        newkey = midkey;
    }
    if (nd->numtree < DEGREE)
    {
        insnode(nd, pos, newkey, rightnode);
        return nd;
    }
    // 루트까지 차버리면 루트 쪼개기
    nd2 = Split(nd, pos, newkey, leftnode, rightnode, &midkey);
    root = new Mnode(NULL, 2);
    root->k[0] = midkey;
    root->son[0] = nd;
    root->son[1] = nd2;
    nd->father = root;
    nd2->father = root;
    return(root);
}