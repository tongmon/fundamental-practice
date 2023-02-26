#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12911
다음 큰 숫자 문제.
이진수로 변환해서 1의 자릿수만 같고 바로 다음 큰 숫자를 만들어주면 된다.
만약에 1101 이런 수면 1110 이게 다음 큰 수가 되는 식이다.
이게 잘보면 이진수로 바꾼 숫자를 제일 큰 자릿수부터 내려가면서 읽게 되면
최초로 나온 01을 10로 바꾸면 된다.
그리고 나머지 1들은 제일 작게 옆으로 붙여주면 된다.
그니까 다른 예시를 들어보면 1001110 여기에서 다음 큰 수는 1010011 얘가 된다.
처음 나온 01을 10으로 바꾸고 나머지 1들을 최대한 오른쪽으로 붙인 결과가 1010011이다.
이대로 구현하면 밑과 같은 코드가 나온다.
시간 복잡도는 int형에서 진행하기에 제일 길어봤자 O(32 + 알파)이다.
다른 사람 풀이를 보니 주어진 수에서 1씩 더하면서 그 수를 이진변환하여 1의 수가 같은지를
매번 체크하던데 그 풀이는 수가 커질수록 비효율적이다.
이 문제를 통해 구현 능력을 길러간다.
*/

int solution(int n) {
	int answer = 0, mult = 1;
	deque<int> Bin, newBin;
	while (n > 0) {
		Bin.push_back(n % 2);
		n /= 2;
	}
	int back = Bin[0], i = 1, bCnt = back ? 1 : 0;
	for (; i < Bin.size(); i++) {
		if (back == 1 && !Bin[i])
			break;
		if (Bin[i])
			bCnt++;
		back = Bin[i];
	}
	if (i == Bin.size())
		Bin.push_back(1);
	else
		Bin[i] = 1;
	Bin[i - 1] = 0;
	for (int p = 0; p < i; p++) {
		if (bCnt > 1) {
			newBin.push_back(1);
			bCnt--;
		}
		else
			newBin.push_back(0);
	}
	for (int p = i; p < Bin.size(); p++)
		newBin.push_back(Bin[p]);
	for (auto B : newBin) {
		answer += mult * B;
		mult *= 2;
	}
	return answer;
}