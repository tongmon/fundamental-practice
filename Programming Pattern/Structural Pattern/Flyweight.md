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
};
```
이제 같은 닉네임의 유저가 생성될 때 nickname_list에서 이미 존재하는 닉네임인지 여부를 확인하면 된다.  
확인하는 방식은 이진 탐색, 해쉬맵 등이 있지만 여기선 이진 탐색 방식을 사용하겠다.  
&nbsp;  

nickname_list에서 같은 닉네임을 찾았다면 해당 닉네임을 재활용하기 위해 인덱스를 알고 있어야 한다.  
따라서 User 구조체의 구조는 밑과 같이 바뀐다.  
```c++
struct User
{
    int id;
    unsigned long long nickname_key;
};

std::binary_search(user_list.begin(), user_list.end(), nickname);
```
이제 User의 nickname은 nickname_key를 통해 접근하게 된다.  

&nbsp;  


## 