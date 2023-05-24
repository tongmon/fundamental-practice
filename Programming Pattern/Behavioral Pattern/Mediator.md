# Mediator Pattern   

컴포넌트끼리 소통을 위해 서로를 직접 참조해야 하는 경우가 있다.  
하지만 참조하려는 컴포넌트가 수명이 다해 nullptr인 경우도 있을 것이고 컴포넌트 간의 참조 순서가 꼬여 문제가 발생할 수도 있다.  
따라서 컴포넌트 간의 결합을 느슨하게 하는 중간 역할이 필요하다.  
중재자(매개자) 패턴은 컴포넌트끼리의 소통만을 위해 존재하는 **중재자**를 따로 두어 결합도를 낮춘다.  
&nbsp;  

## 컴포넌트 리스트    

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
상호 참조를 방지하기 위해 Person.hpp에 정의한다.  

Person.cpp 정의부는 밑과 같다.  
```c++
Person::Person(const std::string &name)
    : name(name)
{
}

void Person::receive(const std::string &origin, const std::string &message)
{
    std::string s{origin + ": \"" + message + "\""};
    std::cout << "[" << name << "'s chat session] " << s << "\n";
    chat_log.emplace_back(s);
}

void Person::say(const std::string &message) const
{
    room->broadcast(name, message);
}

void Person::private_message(const std::string &who, const std::string &message) const
{
    room->message(name, who, message);
}
```
각 함수들을 보면 알겠지만 채팅 내용을 수신하는 것을 제외하면 모두 **중재자** 역할을 하는 room에 작업을 요청한다.  
&nbsp;  

중재자인 채팅룸은 다음과 같이 구현된다.  
```c++
struct Person;

struct ChatRoom
{
    std::vector<Person *> people; // 추가만 한다고 가정한다

    void join(Person *p);
    void broadcast(const std::string &origin, const std::string &message);
    void message(const std::string &origin, const std::string &who, const std::string &message);
};
```
마찬가지로 ChatRoom.hpp에 정의한다.  
Person 컴포넌트들을 리스트에 담아 소통을 중재한다.  

ChatRoom.cpp는 밑과 같다.  
```c++
void ChatRoom::broadcast(const std::string &origin, const std::string &message)
{
    for (auto p : people)
        if (p->name != origin)
            p->receive(origin, message);
}

void ChatRoom::join(Person *p)
{
    std::string join_msg = p->name + " joins the chat";
    broadcast("room", join_msg);

    p->room = this;
    people.push_back(p);
}

void ChatRoom::message(const std::string &origin, const std::string &who, const std::string &message)
{
    auto target = find_if(begin(people), end(people), [&](const Person *p) { return p->name == who; });
    if (target != end(people))
    {
        (*target)->receive(origin, message);
    }
}
```
broadcast는 전체 메시지이다.  
join은 채팅방 입장 시 수행할 기능이 들어있다.  
message는 특정 사람에게 메시지를 보내는 기능이 들어있다.  
구현부를 보면 알겠지만 Person ⇋ ChatRoom ⇋ Person 이렇게 Person과 ChatRoom은 소통하지만 Person끼리는 직접적으로 소통하지 않는다.  
&nbsp;  

Person, ChatRoom은 밑과 같이 활용할 수 있을 것이다.  
```c++
ChatRoom room;

Person john{"john"};
Person jane{"jane"};
Person simon("simon");

room.join(&john);
room.join(&jane);

john.say("hi room");
jane.say("oh, hey john");

room.join(&simon);

simon.say("hi everyone!");
jane.private_message("simon", "glad you could join us, simon");
```
중재자는 하나만 존재한다.  
&nbsp;  

## 중재자와 이벤트  

이번에 다룰 예제는 [책임 사슬 패턴](https://github.com/tongmon/fundamental-practice/blob/master/Programming%20Pattern/Behavioral%20Pattern/Chain%20of%20Responsibility.md)에서 보았던 [브로커 사슬](https://github.com/tongmon/fundamental-practice/blob/master/Programming%20Pattern/Behavioral%20Pattern/Chain%20of%20Responsibility.md#%EB%B8%8C%EB%A1%9C%EC%BB%A4-%EC%82%AC%EC%8A%AC)과 비슷한 패턴이다.  
알림을 발생시키는 객체인 시그널, 알림을 처리하는 슬롯을 다룬다.  
해당 예제에선 시그널은 플레이어, 슬롯은 NPC가 추가하는 람다 함수가 된다.  
&nbsp;  

일단 밑과 같은 이벤트 데이터가 있다.  
```c++
struct EventData
{
    virtual void print() const = 0;
    virtual ~EventData() = default;
};
```
인터페이스로 상속을 통해 사용가능하다.  

게임을 플레이하는 플레이어가 레벨이 오르는 이벤트를 정의해보자.  
```c++
struct PlayerLevelUpData : EventData
{
    std::string player_name;
    int player_lvl;

    PlayerLevelUpData(const std::string &player_name, int lvl)
        : player_name{player_name}, player_lvl{lvl}
    {
    }

    void print() const
    {
        std::cout << player_name << " have reach " << player_lvl << " level!\n";
    }
};
```
서버에 해당 플레이어의 레벨 상승 소식을 알려주기 위해 print() 함수를 위와 같이 구현해준다.  

**중재자**는 밑과 같다.  
```c++
struct Game
{
    std::list<std::function<void(EventData *)>> events; // 관찰자
};
```
이벤트 처리에 관련된 함수만 담을 뿐 딱히 어떤 일을 수행하지는 않는다.  

플레이어는 밑과 같이 생겼다.  
```c++
struct Player
{
    std::string name;
    int level;
    Game &game;

    Player(const std::string &name, Game &game)
        : name{name}, game{game}
    {
        level = 0;
    }

    void level_up()
    {
        level++;
        PlayerLevelUpData pl{name, level};
        for (const auto &func : game.events)
            func(&pl);
    }
};
```
레벨이 상승하면 **중재자**인 Game에게 이벤트 처리를 부탁한다.  

해당 게임은 레벨 3에 도달하면 레벨 상승 보상을 플레이어에게 주는 시스템을 가지고 있다.  
```c++
struct NPC
{
    Game &game;
    NPC(Game &game)
        : game{game}
    {
        game.events.push_back([](EventData *event) -> void {
            auto pl = dynamic_cast<PlayerLevelUpData *>(event);
            if (pl && pl->player_lvl == 3)
                std::cout << pl->player_name << " get level up reward!\n";
        });
    }
};
```
게임 내의 NPC는 플레이어가 레벨 3에 도달하는 이벤트를 처리하기 위해 중재자에게 이벤트 처리 함수를 추가한다.  

활용은 밑과 같이 할 수 있다.  
```c++
Game game;
Player player{"tongstar", game};
NPC npc{game};

player.level_up();
player.level_up();
player.level_up(); // 해당 시점에서 레벨업 보상을 획득한다.  
```
game은 플레이어의 레벨을 지켜보다가 레벨 3에 도달하는 시점에 NPC가 지시한대로 레벨업 보상을 플레이어에게 준다.  
해당 예시도 Player ⇋ Game ⇋ NPC 이러한 구조를 취하고 있다.  
Player와 NPC는 서로 직접 소통하지 않는다.  
&nbsp;  

### Boost.Signals2  

이렇게 함수 객체를 이용해 이벤트를 처리하는 구조는 Boost.Signals2를 이용해 개선이 가능하다.  
```c++
struct Game
{
    boost::signals2::signal<void(EventData *)> events; // 관찰자
};

struct Player
{
    std::string name;
    int level;
    Game &game;

    Player(const std::string &name, Game &game)
        : name{name}, game{game}
    {
        level = 0;
    }

    void level_up()
    {
        level++;
        PlayerLevelUpData pl{name, level};
        game.events(&pl);
    }
};

struct NPC
{
    Game &game;
    NPC(Game &game)
        : game{game}
    {
        game.events.connect([](EventData *event) -> void {
            auto pl = dynamic_cast<PlayerLevelUpData *>(event);
            if (pl && pl->player_lvl == 3)
                std::cout << pl->player_name << " get level up reward!\n";
        });
    }
};
```
좀 더 구현이 간략해진다.  
&nbsp;  

## 요약  

1. 중재자 패턴은 컴포넌트가 서로를 직접 참조하지 않고도 소통할 수 있도록 도와준다.  

2. 가장 단순한 중재자 패턴은 중재자 내부 멤버 변수로 컴포넌트들을 담는 리스트를 두고 이용하는 것이다.  

3. 이벤트를 등록하고 수신하는 형태로 중재자를 구성할 수 있다.  
    이 경우 컴포넌트 간 소통을 할 때 전달할 정보에 대한 이벤트 구조체가 정의되어 있어야 한다.  