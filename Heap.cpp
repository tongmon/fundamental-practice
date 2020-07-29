#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

#define SIZE 23

bool Hrecur(int a[], int size, int index, int option)
{
    if (index >= size)
    {
        return true;
    }
    if (option == true) // 최대 힙
    {
        if (a[(index - 1) / 2] < a[index])
        {
            return false;
        }
    }
    else if(option == false) // 최소 힙
    {
        if (a[(index - 1) / 2] > a[index])
        {
            return false;
        }
    }
    return (Hrecur(a, size, index * 2 + 1, option) && Hrecur(a, size, index * 2 + 2, option));
}

bool isHeapRecur(int a[], int size) // 배열이 힙 구조인지 검사 (재귀)
{
    if (size < 2)
    {
        cout << "Ary size is too small to judge" << endl;
        return false;
    }
    if (a[0] > a[1]) // 최대 힙
    {
        return (Hrecur(a, size, 1, true) && Hrecur(a, size, 2, true));
    }
    return (Hrecur(a, size, 1, false) && Hrecur(a, size, 2, false));
}

bool isHeapIter(int a[], int size) // 배열이 힙 구조인지 검사 (반복)
{
    bool is_max = false;
    if (size < 2)
    {
        cout << "Ary size is too small to judge" << endl;
        return false;
    }
    if (a[0] > a[1]) // 최대 힙
    {
        is_max = true;
    }
    int f = 0;
    int s = 2 * f + 1;
    int k = 2;
    while (f < size)
    {
        for (int i = s; i < s + k; i++)
        {
            if (i < size)
            {
                if (is_max == true && a[s] > a[f])
                {
                    return false;
                }
                else if (is_max == false && a[s] < a[f])
                {
                    return false;
                }
            }
            else
            {
                return true;
            }
        }
        k = k * k;
        f = s;
        s = 2 * f + 1;
    }
    return true;
}

void randnum(int* num, int size);

class heap
{
    int* ary;
    int n;
public:
    heap(int a) { ary = new int[a]; n = 0; }
    ~heap() { delete[]ary; }
    void insert(int a);
    int del();
    void display();
    int* getAry() { return ary; }
};

int main()
{
    int random[SIZE];
    heap a(SIZE);

    randnum(random, SIZE);

    if (true == isHeapIter(random, SIZE))
    {
        cout << "This is heap" << endl;
    }
    else
    {
        cout << "This is not heap" << endl;
    }

    for (int i = 0; i < SIZE; i++)
    {
        a.insert(random[i]);
        cout << random[i] << " ";
    }
    cout << endl;

    cout << "\nHeap" << endl;
    a.display();

    if (true == isHeapIter(a.getAry(), SIZE))
    {
        cout << "This is heap" << endl;
    }
    else
    {
        cout << "This is not heap" << endl;
    }

    cout << "\nDeletion" << endl;
    for (int i = 0; i < SIZE; i++)
    {
        cout << a.del() << " ";
    }
    cout << endl;
}

void heap::insert(int a)
{
    if (n == 0)
    {
        ary[n] = a;
        n++;
        return;
    }
    else if (n == (_msize(ary) / sizeof(int)))
    {
        cout << "heap is full" << endl;
        return;
    }
    int f = (n - 1) / 2;
    int s = n;
    while (s > 0)
    {
        if (a < ary[f]) //오름차순
        {
            ary[s] = ary[f];
        }
        else
        {
            break;
        }
        s = f;
        f = (s - 1) / 2;
    }
    ary[s] = a;
    n++;
    return;
}

int heap::del()
{
    if (n == 0)
    {
        cout << "heap is empty" << endl;
        exit(1);
    }
    int root = ary[0];
    int branch = ary[n - 1];
    int f = 0;
    int s = 2 * f + 1;
    while (s < n - 1)
    {
        if (ary[s] > ary[s + 1]) // 두 자식을 비교 후에 작은 놈을 올린다.
        {
            s++;
        }
        if (branch < ary[s])
        {
            break;
        }
        ary[f] = ary[s];
        f = s;
        s = f * 2 + 1;
    }
    ary[f] = branch;
    n--;
    return root;
}

void heap::display()
{
    for (int i = 0; i < n; i++)
    {
        cout << *(ary + i) << " ";
    }
    cout << endl;
}

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