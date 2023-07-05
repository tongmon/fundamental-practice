using System;

/*
https://www.acmicpc.net/problem/1357
WPF를 공부하고 있어 C#으로 짜봤다.
먼가... 먼가 형변환이 C++에 비해 길고 불편하게 느껴지는건 기분탓일까...
*/

namespace Csharp_Algo
{
    class Program
    {
        static void Main(string[] args)
        {
            int ton(string k)
            {
                var p = k.ToCharArray();
                Array.Reverse(p);
                return int.Parse(new string(p));
            }
            string str = Console.ReadLine();
            string[] n = str.Split(" ");
            Console.WriteLine(ton((ton(n[0]) + ton(n[1])).ToString()));
        }
    }
}