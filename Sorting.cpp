#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

// 대표적인 정렬 알고리즘
// 업계 표준으로 보통 퀵정렬이 많이 쓰인다고 한다.
// 분할-정복이라는 방식이 중요하니 머리에서 되새김질 해라

#define SIZE 20

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

void siftup(int x[], int n)
{
    int i, s, f, element;
    for (i = 1; i < n; i++)
    {
        element = x[i];
        s = i;
        f = (s - 1) / 2;
        while (s > 0 && x[f] < element)
        {
            x[s] = x[f];
            s = f;
            f = (s - 1) / 2;
        }
        x[s] = element;
    }
}

void Heapsort(int x[], int n) // 힙정렬
{
    siftup(x, n);
    //siftdown
    for (int i = n - 1; i > 0; i--)
    {
        int  ivalue = x[i];
        int f, s;
        x[i] = x[0];
        f = 0;
        if (i > 2 && x[2] > x[1])
        {
            s = 2;
        }
        else
        {
            s = 1;
        }
        while (s <= i - 1 && ivalue < x[s] && i != 1)
        {
            x[f] = x[s];
            f = s;
            s = 2 * f + 1;
            if (x[s] < x[s + 1])
            {
                s = s + 1;
            }
        }
        x[f] = ivalue;
    }
}

void merge(int x[], int low, int mid, int high)
{
    int i, j, k = 0;
    int* aux = new int[high - low + 1];
    for (i = low, j = mid + 1; i <= mid && j <= high;)
    {
        if (x[i] <= x[j])
        {
            aux[k++] = x[i++];
        }
        else
        {
            aux[k++] = x[j++];
        }
    }
    for (; i <= mid; i++, k++)
    {
        aux[k] = x[i];
    }
    for (; j <= high; j++, k++)
    {
        aux[k] = x[j];
    }
    for (i = low, k = 0; i <= high; i++, k++)
    {
        x[i] = aux[k];
    }
    delete[]aux;
}

void Mergesort(int x[], int low, int high = -2) // 합병정렬
{
    if (high == -2)
    {
        high = low - 1;
        low = 0;
    }
    if (low < high)
    {
        int mid = (low + high) / 2;
        Mergesort(x, low, mid);
        Mergesort(x, mid + 1, high);
        merge(x, low, mid, high);
    }
}

void partition(int x[], int lb, int ub, int* pj)
{
    int pivot = x[lb], down = lb, up = ub, temp;
    while (down < up)
    {
        while (x[down] <= pivot && down < ub)
        {
            down++;
        }
        while (x[up] > pivot)
        {
            up--;
        }
        if (down < up)
        {
            temp = x[down];
            x[down] = x[up];
            x[up] = temp;
        }
    }
    x[lb] = x[up];
    x[up] = pivot;
    *pj = up;
}

void Quick(int x[], int lb, int ub = -2) // 퀵정렬
{
    int j;
    if (ub == -2)
    {
        ub = lb - 1;
        lb = 0;
    }
    else if (lb >= ub)
    { return; }
    partition(x, lb, ub, &j);
    Quick(x, lb, j - 1);
    Quick(x, j + 1, ub);
}

void Shell(int ary[], int size, int incrmnts[] = NULL, int incsize = 0) // 쉘정렬
{
    int incr, j, k, gap, y;
    if (incsize == 0)
    {
        int p[4] = { 7,5,3,1 };
        incrmnts = p;
        incsize = 4;
    }
    for (incr = 0; incr < incsize; incr++)
    {
        gap = incrmnts[incr];
        for (j = gap; j < size; j++)
        {
            y = ary[j];
            for (k = j - gap; k >= 0 && y < ary[k]; k = k - gap)
            {
                ary[k + gap] = ary[k];
            }
            ary[k + gap] = y;
        }
    }
}

void Insert(int ary[], int size) // 삽입정렬
{
    int Selection, j;
    for (int i = 1; i < size; i++)
    {
        Selection = ary[i];
        for (j = i - 1; j >= 0; j--)
        {
            if (Selection > ary[j])
            {
                ary[j + 1] = ary[j];
            }
            else
            {
                break;
            }
        }
        ary[j + 1] = Selection;
    }
}

void Selsort(int x[], int n) // 선택정렬
{
    int i, indx, j, large;
    for (i = n - 1; i > 0; i--) 
    {
        large = x[0];
        indx = 0;
        for (j = 1; j <= i; j++)
        {
            if (x[j] > large) 
            {
                large = x[j];
                indx = j;
            }
        }
        x[indx] = x[i];
        x[i] = large;
    }
}

void Bubsort(int x[], int n) // 버블정렬
{
    int temp = 0;
    bool flag = false; // 바뀐지 아닌지 체크
    for (int i = n - 1; i > 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (x[j] > x[j + 1])
            {
                temp = x[j];
                x[j] = x[j + 1];
                x[j + 1] = temp;
                flag = true;
            }
        }
        if (flag == false) // 바뀔게 없으니 끝
        { return; }
    }
}
int main()
{
    int num[SIZE];
    randnum(num, SIZE);
    for (int i = 0; i < SIZE; i++)
    { cout << num[i] << " "; }
    cout << endl;
    Mergesort(num, SIZE);
    for (int i = 0; i < SIZE; i++)
    { cout << num[i] << " "; }
}