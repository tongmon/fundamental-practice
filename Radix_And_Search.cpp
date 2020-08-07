#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

#define MAX_SIZE 120

// 비교가 필요없는 정렬이 있다????
// 그것이 바로 기수 정렬
// 비교가 필요없어 빠른 경우가 많지만 그만큼 버퍼가 많이 필요하다.
// 버퍼(큐)의 수는 십진수면 0 ~ 9까지 10개, 이진수면 2개, 알파벳이면 26개 이런식으로 늘어나야한다.
// 십진수 자리수는 어떻게 구하냐면 예를 들어 121의 십의 자리수 구하려면 121을 10으로 나눈후에 %10을 또 써주면 된다.
// 100의 자리는 100으로 나눈 후에 %10... 이런식이다.
// 순환 기법 연습으로 Pow함수 짰으니 기억 잘 안날 때마다 되새길 것

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

double Pow(double num, int factor) // 순환 기법 잘봐라
{
    if (factor == 0)
    {
        return 1;
    }
    else if (factor % 2 == 0)
    {
        return Pow(num * num, factor / 2);
    }
    return num * Pow(num * num, (factor - 1) / 2);
}

void Radix(int* ary, int size) // 기수 정렬
{
    vector<int> Digit[10];
    int factor = 1; int numeral = 10, bigone = 0, max = 0;
    for (int i = 0; i < size; i++)
    {
        if (bigone < ary[i])
        {
            bigone = ary[i];
        }
    }
    while (bigone != 0)
    {
        bigone = bigone / 10;
        max++;
    }
    for (int p = 0; p < max; p++)
    {
        int k = 0;
        for (int i = 0; i < size; i++)
        {
            // 각 자리의 숫자 구하기
            int index = ary[i] / factor;
            index = index % numeral;
            // 각 자리 수에 걸맞는 큐에 삽입
            Digit[index].push_back(ary[i]);
        }
        for (int i = 0; i < numeral; i++)
        {
            while (Digit[i].empty() == false)
            {
                ary[k++] = Digit[i].front();
                Digit[i].erase(Digit[i].begin());
            }
        }
        factor = factor * numeral;
    }
}

void Bsearch_Re(int* ary, int num, int start, int end)
{
    int mid = (start + end) / 2;
    if (start > end)
    {
        cout << "Can't find the element!" << endl; return;
    }
    else if (ary[mid] == num)
    {
        cout << "Found element: " << ary[mid] << endl; return;
    }
    else if (num < ary[mid])
    {
        Bsearch_Re(ary, num, start, mid - 1); return;
    }
    Bsearch_Re(ary, num, mid + 1, end); return;
}

void Bsearch(int* ary, int size, int num)
{
    int start = 0, end = size - 1, mid;
    while (start <= end)
    {
        mid = (start + end) / 2;
        if (ary[mid] == num)
        {
            cout << "Found element: " << ary[mid] << endl; return;
        }
        else if (ary[mid] < num)
        {
            start = mid + 1;
        }
        else
        {
            end = mid - 1;
        }
    }
    cout << "Can't find the element!" << endl; return;
}

int main()
{
    int rand[MAX_SIZE];
    randnum(rand, MAX_SIZE);
    Radix(rand, MAX_SIZE);
    for (int i = 0; i < MAX_SIZE; i++)
    {
        cout << rand[i] << " ";
    }
    cout << endl;
    Bsearch_Re(rand, 30, 0, MAX_SIZE - 1);
    Bsearch(rand, MAX_SIZE, 112);
}