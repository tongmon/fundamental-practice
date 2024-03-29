# Command Pattern   

어떤 객체의 API를 직접 다루어 조작하는 것이 아니라 그 객체에게 무엇을 하라고 명령을 내리는 패턴이다.  
명령을 통해 특정 객체를 조작하기 때문에 명령 수행 전의 객체 상태를 알기 용이하다.  
따라서 Undo를 유연하게 처리해야 하는 상황에서 많이 쓰인다.  
&nbsp;  

아래와 같은 입출금 통장 클래스가 존재한다.  
```c++
struct BankAccount {
    int balance = 0;
    int overdraft_limit = -500;

    void deposit(int amount) {
        balance += amount;
        std::cout << "deposited: " << amount << ", balance now: " << balance << "\n";
    }

    void withdraw(int amount) {
        if (balance - amount >= overdraft_limit) {
            balance -= amount;
            std::cout << "withdrew: " << amount << ", balance now: " << balance << "\n";
        }
    }
};
```
초과 출금 금액 한도는 500이다.  
해당 클래스는 프로젝트 내부적으로 하도 많이 쓰여 바꾸기 어려운 상태라고 가정한다.  
이러한 상황에서 커맨드 패턴을 활용해보자.  
&nbsp;  

## 구현  

커맨트 패턴의 토대를 다지기 위해 밑과 같은 인터페이스를 만들어 준다.  
```c++
struct Command {
    virtual void call() = 0;
};
```
&nbsp;  

해당 인터페이스를 상속하여 입출금 계좌 커맨트 클래스를 만들어 준다.  
```c++
struct BankAccountCommand : Command {
    BankAccount &account;
    enum Action { deposit,
                  withdraw } action;
    int amount;

    BankAccountCommand(BankAccount &account,
                       const Action &action, const int &amount)
        : account(account), action(action), amount(amount) {}

    void call() {
        switch (action) {
        case deposit:
            account.deposit(amount);
            break;
        case withdraw:
            account.withdraw(amount);
            break;
        default:
            break;
        }
    }
};
```
BankAccountCommand는 BankAccount에게 특정 명령을 내리기 위해 설계된 클래스이다.  
계좌, 어떤 명령을 내릴지, 금액 등 명령을 수행하기 위한 변수들은 다 가지고 있다.  
&nbsp;  

밑은 명령 수행 방법이다.    
```c++
BankAccount account;
BankAccountCommand command{account, BankAccountCommand::deposit, 100};
command.call();
```
BankAccountCommand 클래스를 통해 명령을 세팅하고 call() 함수로 명령을 수행한다.  
BankAccount 클래스의 deposit(), withdraw() 함수가 노출되는 것이 싫다면 해당 함수들을 private으로 설정하고 friend 클래스 선언을 이용하면 된다.  
&nbsp;  

## Undo 작업  

커맨드 패턴의 장점인 Undo 작업을 구현해보자.  
일단 커맨드 인터페이스에 undo()를 밑과 같이 추가해준다.  
```c++
struct Command {
    virtual void call() = 0;
    virtual void undo() = 0;
};
```
&nbsp;  

Undo 작업은 밑과 같이 간단하다.  
```c++
void undo() {
    switch (action) {
    case withdraw:
        account.deposit(amount);
        break;
    case deposit:
        account.withdraw(amount);
        break;
    default:
        break;
    }
}
```
그냥 청개구리 마냥 반대로 해주면 된다.  
입금 명령이였다면 출금하고, 출금 명령이였다면 입금한다.  
&nbsp;  

근데 문제가 있다.  
전재산이 5000인 사람이 6000을 출금한 뒤에 Undo를 하면 어떻게 될까?  
일단 초과 출금 금액이 500이기에 출금이 실패한다.  
Undo가 진행되어 출금의 반대인 입금 로직이 수행되고 5000 금액에 6000이 더해져 11000으로 재산이 불어나게 된다...  
&nbsp;  

해결하려면 일단 밑과 같이 BankAccount 클래스의 withdraw() 함수를 수정해준다.  
```c++
bool withdraw(int amount) {
    if (balance - amount >= overdraft_limit) {
        balance -= amount;
        std::cout << "withdrew " << amount << ", balance now " << balance << "\n";
        return true;
    }
    return false;
}
```
이제 출금 성공 여부를 알 수가 있다.  
&nbsp;  

이제 완성된 BankAccountCommand 클래스를 보자.  
```c++
struct BankAccountCommand : Command {
    BankAccount &account;
    enum Action { deposit,
                  withdraw } action;
    int amount;
    bool withdrawal_succeeded;

    BankAccountCommand(BankAccount &account,
                       const Action &action, const int &amount)
        : account(account), action(action), amount(amount) {}

    void call() {
        switch (action) {
        case deposit:
            account.deposit(amount);
            break;
        case withdraw:
            withdrawal_succeeded = account.withdraw(amount);
            break;
        default:
            break;
        }
    }

    void undo() {
        switch (action) {
        case withdraw:
            if (withdrawal_succeeded)
                account.deposit(amount);
            break;
        case deposit:
            account.withdraw(amount);
            break;
        default:
            break;
        }
    }
};
```
출금이 성공한 경우에만 Undo 할 수 있어 문제가 해결되었다.   
&nbsp;  

## 컴포지트 커맨드  

지금까지는 출금, 입금, Undo 행위만 다뤘다.  
이제 다른 계좌로 이체하는 명령을 만들어보자.  
A 계좌에서 출금하고 B 계좌에 입금하면 계좌 이체가 된다.  
&nbsp;  

다중 명령을 수행할 수 있는 컴포지트 커맨드 인터페이스를 만들어보자.  
```c++
struct CompositeBankAccountCommand : std::vector<BankAccountCommand> {
    CompositeBankAccountCommand(const std::initializer_list<BankAccountCommand> &items)
        : std::vector<BankAccountCommand>(items) {
    }

    void call() {
        for (auto &cmd : *this)
            cmd.call();
    }

    void undo() {
        for (auto iter = rbegin(); iter != rend(); ++iter)
            iter->undo();
    }
};
```
BankAccountCommand 명령을 배열로 처리하면 된다.  
유심히 봐야할 점은 undo() 함수는 명령의 역순이기에 iterator를 반대로 순회하고 있다는 것이다.  
&nbsp;  

아래는 계좌 이체 커맨드 클래스이다.  
```c++
struct AccountTransferCommand : CompositeBankAccountCommand {
    AccountTransferCommand(BankAccount &from, BankAccount &to, int amount)
        : CompositeBankAccountCommand(
              {BankAccountCommand{from, BankAccountCommand::withdraw, amount},
               BankAccountCommand{to, BankAccountCommand::deposit, amount}}) {
    }
};
```
출금, 입금 명령을 연달아 수행하기 위해 CompositeBankAccountCommand에 넣어주고 있다.  
AccountTransferCommand 클래스 사용자는 단지 출금 계좌, 입금 계좌, 이체 금액을 알고 있으면 된다.  
&nbsp;  

유심히 로직을 보면 CompositeBankAccountCommand 구조체가 불완전한 것을 알 수 있다.  
예를 들어 ```A 계좌 출금 -> B 계좌 입금 -> B 계좌 출금 -> C 계좌 입금``` 이러한 다중 명령이 있다고 하자.  
3번째 명령인 ```B 계좌 출금```에서 오류가 발생되었다고 하자.  
이 경우 여태 실행했던 ```A 계좌 출금```, ```B 계좌 입금``` 명령을 철회하는 것이 맞을 텐데 현재 CompositeBankAccountCommand 구조체는 이러한 장치가 없다.  
이러한 상황을 방지해보자.  
&nbsp;  

보편적으로 접근하기 위해 Command 구조체를 밑과 같이 수정해준다.  
```c++
struct Command {
    bool succeeded;
    virtual void call() = 0;
    virtual void undo() = 0;
};
```
특정 명령의 성공 여부를 알려주는 succeeded 변수를 추가한다.  
&nbsp;  

그 다음 BankAccountCommand 구조체도 수정해보자.  
```c++
struct BankAccountCommand : Command {
    BankAccount &account;
    enum Action { deposit,
                  withdraw } action;
    int amount;

    BankAccountCommand(BankAccount &account,
                       const Action &action, const int &amount)
        : account(account), action(action), amount(amount) {}

    void call() {
        succeeded = false;
        switch (action) {
        case deposit:
            account.deposit(amount);
            succeeded = true;
            break;
        case withdraw:
            succeeded = account.withdraw(amount);
            break;
        default:
            break;
        }
    }

    void undo() {
        switch (action) {
        case withdraw:
            if (succeeded)
                account.deposit(amount);
            break;
        case deposit:
            account.withdraw(amount);
            break;
        default:
            break;
        }
    }
};
```
withdrawal_succeeded가 Command 구조체에서 상속된 succeeded로 변경되었다.  
&nbsp;  

마지막으로 CompositeBankAccountCommand 구조체를 고쳐보자.  
```c++
struct CompositeBankAccountCommand : std::vector<BankAccountCommand> {
    CompositeBankAccountCommand(const std::initializer_list<BankAccountCommand> &items)
        : std::vector<BankAccountCommand>(items) {
    }

    int failure_index;

    void call() {
        failure_index = 0;
        for (int i = 0; i < this->size(); i++) {
            this->at(i).call();
            if (!this->at(i).succeeded) {
                failure_index = i;
                break;
            }
        }

        for (int i = failure_index - 1; i >= 0; i--)
            this->at(i).undo();
    }

    void undo() {
        for (auto iter = rbegin(); iter != rend(); ++iter)
            iter->undo();
    }
};
```
call() 함수를 보면 failure_index 멤버 변수를 통해 어느 시점에서 명령이 실패하였는지를 알아내고 실패 전까지 실행하였던 명령들을 Undo한다.  
&nbsp;  

이외에도 call() 함수를 한번도 사용하지 않았는데 undo()가 수행되는 문제도 있다.  
undo() 함수의 최대 수행 가능 횟수는 call() 함수의 수행 횟수다.  
이 사실을 토대로 BankAccountCommand를 좀 더 수정해보자.  
```c++
struct BankAccountCommand : Command {
    BankAccount &account;
    enum Action { deposit,
                  withdraw,
                  action_cnt } action;
    int amount;
    int call_executed_cnt[action_cnt] = { 0, };

    BankAccountCommand(BankAccount &account, const Action &action, const int &amount)
        : account(account), action(action), amount(amount) {}

    void call() {
        succeeded = false;
        switch (action) {
        case deposit:
            account.deposit(amount);
            succeeded = true;
            call_executed_cnt[deposit]++;
            break;
        case withdraw:
            succeeded = account.withdraw(amount);
            if (succeeded)
                call_executed_cnt[withdraw]++;
            break;
        default:
            break;
        }
    }

    void undo() {
        switch (action) {
        case withdraw:
            if (call_executed_cnt[withdraw]) {
                account.deposit(amount);
                call_executed_cnt[withdraw]--;
            }
            break;
        case deposit:
            if (call_executed_cnt[deposit]) {
                account.withdraw(amount);
                call_executed_cnt[deposit]--;
            }
            break;
        default:
            break;
        }
    }
};
```
call_executed_cnt라는 각 명령별 카운터가 생겼다.  
이제 각 명령의 call() 수행 횟수가 기록되어 무분별하게 undo() 로직이 수행되지 않는다.  
&nbsp;  

## 명령과 조회의 분리  

먼저 명령과 조회의 정확한 의미를 보고가자.  

- **명령**  
    상태 변화를 일으킴  
    결괏값의 생성이 없음  

- **조회**  
    정보 요청  
    상태 변화를 만들지 않음  
    결괏값 발생  

명령과 조회 방식을 사용하여 기존의 get / set 방식을 대체할 수 있다.  
밑의 Creature 클래스 예시를 보자.  
```c++
class Creature
{
    int _strength;
    int _agility;

  public:
    Creature(int strength, int agility)
        : _strength{strength}, _agility{agility}
    {
    }

    void process_command(const CreatureCommand &cc);
    int process_query(const CreatureQuery &q) const;
};
```
strength, agility 멤버 변수가 있지만 get / set 관련 함수는 없다.  
멤버 변수를 변경하고 한다면 process_command() 함수로 명령을 내린다.  
특정 멤버 변수를 얻고 싶다면 process_query() 함수에게 쿼리를 전달한다.  
&nbsp;  

Creature의 능력치에 대한 enum class를 구현해준다.  
```c++
enum class CreatureAbility
{
    strength,
    agility
};
```
어떤 멤버 변수 상태를 변경하기 위한 명령인지 구분하기 위해서 필요하다.  
어떤 멤버 변수 값을 획득하고 싶은지 전달해주는 쿼리에 필요하다.  
&nbsp;  

생명체 클래스에게 내릴 명령을 밑과 같이 정의한다.  
```c++
struct CreatureCommand
{
    enum Action
    {
        set,
        increase,
        decrease
    } action;
    CreatureAbility ability;
    int amount;
};
```
정수형 변수를 바꾸기 위한 명령에 필요한 정보는 다 있다.  
어떤 값을, 얼마 만큼, 세팅 or 증가 or 감소할 것인지를 정하면 된다.  
&nbsp;  

어떤 값을 획득할 것인지 조회 함수에게 알려주는 쿼리는 밑과 같다.  
```c++
struct CreatureQuery
{
    CreatureAbility ability;
};
```
별 것은 없고 그냥 획득하고자 하는 ability를 정해주면 된다.  
&nbsp;  

이제 미구현된 명령, 조회 함수를 구현해보자.  
밑은 명령 함수이다.  
```c++
void process_command(const CreatureCommand &cc)
{
    int *ability;
    switch (cc.ability)
    {
    case CreatureAbility::strength:
        ability = &_strength;
        break;
    case CreatureAbility::agility:
        ability = &_agility;
        break;
    default:
        break;
    }
    switch (cc.action)
    {
    case CreatureCommand::set:
        *ability = cc.amount;
        break;
    case CreatureCommand::increase:
        *ability += cc.amount;
        break;
    case CreatureCommand::decrease:
        *ability -= cc.amount;
        break;
    }
}
```
어떤 멤버 변수에 대한 명령인지 알아낸 뒤 그 값을 주어진 양 만큼 정해진 방법으로 변경한다.  
&nbsp;  

밑은 조회 함수이다.  
```c++
int process_query(const CreatureQuery &q) const
{
    switch (q.ability)
    {
    case CreatureAbility::agility:
        return _agility;
    case CreatureAbility::strength:
        return _strength;
    }
}
```
그냥 쿼리에서 정해준 능력치를 반환해주면 된다.  
&nbsp;  

명령, 조회 방식에서 get / set 방식으로 바꾸는 것은 어렵지 않다.  
```c++ 
void strength(const int &value)
{
    process_command(CreatureCommand{CreatureCommand::set, CreatureAbility::strength, value});
}

int strength() const
{
    return process_query(CreatureQuery{CreatureAbility::strength});
}

void agility(const int &value)
{
    process_command(CreatureCommand{CreatureCommand::set, CreatureAbility::agility, value});
}

int agility() const
{
    return process_query(CreatureQuery{CreatureAbility::agility});
}
```
process_command(), process_query() 함수를 적절히 사용해주면 된다.  
&nbsp;  

## 요약  

1. 커맨드 패턴은 특정 객체의 함수를 직접 호출해서 조작하는 것이 아닌 그 객체를 감싸는 명령 클래스를 만들어 명령 클래스를 이용해 객체에 명령을 내리는 패턴이다.  

2. 대상 객체에 변화를 일으키지 않는다면 어떤 정보만 획득하기 위한 명령 클래스인 조회 객체를 만들어 처리할 수도 있다.  

3. 커맨드 패턴은 ```복사하기```, ```붙여넣기```, ```되돌리기```와 같은 여러 작업의 연속체를 처리하는 곳에 많이 쓰인다.  