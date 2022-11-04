using System;
using System.Collections.Generic;
using System.Linq;

/*
https://www.acmicpc.net/problem/17176
알파벳을 적절히 배열 인덱싱 해주면 된다.
*/

namespace Csharp_Algo
{
    class Program
    {
        static void Main(string[] args)
        {
            int n = int.Parse(Console.ReadLine()), k;
            int[] a = new int[55];
            var q = Console.ReadLine().Split(' ').ToList<string>().Select(int.Parse);
            foreach(var p in q)
                a[p]++;
            string l = Console.ReadLine();
            foreach(var c in l) {
                k = 0;
                if ('A' <= c && c <= 'Z') k = c - 'A' + 1;
                else if ('a' <= c && c <= 'z') k = c - 'a' + 27;
                if (a[k] != 0)
                    a[k]--;
                else { n = 0; break; }
            }
            Console.WriteLine(n == 0 ? 'n' : 'y');
        }
    }
}