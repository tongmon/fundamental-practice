#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
KMP 알고리즘
단순하게 틀리면 한 칸 앞으로가서 다시 문자열을 탐색하는 방식은 O(M*N) 복잡도가 걸린다.
하지만 모두 돌아가지않고 적절하게 중간에서 멈춰 탐색을 재개하는 KMP 알고리즘을 사용한다면
O(M+N)으로 시간이 확 줄어든다!
이 알고리즘의 핵심은 lps 배열을 만드는 것에 있다.
접두사, 접미사를 분석해 lps 배열을 만들고 그 배열을 이용해 끝까지 다시 돌아가지 않고 중간에
멈춰 탐색을 재개할 수 있다.
이 알고리즘과 별개로 함수에 포인터형을 넘기고 그 자료에 대한 임의 탐색을 진행할 경우
.at() 함수를 사용하지 않으면 오류가 난다. 
설령 오류가 안났다 하더라도 그 자료에 대한 탐색이 이루어지지 않는다는 것을 명심해라.
*/

void LPS_Maker(string * Pattern, vector<int> *lps) // lps 배열을 생성하면서도 여태 만들어진 lps 값들을 이용한다.
{
	lps->reserve(Pattern->length());
	int j = 0; lps->push_back(0);
	for (int i = 1; i < Pattern->length(); i++)
	{
		while (j > 0 && Pattern->at(i) != Pattern->at(j)) // 접두사와 접미사가 같지 않다면 어디까지 물러서야하는지 lps배열을 참조해 알아낸다.
		{
			j = lps->at(j - 1);
		}
		if (Pattern->at(i) == Pattern->at(j)) // 접두사와 접미사가 같다면 얼마나 같은 문자들이 있는지가 수가 담긴 j를 lps 배열에 넣어준다.
		{
			lps->push_back(++j);
		}
		else lps->push_back(0); // 끝까지 다르다면 lps 배열에 0을 넣어준다.
	}
}

// 간단하게 얘 써라, 반환형은 배열인데 어느 부분부터 매칭되는지 들어간다.
// Target에서 특정 Pattern이 어디에 위치하는지 빠르게 알 수 있다.
vector<size_t> KMP(const string& Target, const string& Pattern)
{
	vector<size_t> lps, Result;
	lps.reserve(Pattern.length());
	lps.push_back(0);
	for (int i = 1, k = 0; i < Pattern.length(); i++) {
		while (k > 0 && Pattern[i] != Pattern[k])
			k = lps[k - 1];
		lps.push_back((Pattern[i] == Pattern[k] ? ++k : 0));
	}
	for (int i = 0, j = 0; i < Target.length(); i++) {
		while (j > 0 && Target[i] != Pattern[j])
			j = lps[j - 1];
		if (Target[i] == Pattern[j]) {
			if (j == Pattern.length() - 1) {
				Result.push_back(i - Pattern.length() + 2);
				j = lps[j];
			}
			else j++;
		}
	}
	return Result;
}

int main(void)
{
	string Pattern, Info; 
	cout << "문자열을 입력하세요: "; cin >> Info;
	cout << "찾을 패턴을 입력하세요: "; cin >> Pattern;
	int Pat_Size = Pattern.length(); // 패턴의 크기 입력
	vector<int> lps; // 비효울적으로 처음부터 다시 돌아가서 탐색하지 않게 어디까지 돌아가야 하는지에 대한 정보가 저장되는 배열
	LPS_Maker(&Pattern, &lps); // lps 배열을 생성
	for (int i = 0; i < Pat_Size; i++) // 결정된 lps 배열값 출력
	{
		cout << Pattern[i] << " ---> " << lps[i] << '\n';
	}
	for (int i = 0, j = 0; i < Info.length(); i++)
	{
		while (j > 0 && Info[i] != Pattern[j]) // lps 배열 생성시와 비슷하게 어디까지 돌아가서 탐색해야 하는지 lps 값을 참조하여 알아낸다.
		{
			j = lps[j - 1];
		}
		if (Info[i] == Pattern[j]) // 문자가 패턴과 같다면
		{
			if (j == Pat_Size - 1)  // 패턴과 모두 같아졌다면 매칭이 된 것이다.
			{
				cout << i - Pat_Size + 2 << "번째부터 매칭되었습니다!\n";
				j = lps[j]; // 같아졌을 경우 어디까지 물러서는지는 lps[j]에 담기게 된다.
			}
			else j++; // 문자가 패턴과 같지만 아직 매칭된 것이 아니므로 j를 증가시킨다. i는 저절로 증가된다.
		}
	}
	cout << '\n';
	vector<size_t> A = KMP("stringstringsfdrinringstr", "str");
	for (auto a : A) {
		cout << a << ' ';
	}
}