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

