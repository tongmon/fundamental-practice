# Flyweight Pattern  

대단히 많은 수의 매우 비슷한 객체들이 사용되어야 하는 경우 유용한 패턴이다.  
간단히 말해 메모리를 절약해주는 캐싱을 적용하는 데 중점을 둔 패턴이다.  
&nbsp;  

예를 들어 온라인 게임에서 유저들의 닉네임을 관리한다고 해보자.  
해당 온라인 게임에서 ID는 고유해도 닉네임은 중복이 될 수 있다고 가정한다.  
그러한 경우 밑과 같은 클래스를 도출할 수 있다.  
```c++
class UserManager
{
public:
    struct User
    {
        int id;
        std::string nickname;
    };

    void add_user(const std::string &nickname)
    {
        user_list.push_back(User{++id, nickname});
    }

private:
    inline static std::vector<User> user_list = {};
    inline static int id = 0;
};
```
유저는 고유한 ID와 중복 가능한 Nickname으로 구성된다.  
위 UserManager의 문제는 닉네임이 겹치는 유저들이 생성될 때마다 메모리 낭비가 발생한다는 것이다.   
&nbsp;  

이 때 플라이웨이트 패턴을 적용해 해결해보자.  
일단 nickname 속성이 중복되면서 문제가 발생하기에 nickname을 따로 저장해두는 곳을 만든다.  

```c++
class UserManager
{
    // 구현부 생략

private:
    inline static std::vector<std::string> nickname_list = {};
    // 나머지 멤버 생략
};
```
이제 같은 닉네임의 유저가 생성될 때 nickname_list에서 이미 존재하는 닉네임인지 여부를 확인하면 된다.  
확인하는 방식은 인덱스와 포인터 방식이 있다.  
먼저 인덱스 방식을 사용해보자.  
&nbsp;  

nickname_list에서 같은 닉네임을 찾았다면 해당 닉네임을 재활용하기 위해 인덱스를 알고 있어야 한다.  
따라서 User 구조체의 구조는 밑과 같이 바뀐다.  
```c++
struct User
{
    int id;
    unsigned int nickname_index;
    const std::string &nickname() const { return nickname_list[nickname_index]; }
};
```
이제 User의 nickname은 nickname_key를 통해 접근하게 된다.  
&nbsp;  

add_user() 함수의 로직도 바뀌어야 한다.  
```c++
void add_user(const std::string &nickname)
{
    auto iter = std::find(nickname_list.begin(), nickname_list.end(), nickname);
    if (iter == nickname_list.end())
        iter = nickname_list.insert(iter, nickname);
    user_list.push_back(User{++id, static_cast<unsigned int>(iter - nickname_list.begin())});
}
```
만약 nickname_list에 이미 존재하는 닉네임이라면 해당 닉네임의 인덱스를 User가 가지고 있으면 된다.    
새로운 nickname이 등장할 때마다 nickname_list에 추가해줘야 한다.  
인덱스의 자료형을 short, char 등으로 바꿔 메모리를 더 아낄 수 있다.  
문제는 이미 추가된 nickname인지 확인하는데 O(N)의 복잡도가 도출된다는 것이다.  
&nbsp;  

다음으로 해쉬맵 방식을 사용해보자.  
일단 추가적으로 해쉬맵 자료형이 존재해야 한다.  
```c++
class UserManager
{
    // 구현부 생략

private:
    inline static std::unordered_set<std::string> nickname_list = {};
    // 나머지 멤버 생략
};
```
&nbsp;  

해쉬맵에서는 인덱스 대신에 포인터를 사용해서 nickname을 가리킨다.  
```c++
struct User
{
    int id;
    const std::string *nickname_ptr;
    const std::string &nickname() const { return *nickname_ptr; }
};
```
stl의 unordered 구조들은 삽입, 삭제되면서 재해싱이 발생될 때 Iterator들의 순서는 바뀌어 재사용이 불가능하다. (궁금하다면 Iterator Invalidation Rules를 참고하자.)   
하지만 unordered 구조에 담겨져 있는 객체들의 할당 위치는 고정이기에 해당 객체들을 가리키는 참조나 포인터는 그 객체가 삭제되지 않는 이상 항상 유효하다.  
각 자료구조 Iterator에 대해 더 많은 내용이 궁금하다면 C++의 Iterator Invalidation Rules를 참고해보자.  
&nbsp;  

add_user() 함수의 로직도 이에 맞춰 바꿔보자.  
```c++
void add_user(const std::string &nickname)
{
    user_list.push_back(User{++id, &*nickname_list.insert(nickname).first});
}
```
해쉬맵을 사용하기에 이미 추가된 nickname인지 확인하는 데 O(1)의 복잡도가 도출된다.  
문제는 포인터의 크기가 64-bit 운영체제에서 8byte, 32-bit 운영체제에서 4byte로 작은 크기는 아니다.  
처리 속도에서 손해를 보더라도 메모리를 극적으로 줄이고 싶다면 인덱스 방식이 더 좋다.  
&nbsp;  

## Boost의 Flyweight  

Boost 라이브러리는 자체적으로 Flyweight 패턴을 지원한다.  
사용법은 밑과 같다.  
```c++
class UserManager
{
public:
    struct User
    {
        int id;
        boost::flyweight<std::string> nickname;
        User(int id, const std::string &nickname) : id{id}, nickname{nickname} {}
    };

    void add_user(const std::string &nickname)
    {
        user_list.push_back(User{++id, nickname});
    }

private:
    inline static std::vector<User> user_list = {};
    inline static int id = 0;
};
```
flyweight 자료형에 값을 할당할 때 이미 존재하는 값인지 확인하기에 따로 전역 객체를 선언할 필요가 없다.  
&nbsp;  

## 문자열 범위  

Flyweight 패턴의 대표적인 예시인 문자열 범위를 다루는 상황을 생각해보자.  
특정 범위를 지정해주면 그 범위 만큼 문자들을 대문자로 변환하는 문자열 클래스가 있다고 하자.  
```c++
class Text
{
    std::string str;
    bool *upper;

public:
    explicit Text(const std::string str) : str{str}
    {
        upper = new bool[str.length()];
        std::memset(upper, false, str.length());
    }
    ~Text() { delete[] upper; }

    void capitalize(int start, int end, bool reset = false)
    {
        if (reset)
            std::memset(upper, false, str.length());

        for (int i = start; i <= end; i++)
            upper[i] = true;
    }

    std::string text()
    {
        std::string result;
        for (int i = 0; i < str.length(); i++)
            result += upper[i] ? std::toupper(str[i]) : str[i];
        return result;
    }
};
```
위 예시는 제일 단순하게 생각한 방식이다.  
문자열 크기 만큼 대문자 여부를 나타내는 bool형 배열을 만들어 이를 활용한다.  
문자열이 길어질수록 메모리 낭비가 심해진다.  
&nbsp;  

메모리 소비율을 개선하기 위해 범위를 사용해보자.  
범위라는 것은 시작점과 끝점을 알고 있으면 정의된다.  
범위 구조체는 밑과 같을 것이다.  
```c++
struct TextRange
{
    int start, end;
};
```
&nbsp;  

여러 범위가 주어질 수 있으니 TextRange 배열이 필요할 것이다.  
```c++
class Text
{
    // 구현부 생략

    std::vector<TextRange> ranges;
};
```
&nbsp;  

메모리를 좀 더 절약하기 위해 capitalize() 함수를 수정해보자.  
```c++
void capitalize(int start, int end, bool reset = false)
{
    if (reset)
        ranges.clear();
    for (int i = 0; i < ranges.size(); i++)
    {
        if (ranges[i].start <= start && end <= ranges[i].end)
            return;
        if (start < ranges[i].start && ranges[i].end < end)
            ranges.erase(ranges.begin() + i--);
    }
    ranges.push_back({start, end});
}
```
같은 범위, 기존 범위로 대체 가능한 작은 범위가 들어오면 무시하고 기존의 범위들을 포함하는 새로운 범위가 들어오면 기존 범위들을 삭제한다.  
&nbsp;  

하지만 ```3 ~ 6``` / ```7 ~ 11``` 이렇게 범위가 있으면 이를 ```3 ~ 11```로 바꿔주는 것이 저장시 효율적이지 않을까?  
capitalize() 함수를 수정해보자.  
```c++
void capitalize(int start, int end, bool reset = false)
{
    if (reset)
        ranges.clear();
    for (int i = 0; i < ranges.size(); i++)
    {
        if (ranges[i].start <= start && end <= ranges[i].end)
            return;
        if (start < ranges[i].start && ranges[i].end < end)
            ranges.erase(ranges.begin() + i--);
        else
        {
            if (ranges[i].start <= start && start <= ranges[i].end + 1)
            {
                ranges[i].end = end;
                return;
            }
            if (ranges[i].start - 1 <= end && end <= ranges[i].end)
            {
                ranges[i].start = start;
                return;
            }
        }
    }
    ranges.push_back({start, end});
}
```
하지만 아직 개선점이 남았다.   
```3 ~ 5``` / ```7 ~ 11``` / ```4 ~ 7``` 이렇게 범위가 삽입된다면 ```3 ~ 7``` / ```7 ~ 11``` 이렇게 범위가 재조정 될 것이다.  
```3 ~ 7``` / ```7 ~ 11``` 이 범위들은 ```3 ~ 11```로 합칠 수 있지만 재조정이 안되고 이렇게 남아있어 메모리 낭비가 발생한다.  
&nbsp;  

재귀를 이용해 재조정이 가능한 범위들을 남김없이 합쳐주자.  
```c++
void capitalize(int start, int end, bool reset = false)
{
    if (reset)
        ranges.clear();
    for (int i = 0; i < ranges.size(); i++)
    {
        if (ranges[i].start <= start && end <= ranges[i].end)
            return;
        if (start < ranges[i].start && ranges[i].end < end)
            ranges.erase(ranges.begin() + i--);
        else
        {
            TextRange range{-1, -1};
            if (ranges[i].start <= start && start <= ranges[i].end + 1)
                range = {ranges[i].start, end};
            else if (ranges[i].start - 1 <= end && end <= ranges[i].end)
                range = {start, ranges[i].end};
            if (range.start >= 0)
            {
                ranges.erase(ranges.begin() + i);
                capitalize(range.start, range.end);
                return;
            }
        }
    }
    ranges.push_back({start, end});
}
```
여기서 좀 더 나아가 ranges의 자료형을 std::vector<>에서 std::unordered_set<>으로 바꾼다면 속도면에서도 최적화를 꾀할 수 있다.   
이렇게 플라이웨이트 패턴은 메모리 최적화에 중점이 맞춰져 있기에 상황에 따라 알고리즘적인 사고방식이 꽤나 요구된다.  
&nbsp;  

메모리 낭비를 줄이는 Text 클래스의 전체적인 모습은 밑과 같다.  
```c++
class Text
{
    struct TextRange
    {
        int start, end;
    };

    std::string str;
    std::vector<TextRange> ranges;

public:
    explicit Text(const std::string str) : str{str}
    {
    }
    ~Text() {}

    void capitalize(int start, int end, bool reset = false)
    {
        if (reset)
            ranges.clear();
        for (int i = 0; i < ranges.size(); i++)
        {
            if (ranges[i].start <= start && end <= ranges[i].end)
                return;
            if (start < ranges[i].start && ranges[i].end < end)
                ranges.erase(ranges.begin() + i--);
            else
            {
                TextRange range{-1, -1};
                if (ranges[i].start <= start && start <= ranges[i].end + 1)
                    range = {ranges[i].start, end};
                else if (ranges[i].start - 1 <= end && end <= ranges[i].end)
                    range = {start, ranges[i].end};
                if (range.start >= 0)
                {
                    ranges.erase(ranges.begin() + i);
                    capitalize(range.start, range.end);
                    return;
                }
            }
        }
        ranges.push_back({start, end});
    }

    std::string text()
    {
        std::string result;

        for (int i = 0; i < str.length(); i++)
        {
            auto ch = str[i];
            for (const auto &range : ranges)
                if (range.start <= i && i <= range.end)
                {
                    ch = std::toupper(ch);
                    break;
                }
            result += ch;
        }

        return result;
    }
};
```
기존에 bool형 배열을 사용해 대문자 판별을 진행한 방식은 문자열 길이에 따라 메모리 사용량이 늘어나서 비효율적이다.  
지금처럼 범위를 이용한다면 int형 2개로 고정이 되기 때문에 메모리 사용량이 훨씬 줄어들게 된다.  
바뀐 text(), capitalize() 함수의 수행 속도 하락은 메모리 절약적인 장점이 크기에 그렇게 큰 단점으로 작용하지 않는다.  
&nbsp;  

## 요약  

1. 플라이웨이트 패턴은 메모리를 절약하기 위한 패턴이다.  

2. 플라이웨이트 패턴은 매우 다양한 형태로 구현될 수 있어 상황에 따라 사용 방식이 천차만별이다.  