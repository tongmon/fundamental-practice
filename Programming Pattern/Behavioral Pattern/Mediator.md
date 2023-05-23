# Mediator Pattern   

컴포넌트끼리 소통을 위해 서로를 직접 참조해야 하는 경우가 있다.  
하지만 참조하려는 컴포넌트가 수명이 다해 nullptr인 경우도 있을 것이고 컴포넌트 간의 참조 순서가 꼬여 문제가 발생할 수도 있다.  
이러한 문제를 해결하기 위한 로직을 컴포넌트 안에 직접 넣는 것은 직관적이지 않다.  
따라서 오직 컴포넌트끼리의 소통을 위해 존재하는 **중재자**를 따로 두어 관리하는 방식이 생겼는데 이것이 중재자(매개자) 패턴이다.  
&nbsp;  

## 채팅방  

중재자 패턴이 대표적으로 쓰일 수 있는 곳은 채팅방이다.  
**사람**이라는 컴포넌트가 있고 **방**이라는 중재자가 있다.  
&nbsp;  

사람에 대한 클래스는 밑과 같다.  
```c++
struct ChatRoom;

struct Person
{
    std::string name;
    ChatRoom *room = nullptr;
    std::vector<std::string> chat_log;

    Person(const std::string &name);

    void receive(const std::string &origin, const std::string &message);
    void say(const std::string &message) const;
    void private_message(const std::string &who, const std::string &message) const;
};
```

## 요약  

