#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/3568
문자열 구현 문제다.
주어진 요구대로 구현하면 된다.
*/

string A, buf, ext, N;
int l;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	getline(cin, A);
	for (int i = 0; i < A.size(); i++) {
		if (A[i] == ' ') {
			l = i + 1;
			break;
		}
		else
			ext += A[i];
	}
	for (int i = l; i < A.size(); i++) {
		if (A[i] == ';' || A[i] == ',') {
			cout << ext + buf + ' ' + N + ";\n";
			buf.clear();
			N.clear();
		}
		else if (A[i] == '[') {
			buf.insert(buf.begin(), ']');
			buf.insert(buf.begin(), '[');
			i++;
		}
		else if (('a' <= A[i] && A[i] <= 'z') 
			|| ('A' <= A[i] && A[i] <= 'Z'))
			N += A[i];
		else if(A[i] != ' ')
			buf.insert(buf.begin(), A[i]);
	}
}