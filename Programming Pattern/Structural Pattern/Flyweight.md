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
확인하는 방식은 이진 탐색, 해쉬맵 등이 있다.  
먼저 이진 탐색 방식을 사용해보자.  
이진 탐색 방식을 사용하기에 nickname_list는 항상 정렬된 상태를 유지해야 한다.  
&nbsp;  

nickname_list에서 같은 닉네임을 찾았다면 해당 닉네임을 재활용하기 위해 인덱스를 알고 있어야 한다.  
따라서 User 구조체의 구조는 밑과 같이 바뀐다.  
```c++
struct User
{
    int id;
    long long nickname_key;
    const std::string &nickname() const { return nickname_list[nickname_key]; }
};
```
이제 User의 nickname은 nickname_key를 통해 접근하게 된다.  
&nbsp;  

add_user() 함수의 로직도 바뀌어야 한다.  
```c++
void add_user(const std::string &nickname)
{
    auto target = std::lower_bound(nickname_list.begin(), nickname_list.end(), nickname);
    if (target == nickname_list.end() || *target != nickname)
    {
        std::for_each(user_list.begin(), user_list.end(), [&](auto &user)
                      { if (nickname < user.nickname()) user.nickname_key++; });
        target = nickname_list.insert(target, nickname);
    }
    user_list.push_back(User{++id, target - nickname_list.begin()});
}
```
만약 nickname_list에 이미 존재하는 닉네임이라면 해당 닉네임의 인덱스를 User가 가지고 있으면 된다.    
새로운 nickname이 등장할 때마다 nickname_list에 정렬해 추가해줘야 한다.  
nickname_list에 새로운 값이 추가될 때마다 User 구조체에서 특정 이름을 가리키고 있던 인덱스 값들도 바뀌어야 해서 삽입시 O(N)의 복잡도가 도출된다.  
인덱스를 통해 객체를 가리키기 때문에 새로운 객체가 많이 생성되지 않는 상황에서는 인덱스의 자료형을 short, char 등으로 사용해 용량을 더욱 줄일 수 있다.  
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

이진 탐색에서는 인덱스를 사용했다면 해쉬맵에서는 포인터를 사용해서 nickname을 가리킨다.  
```c++
struct User
{
    int id;
    const std::string *nickname_ptr;
    const std::string &nickname() const { return *nickname_ptr; }
};
```
&nbsp;  

add_user() 함수의 로직도 이에 맞춰 바꿔보자.  
```c++
void add_user(const std::string &nickname)
{
    auto iter = nickname_list.find(nickname);
    if (iter == nickname_list.end())
        iter = nickname_list.insert(nickname).first;
    user_list.push_back(User{++id, &*iter});
}
```
새로운 nickname이 등장해서 nickname_list에 추가된다 하더라도 nickname을 가리키던 포인터에는 영향이 없다.  
따라서 삽입시 O(1)의 복잡도가 도출된다.  
문제는 포인터의 크기가 64-bit 운영체제에서 8byte, 32-bit 운영체제에서 4byte로 작은 크기는 아니다.  
처리 속도에서 조금 손해를 보더라도 메모리를 많이 줄이고 싶다면 이진 탐색 방식이 더 좋다.  
속도와 메모리 사용량 둘 다 적절하게 잡고 싶다면 
&nbsp;  

## Boost의 Flyweight  

Boost 라이브러리는 자체적으로 Flyweight 패턴을 지원한다.  
