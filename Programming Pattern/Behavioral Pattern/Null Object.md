# Null Object  

특정 모듈을 이용할 때 필요없는 기능까지 동봉되어 있는 상황이 있을 것이다.  
이러한 경우 특정 기능만 배제하기 위해 Null Object를 만들어 사용하면 편하다.  
한번 예시를 살펴보자.  
&nbsp;  

특정 계좌 클래스에서 로깅을 사용하고 있다.  
```c++
struct Logger
{
    virtual ~Logger() = default;
    virtual void info(const std::string &s) = 0;
    virtual void warning(const std::string &s) = 0;
};
```
로깅 인터페이스는 위와 같다.  

계좌 클래스는 밑과 같다.  
```c++
struct BankAccount
{
    std::shared_ptr<Logger> logger;
    std::string name;
    int balance = 0;

    BankAccount(const std::shared_ptr<Logger> &logger, const std::string &name, int balance)
        : logger{logger}, name{name}, balance{balance}
    {
    }

    void deposit(int amount)
    {
        balance += amount;
        logger->info("Deposited $" + std::to_string(amount) + " to " + name + ", balance is now $" + std::to_string(balance));
    }

    // 다른 멤버들...
};
```
```deposit()``` 함수에 볼 수 있듯이 logger 인터페이스를 이용하여 로그를 출력하고 있다.  

콘솔창에 로그를 출력하고자 한다면 밑과 같은 logger를 고려할 수 있다.  
```c++
struct ConsoleLogger : public Logger
{
    void info(const std::string &s)
    {
        std::cout << "INFO: " << s << std::endl;
    }

    void warning(const std::string &s)
    {
        std::cout << "WARN: " << s << std::endl;
    }
};
```
해당 로거를 계좌를 초기화하는 시점에 넣어주면 된다.  
하지만 로그를 출력하기 싫다면 어떻게 해야할까?  
&nbsp;  

## Null Logger  

일단 첫번째로 밑과 같이 생각해볼 수 있다.  
```c++
struct BankAccount
{
    // 동일 구현부 생략

    BankAccount(const std::shared_ptr<Logger> &logger, const std::string &name, int balance)
        : name{name}, balance{balance}
    {
        this->logger = logger ? logger : nullptr;
    }

    void deposit(int amount)
    {
        balance += amount;

        if (logger)
            logger->info("Deposited $" + std::to_string(amount) + " to " + name + ", balance is now $" + std::to_string(balance));
    }
};
```
하지만 logger를 nullptr로 넘기는 방식은 위험하고 번거롭다.  
당장 deposit() 함수만 봐도 logger의 null 유무를 따져야 하는데 클래스 멤버가 굉장히 많다면?  
수정할 부분과 생각할 것이 많아진다.  

밑과 같이 ```std::optional```을 이용할 수도 있다.  
```c++
struct BankAccount
{
    // 동일 구현부 생략

    std::optional<std::shared_ptr<Logger>> logger;

    BankAccount(const std::shared_ptr<Logger> &logger, const std::string &name, int balance)
        : name{name}, balance{balance}
    {
        if (logger)
            this->logger = logger;
        else
            this->logger = std::nullopt;
    }

    void deposit(int amount)
    {
        balance += amount;
        if (logger.has_value())
            logger.value()->info("Deposited $" + std::to_string(amount) + " to " + name + ", balance is now $" + std::to_string(balance));
    }
};
```
관례적으로나 의도적으로나 모두 맞다.  
하지만 nullptr로 넘기는 방식과 마찬가지로 번거롭다.  

대신에 밑과 같이 Null Object를 만들면 굉장히 편해진다.  
```c++
struct NullLogger : public Logger
{
    void info(const std::string &s) {}
    void warning(const std::string &s) {}
};
```
단지 logger에 NullLogger를 넣어 로그 출력을 방지할 수 있다.  
나머지 부분은 수정할 필요가 없다.  
&nbsp;  

## 묵시적 Null Object  

살짝 기교적인 기법으로 호출과 집행을 나누어 처리하는 방식이 있다.  
밑과 같은 Logger와 BankAccout를 이어주는 중간 다리 역할을 하는 OptionalLogger를 만들어준다.  
```c++
struct OptionalLogger : Logger
{
    std::shared_ptr<Logger> impl;
    OptionalLogger(const std::shared_ptr<Logger> &logger)
        : impl(logger)
    {
    }
    void info(const std::string &s)
    {
        if (impl)
            impl->info(s);
    }
    void warning(const std::string &s)
    {
        if (impl)
            impl->warning(s);
    }
};
```
이제 null 포인터 검사는 BankAccout말고 해당 Logger에서 진행한다.  

BankAccout의 모습도 살짝 달라진다.  
```c++
struct BankAccount
{
    inline static std::shared_ptr<Logger> no_logging = {};

    std::shared_ptr<OptionalLogger> logger;
    std::string name;
    int balance = 0;

    BankAccount(const std::string &name, int balance, const std::shared_ptr<Logger> &logger = no_logging)
        : logger{std::make_shared<OptionalLogger>(logger)},
          name{name},
          balance{balance}
    {
    }

    // 동일 구현부 생략
};
```
정적 클래스 변수로 nullptr인 no_logging이 추가되었다.  
생성자에 Logger를 따로 지정해주지 않으면 no_logging이 기본으로 들어가게 된다.  
logger에 어떤 값이 채워지던 OptionalLogger가 대신 처리해주기 때문에 안전하다.  

활용은 밑과 같다.  
```c++
BankAccount ba_01{"tongstar's account", 100};
ba_01.deposit(200);

BankAccount ba_02{"tongstar's account", 100, std::make_shared<ConsoleLogger>()};
ba_02.deposit(200);
```
Logger를 넣지 않거나 유효하지 않은 녀석을 넣으면 OptionalLogger가 nullptr을 검사해 로깅 출력을 하지 않을 것이다.  
Logger를 넣으면 해당 Logger가 의도하는 그대로 작동한다.   
&nbsp;  

## 요약  

1. 포인터를 이용하는 모든 곳에 유효성 검사를 할 책임이 없다면 Null Object가 효과적인 대안이다.  

2. Null Object를 적극적으로 활용하고 싶다면 default 값으로 힌트를 주거나 주석을 달아 사용자가 명확히 알 수 있도록 해야 한다.  