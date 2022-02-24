using System;
using System.Collections.Generic;
using System.Linq;

/*
https://www.acmicpc.net/problem/4158
해쉬맵으로 매칭시키면 된다.
*/

class Solution
{
    static void Main(string[] args)
    {
        while (true)
        {
            var l = Console.ReadLine().ToString().Split(' ').Select(int.Parse).ToList();
            if (l[0] == 0 && l[1] == 0)
                break;
            List<int> list = new List<int>();
            Dictionary<int, int> d = new Dictionary<int, int>();
            int a = 0;
            for (int j = 0; j < 2; j++) {
                for (int i = 0; i < l[j]; i++) {
                    int k = int.Parse(Console.ReadLine().ToString()), p;
                    d[k] = d.TryGetValue(k, out p) ? p + 1 : 1;                    
                }
            }
            foreach(var u in d) {
                if (u.Value > 1) a++;
            }
            Console.WriteLine(a);
        }
    }
}