using System;
using System.Collections.Generic;
using System.Linq;

/*
https://www.acmicpc.net/problem/2491
오름차순 한번, 내림차순 한번 총 두번 for문을 돌면된다.
*/

class Solution
{
    static void Main(string[] args)
    {
        Console.ReadLine();
        var l = Console.ReadLine().Split(' ').Select(int.Parse).ToList();
        int b, c, a = 1;
        for (int j = 0; j < 2; j++) {
            b = l[0]; c = 1;
            for (int i = 1; i < l.Count(); i++)
            {
                c = j > 0 ? (l[i] >= b ? c + 1 : 1) : (l[i] <= b ? c + 1 : 1);
                b = l[i];
                a = Math.Max(a, c);
            }
        }
        Console.WriteLine(a);
    }
}