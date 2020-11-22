#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
using namespace std;

string Send_Data, Code, Real_Data, Input, Paser;
deque<char> Comp;

void Analyzer()
{
    int Gap = 0, k;
    for (int i = 0; i < Input.size(); i++)
    {
        if (Input[i] == '+')
        {
            Paser.erase(Paser.begin());
            k = Gap - stoi(Paser);
            while (k > 1)
            {
                Code.push_back('0'); k--;
            }
            Code.push_back('1'); Gap = stoi(Paser); Paser.clear();
        }
        else Paser.push_back(Input[i]);
    }
    if (Paser[0] == '1')
    {
        while (Gap > 1)
        {
            Code.push_back('0'); Gap--;
        }
        Code.push_back('1'); return;
    }
    Paser.erase(Paser.begin());
    k = Gap - stoi(Paser);
    while (k > 1)
    {
        Code.push_back('0'); k--;
    }
    Code.push_back('1'); k = stoi(Paser);
    while (k > 0)
    {
        Code.push_back('0'); k--;
    }
}

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << "생성 다항식을 입력하세요: "; cin >> Input;
    cout << "전송 데이터를 입력하세요: "; cin >> Send_Data;
    Analyzer();
    int Slide = Code.size(); Real_Data = Send_Data;
    for (int i = 0; i < Slide - 1; i++)
    {
        Send_Data.push_back('0');
    }
    for (int i = 0; i < Slide; i++)
    {
        Comp.push_back(((Code[i] - '0') ^ (Send_Data[i] - '0')) + '0');
    }
    Comp.pop_front(); Comp.push_back(Send_Data[Slide]);
    for (int i = 1;; i++)
    {
        int Front = Comp.front();
        for (int j = 0; j < Slide; j++)
        {
            if (Code[0] == Front)
            {
                Comp.push_back(((Code[j] - '0') ^ (Comp.front() - '0')) + '0');
            }
            else
            {
                Comp.push_back((0 ^ (Comp.front() - '0')) + '0');
            }
            Comp.pop_front();
        }
        Comp.pop_front(); 
        if (Slide + i == Send_Data.size()) break;
        Comp.push_back(Send_Data[Slide + i]);
    }
    cout << "Check Sum: ";
    for (int i = 0; i < Comp.size(); i++)
    {
        cout << Comp[i]; Real_Data.push_back(Comp[i]);
    }
    cout << "\n송신 데이터: " << Real_Data;
}