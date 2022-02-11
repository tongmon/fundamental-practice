using System;
using System.Collections.Generic;
using System.Linq;

/*
https://www.acmicpc.net/problem/2358
*/

namespace Csharp_Algo
{
    class Program
    {
        static void Main(string[] args)
        {
            int t = int.Parse(Console.ReadLine()), n = 0, b;
            List<Tuple<int, int>> c = new List<Tuple<int, int>>();
            for (int i = 0; i < t; i++) {
                List<int> l = Console.ReadLine().Split(' ').Select(int.Parse).ToList<int>();
                c.Add((l[0], l[1]).ToTuple<int,int>());
            }
            c.Sort((a, b) => { if (a.Item1 == b.Item2) return a.Item2.CompareTo(b.Item2); return a.Item1.CompareTo(b.Item1); });
            for (int i = 1; i < c.Count; i++) {
                
            }
        }
    }
}