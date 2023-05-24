# Memento Pattern   

[커맨드 패턴](https://github.com/tongmon/fundamental-practice/blob/master/Programming%20Pattern/Behavioral%20Pattern/Command.md)은 어떤 명령을 기준으로 Undo/Redo를 수행할 수 있다.  
따라서 명령만 따로 기록해놓으면 과거의 어떤 지점으로든 상태를 되돌릴 수가 있다.  

메멘토 패턴은 **명령**을 거슬러 올라가는 방식으로 Redo/Undo를 수행하지 않고 저장해놓은 특정 **상태**를 가지고 Redo/Undo를 수행한다.  
특정 상태를 **토큰**이라 칭하기도 한다.  
이러한 **상태**들을 배열에 저장해두고 꺼내와 과거 시점으로 되돌아 갈 수 있다.  
&nbsp;  

## 은행 계좌  

[커맨드 패턴](https://github.com/tongmon/fundamental-practice/blob/master/Programming%20Pattern/Behavioral%20Pattern/Command.md)에서 살펴봤던 은행 계좌 예제를 다시 다뤄보자.  
```c++
class BankAccount
{
    int balance = 0;

  public:
    explicit BankAccount(const int balance)
        : balance(balance)
    {
    }

    Memento deposit(int amount)
    {
        balance += amount;
        return Memento{balance};
    }

    void restore(const Memento &m)
    {
        balance = m.balance;
    }
};
```
계좌는 위와 같다.  
입금, 복구 두 가지 함수가 있다.  
특이한 점으로는 뒤에 등장할 메멘토를 사용한다.  

메멘토는 밑과 같다.  
```c++
class Memento
{
    int balance;

  public:
    explicit Memento(int balance)
        : balance(balance)
    {
    }
    friend class BankAccount;
};
```
별로 특이한 것이 없다.  
그저 특정 시점의 금액을 저장하기 위해 존재할 뿐이다.  
하지만 메멘토 상태를 이용할 때 지켜져야 할 두 가지 사항이 있다.  

- 메멘토 상태는 불변이여야 한다.  
    메멘토의 상태 값을 변경해서 없던 과거를 만들면 안된다.  
  
- 메멘토 상태를 사용하고자 하는 클래스와 친구여야 한다.  
    위 예시에서는 BankAccount가 되겠다.  
&nbsp;  

구현이 되었다면 밑과 같이 활용할 수 있다.  
```c++
BankAccount ba{100};
auto token_01 = ba.deposit(50); // 사용자가 오후 5시 50만원 입금

// 오후 7시 ~ 오후 12까지 전산 오류

auto token_02 = ba.deposit(25); // 사용자가 오후 11시 25만원 입금... 전산 오류 중이라 돈이 증발...?

ba.restore(token_01); // 돈이 증발된 고객들의 항의를 잠재우고자 오후 5시 시점으로 Undo

ba.restore(token_02); // 오후 11시 시점으로 Redo도 가능...
```
위와 같이 특점 시점에 반환된 메멘토 상태를 가지고 Undo/Redo가 가능하다.  
&nbsp;  

## Undo, Redo 인터페이스  

위에서 Undo, Redo를 진행했지만 어떤 함수를 이용해 진행한 것이 아니라 메멘토 상태를 이용해 즉석해 진행한 것이다.  
연속적인 Undo, Redo를 위해 직접 Undo/Redo 함수를 구현해보자.  

일단 기존의 BankAccount를 개선해야 한다.  
```c++
class BankAccount
{
    int balance = 0;
    std::vector<std::shared_ptr<Memento>> changes;
    int current;

  public:
    explicit BankAccount(const int balance)
        : balance(balance)
    {
        changes.emplace_back(std::make_shared<Memento>(balance));
        current = 0;
    }
};
```
특정 시점의 상태만이 아니라 모든 상태를 기록해야 하기에 메멘토 상태 배열이 필요하다.  
그리고 현재 어떤 상태인지 알 수 있도록 현재 상태를 메멘토 상태 배열의 인덱스 형태로 저장한다.  
&nbsp;  

입금 함수는 밑과 같다.  
```c++
class BankAccount
{   
    // 나머지 생략 

    std::shared_ptr<Memento> deposit(int amount)
    {
        balance += amount;
        auto m = std::make_shared<Memento>(balance);
        changes.push_back(m);
        ++current;
        return m;
    }
};
```
해당 시점의 메멘토 상태를 저장하고 현재 상태 인덱스를 하나 증가시킨다.  

복구 함수는 밑과 같다.  
```c++
class BankAccount
{
    // 나머지 생략 

    void restore(const std::shared_ptr<Memento> &m)
    {
        if (m)
        {
            balance = m->balance;
            changes.push_back(m);
            current = changes.size() - 1;
        }
    }
};
```
일단 주어진 메멘토 상태를 적용한다.  
복구도 상태가 변경된 것이기에 변경 기록을 남겨야 한다.  
따라서 현재 상태의 인덱스가 가장 최신 상태인 ```changes.size() - 1```로 바뀌어야 한다.  
&nbsp;  

Undo는 밑과 같다.  
```c++
class BankAccount
{    
    // 나머지 생략 

    std::shared_ptr<Memento> undo()
    {
        if (current > 0)
        {
            --current;
            auto m = changes[current];
            balance = m->balance;
            return m;
        }
        return {};
    }
};
```
변하는 것은 현재 상태 인덱스 뿐이다.  
그저 한번 뒤로 이동한 뒤 그 값이 가리키는 메멘토 상태를 반환하면 된다.  
물론 현재 상태가 0이라면 뒤로 이동할 것이 없기 때문에 비어있는 포인터 값을 반환한다.  
해당 값은 어짜피 ```restore()``` 함수에서 무시되어 BankAccount에 영향이 없다.  
&nbsp;  

Redo는 밑과 같다.  
```c++
class BankAccount
{
    // 나머지 생략 

    std::shared_ptr<Memento> redo()
    {
        if (current + 1 < changes.size())
        {
            ++current;
            auto m = changes[current];
            balance = m->balance;
            return m;
        }
        return {};
    }
};
```
Undo와 반대되는 행위를 하면 된다.  
이제 앞으로 한 번 이동한 뒤 그 값이 가리키는 메멘토 상태를 반환하면 된다.  
이번에도 역시 앞으로 이동할 것이 없으면 비어있는 포인터 값을 반환한다.  
&nbsp;  

밑과 같이 활용할 수 있다.  
```c++
BankAccount ba{100};

auto token_01 = ba.deposit(50);
auto token_02 = ba.deposit(25);

ba.undo();
ba.undo();

// 현재 잔고 100

ba.redo();
ba.redo();
ba.restore(ba.redo()); // 문제 없다.  

// 현재 잔고 175
```
restore() 함수가 빈 포인터를 무시하기에 ```ba.restore(ba.redo());``` 이렇게 해도 문제는 없다.  
&nbsp;  

## 요약  

1. 메멘토 패턴은 특정 시점의 상태를 저장하여 Undo/Redo를 가능케 한다.  

2. 각 시점의 메멘토 상태를 저장해놓은 변경 기록 배열을 만들면 유용하게 활용이 가능하다.  
