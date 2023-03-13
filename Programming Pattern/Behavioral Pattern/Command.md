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
    virtual void call() const = 0;
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

    void call() const {
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

