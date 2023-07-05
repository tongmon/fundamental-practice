using System;
using System.Collections.Generic;

/*
https://www.acmicpc.net/problem/11899
스택을 이용해서 해봤다.
C#으로 짠 짧은 코드를 봤는데 다음과 같은 코드가 있더라.
var s = Console.ReadLine();
while (s.Contains("()")) s = s.Replace("()", "");
Console.WriteLine(s.Length);
문자열로 교체를 진행하여 개수를 구하는 방식인데 속도는 느리지만 짧다...
*/

namespace Csharp_Algo
{
    class Program
    {
        static void Main(string[] args)
        {
            Stack<int> l = new Stack<int>();
            string s = Console.ReadLine();
            int a = 0;
            foreach(var c in s)
            {
                if (l.Count == 0 && c == ')')
                    a++;
                else if (c == ')')
                    l.Pop();
                else
                    l.Push(1);
            }
            Console.WriteLine(a + l.Count);
        }
    }
}