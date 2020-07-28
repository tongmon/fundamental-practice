#include <windows.h>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

class BSearchTree;

class BinaryNode {
    friend class BSearchTree;
private:
    BinaryNode* Left;
    char data;
    BinaryNode* Right;
    BinaryNode(BinaryNode* lp = NULL, char d = '\0', BinaryNode* rp = NULL) :
        Left(lp), data(d), Right(rp) { }
public:
    char getData() { return data; }
};

class BSearchTree {
private:
    BinaryNode* root;
public:
    BSearchTree() : root(NULL) { }
    BinaryNode* GetRoot() { return root; }
    int CreatTree(int, char*);
    BinaryNode* NodeSearch(char x, BinaryNode** parent, bool option);
    BinaryNode* NodeSearch(char x, bool option = false) 
    {
        BinaryNode* buffer;
        return NodeSearch(x, &buffer, option);
    }
    void Inorder();
    void Preorder();
    void Postorder();
    void Lvlorder();
    void DeleteNode(BinaryNode*);
    void Display(BinaryNode* p, int height, int curx);
    void Display()
    {
        int h = Height(root);
        Display(root, h, h * h);
    }
    void SelDeletion(char x);
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


int main()
{
    char ary[] = { 'M', 'F', 'P', 'D', 'O', 'G', 'K', 'S', 'V', 'R' };
    BSearchTree BST;
    BST.CreatTree(sizeof(ary), ary);
    BST.SelDeletion('F');
    BST.Display();
    cout << endl;
    
    cout << "\nInorder" << endl;
    BST.Inorder();
    cout << endl;

    cout << "\nPreorder" << endl;
    BST.Preorder();
    cout << endl;

    cout << "\nPostorder" << endl;
    BST.Postorder();
    cout << endl;

    cout << "\nLevelorder" << endl;
    BST.Lvlorder();
    cout << "\n\n";

    cout << BST.NodeSearch('P')->getData() << endl;
}

void BSearchTree::Display(BinaryNode* p, int height, int curx)
{
    if (p == NULL)
    {
        return;
    }
    int y = Height(GetRoot()) - height;
    COORD Pos = { curx, y * 2 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
    cout << "|" << p->data << "|";
    Display(p->Left, height - 1, curx - (height - 1) * (height - 1));
    Display(p->Right, height - 1, curx + (height - 1) * (height - 1));
}

int BSearchTree::CreatTree(int n, char* IntArray)
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

BinaryNode* BSearchTree::NodeSearch(char x, BinaryNode** parent, bool option) // option이 false면 찾기만하고 true면 없을 때 삽입까지
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

void BSearchTree::SelDeletion(char x)
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