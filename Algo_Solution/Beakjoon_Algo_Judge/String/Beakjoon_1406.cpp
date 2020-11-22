#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1406
간단하게 풀어버릴수 있는 문제 인줄 알았으나... 시간초과가 문제였다.
이 문제를 풀면서 느낀점이 많은데 일단 char형 한 글자를 입력받을 경우 scanf("%c", &Order); 이렇게 받으면 건너 뛰는 경우가 있다.
따라서 한 칸 띄고 scanf(" %c", &Order); 이렇게 받아야 받아진다.
그리고 배열형 STL에서 삭제와 삽입시에 걸리는 오버헤드가 생각보다 크다는 것이였다.
String 형을 기준으로 작성한 편집기는 제한시간 0.3초를 벗어나는 반면 List 형을 기준으로 작성한 편집기는 빠르게 편집이 가능하였다.
list는 인덱스 기반으로 코드를 작성할 수가 없어서 iterator(반복자)를 알아야 했는데 이 부분이 내가 많이 부족했다는 것을 깨달았다.
iterator 사용시에 자주 사용되는 insert, erase의 기능을 잘 알아야 한다.
insert는 현 반복자에 삽입을 하고 삽입을 한 그 위치의 반복자를 반환한다. 따라서 원래 위치로 되돌리려면 
iter = Editor.insert(iter, Ins); iter++; 뒤에 ++을 해주어야 한다.
erase는 현 반복자에 있는 원소를 삭제하고 그 다음 위치의 반복자를 반환한다. 
예로 1 2 3 이 있는 리스트가 있고 iter가 3을 가리키고 있으면 erase(iter)할 시에 iter는 end()를 가리키게 된다.
이 문제를 통해 삽입 삭제가 빈번히 일어날 경우에는 리스트를 사용하는 것이 훨 효율적이라는 것을 이해하고 간다.
*/

#pragma warning(disable:4996)

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    string buffer;
    cin >> buffer;
    int Ordernum;
    cin >> Ordernum;
    char Order, Ins;
    // list<char> Editor(buffer.begin(), buffer.end()); // 문자열을 리스트로  
    list<char> Editor;
    for (int i = 0; i < buffer.size(); i++)
    {
        Editor.push_back(buffer[i]);
    }
    auto iter = Editor.end();
    for (int i = 0; i < Ordernum; i++)
    {
        cin >> Order; 
        if (Order == 'P')
        {
            cin >> Ins;
            if (iter == Editor.end())
            {
                Editor.push_back(Ins);  iter = Editor.end();
            }
            else
            {
                iter = Editor.insert(iter, Ins); iter++;
            }
        }
        else if (Order == 'L')
        {
            if (iter != Editor.begin())
            {
                iter--;
            }
        }
        else if (Order == 'D')
        {
            if (iter != Editor.end())
            {
                iter++;
            }
        }
        else
        {
            if (iter != Editor.begin())
            {
                --iter; iter = Editor.erase(iter);
            }
        }
    }
    for (auto p = Editor.begin();p != Editor.end();p++)
    {
        cout << *p;
    }
}

/*
// 시간초과가 난다. 배열형 삭제, 삽입 오버헤드가 그대로 단점으로 나타나는 예
int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int Ordernum;
    string buffer;
    char Order, Ins;
    cin >> buffer;
    cin >> Ordernum;
    int index = buffer.size(), Length = index;
    for (int i = 0; i < Ordernum; i++)
    {
        cin >> Order;
        if (Order == 'P')
        {
            cin >> Ins;
            if (Length == index)
            {
                buffer.push_back(Ins);
            }
            else
            {
                buffer.insert(buffer.begin() + index, Ins);
            }
            index++; Length++;
        }
        else if (Order == 'L')
        {
            if (index != 0)
            {
                index--;
            }
        }
        else if (Order == 'D')
        {
            if (index != Length)
            {
                index++;
            }
        }
        else
        {
            if (index == Length)
            {
                buffer.pop_back(); index--; Length--;
            }
            else if (index != 0)
            {
                buffer.erase(buffer.begin() + index - 1); index--; Length--;
            }
        }
    }
    cout << buffer;
}
*/