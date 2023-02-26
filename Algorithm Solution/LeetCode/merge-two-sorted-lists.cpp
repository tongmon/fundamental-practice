#include <bits/stdc++.h>
using namespace std;

/*
https://leetcode.com/problems/merge-two-sorted-lists/
정렬된 연결리스트 연결하기...
합병정렬할 때 하던 원리대로 하면된다. (병합정렬이였던가?...)
*/

struct ListNode 
{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* R = new ListNode(), * Q = R;
        while (list1 || list2) {
            if (list1 && list2) {
                Q->next = new ListNode((list1->val < list2->val ? list1 : list2)->val, nullptr);
                list1->val < list2->val ? list1 = list1->next : list2 = list2->next;
                Q = Q->next;
            }
            else {
                Q->next = list1 ? list1 : list2;
                break;
            }
        }
        return R->next;
    }
};