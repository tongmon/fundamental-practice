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
struct BanckAccount
{
    std::shared_ptr<Logger> logger;
    std::string name;
    int balance = 0;

    BanckAccount(const std::shared_ptr<Logger> &logger, const std::string &name, int balance)
        : logger{logger}, name{name}, balance{balance}
    {
    }

    void deposit(int amount)
    {
        balance += amount;
        logger->info("Deposited $" + std::to_string(amount) + "to " + name + ", balance is now $" + std::to_string(balance));
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
struct BanckAccount
{
    // 동일 구현부 생략

    BanckAccount(const std::shared_ptr<Logger> &logger, const std::string &name, int balance)
        : name{name}, balance{balance}
    {
        this->logger = logger ? logger : nullptr;
    }

    void deposit(int amount)
    {
        balance += amount;

        if (logger)
            logger->info("Deposited $" + std::to_string(amount) + "to " + name + ", balance is now $" + std::to_string(balance));
    }
};
```
하지만 logger를 nullptr로 넘기는 방식은 위험하고 번거롭다.  
당장 deposit() 함수만 봐도 logger의 null 유무를 따져야 하는데 클래스 멤버가 굉장히 많다면?  
수정할 부분과 생각할 것이 많아진다.  

밑과 같이 ```std::optional```을 이용할 수도 있다.  
```c++
struct BanckAccount
{
    // 동일 구현부 생략

    std::optional<std::shared_ptr<Logger>> logger;

    BanckAccount(const std::shared_ptr<Logger> &logger, const std::string &name, int balance)
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
            logger.value()->info("Deposited $" + std::to_string(amount) + "to " + name + ", balance is now $" + std::to_string(balance));
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

&nbsp;  

