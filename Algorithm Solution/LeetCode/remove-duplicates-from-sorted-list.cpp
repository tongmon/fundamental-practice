#include <bits/stdc++.h>
using namespace std;

/*
https://leetcode.com/problems/remove-duplicates-from-sorted-list/submissions/
정렬된 연결리스트가 주어지면 그 연결리스트에서 중복된 원소들 제거하고
다시 반환하는 문제.
이전 노드의 val 값과 현재 val 값이 같은지 아닌지에 따라 다르게 루프를 짜면된다.
같으면 삭제를 하는 절차를 밟으면 되고 아니면 이전값을 수정하고 그냥 넘어가면 된다.
*/

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
	ListNode* deleteDuplicates(ListNode* head) {
		ListNode* p = head, * prev = p;
		int back = -101;
		while (p != NULL)
		{
			if (back == p->val)
				prev->next = p->next;
			else {
				prev = p;
				back = p->val;
			}
			p = p->next;
		}
		return head;
	}
};