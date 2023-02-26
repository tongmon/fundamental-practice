using System;
using System.Collections.Generic;
using System.Linq;

/*
https://www.acmicpc.net/problem/2501
그저... 약수구하기... 제일 큰수가 10000이라 무지성 나누기하면 된다.
쉬어가기;;
*/

class Solution
{
    static void Main(string[] args)
    {
        var l = Console.ReadLine().Split(' ');
        int a = int.Parse(l[0]), b = int.Parse(l[1]);
        List<int> c = new List<int>();
        for (int i = 1; i <= a; i++) {
            if(a % i == 0)
                c.Add(i);
        }
        Console.WriteLine(c.Count < b ? 0 : c[b - 1]);
    }
}