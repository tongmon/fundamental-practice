#include <bits/stdc++.h>
using namespace std;

/*
https://leetcode.com/problems/linked-list-cycle/submissions/
연결 리스트 사이클 문제.
자료구조 책 읽으면서 습득한 사전지식이 있어서 때려박았다.
연결 리스트에서 순환을 확인하는 방법은 포인터 두개를 사용하여
하나는 한 칸씩 이동하고, 나머지 하나는 두 칸씩 이동하는 방식으로 처리하다보면
순환이 존재하는 연결리스트에서는 이 두 포인터가 겹치는 순간이 생긴다.
이를 처리 해주면 된다.
순환이 없다면 두 포인터 중 하나가 Null을 가리키므로 이 조건으로 순환 검사를 빠져나올 수 있다.
이 문제를 연결리스트 지식을 늘려간다.
*/

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL) {}	
};

class Solution {
public:
	bool hasCycle(ListNode* head) {
		if (head == NULL || head->next == NULL || head->next->next == NULL)
			return false;
		ListNode* One = head->next, * Two = head->next->next;
		while (One != NULL && Two != NULL && Two->next != NULL) {
			if (One == Two)
				return true;
			One = One->next;
			Two = Two->next->next;
		}
		return false;
	}
};