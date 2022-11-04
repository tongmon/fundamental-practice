/*
https://www.acmicpc.net/problem/10817
세 수 비교..
삼항연산자를 쓰거나 정렬을 하거나... 아마 삼항연산자가 더 숏코딩일 듯하다.
C++람다만 쓰다가 C#람다 쓰려니 헷갈린다;;
*/

class Solution
{
    static void Main(string[] args)
    {
        var l = Console.ReadLine().Split(' ').Select(int.Parse).ToList();
        l.Sort((a, b) => { return a.CompareTo(b); });
        Console.WriteLine(l[1]);
    }
}