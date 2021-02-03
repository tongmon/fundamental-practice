#include <bits/stdc++.h>
using namespace std;

/*
https://leetcode.com/problems/maximum-subarray/submissions/
최대 연속합 문제다.
두 가지로 풀 수 있는데 나는 그리디적인 방식으로 풀었다.
일단 '연속'합이기에 투 포인터 같은 방식을 떠올렸는데 음수가 끼워져 있었고
좀 더 생각해보니 현재 더해온 값이 A라 하고 다음에 더할 값이 B라 하면
A + B가 B보다 더 크면 그대로 A + B로 합친 결과를 이어가면 되는 것이고
만약 그냥 B가 더 크면 예전까지 더해왔던 값을 버리고 B부터 새로 출발하면 되는 것이다.
이렇게 계속 진행하면서 가장 큰 합을 구하면 된다.
Dp로도 풀 수 있는데 사실 그리디적인 방식과 별 차이가 없다.
점화식이 dp[i] = max(dp[i-1]+nums[i], nums[i]) 이렇게 짜여진다.
그리디 방식이 Dp방식을 용량 O(1) 으로 줄인 것이라고 봐도 된다.
이 문제를 통해 그리디 문제 실력을 늘려간다.
*/

class Solution {
public:
	int maxSubArray(vector<int>& nums) {
		long long Ans = nums[0], Max = nums[0];
		for (int i = 1; i < nums.size(); i++)
		{
			Ans = nums[i] > Ans + nums[i] ? nums[i] : Ans + nums[i];
			Max = max(Max, Ans);
		}
		return Max;
	}
};