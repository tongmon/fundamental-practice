using System;
using System.Collections.Generic;

/*
https://www.acmicpc.net/problem/2947
버블정렬을 직접 구현하면 된다.
지금 출력할 때 foreach로 일일이 해주고 있지만 string.Join(" ", N)을 통해 나온 문자열을 출력하면 숏코딩이 가능하다.
*/

namespace Csharp_Algo
{
    class Program
    {
        static void Main(string[] args)
        {
            string l = Console.ReadLine();
            string[] a = l.Split(' ');
            bool ch = true;
            List<int> N = new List<int>();
            foreach(var s in a)
                N.Add(s[0] - '0');
            while (ch == true) {
                ch = false;
                for (int i = 0; i < N.Count - 1; i++)
                {
                    if (N[i] > N[i + 1])
                    {
                        var temp = N[i];
                        N[i] = N[i + 1];
                        N[i + 1] = temp;
                        ch = true;
                        foreach (var t in N)
                            Console.Write(t.ToString() + ' ');
                        Console.WriteLine();
                    }
                }
            }
        }
    }
}