# Iterator Pattern   

복잡한 데이터일수록 순회와 관련된 문제가 발생한다.  
해당 문제를 해결하기 위해 반복자 패턴이 많이 사용된다.  
반복자는 순회를 하는 경우 사용되기에 몇 가지 연산자만 재정의해주면 된다.   
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

배열이 아닌 자료구조에서 반복자를 어떻게 응용하는지 이진 트리를 통해 알아보자.  
밑과 같이 트리 노드가 존재한다.  
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

    Node(const T &value, Node<T> *const left = nullptr, Node<T> *const right = nullptr)
        : value(value), left(left), right(right)
    {
        if (left)
            left->parent = this;
        if (right)
            right->parent = this;
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
```
보통의 이진 트리 노드다.  
양 가지에 대한 포인터, 부모에 대한 포인터, 자신이 속한 트리에 대한 포인터가 존재한다.  
&nbsp;  

다음은 이진 트리에 대한 구조체다.  
```c++
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
};
```
보통의 이진 트리와 같이 루트 노드가 멤버 변수로 존재한다.  
&nbsp;  

해당 이진 트리에 반복자 기능을 부여해보자.  
```c++
template <typename T>
struct BinaryTree
{
    // 나머지 구현부 생략

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
                Node<U> *p = current->parent;
                if (p && p->right == current)
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
};
```
전위 순회에 대한 반복자 클래스를 이진 트리 내부에다가 만들어줬다.  
반복자를 사용하기 위해 ```!=, ++, *```에 대한 연산자들을 재정의하였다.   
&nbsp;  

전위 순회 반복자를 STL 형식의 반복자 인터페이스와 같이 만들기 위해 밑과 같이 구현한다.  
```c++
template <typename T>
struct BinaryTree
{
    // 나머지 로직 생략

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
```
전위 순회 반복자이기에 begin() 함수는 root 부터 시작한다.  
&nbsp;  

만들어진 반복자를 이용해 밑과 같이 순회가 가능하다.  
```c++
BinaryTree<std::string> family
{
    new Node<std::string>
    {
        "me",
        new Node<std::string>
        {
            "mother",
            new Node<std::string>{"mother's mother"},
            new Node<std::string>{"mother's father"}
        },
        new Node<std::string>{"father"}
    }
};

for (auto it = family.begin(); it != family.end(); ++it)
{
    std::cout << (*it).value << "\n";
}

for (auto &item : family)
    std::cout << item.value << "\n";
```
전위 순회이기에 ```me, mother, mother's mother, mother's father, father``` 순으로 출력될 것이다.  
&nbsp;  

중위 순회도 비슷한 방식으로 만들고 타입 이름을 다르게 선언하면 될 것이다.  
```c++
template <typename U>
struct InOrderIterator
{
    Node<U> *current;
    explicit InOrderIterator(Node<U> *current)
        : current(current)
    {
    }
    bool operator!=(const InOrderIterator<U> &other)
    {
        return current != other.current;
    }
    InOrderIterator<U> &operator++()
    {
        if (current->right)
        {
            current = current->right;
            while (current->left)
                current = current->left;
        }
        else
        {
            Node<U> *p = current->parent;
            while (p && current == p->right)
            {
                current = p;
                p = p->parent;
            }
            current = p;
        }
        return *this;
    }
    Node<U> &operator*()
    {
        return *current;
    }
};

using in_iterator = InOrderIterator<T>;

in_iterator in_end()
{
    return in_iterator{nullptr};
}

in_iterator in_begin()
{
    Node<T> *n = root;
    if (n)
        while (n->left)
            n = n->left;
    return in_iterator{n};
}
```
중위 순회이기에 in_begin() 함수에서 제일 좌측 노드부터 시작하는 것을 볼 수 있다.  
&nbsp;  

순회 방식을 별도의 객체로 분리하여 제공하는 방식도 있다.  
```c++
template <typename T>
struct BinaryTree
{
    // 나머지 구현부 생략

    explicit BinaryTree(Node<T> *const root)
        : root{root}, inorder{*this}
    {
        root->set_tree(this);
    }

    class inorder_traversal
    {
        BinaryTree<T> &tree;

      public:
        inorder_traversal(BinaryTree<T> &tree)
            : tree{tree}
        {
        }
        in_iterator begin()
        {
            return tree.in_begin();
        }
        in_iterator end()
        {
            return tree.in_end();
        }
    } inorder;
};
```
inorder라는 중위 순회를 위한 클래스가 멤버 변수로 추가되었다.  
그리고 해당 멤버 변수를 생성자에서 초기화해주고 있다.  
&nbsp;  

이렇게 하면 in_begin() 같은 인터페이스를 사용하지 않고 직관적으로 밑과 같이 순회가 가능하다.  
```c++
for (auto &item : family.inorder)
    std::cout << item.value << "\n";
```
&nbsp;  

## 코루틴을 이용한 순회  

위에서 다루었던 ```operator++()``` 함수들을 보면 코드가 직관적이지 않다.  
C++20에서 도입된 코루틴을 사용하면 반복자에서 ```++``` 연산자를 재정의할 때 좀 더 직관적이게 코드를 작성할 수 있다.  
코루틴에 대한 자세한 내용은 [이곳](https://github.com/tongmon/fundamental-practice/blob/master/Programming%20Language/C%2B%2B/Confusing%20Concepts/Parallelism%20and%20Concurrency.md#coroutine)을 참고하자.  
예시에서 쓰일 코루틴의 제너레이터는 [이곳](https://github.com/tongmon/fundamental-practice/blob/master/Programming%20Language/C%2B%2B/Confusing%20Concepts/Parallelism%20and%20Concurrency.md#%ED%85%9C%ED%94%8C%EB%A6%BF-%EC%A0%81%EC%9A%A9)에 구현되어 있다.  
&nbsp;  



