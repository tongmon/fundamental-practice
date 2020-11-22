#include <bits/stdc++.h>
using namespace std;

bool cmp(string a, string b) {
	return a + b > b + a;
}

string solution(vector<int> numbers)
{
	string answer = "";
	vector<string> K;
	for (auto num : numbers) {
		K.push_back(to_string(num));
	}
	sort(K.begin(), K.end(), cmp);
	if (K.front() == "0") return "0";
	for (auto num : K) {
		answer += num;
	}
	return answer;
}