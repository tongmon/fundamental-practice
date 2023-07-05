#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2457
생각은 했는데 구현에서 굉장히 헷갈려서 힘든 여정이였다....
계속 머리에서 이러면 되네, 어 이러면 안되잖아 이러한 생각이
반복되었다.. 결국 노트에 범위를 적어가며 생각해보면서
구현했다.
어떻게 푸냐면 월, 일로 입력이 주어지기에 월, 일을 실제 날짜로 바꾼다.
3 1 ~ 11 30 까지 꽃이 피는 최소 개수기에 그 이외의 범위는 잘라버린다.
예를들어 2 8 ~ 11 2 가 들어오면 3 1 ~ 11 2 로 잘라버린다는 것이다.
이렇게 잘라진 범위들을 시작 날짜 기준으로 정렬하고 그리디적인 기법으로 푸는 것이다.
정렬이 된다면 날짜 그래프는 밑과 같다.

|--------|
|----------|
|--------------|
   |--------|
   |-----------|
      |--------------|
	               |--------------|
이런 방식으로 정렬이 되게 되고
이게 11 30 일까지 연결만 쭉 되면 되는 것이다.
처음과 끝 사이를 검사하고 제일 큰 끝 값을 찾은 다음에 
그 큰 끝 값을 가진 녀석의 처음과 끝 사이를 또 검사하고..
이를 반복해가면서 11 30까지 연결되는지 확인하면 된다.
처음과 끝이 바뀌는 것이 확정될 때마다 개수를 더하면 되는 것이고
처음과 끝의 범위가 같다면 더이상 진행이 불가하니 검사를 종료한다.
이 때 검사 종료시에 끝범위가 11 30이라면 최소 꽃 개수가 도출되고
아니면 0을 출력하면 된다.
이를 구현하는데 머리가 자꾸 꼬여서 고생했다.. 구현 능력을 더 길러야겠다.
다른 사람의 풀이를 보니 날짜를 선형적인 수로 변경할 때 나는 실제 날짜를
계산했지만 다른 사람은 월에 100을 곱하고 일과 더했다.
이게 가능한 이유는 달마다 일 수가 달라도 크고 작고만 판단하면 되기에
날짜마다 차이가 얼마가 나던 상관이 없다.
달에 100을 곱하는 것이 내 풀이보다 깔끔해지더라. 이를 알아가자
이 문제를 통해 그리디 문제에 익숙해져간다.
*/

int N, sm, sd, em, ed, Day[13], Ans = 1, Max, St;
vector<pair<int, int>> Fl;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (auto& a : Day) a = 31;
	Day[4] = Day[6] = Day[9] = Day[11] = 30; Day[2] = 28; Day[0] = 0;
	int Sum = 0, buf;
	for (int i = 1; i < 13; i++) {
		buf = Day[i];
		Day[i] = Sum;
		Sum += buf;
	}
	int Sday = Day[3] + 1, Eday = Day[11] + 30;
	for (int i = 0; i < N; i++) {
		cin >> sm >> sd >> em >> ed;
		int f = Day[sm] + sd, e = Day[em] + ed - 1;
		if (f > Eday || e < Sday)
			continue;
		if (f < Sday)
			f = Sday;
		if (e > Eday)
			e = Eday;
		if (f == Sday && Max < e)
			Max = e;
		Fl.push_back({ f,e });
	}
	sort(Fl.begin(), Fl.end());
	if (!Max) {
		cout << 0;
		return 0;
	}
	while (Max != Eday) {
		int i, buf = 0, Ind = 0;
		for (i = St; i < N && Fl[i].first <= Max + 1; i++) {
			if (buf < Fl[i].second) {
				buf = Fl[i].second;
				Ind = i;
			}
		}
		if (Ind == St)
			break;
		Max = buf;
		St = Ind;
		Ans++;
	}
	if (Max == Eday)
		cout << Ans;
	else
		cout << 0;
}