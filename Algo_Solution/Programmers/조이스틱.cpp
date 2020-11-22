#include <bits/stdc++.h>
using namespace std;

int solution(string name) {
	int answer = 0, i = 0;
	int Len = name.size();
	string K(Len, 'A');
	while (true) {
		K[i] = name[i];
		name[i] - 'A' > 'Z' + 1 - name[i] ? answer += 'Z' + 1 - name[i] : answer += name[i] - 'A';
		if (K == name) break;
		for (int j = 1; j < name.size(); j++) {
			if (name[(i + j) % name.size()] != K[(i + j) % name.size()]) {
				i = (i + j) % name.size();
				answer += j; break;
			}
			else if (name[(i + name.size() - j) % name.size()] != K[(i + name.size() - j) % name.size()]) {
				i = (i + name.size() - j) % name.size();
				answer += j; break;
			}
		}
	}
	return answer;
}