#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1991
트리 구현 문제다.
클래스로 트리 구현해서 할 수도 있지만 귀찮기에 배열로 만들었다.
다른 사람의 풀이를 보니 char tree[26][2] = { '.', }; 이렇게 푼사람이 있던데 이 방법이 더 효율적인듯 하다.
나는 일차원 배열로 풀었기에 순회를 돌때는 위의 방식과 속도 차이가 없지만 삽입시에 난 이중for문이 돌고 위의 방식은
단일 for문으로 처리가 끝난다.
이 문제를 통해 트리문제를 배열로 풀려할 때 이차원 배열도 고려할 수 있다는 점을 배우고 간다.
*/

#pragma warning(disable:4996)

char Tree[1000] = { 0, };

int goLeft(int index)
{
    return 2 * index + 1;
}

int goRight(int index)
{
    return 2 * index + 2;
}

void Intrav(int index)
{
    if (Tree[index] == '.')
    {
        return;
    }
    Intrav(goLeft(index));
    cout << Tree[index];
    Intrav(goRight(index));
}

void Post(int index)
{
    if (Tree[index] == '.')
    {
        return;
    }
    Post(goLeft(index));
    Post(goRight(index));
    cout << Tree[index];
}

void Pre(int index)
{
    if (Tree[index] == '.')
    {
        return;
    }   
    cout << Tree[index];
    Pre(goLeft(index));
    Pre(goRight(index));
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int N, index; cin >> N;
    char root, left, right;
    cin >> root >> left >> right;
    Tree[0] = root; Tree[1] = left; Tree[2] = right;
    for (int i = 1; i < N; i++)
    {
        cin >> root >> left >> right;
        for (int j = 0;; j++)
        {
            if (Tree[j] == root)
            {
                index = j; break;
            }
        }
        Tree[index * 2 + 1] = left; Tree[index * 2 + 2] = right;
    }
    Pre(0); cout << "\n";
    Intrav(0); cout << "\n";
    Post(0);
}