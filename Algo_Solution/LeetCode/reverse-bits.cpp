#include <bits/stdc++.h>
using namespace std;

/*
https://leetcode.com/problems/reverse-bits/submissions/
비트 뒤집기...
bitset을 이용했다.
*/

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        bitset<32> b = n;
        string k;
        for (int i = 0; i < 32; i++)
            k += (b[i] + '0');
        return bitset<32>(k).to_ulong();
    }
};