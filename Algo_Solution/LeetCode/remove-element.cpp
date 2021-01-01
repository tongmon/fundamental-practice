/*
https://leetcode.com/problems/remove-element/
배열 삭제 관련해서 최적화 시켜야하는 문제이다.
문제에서 필요없는 원소들은 임의의 수로 바꿔치기해도 상관없다라고
힌트를 때려버려서... 그냥 그대로 삭제할 원소 바꾸고 정렬했다.
*/

class Solution {
public:
	int removeElement(vector<int>& nums, int val) {
		int Ans = nums.size();
		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] == val) {
				Ans--;
				nums[i] = 110;
			}
		}
		sort(nums.begin(), nums.end());
		return Ans;
	}
};