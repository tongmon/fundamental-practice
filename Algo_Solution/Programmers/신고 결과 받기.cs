using System;
using System.Collections.Generic;
using System.Linq;

/*
https://programmers.co.kr/learn/courses/30/lessons/92334
신고 결과 받기 문제.
해쉬맵을 잘 사용하면 된다.
신고당한 사람이 신고한 사람을 참조 가능해야 하고 그 반대도 가능해야 한다는 것이 중요하다.
*/

class Solution
{
    public int[] solution(string[] id_list, string[] report, int k)
    {
        int[] a = new int[id_list.Length];
        int o;
        Dictionary<string, int> V = new Dictionary<string, int>(), I = new Dictionary<string, int>(), q = new Dictionary<string, int>();
        Dictionary<string, List<string>> S = new Dictionary<string, List<string>>();
        for (int i = 0; i < id_list.Length; i++) {
            I[id_list[i]] = i;
            q[id_list[i]] = 0;
            S[id_list[i]] = new List<string>();
        }
        foreach(var r in report) {
            if(!V.TryGetValue(r, out o)) {
                var R = r.Split(' ').ToList<string>();
                S[R[1]].Add(R[0]);
                q[R[1]]++;
                V[r] = 0;
            }
        }
        foreach (var n in id_list) {
            if(q[n] >= k) {
                foreach (var x in S[n])
                    a[I[x]]++;
            }
        }
        return a;
    }
    static void Main(string[] args)
    {
        
    }
}
