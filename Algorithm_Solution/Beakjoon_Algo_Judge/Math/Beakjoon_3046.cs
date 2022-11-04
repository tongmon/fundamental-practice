using System;
using System.Collections.Generic;
using System.Linq;

/*
https://www.acmicpc.net/problem/3046
단순 산술 문제...
*/

class Solution
{
    static void Main(string[] args)
    {
        var l = Console.ReadLine().Split(' ').Select(int.Parse).ToList();
        Console.WriteLine(l[1] * 2 - l[0]);
    }
}
