#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <functional>
using namespace std;

// 힙을 이용한 호프만 코드 생성기
// 자료의 빈도수에 따라 용량을 가변하기 위한 방법. 
// 자료가 많다면 줄이고 적다면 늘린다. 하지만 중복되는 코드가 없어 순서대로 읽어서 출력 가능
// 원래는 헤더 "Binary.h" 에 이진 트리 자료 구조가 포함이였지만 깃 허브에 한 번에 올리기 위해 따로 빼내어 같이 담는다.
// 코드 짜면서 배운 교훈: using namespace std; 이거 .h와 .cpp파일에도 달아주지 않으면 컴파일러가 vector를 인식하지 못한다.

typedef struct _Spel // 빈도수, 글자 정보
{
    int Freq = 0;
    char spel = '\0';
} SpelFreq;
class BinaryTree;

typedef struct _Hoff // 호프만 코드에 대한 정보 집합
{
    char* H_code;
    char spel;
    int Freq;
} Hoffmann_Code;

class BinaryNode {
    friend class BinaryTree;
private:
    BinaryNode* Left;
    SpelFreq data;
    BinaryNode* Right;
public:
    BinaryNode(BinaryNode* lp = NULL, int freq = -1, char d = -1, BinaryNode* rp = NULL)
    {
        Left = lp; Right = rp; data.Freq = freq; data.spel = d;
    }
    SpelFreq getData() { return data; }
    void setRight(BinaryNode* p) { Right = p; }
    void setLeft(BinaryNode* p) { Left = p; }
    BinaryNode* getRight() { return Right; }
    BinaryNode* getLeft() { return Left; }
};

class BinaryTree
{
    BinaryNode* root;
public:
    BinaryTree() :root(NULL) {}
    BinaryTree(int a, char b)
    {
        BinaryNode* ptr = new BinaryNode(NULL, a, b, NULL);
        root = ptr;
    }
    ~BinaryTree()
    {
        DeleteNode(root);
    }
    BinaryNode* Getroot() { return root; }
    BinaryNode* SetLeft(BinaryNode*, int, char);
    BinaryNode* SetRight(BinaryNode*, int, char);
    BinaryNode* SetRoot(BinaryNode*);
    char* GetCode(BinaryNode* p, char letter, vector<char> storage);
    char* GetCode(char letter)
    {
        vector<char> buffer;
        return GetCode(root, letter, buffer);
    }
    void DeleteNode(BinaryNode* p)
    {
        if (p != NULL)
        {
            DeleteNode(p->Left);
            DeleteNode(p->Right);
            delete p;
        }
    }
};

bool operator>(SpelFreq a, SpelFreq b) // greater than operator는 꼭!!! > 로 선언
{
    if (a.Freq == b.Freq) // 빈도 수가 같으면
    {
        return a.spel > b.spel; // 글자 사전 순
    }
    else
    {
        return a.Freq > b.Freq; // 빈도 수 작은 순
    }
}

bool operator<(SpelFreq a, SpelFreq b) // lesser than operator는 꼭!!! < 로 선언
{
    if (a.Freq == b.Freq) // 빈도 수가 같으면
    {
        return a.spel < b.spel; // 글자 사전 순
    }
    else
    {
        return a.Freq < b.Freq; // 빈도 수 작은 순
    }
}

void Reader(vector<SpelFreq>* data, const char* sent)
{
    int i = 0;
    while (sent[i] != '\0')
    {
        if (sent[i] != ' ' && sent[i] != ',' && sent[i] != '.' && sent[i] != '"')
        {
            bool flag = false;
            for (int k = 0; k < data->size(); k++)
            {
                if (data->at(k).spel == sent[i])
                {
                    flag = true;
                    data->at(k).Freq = data->at(k).Freq + 1;
                    break;
                }
            }
            if (flag == false)
            {
                SpelFreq buffer; buffer.Freq = 1; buffer.spel = sent[i];
                data->push_back(buffer);
            }
        }
        i++;
    }
}

BinaryNode* Hoffmann_tree(vector<SpelFreq> data)
{
    priority_queue<SpelFreq, vector<SpelFreq>, greater<SpelFreq>> data_que;
    vector<BinaryNode*> storage;
    SpelFreq Poped_1, Poped_2, Poped_3;
    BinaryNode* buffer_1 = NULL, * buffer_2 = NULL, * buffer_3 = NULL;
    bool is_1, is_2;
    char dist = -1;
    for (int i = 0; i < data.size(); i++)
    {
        data_que.push(data[i]);
    }
    while (data_que.size() > 1)
    {
        is_1 = is_2 = false;
        Poped_1 = data_que.top(); data_que.pop();
        Poped_2 = data_que.top(); data_que.pop();
        Poped_3.Freq = Poped_1.Freq + Poped_2.Freq; Poped_3.spel = dist--;
        for (int i = 0; i < storage.size(); i++)
        {
            int freq = storage[i]->getData().Freq;
            char letter = storage[i]->getData().spel;
            if ((freq == Poped_1.Freq) && (letter == Poped_1.spel))
            {
                is_1 = true;
                buffer_1 = storage[i];
                storage.erase(storage.begin() + i); i--;
            }
            else if ((freq == Poped_2.Freq) && (letter == Poped_2.spel))
            {
                is_2 = true;
                buffer_2 = storage[i];
                storage.erase(storage.begin() + i); i--;
            }
        }
        if (is_1 == false)
        {
            buffer_1 = new BinaryNode(NULL, Poped_1.Freq, Poped_1.spel, NULL);
        }
        if (is_2 == false)
        {
            buffer_2 = new BinaryNode(NULL, Poped_2.Freq, Poped_2.spel, NULL);
        }
        buffer_3 = new BinaryNode(NULL, Poped_3.Freq, Poped_3.spel, NULL);
        storage.push_back(buffer_3);

        // 트리 구성
        buffer_3->setLeft(buffer_1);
        buffer_3->setRight(buffer_2);

        data_que.push(Poped_3);
    }
    return buffer_3; // 호프만 계수 측정 트리의 루트 반환
}

int main()
{
    BinaryTree HoffTree;
    vector<SpelFreq> data;

    const char* sentence = "The remainder of the song tells of many unrelated events, with the refrain of Blinded by the light, cut loose like a deuce, another runner in the night";
    // The remainder of the song tells of many unrelated events, with the refrain of Blinded by the light, cut loose like a deuce, another runner in the night.
    // "According to Springsteen, he wrote the song by going through a rhyming dictionary in search of appropriate words."
    Reader(&data, sentence);
    HoffTree.SetRoot(Hoffmann_tree(data));
    
    sort(data.begin(), data.end());

    Hoffmann_Code* ary = new Hoffmann_Code[data.size()];

    for (int i = 0; i < data.size(); i++)
    {
        ary[i].H_code = HoffTree.GetCode(data[i].spel);
        ary[i].Freq = data[i].Freq;
        ary[i].spel = data[i].spel;
        cout << "글자: " << ary[i].spel << " 빈도수: " << ary[i].Freq << " 호프만 코드: " << ary[i].H_code << endl;
    }
}

BinaryNode* BinaryTree::SetLeft(BinaryNode* p, int k, char a)
{
    if (p == NULL)
    {
        cout << "Void Insertion" << endl;
        return NULL;
    }
    if (p->Left != NULL)
    {
        cout << "Wrong Insertion" << endl;
        return NULL;
    }
    BinaryNode* ptr = new BinaryNode(NULL, k, a, NULL);
    p->Left = ptr;
    return p->Left;
}

BinaryNode* BinaryTree::SetRight(BinaryNode* p, int k, char a)
{
    if (p == NULL)
    {
        cout << "Void Insertion" << endl;
        return NULL;
    }
    if (p->Right != NULL)
    {
        cout << "Wrong Insertion" << endl;
        return NULL;
    }
    BinaryNode* ptr = new BinaryNode(NULL, k, a, NULL);
    p->Right = ptr;
    return p->Right;
}

BinaryNode* BinaryTree::SetRoot(BinaryNode* p)
{
    if (p == NULL)
    {
        cout << "Current Root is NULL" << endl;
        return NULL;
    }
    root = p;
    return root;
}

char* BinaryTree::GetCode(BinaryNode* p, char letter, vector<char> storage)
{
    if (p->Left == NULL && p->Right == NULL)
    {
        if (letter == p->data.spel)
        {
            char* ptr = new char[storage.size() + 1];
            for (int i = 0; i < storage.size(); i++)
            {
                ptr[i] = storage[i];
            }
            ptr[_msize(ptr) - 1] = '\0';
            return ptr;
        }
        return NULL;
    }
    char* ptr_1, * ptr_2;
    storage.push_back('1');
    ptr_1 = GetCode(p->Left, letter, storage);
    storage.pop_back();
    storage.push_back('0');
    ptr_2 = GetCode(p->Right, letter, storage);
    if (ptr_1 == NULL && ptr_2 == NULL)
    {
        return NULL;
    }
    else if (ptr_1 == NULL)
    {
        return ptr_2;
    }
    return ptr_1;
}