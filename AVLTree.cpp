#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <ctime>
#include <cstdlib>
using namespace std;

// AVL트리 삽입, 삭제 구현
// 기존의 이진탐색트리를 상속하여 제작했다.
// 회전을 통해 깨진 균형을 맞추어 주는게 핵심
// 삽입과 삭제 모두 지나왔던 노드들의 균형을 맞추어주기 위해 재귀가 사용된다.
// 스택으로도 구현가능하다.

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

class BSearchTree;

class BinaryNode {
    friend class BSearchTree;
private:
    BinaryNode* Left;
    int data;
    BinaryNode* Right;
public:
    BinaryNode(BinaryNode* lp = NULL, char d = '\0', BinaryNode* rp = NULL) :
        Left(lp), data(d), Right(rp) { }
    char getData() { return data; }
    BinaryNode* getLeft() { return Left; }
    BinaryNode* getRight() { return Right; }
    void setLeft(BinaryNode* p) { Left = p; }
    void setRight(BinaryNode* p) { Right = p; }
};

class BSearchTree {
private:
    BinaryNode* root;
public:
    BSearchTree() : root(NULL) { }
    BinaryNode* GetRoot() { return root; }
    void setRoot(BinaryNode* p) { root = p; }
    int CreatTree(int, int*);
    BinaryNode* NodeSearch(int x, BinaryNode** parent, bool option);
    BinaryNode* NodeSearch(int x, bool option = false)
    {
        BinaryNode* buffer;
        return NodeSearch(x, &buffer, option);
    }
    void Inorder();
    void Preorder();
    void Postorder();
    void Lvlorder();
    void DeleteNode(BinaryNode*);
    void SelDeletion(int x);
    int LeafCount(BinaryNode* p)
    {
        if (p == NULL)
        {
            return 0;
        }
        if (p->Left == NULL && p->Right == NULL)
        {
            return 1;
        }
        return LeafCount(p->Left) + LeafCount(p->Right);
    }
    int Height(BinaryNode* p)
    {
        if (p == NULL)
        {
            return 0;
        }
        int L = Height(p->Left) + 1;
        int R = Height(p->Right) + 1;
        int largeone = L >= R ? L : R;
        return largeone;
    }
};

class AVLTree : public BSearchTree
{
public:
    int getHeightDiff(BinaryNode* node)
    {
        if (node == NULL)
        {
            return 0;
        }
        int hleft = Height(node->getLeft());
        int hright = Height(node->getRight());
        return hleft - hright;
    }
    BinaryNode* rotateLL(BinaryNode* parent)
    {
        BinaryNode* child = parent->getLeft();
        BinaryNode* buffer = child->getRight();
        parent->setLeft(buffer);
        child->setRight(parent); return child;
    }
    BinaryNode* rotateRR(BinaryNode* parent)
    {
        BinaryNode* child = parent->getRight();
        BinaryNode* buffer = child->getLeft();
        parent->setRight(buffer);
        child->setLeft(parent); return child;
    }
    BinaryNode* rotateRL(BinaryNode* parent)
    {
        BinaryNode* child = parent->getRight();
        parent->setRight(rotateLL(child));
        return rotateRR(parent);
    }
    BinaryNode* rotateLR(BinaryNode* parent)
    {
        BinaryNode* child = parent->getLeft();
        parent->setLeft(rotateRR(child));
        return rotateLL(parent);
    }
    BinaryNode* reBalance(BinaryNode* parent)
    {
        int Hdiff = getHeightDiff(parent);
        if (Hdiff > 1)
        {
            if (0 < getHeightDiff(parent->getLeft()))
            {
                parent = rotateLL(parent);
            }
            else
            {
                parent = rotateLR(parent);
            }
        }
        else if (Hdiff < -1)
        {
            if (0 > getHeightDiff(parent->getRight()))
            {
                parent = rotateRR(parent);
            }
            else
            {
                parent = rotateRL(parent);
            }
        }
        return parent;
    }
    BinaryNode* Insert(int a)
    {
        if (GetRoot() == NULL)
        {
            BinaryNode* p = new BinaryNode(NULL, a, NULL);
            setRoot(p);
            return p;
        }
        BinaryNode* p = InsAVL(GetRoot(), a);
        setRoot(p); return p;
    }
    BinaryNode* InsAVL(BinaryNode* parent, int a)
    {
        if (parent->getData() > a)
        {
            if (parent->getLeft() != NULL)
            {
                parent->setLeft(InsAVL(parent->getLeft(), a));
            }
            else
            {
                BinaryNode* p = new BinaryNode(NULL, a, NULL);
                parent->setLeft(p);
            }
            return reBalance(parent);
        }
        else if (parent->getData() < a)
        {
            if (parent->getRight() != NULL)
            {
                parent->setRight(InsAVL(parent->getRight(), a));
            }
            else
            {
                BinaryNode* p = new BinaryNode(NULL, a, NULL);
                parent->setRight(p);
            }
            return reBalance(parent);
        }
        cout << "Can't insert overlapped key!" << endl;
        return NULL;
    }
    BinaryNode* Del(int a)
    {
        if (GetRoot() == NULL)
        {
            cout << "Void deletion!" << endl; return NULL;
        }
        BinaryNode* p = delAVL(GetRoot(), a);
        setRoot(p); return p;
    }
    BinaryNode* delAVL(BinaryNode* parent, int a)
    {
        if (parent->getData() > a)
        {
            if (parent->getLeft() != NULL)
            {
                parent->setLeft(delAVL(parent->getLeft(), a));
                return reBalance(parent);
            }
            else
            {
                cout << "Can't find key" << endl;
                return NULL;
            }
        }
        else if (parent->getData() < a)
        {
            if (parent->getRight() != NULL)
            {
                parent->setRight(delAVL(parent->getRight(), a));
                return reBalance(parent);
            }
            else
            {
                cout << "Can't find key" << endl;
                return NULL;
            }
        }
        // 삭제할 키를 찾음
        if (parent->getLeft() == NULL && parent->getRight() == NULL) // 잎노드
        {
            delete parent;
            return NULL;
        }
        else if (parent->getLeft() == NULL || parent->getRight() == NULL) // 자식이 하나만 있음
        {
            BinaryNode* son;
            if (parent->getRight() != NULL)
            {
                son = parent->getRight();
            }
            else
            {
                son = parent->getLeft();
            }
            delete parent;
            return reBalance(son);
        }
        else // 자식이 두개
        {
            BinaryNode* succp = parent;
            BinaryNode* succ = parent->getRight();
            while (succ->getLeft() != NULL)
            {
                succp = succ;
                succ = succ->getLeft();
            }
            if (succp != parent)
            {
                succp->setLeft(succ->getRight());
            }
            else
            {
                succp->setRight(succ->getRight());
            }
            succ->setLeft(parent->getLeft());
            succ->setRight(parent->getRight());
            delete parent;
            return reBalance(succ);
        }
    }
};

int main()
{
    AVLTree test;
    int ary[10];
    randnum(ary, 10);
    for (int i = 0; i < 10; i++)
    {
        test.Insert(ary[i]);
    }
    test.Inorder();
    test.Del(3);
    test.Del(10);
    cout << endl;
    test.Inorder();
}

int BSearchTree::CreatTree(int n, int* IntArray)
{
    BinaryNode* p, * q;
    for (int i = 0; i < n; ++i)
    {
        q = NULL; p = root;
        while (p != NULL)
        {
            q = p;
            if (IntArray[i] == p->data)
            {
                return 0;
            }
            if (IntArray[i] < p->data)
            {
                p = p->Left;
            }
            else
            {
                p = p->Right;
            }
        }
        p = new BinaryNode;
        p->data = IntArray[i];
        if (!root)
        {
            root = p;
        }
        else if (q->data < IntArray[i])
        {
            q->Right = p;
        }
        else
        {
            q->Left = p;
        }
    }
    return 1;
}

BinaryNode* BSearchTree::NodeSearch(int x, BinaryNode** parent, bool option) // option이 false면 찾기만하고 true면 없을 때 삽입까지
{
    BinaryNode* p, * q, * r;
    r = q = NULL;
    p = root;
    while (p != NULL)
    {
        r = q;
        q = p;
        if (p->data == x)
        {
            *parent = r;
            return p;
        }
        if (p->data > x)
        {
            p = p->Left;
        }
        else
        {
            p = p->Right;
        }
    }
    if (option == false)
    {
        *parent = NULL;
        return NULL;
    }
    p = new BinaryNode;
    p->data = x;
    if (!root)
    {
        root = p;
    }
    else if (q->data < x)
    {
        q->Right = p;
    }
    else
    {
        q->Left = p;
    }
    *parent = q;
    return p;
}

void BSearchTree::Inorder()
{
    stack<BinaryNode*> STACK;
    BinaryNode* p = root;

    while (1)
    {
        while (p != NULL)
        {
            STACK.push(p);
            p = p->Left;
        }
        if (STACK.empty() == false)
        {
            p = STACK.top();
            STACK.pop();
            cout << p->data << " ";
            p = p->Right;
        }
        else
        {
            break;
        }
    }
}

void BSearchTree::Preorder()
{
    stack<BinaryNode*> STACK;
    BinaryNode* p = root;

    while (1)
    {
        while (p != NULL)
        {
            cout << p->data << " ";
            STACK.push(p);
            p = p->Left;
        }
        if (STACK.empty() == false)
        {
            p = STACK.top();
            STACK.pop();
            p = p->Right;
        }
        else
        {
            break;
        }
    }
}

void BSearchTree::Postorder()
{
    stack<BinaryNode*> STACK;
    BinaryNode* p = root;
    BinaryNode* q = NULL;

    while (root != NULL)
    {
        while (p != NULL) // right과 left가 둘 다 널이면
        {
            q = p;
            STACK.push(q);
            p = p->Left;
            if (p == NULL)
            {
                p = q->Right;
            }
        }
        if (STACK.empty() == false)
        {
            cout << STACK.top()->data << " ";
            STACK.pop();
            if (STACK.empty() == false)
            {
                p = STACK.top();
            }
            else
            {
                return;
            }
            while (p->Right == NULL || p->Right == q)
            {
                cout << p->data << " ";
                q = p;
                STACK.pop();
                if (STACK.empty() == false)
                {
                    p = STACK.top();
                }
                else
                {
                    return;
                }
            }
            p = p->Right;
        }
    }
}

void BSearchTree::Lvlorder()
{
    if (root == NULL) return;
    queue<BinaryNode*> lvl;
    lvl.push(root);
    while (lvl.empty() == false)
    {
        BinaryNode* p = lvl.front();
        lvl.pop();
        if (p->Left != NULL)
        {
            lvl.push(p->Left);
        }
        if (p->Right != NULL)
        {
            lvl.push(p->Right);
        }
        cout << p->data << " ";
    }
}

void BSearchTree::DeleteNode(BinaryNode* ptr)
{
    if (ptr) {
        DeleteNode(ptr->Left);
        DeleteNode(ptr->Right);
        delete ptr;
    }
}

void BSearchTree::SelDeletion(int x)
{
    BinaryNode* parent;
    BinaryNode* p = NodeSearch(x, &parent, false);
    if (p == NULL)
    {
        cout << "void Deletion" << endl;
        return;
    }
    if (p->Left == NULL && p->Right == NULL) // 잎노드
    {
        if (parent == NULL)
        {
            root = NULL;
        }
        else if (parent->data > p->data)
        {
            parent->Left = NULL;
        }
        else
        {
            parent->Right = NULL;
        }
    }
    else if (p->Left == NULL || p->Right == NULL) // 자식이 하나만 있음
    {
        BinaryNode* son;
        if (p->Right != NULL)
        {
            son = p->Right;
        }
        else
        {
            son = p->Left;
        }
        if (parent == NULL)
        {
            root = son;
        }
        else if (parent->data > p->data)
        {
            parent->Left = son;
        }
        else
        {
            parent->Right = son;
        }
    }
    else // 자식이 둘다 있음, 실제로 데이터만 바꿔도 되지만 난 노드 자리를 통째로 바꿨다.
    {
        BinaryNode* succp = p;
        BinaryNode* succ = p->Right;
        while (succ->Left != NULL)
        {
            succp = succ;
            succ = succ->Left;
        }
        if (succp != p)
        {
            succp->Left = succ->Right;
        }
        else
        {
            succp->Right = succ->Right;
        }
        if (parent == NULL)
        {
            root = succ;
        }
        else if (parent->data > p->data)
        {
            parent->Left = succ;
        }
        else
        {
            parent->Right = succ;
        }
        succ->Left = p->Left;
        succ->Right = p->Right;
    }
    delete p;
}