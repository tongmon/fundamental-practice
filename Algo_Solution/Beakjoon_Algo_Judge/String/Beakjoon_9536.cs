using System;
using System.Collections.Generic;
using System.Linq;

/*
https://www.acmicpc.net/problem/9536
문자열 파싱은 C++보다 편한듯 한데... C#의 해쉬맵이나 다른 라이브러리들이 생각보다 숏코딩하기 어려운듯하다.
많이 짜봐야겠다.
*/

namespace Csharp_Algo
{
    class Program
    {
        static void Main(string[] args)
        {
            int t = int.Parse(Console.ReadLine()), u;
            for (int i = 0; i < t; i++)
            {
                List<string> p = Console.ReadLine().Split(' ').ToList();
                Dictionary<string, int> h = new Dictionary<string, int>();
                while (true)
                {
                    string l = Console.ReadLine();
                    if (l[l.Length - 1] == '?') 
                        break;
                    List<string> a = l.Split(' ').ToList();
                    h[a[2]] = 1;
                }
                foreach(var s in p)
                {
                    if (!h.TryGetValue(s, out u))
                        Console.Write(s + ' ');
                }
                Console.WriteLine();
            }
        }
    }
}
