#include <bits/stdc++.h>
using namespace std;

/*
https://leetcode.com/problems/add-two-numbers/
연결리스트 관련한 구현 문제
올림만 잘 신경 써주면 된다.
*/

struct ListNode
{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};


class Solution
{
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        ListNode* p = new ListNode((l1->val + l2->val) % 10), * r = p, * t = nullptr;
        std::vector<int> a, b;
        while (l1)
        {
            a.push_back(l1->val);
            l1 = l1->next;
        }
        while (l2)
        {
            b.push_back(l2->val);
            l2 = l2->next;
        }
        int s = min(a.size(), b.size()), u = (a[0] + b[0]) / 10, i;
        for (i = 1; i < s; i++)
        {
            t = new ListNode((a[i] + b[i] + u) % 10);
            u = (a[i] + b[i] + u) / 10;
            p->next = t;
            p = t;
        }
        std::vector<int>* m = a.size() > b.size() ? &a : &b;
        for (; i < m->size(); i++)
        {
            t = new ListNode(((*m)[i] + u) % 10);
            u = ((*m)[i] + u) / 10;
            p->next = t;
            p = t;
        }
        if (u)
            p->next = new ListNode(u);
        return r;
    }
};