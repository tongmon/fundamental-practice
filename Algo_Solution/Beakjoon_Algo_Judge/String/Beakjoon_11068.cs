using System;
using System.Collections.Generic;
using System.Linq;

/*
https://www.acmicpc.net/problem/11068
진법 변환하고 회문 비교를 해주면 된다.
*/

namespace Csharp_Algo
{
    class Program
    {
        static void Main(string[] args)
        {
            string l = Console.ReadLine();
            for (int i = 0; i < int.Parse(l); i++) {
                string n = Console.ReadLine();
                int P = int.Parse(n), f = 0;
                for (int j = 2; j < 65 && f == 0; j++) {
                    int N = P;
                    List<int> L = new List<int>();
                    while (N != 0) {
                        L.Add(N % j);
                        N /= j;
                    }
                    f = 1;
                    for (int x = 0; x < L.Count / 2 && f == 1; x++) {
                        if (L[x] != L[L.Count - x - 1])
                            f = 0;
                    }
                }
                Console.WriteLine(f);
            }
        }
    }
}