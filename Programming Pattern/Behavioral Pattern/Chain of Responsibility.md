# Chain of Responsibility  

책임 사슬 패턴에 대해 다룬다.  
마약이 불법인 국가에서 어떤 사람이 마약을 한 혐의로 붙잡혔다.  
처벌 받을 사람이 그 사람 한 명 뿐일까?  
마약을 유통한 브로커부터 제조인까지 처벌 받을 사람이 사슬처럼 연결되어 뻗어나갈 것이다.  
이것이 책임 사슬이다.  
&nbsp;  

## 포인터 사슬  

밑과 같은 생명체 클래스가 존재한다.  
```c++
struct Creature
{
    std::string name;
    int health;
    int move_speed;
};
```
생명체에는 이름, 체력, 이동 속도 정도가 속성으로 존재한다.  
딱 봐도 구조체 구성이 게임을 만들 때 활용하기 좋게 생겼다.  
&nbsp;  

생명체 클래스를 가지고 게임이 만드는 경우 특정 상황을 생각해보자.  
생명체는 게임이 진행되면서 체력이 깎이기도 하며 늪지대 같은 곳을 걸어다닐 때는 이동 속도도 낮아질 것이다.  
이러한 이벤트들이 많이 발생될 때 차근 차근 해결해 나가기 위해 포인터 사슬 패턴을 적용해보자.  
&nbsp;  

먼저 밑과 같은 생명체에 영향을 주기 위한 클래스가 있다.  
```c++
class CreatureModifier
{
    CreatureModifier *next;

protected:
    Creature &creature;

public:
    explicit CreatureModifier(Creature &creature) : creature{creature}, next{nullptr} {}

    void add(CreatureModifier *modifier)
    {
        if (next)
            next->add(modifier);
        else
            next = modifier;
    }

    virtual void handle()
    {
        if (next)
            next->handle();
    }
};
```
CreatureModifier 클래스는 연결리스트 형태를 취하고 있다.  
중요하게 봐야할 함수는 handle()로 handle() 함수가 한번 호출되면 사슬이 연결된 것 같이 연쇄적으로 작용한다는 것이다.  
CreatureModifier는 생명체 클래스를 처리하기 위한 인터페이스 역할을 해줄 것이다.  
&nbsp;  

생명체가 공격당하는 이벤트에 대한 클래스는 밑과 같다.  
```c++
class Attacked : public CreatureModifier
{
    int damage;

public:
    explicit Attacked(Creature &creature, int damage)
        : CreatureModifier(creature), damage{damage} {}

    void handle()
    {
        creature.health = std::max(0, creature.health - damage);
        CreatureModifier::handle();
    }
};
```
특정 데미지를 생명체에게 입힐 수가 있다.  
중요한 점은 연쇄적 호출을 적용하기 위해 재정의한 handle() 함수에서 ```CreatureModifier::handle();```를 호출하고 있다는 것이다.  
&nbsp;  

느려짐 디버프에 걸린 이벤트에 대한 클래스는 밑과 같다.  
```c++
class SnailDebuff : public CreatureModifier
{
public:
    explicit SnailDebuff(Creature &creature) : CreatureModifier(creature) {}

    void handle()
    {
        creature.move_speed = std::max(0, creature.move_speed - 5);
        CreatureModifier::handle();
    }
};
```
별거 없다.  
Attacked와 구조는 비슷하면서 이동속도만 감소될 뿐이다.  
&nbsp;  

고블린이 데미지를 입고 속도가 느려지는 상황은 밑과 같이 표현할 수 있다.  
```c++
Creature goblin{"cutty", 100, 20};

CreatureModifier goblin_modifier{goblin};
Attacked attacked{goblin, 40};
SnailDebuff snail_debuff{goblin};

goblin_modifier.add(&attacked);
goblin_modifier.add(&snail_debuff);

goblin_modifier.handle();
```
&nbsp;  

만약 데미지도 무효화하고 속도 디버프도 없애는 물약 같은 것을 고블린이 먹었다고 할 때 이 물약은 어떻게 표현할 수 있을까?  
밑은 물약에 대한 클래스이다.  
```c++
class DrinkCanclePotion : public CreatureModifier
{
public:
    explicit DrinkCanclePotion(Creature &creature) : CreatureModifier(creature) {}

    void handle() {}
};
```
단순히 handle() 함수에서 아무것도 안하면 된다...
&nbsp;  

밑과 같이 무효화 포션을 먹은 고블린은 추후에 어떠한 이벤트가 발생해도 그 효과를 받지 못한다.  
```c++
Creature goblin{"cutty", 100, 20};

CreatureModifier goblin_modifier{goblin};
Attacked attacked{goblin, 40};
SnailDebuff snail_debuff{goblin};
DrinkCanclePotion drink_cancle_potion{goblin};

goblin_modifier.add(&drink_cancle_potion);
goblin_modifier.add(&attacked);
goblin_modifier.add(&snail_debuff);

goblin_modifier.handle();
```
지금까지 본 이벤트의 순차적 처리 말고도 특정 장비(예를 들어 츄리닝 바지, 꽃 무늬 옷, 도라에몽 모자) 세트를 입는 순차적 행위를 프리셋으로 저장하여 원하는 시점에 불러 사용할 때 쓰일 수도 있다.  
&nbsp;  

## 브로커 사슬  

포인터 사슬의 문제점은 handle() 함수가 호출되면 원본 객체의 데이터 값을 남겨둘 수 없다는 것이다.  
즉 Undo가 불편해진다.  
브로커 사슬을 통해 이를 해결해보자.  
&nbsp;  

먼저 밑과 같은 쿼리 클래스가 존재한다.  
```c++
struct Query {
    std::string name;

    Query(const std::string &name) : name(name) {}
    virtual ~Query() {};
};
```
해당 클래스는 특정 함수 로직이 수행되기 위해 필요한 변수들을 제공해주는 쿼리 역할을 하게 된다.  
멤버 변수인 name은 생명체의 이름을 나타내고 앞으로 설명할 예시에서 생명체 고유의 id 역할을 한다.  
가상 소멸자가 존재하는 이유는 ```dynamic_cast<>```를 원활하게 이용하기 위해서인데 후에 보강 설명을 하겠다.  
&nbsp;  

공격을 당하는 이벤트, 속도 감소 디버프 이벤트 등에 대한 쿼리 클래스는 밑과 같다.  
```c++
struct AttackedQuery : public Query {
    int health;
    int damage;

    AttackedQuery(const std::string &name, const int &health, const int &damage)
        : Query(name), health{health}, damage{damage} {
    }
};

struct SnailDebuffQuery : public Query {
    int move_speed;

    SnailDebuffQuery(const std::string &name, const int &move_speed)
        : Query(name), move_speed{move_speed} {
    }
};
```
공격을 당하는 이벤트에는 생명체의 체력과 얼마 만큼의 데미지를 입었는지에 대한 정보가 필요하다.  
속도 감소 디버프는 이동 속도에 대한 정보만 있으면 된다.  
&nbsp;  

밑은 함수를 리스트 형태로 저장하고 있는 Game 클래스이다.  
```c++
struct Game
{
    std::list<std::function<void(Query &)>> queries;
};
```
이 클래스가 브로커 패턴의 핵심인 매개자이다.  
&nbsp;  

밑은 생명체 클래스이다.  
```c++
class Creature {
    Game &game;
    int health;
    int move_speed;

   public:
    std::string name;

    Creature(Game &game, const std::string &name, const int &health, const int &move_speed)
        : game(game),
          health(health),
          move_speed(move_speed),
          name(name) {
    }

    int attacked(int damage) {
        AttackedQuery q{name, health, damage};
        for (const auto &func : game.queries)
            func(q);
        return q.health;
    }

    int snail_debuffed() {
        SnailDebuffQuery q{name, move_speed};
        for (const auto &func : game.queries)
            func(q);
        return q.move_speed;
    }

    friend std::ostream &operator<<(std::ostream &os, Creature &obj) {
        return os
               << "name: " << obj.name
               << " health: " << obj.attacked(10)  // note here
               << " move speed: " << obj.move_speed;
    }
};
```
attacked(), snail_debuffed() 함수에서 전에 정의해놓은 쿼리들을 사용하는 모습을 볼 수 있다.  
쿼리에 생명체의 멤버 변수를 옮겨 담고 함수 리스트의 함수들을 실행하면서 쿼리의 멤버 변수를 바꾸기 때문에 생명체 객체의 원본을 유지할 수 있다.  
&nbsp;  


```c++
class CreatureModifier {
   protected:
    Game &game;
    Creature &creature;

   public:
    virtual ~CreatureModifier() = default;

    CreatureModifier(Game &game, Creature &creature)
        : game(game),
          creature(creature) {
    }
};
```

```c++
class AttackedModifier : public CreatureModifier {
    std::list<std::function<void(Query &)>>::iterator iter;

   public:
    AttackedModifier(Game &game, Creature &creature)
        : CreatureModifier(game, creature) {
        iter = game.queries.insert(game.queries.end(), [&](Query &q) {
            AttackedQuery *aq = dynamic_cast<AttackedQuery *>(&q);
            if (aq && creature.name == aq->name)
                aq->health = std::max(0, aq->health - aq->damage);
        });
    }

    ~AttackedModifier() {
        game.queries.erase(iter);
    }
};
```