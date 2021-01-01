/*
https://leetcode.com/problems/two-sum/
해쉬맵을 이용하는 문제.
이중포문으로 전체 탐색을 할 수도 있지만 느리다.
해쉬맵으로 타켓 숫자 - 현재 숫자 = 더해야 할 숫자, 이런 원리를 이용하면
해쉬 테이블을 뒤져보아서 더해야 할 숫자가 존재하면 그 인덱스들을 반환하면 된다.
*/

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> Numb;
        for (auto n : nums) {
            if (Numb.find(n) == Numb.end())
                Numb[n] = 1;
            else
                Numb[n]++;
        }
        for (int i = 0; i < nums.size(); i++)
        {
            int buf = target - nums[i];
            if ((buf == nums[i] && Numb[buf] > 1)
                || Numb.find(buf) != Numb.end()) {
                for (int j = i + 1; j < nums.size(); j++) {
                    if (buf == nums[j])
                        return { i,j };
                }
            }
        }
        return { 0 };
    }
};