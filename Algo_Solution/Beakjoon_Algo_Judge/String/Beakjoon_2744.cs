using System;
using System.Collections.Generic;

/*
https://www.acmicpc.net/problem/2744
C# 대소문자 ToUpper, ToLower
*/

namespace Csharp_Algo
{
    class Program
    {
        static void Main(string[] args)
        {
            string s = Console.ReadLine(), a = "";
            foreach(var c in s) {
                a += ('a' <= c && c <= 'z') ? c.ToString().ToUpper() : c.ToString().ToLower();
            }
            Console.WriteLine(a);
        }
    }
}