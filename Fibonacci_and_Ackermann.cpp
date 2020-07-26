#include <iostream>
#include <queue>
using namespace std;

int Fibonacci_Q(int loop) // 큐를 이용한 피보나치
{
    queue<int> Fib;
    Fib.push(0); Fib.push(1);
    while (loop >= 1)
    {
        loop--;
        Fib.push(Fib.front() + Fib.back());
        Fib.pop();
    }
    return Fib.front();
}

int Fibonacci_Re(int loop, int post = 0, int front = 1) // 반복형 재귀를 이용한 피보나치
{
    if (loop <= 0) return post;
    Fibonacci_Re(--loop, front, post + front);
}

int Fibonacci(int loop) // 재귀를 이용한 피보나치
{
    if (loop <= 0) return 0;
    else if (loop == 1) return 1;
    else
    {
        return Fibonacci(loop - 1) + Fibonacci(loop - 2);
    }
}

int Fibo(int* count, int loop)
{
    count[loop]++;
    if (loop <= 0)
    {
        return 0;
    }
    else if (loop == 1)
    {
        return 1;
    }
    else
    {
        return Fibo(count, loop - 1) + Fibo(count, loop - 2);
    }
}

void printFib(int loop) // 피보나치 재귀가 얼마나 비효율적인지 알기위한 카운트 함수
{
    int* ary = new int[loop + 1];
    for (int i = 0; i <= loop; i++)
    {
        ary[i] = 0;
    }
    Fibo(ary, loop);
    for (int i = 0; i <= loop; i++)
    {
        cout << "Fibo(" << i << ") = " << ary[i] << "번\n";
    }
    delete[]ary;
}

int Ackermann(int m, int n) // 수가 조금해도 미친듯이 값이 불려지는 애커만 함수
{
    if (m == 0)
    {
        return n + 1;
    }
    else if (m > 0 && n == 0)
    {
        return Ackermann(m - 1, 1);
    }
    else if (m > 0 && n > 0)
    {
        return Ackermann(m - 1, Ackermann(m, n - 1));
    }
    cout << "error" << endl;
    return -1;
}
