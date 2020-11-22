#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

/*
Map을 이용한 집합 연산.... 최대 연산 시간은 nlog(n)이다.
맵을 쓰지 않는다면 유니온 파인드로 n*n의 시간 복잡도가 필요하다.
사실 밑과 같은 뻘짓을 하지 않고 STL에서 표준으로 함수를 제공한다.
표준 제공 함수들 사용법은 밑에 주석처리 해놓았다.
*/

#pragma warning(disable:4996)

#define SIZE 10000

class Set_Calculation
{
    vector<int> Set;
    unordered_map<int, int> Parent;
public:
    Set_Calculation() {}
    void Print_Union(vector<int>* Set_1, vector<int>* Set_2)
    {
        for (int i = 0; i < Set_1->size(); i++)
        {
            Parent[Set_1->at(i)] = Set_1->at(i);
        }
        for (int i = 0; i < Set_2->size(); i++)
        {
            Parent[Set_2->at(i)] = Set_2->at(i);
        }
        for (auto iter = Parent.begin(); iter != Parent.end(); iter++)
        {
            Set.push_back((*iter).second);
        }
        Print_Set();
    }
    void Print_Inter(vector<int>* Set_1, vector<int>* Set_2)
    {
        for (int i = 0; i < Set_1->size(); i++)
        {
            Parent[Set_1->at(i)] = Set_1->at(i);
        }
        for (int i = 0; i < Set_2->size(); i++)
        {
            if (Parent.find(Set_2->at(i)) != Parent.end())
            {
                Set.push_back(Set_2->at(i));
            }
        }
        Print_Set();
    }
    void Print_Minus(vector<int>* Set_1, vector<int>* Set_2)
    {
        for (int i = 0; i < Set_1->size(); i++)
        {
            Parent[Set_1->at(i)] = Set_1->at(i);
        }
        for (int i = 0; i < Set_2->size(); i++)
        {
            if (Parent.find(Set_2->at(i)) != Parent.end())
            {
                Parent.erase(Set_2->at(i));
            }
        }
        for (auto iter = Parent.begin(); iter != Parent.end(); iter++)
        {
            Set.push_back((*iter).second);
        }
        Print_Set();
    }
    void Print_Set()
    {
        sort(Set.begin(), Set.end());
        for (auto iter = Set.begin(); iter != Set.end(); iter++)
        {
            cout << *iter << " ";
        }
        cout << '\n'; Set.clear(); Parent.clear();
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    vector<int> Set_1 = { 1, 4, 5, 8, 11, 20110 };
    vector<int> Set_2 = { 1, 5, 7, 10, 452 };
    vector<int> buffer(Set_1.size(), Set_2.size());
    Set_Calculation Calculate_Set;
    cout << "합집합: ";
    Calculate_Set.Print_Union(&Set_1, &Set_2);
    // set_union(Set_1.begin(), Set_1.end(), Set_2.begin(), Set_2.end(), buffer.begin());
    cout << "교집합: ";
    Calculate_Set.Print_Inter(&Set_1, &Set_2);
    // set_intersection(Set_1.begin(), Set_1.end(), Set_2.begin(), Set_2.end(), buffer.begin())
    cout << "차집합(Set_1 - Set_2): ";
    Calculate_Set.Print_Minus(&Set_1, &Set_2);
    // set_difference(Set_1.begin(), Set_1.end(), Set_2.begin(), Set_2.end(), buffer.begin());
}