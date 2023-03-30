# Iterator Pattern   

복잡한 데이터일수록 순회와 관련된 문제가 발생한다.  
해당 문제를 해결하기 위해 반복자 패턴이 많이 사용된다.  
반복자는 순회를 하기위해 사용되기에 ```다음 항목으로 이동```, ```비교```만 정의해주면 된다.  
따라서 ```++, !=``` 연산자만 재정의해주면 된다.   
&nbsp;  

## 표준 라이브러리 반복자  

첫번째 반복자는 밑과 같이 획득한다.  
```c++
std::vector<std::string> vec{"tongstar", "gyungjun", "starfish", "spongebob"};
std::vector<std::string>::iterator first = vec.begin();
```
벡터를 제외한 대부분의 stl 자료구조들도 동일한 인터페이스를 제공한다.  
&nbsp;  

활용은 밑과 같다.  
```c++
std::string str_first = *first; // 값 참조
size_t first_length = first->length(); // 값 활용

auto second = ++first; // 다음으로 이동
size_t iter_to_index = std::distance(vec.begin(), second); // 반복자를 인덱스로 변환
```
반복자는 마치 포인터처럼 작동한다.  
second는 두번째 원소를 가리키므로 iter_to_index 값은 1이 도출된다.  
&nbsp;  

반복자를 이용한 순회는 밑과 같다.  
```c++
auto iter = vec.begin();
while (iter != vec.end())
{
    // do something...
    iter++;
}

for (auto iter = vec.begin(); iter != vec.end(); iter++)
{
    // do something...
}
```
&nbsp;  

stl 컨테이너를 사용하지 않아도 반복자 사용이 가능하다.  
```c++
char ary[]{"hello world"};
for (auto iter = std::begin(ary); iter != std::end(ary); iter++)
{
    // do something...
}
```
위와 같이 함수형 begin(), end() 함수를 사용하면 된다.  
&nbsp;  

물론 역순회도 가능하다.  
```c++
for (auto iter = vec.rbegin(); iter != vec.rend(); iter++)
{
    // do something...
}
```
주의할 점은 역순회에는 역반복자를 사용하기에 동일하게 ```++``` 연산자가 사용된다는 것이다.  
&nbsp;  

상수 반복자도 존재한다.  
```c++
std::vector<std::string>::const_iterator const_iter = vec.cbegin(); // 상수 반복자
std::vector<std::string>::const_reverse_iterator const_rev_iter = vec.crbegin(); // 상수 역반복자
```
규칙은 간단하다.  
상수면 c가 붙고 역순이면 r이 붙는다.  
&nbsp;  

반복자와 관련된 연산자들이 모두 구현이 되었다면 밑과 같이 범위 기반 for문 사용이 가능하다.  
```c++
for (const auto &item : vec)
{
    // do something...
}
```
&nbsp;  

## 이진 트리의 탐색  

```c++
template <typename T>
struct BinaryTree;

template <typename T>
struct Node
{
    T value;
    Node<T> *left = nullptr;
    Node<T> *right = nullptr;
    Node<T> *parent = nullptr;
    BinaryTree<T> *tree = nullptr;

    explicit Node(const T &value)
        : value(value)
    {
    }

    Node(const T &value, Node<T> *const left, Node<T> *const right)
        : value(value), left(left), right(right)
    {
        this->left->tree = this->right->tree = tree;
        this->left->parent = this->right->parent = this;
    }

    void set_tree(BinaryTree<T> *t)
    {
        tree = t;
        if (left)
            left->set_tree(t);
        if (right)
            right->set_tree(t);
    }

    ~Node()
    {
        if (left)
            delete left;
        if (right)
            delete right;
    }
};

template <typename T>
struct BinaryTree
{
    Node<T> *root = nullptr;

    explicit BinaryTree(Node<T> *const root)
        : root{root}
    {
        root->set_tree(this);
    }

    ~BinaryTree()
    {
        if (root)
            delete root;
    }

    template <typename U>
    struct PreOrderIterator
    {
        Node<U> *current;

        explicit PreOrderIterator(Node<U> *current)
            : current(current)
        {
        }

        bool operator!=(const PreOrderIterator<U> &other)
        {
            return current != other.current;
        }

        PreOrderIterator<U> &operator++()
        {
            if (current->left)
                current = current->left;
            else
            {
                Node<T> *p = current->parent;
                if (p->right == current)
                    p = p->parent;
                current = current->right;
                while (!current && p)
                {
                    current = p->right;
                    p = p->parent;
                }
            }

            return *this;
        }

        Node<U> &operator*()
        {
            return *current;
        }
    };

    using iterator = PreOrderIterator<T>;

    iterator end()
    {
        return iterator{nullptr};
    }

    iterator begin()
    {
        return iterator{root};
    }
};

int main()
{
    //         me
    //        /  \
    //   mother   father
    //      / \
    //   m'm   m'f

    BinaryTree<std::string> family{
        new Node<std::string>{"me",
                              new Node<std::string>{"mother",
                                                    new Node<std::string>{"mother's mother"},
                                                    new Node<std::string>{"mother's father"}},
                              new Node<std::string>{"father"}}};

    for (auto it = family.begin(); it != family.end(); ++it)
    {
        std::cout << (*it).value << "\n";
    }

    return 0;
}
```