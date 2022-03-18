#include <bits/stdc++.h>
using namespace std;

/*
https://leetcode.com/problems/search-insert-position/
배열 탐색 문제.
*/

class Solution {
public:
	int searchInsert(vector<int>& nums, int target) {
		nums.push_back(2e5);

		/*
		// 이진탐색을 이용하는 방법... stl을 사용해서 그런지 적은 데이터 양에서는 13ms로 효율이 좋진 않음 (물론 데이터가 많아질수록 효율짱이겠지만)
		return lower_bound(nums.begin(), nums.end(), target) - nums.begin();
		*/

		// 그냥 순환하며 완전 탐색... 얘는 10ms인데 아마 메모리가 연속적으로 이루어져 있는 적은 데이터 배열을 빠르게 훍어서 이진탐색보다 빠르게 나온듯?
		for (int i = 0; i < nums.size(); i++)
			if (target <= nums[i]) {
				target = i;
				break;
			}
		return target;
	}
};