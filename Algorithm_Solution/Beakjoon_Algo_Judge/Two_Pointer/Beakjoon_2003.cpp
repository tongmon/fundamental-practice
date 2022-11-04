#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2003
�� �����Ͷ�� �˰������� �����ϴ� ������.
�� �����ʹ� �������� �κ����� ���ϴ� ��� ���Ǵ� �˰����ε� ó���� �� �����ʹ� ó�� �迭 ���Ҹ� ����Ų��.
���� ó�� �����Ϳ��� ������ �����ͱ����� �κ����� �۴ٸ� �� ũ�� ����� �־���ϱ⿡ ������ ������ �κ��� �������� ���� ���Ҹ� �����ش�.
�̶� �� �� �ִ� ���� �� �����ʹ� ��� �迭 ���Ұ� �ڿ������ ���� �����Ѵٴ� ���̴�. ������ �����͸� ���������ִ� ������ �κ����� �� ũ�� ����ٴ�
������ �ϰ� �ִ� �˰����̱� �����̴�.
�ƹ�ư �׷���... ���࿡ �ݴ�� �κ����� ��ǥġ���� �� Ŀ���ٸ�? ó�� �����͸� �ݴ�� ������Ű�� �κ����� ���ҵȴ�.
�̸� �������� �ݺ��ؾ� �ϳĸ� ������ �����Ͱ� �迭�� ���������� �� �����״µ� ���� �κ����� ��ǥġ���� �۴�? �׷��� �׸��ϸ� �ȴ�.
�ֳĸ� �κ����� ������ �����Ͱ� ��� �迭�� �� ����Ű�� ���� �� ����ų�� ���� ������ �پ���� �ۿ� �ȳ��ұ� �����̴�. (ó�� �����Ͱ� �����ϸ�)
�̷��� �˰����� ����ϸ� �ð����⵵ ��! N���� ������ Ǯ����.
�����ϰ� ���������� ����for������ ������ ��������!
������ڸ� ��� ���Ұ� �ڿ����� �κ����� ���ؾ��ϴ� ��Ȳ�̸� ��ü�� Ž���� �ʿ䰡 ���� �� ������ �˰����� ����Ѵٴ� ���� �˰� ����!
�ڼ��� ������ �̺��� �����̴ּ�. https://m.blog.naver.com/kks227/220795165570
*/

#pragma warning(disable:4996)

int N, Ary[10001], Count = 0;
long long S, Sum = 0;

/*
void DFS(int Cur, long long Sum) // ��ü Ž��, ���� ������
{
    if (Cur == N) return;
    if (Visited[Cur + 1] == false)
    {
        Visited[Cur + 1] = true; DFS(Cur + 1, 0);
    }
    if (Sum + Ary[Cur] > S) return;
    if (Sum + Ary[Cur] == S) { Count++; return; }
    DFS(Cur + 1, Sum + Ary[Cur]);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> N >> S;
    for (int i = 0; i < N; i++)
    {
        cin >> Ary[i];
    }
    DFS(0, 0);
    cout << Count;
}

int main() // ���� for��, ������
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> N >> S;
    for (int i = 0; i < N; i++)
    {
        cin >> Ary[i];
    }
    for (int i = 0; i < N; i++)
    {
        long long Sum = 0;
        for (int j = i; j < N; j++)
        {
            Sum = Sum + Ary[j]; 
            if (Sum == S) { Count++; break; }
            if (Sum > S) break;
        }
    }
    cout << Count;
}
*/

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> N >> S;
    for (int i = 0; i < N; i++)
        cin >> Ary[i];
    int Low = 0, High = 0;
    while (High < N || Sum >= S)
    {
        if (S == Sum) Count++;
        if (S <= Sum) Sum = Sum - Ary[Low++];
        else if (High < N) Sum = Sum + Ary[High++];
    }
    cout << Count;
}
