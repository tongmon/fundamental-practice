# Singleton Pattern  

매우 유명하지만 미움도 많이 받는 싱글턴 패턴이다.  
애플리케이션 전체에서 객체가 단 하나만 존재해야 하는 상황을 처리하기 위해 탄생했다.  
간단한 예시부터 살펴보자.  
&nbsp;  

## 전역 객체로서의 싱글턴  

일단 싱글턴 패턴을 간단하게 밑과 같이 만들어보자.  
```c++
class Singleton
{
public:
    // !!! 해당 클래스는 단 한번만 생성해야 합니다. !!!
    Singleton() {}
    ~Singleton() {}    
};
```
생성자가 무방비하게 노출되어 있기에 허술하다.  
일단 협업 개발자가 주석에 있는 말을 무시하고 여러 개의 객체를 만들 수도 있다.  
&nbsp;  

좀 더 발전시켜 전역 객체를 만들어 사용한다면 어떨까?  
```c++
class Singleton
{
public:
    Singleton() {}
    ~Singleton() {}    
};

static Singleton singleton{};
```
일단 싱글톤 클래스 사용자들에게 전역 변수 객체가 있다는 것을 알아차리도록 따로 알려줘야 한다.   
그리고 **굉장히 위험한 부분**은 특정 전역 객체가 다른 전역 객체를 참조할 때다.  
전역 객체들의 초기화 순서는 무작위로 결정되기 때문에 이를 프로그래머가 통제하기는 굉장히 까다롭다.  
&nbsp;  

위에서 말한 두가지 문제를 해결한 코드는 밑과 같다.  
```c++
class Singleton
{ 
    Singleton() {}
    ~Singleton() {}

public:
    static Singleton &get()
    {
        static Singleton singleton;
        return singleton;
    }
};
```
사용자는 get() 함수만을 이용해 Singleton 객체에 접근할 수 있어 알아차리기 쉽다.  
get() 함수를 사용할 때 전역 Singleton 객체가 명시적으로 초기화되기에 적어도 생성 시점은 알 수 있다. (C++11 미만 버전에서는 static 변수에 대한 스레드 안정성이 보장이 안되기 때문에 mutex를 통한 코드가 추가적으로 필요하다.)  
&nbsp;  

## 전통적인 구현  

문제는 아직 남았다.  
Singleton 객체가 여러개 생성되는 것을 막지 않고 있다.  
```=``` 연산자로 복제도 가능하고 복사 생성자로 새로운 객체도 생성해줄 수 있다.  
&nbsp;  

여러 객체 생성을 막는 Singleton 클래스는 밑과 같다.  
```c++
class Singleton
{
    Singleton() {}
    ~Singleton() {}

public:
    static Singleton &get()
    {
        static Singleton singleton;
        return singleton;
    }

    Singleton(Singleton const &) = delete;
    Singleton(Singleton &&) = delete;
    Singleton &operator=(Singleton const &) = delete;
    Singleton &operator=(Singleton &&) = delete;
};
```
Singleton 클래스를 어떻게 사용하던 객체는 하나만 존재할 수 있다.  
&nbsp;  

완벽해보이지만... 문제가 하나 더 있다.  
굉장히 드문 경우긴 한데 특정 전역 객체의 소멸자에서 싱글턴 객체를 사용하는 경우 문제가 된다.  
예시를 통해 살펴보자.  
&nbsp;  

밑은 전역 객체의 소멸자에서 싱글톤을 이용하는 코드다.  
```c++
class Singleton
{
    Singleton() {}
    ~Singleton() {}

public:
    static Singleton &get()
    {
        static Singleton singleton;
        return singleton;
    }

    Singleton(Singleton const &) = delete;
    Singleton(Singleton &&) = delete;
    Singleton &operator=(Singleton const &) = delete;
    Singleton &operator=(Singleton &&) = delete;

    void print() { std::cout << "Called by Singleton!\n"; }
};

class StaticObj
{
public:
    StaticObj() {}
    ~StaticObj()
    {
        Singleton::get().print();
    }
};

static StaticObj obj;

int main()
{
    Singleton::get().print();
    return 0;
}
```
일단 main() 함수 종료 시점에서 데이터 영역에 들어가 있는 전역 변수, 정적 변수들을 정리할 것이다.  
이때 정적 변수의 소멸 시점은 프로그래머가 알 수가 없다...  
만약 정적 변수 소멸 시점에서 singleton이 먼저 소멸된 뒤 obj가 소멸된다면?  
StaticObj의 소멸자에서 singleton 변수를 참조하려는데 이미 singleton은 소멸이 되어서 참조 무효화 현상이 발생할 것이다.  
결국 의도한 print() 함수는 수행되지 못할 것이고 최악의 상황에서는 크래쉬가 발생할 수도 있다.  
&nbsp;  

## 포인터 싱글턴  

전역 객체를 사용하지 않고 대신 포인터에 객체를 할당하는 싱글턴 패턴이다.  
포인터를 사용하기 때문에 전역 객체와 다르게 소멸 시점을 프로그래머가 명확히 알 수 있지만 thread-safe 하지 않기에 이를 해결해주는 추가 로직이 붙는다.  
&nbsp;  

가장 간단하게 해결해주는 방법은 mutex 헤더에 있는 call_once 함수를 이용하는 것이다.  
C++에서 포인터를 이용하는 싱글턴 클래스는 아래와 같다.  
```c++
class Singleton
{
    static std::shared_ptr<Singleton> singleton;
    static std::once_flag once;
    Singleton() {}

public:
    static Singleton &get()
    {
        std::call_once(once, []()
                       { singleton = std::shared_ptr<Singleton>(new Singleton()); });

        return *singleton;
    }

    ~Singleton() {}
    Singleton(Singleton const &) = delete;
    Singleton(Singleton &&) = delete;
    Singleton &operator=(Singleton const &) = delete;
    Singleton &operator=(Singleton &&) = delete;
};

std::shared_ptr<Singleton> Singleton::singleton;
std::once_flag Singleton::once;
```
만약 해당 싱글턴 클래스를 .h, .cpp로 분리시켜서 사용할 것이라면 헤더 파일이 아니라 소스 파일에서 ```std::shared_ptr<Singleton> Singleton::singleton; std::once_flag Singleton::once;```를 진행해줘야 한다.  
once_flag와 call_once를 이용해서 포인터 방식의 싱글턴 클래스를 thread-safe하게 만들어주고 있다.  
문제는 소멸자가 싱클턴 클래스 사용자들에게 공개되어 있다는 것이다.  
소멸자를 숨기면 스마트 포인터의 Deleter가 싱글턴 객체의 소멸자에 접근할 수 없어 컴파일이 안된다.  
소멸자를 없애면 포인터 할당 해제를 OS에게 맡겨버리게 된다.  
물론 싱글턴 객체는 애플리케이션 시작과 끝을 모두 함께하기에 따로 할당 해제를 해주지 않아도 운영체제가 알아서 힙 메모리 영역을 정리해주긴 할 것이다. (단순한 Embedded OS에서는 아닌 경우도 있다.)  
이렇게 되면 싱글턴 객체 소멸 순서를 프로그래머가 알지못하기 때문에 전역 객체를 사용하는 싱글턴을 사용하는 것과 다를 것이 없다.  
&nbsp;  

소멸자를 숨기기 위해서는 사용자 정의 Deleter를 구현해주면 된다.  
밑은 소멸자를 숨긴 싱글턴 클래스이다.  
```c++
class Singleton
{
    struct Deleter
    {
        void operator()(Singleton *ptr) { delete ptr; }
    };
    friend Deleter;

    static std::shared_ptr<Singleton> singleton;
    static std::once_flag once;

    Singleton() {}
    ~Singleton() {}

public:
    static Singleton &get()
    {
        std::call_once(once, []()
                       { singleton = std::shared_ptr<Singleton>(new Singleton(), Deleter{}); });

        return *singleton;
    }

    Singleton(Singleton const &) = delete;
    Singleton(Singleton &&) = delete;
    Singleton &operator=(Singleton const &) = delete;
    Singleton &operator=(Singleton &&) = delete;
};

std::shared_ptr<Singleton> Singleton::singleton;
std::once_flag Singleton::once;
```
이렇게 하면 프로그래머는 사용자들에게 소멸자는 숨기면서 싱글턴 객체의 소멸 시점을 명확히 파악할 수 있다.  
이러한 포인터 싱글턴 방식은 객체의 생성, 소멸 시점이 명확하게 파악되어 완벽하다.  
근데 이를 사용하는 프로그래머가 사람인지라 완벽하지 않다...  
만약 특정 포인터 싱글턴 객체의 소멸자에서 다른 포인터 싱글턴 객체를 이용한다면 소멸 순서가 꼬여 null pointer 문제가 발생할 수 있다.   
물론 전역 객체 싱글턴의 문제처럼 프로그래머가 통제를 할 수 없는 수준은 아니지만 각기 다른 싱글턴 클래스의 get() 함수 사용 순서를 프로그래머가 추적하는 것은 매우 까다롭다.  
&nbsp;  

## 피닉스 싱글턴  

전역 싱글턴과 포인터 싱글턴 모두 대부분의 문제는 해결했지만 싱글턴 객체의 소멸 순서가 꼬여 발생하는 문제는 해결하지 못했다.  
피닉스 싱글턴에서는 소멸 순서가 꼬이더라도 죽은 싱글턴 객체가 호출되면 다시 되살리는 방식으로 해당 문제를 해결한다.  
&nbsp;  

피닉스 싱글턴은 싱글턴 객체가 소멸된 후에 다시 생성해야 하기 때문에 동적 할당을 사용한다.    
밑은 shared_ptr을 사용한 피닉스 싱글턴 예시이다.  
```c++
class Singleton
{
    struct Deleter
    {
        void operator()(Singleton *ptr)
        {
            delete ptr;
            singleton = nullptr;
        }
    };
    friend Deleter;

    static std::shared_ptr<Singleton> singleton;
    static std::mutex mut;

    Singleton() {}
    ~Singleton() {}

public:
    static Singleton &get()
    {
        if (!std::atomic_load(&singleton))
        {
            std::lock_guard<std::mutex> lock(mut);
            if (!std::atomic_load(&singleton))
                std::atomic_store(&singleton, std::shared_ptr<Singleton>(new Singleton(), Deleter{}));
        }
        return *singleton;
    }

    Singleton(Singleton const &) = delete;
    Singleton(Singleton &&) = delete;
    Singleton &operator=(Singleton const &) = delete;
    Singleton &operator=(Singleton &&) = delete;
};

std::shared_ptr<Singleton> Singleton::singleton;
std::mutex Singleton::mut;
```
lock_guard를 사용하여 프로세스 전체에서 객체가 단 하나만 존재하도록 해준다.  
&nbsp;  

밑은 unique_ptr을 사용한 피닉스 싱글턴 예시이다.  
```c++
class Singleton
{
    friend std::unique_ptr<Singleton>::deleter_type;

    static std::unique_ptr<Singleton> singleton;
    static std::mutex mut;

    Singleton() {}
    ~Singleton() { singleton.release(); }

public:
    static Singleton &get()
    {
        if (!singleton.get())
        {
            std::lock_guard<std::mutex> lock(mut);
            if (!singleton.get())
                singleton.reset(new Singleton());
        }
        return *singleton;
    }

    Singleton(Singleton const &) = delete;
    Singleton(Singleton &&) = delete;
    Singleton &operator=(Singleton const &) = delete;
    Singleton &operator=(Singleton &&) = delete;
};

std::unique_ptr<Singleton> Singleton::singleton;
std::mutex Singleton::mut;
```



## 싱글턴 단위 테스트  

특정 싱글턴 클래스에서 다른 싱클턴 클래스를 사용할 때 단위 테스트가 껄끄럽다.
예시를 들면서 설명할 것인데 단위 테스트는 Catch2 라이브러리를 사용한다. (Catch2 사용법은 따로 설명하지 않는다.)  
&nbsp;  

인구수를 반환하는 PeopleData 인터페이스가 밑과 같이 존재한다.  
```c++
class PeopleData
{
public:
    virtual unsigned int get_population(const std::string &country_name) = 0;
};
```
&nbsp;  

PeopleData 인터페이스를 상속하는 싱글턴 클래스가 밑과 같이 존재한다.  
```c++
class SingletonPeopleData : public PeopleData
{
    SingletonPeopleData() {}
    std::unordered_map<std::string, unsigned int> countries;

public:
    static SingletonPeopleData &get()
    {
        static SingletonPeopleData singleton;
        return singleton;
    }
    SingletonPeopleData(Singleton const &) = delete;
    SingletonPeopleData(Singleton &&) = delete;
    SingletonPeopleData &operator=(Singleton const &) = delete;
    SingletonPeopleData &operator=(Singleton &&) = delete;

    unsigned int get_population(const std::string &country_name)
    {
        return countries[country_name];
    }
};
```
특정 나라의 인구수를 획득하는 get_population 함수를 정의하였다.  
&nbsp;  

SingletonPeopleData 싱글턴 클래스를 사용하는 SingletonRecordFinder 클래스는 밑과 같다.  
```c++
class SingletonRecordFinder
{
    SingletonRecordFinder() {}

public:
    static SingletonRecordFinder &get()
    {
        static SingletonRecordFinder singleton;
        return singleton;
    }
    SingletonRecordFinder(SingletonRecordFinder const &) = delete;
    SingletonRecordFinder(SingletonRecordFinder &&) = delete;
    SingletonRecordFinder &operator=(SingletonRecordFinder const &) = delete;
    SingletonRecordFinder &operator=(SingletonRecordFinder &&) = delete;

    unsigned int total_population(const std::vector<std::string> &countries)
    {
        unsigned int result = 0;
        for (const auto &country_name : countries)
            result += SingletonPeopleData::get().get_population(country_name);
        return result;
    }
};
```
해당 클래스도 싱글턴 패턴을 이용했다.  
싱글턴에서 다른 싱글턴을 참조하는 상황이 발생했다.  
테스트를 안하고 사용할 때는 문제가 없을 것이다.  
만약 단위 테스트를 해야하는 경우가 생긴다면 어떨까?  
&nbsp;  

Korea에는 17000, Mexico에는 23000 인구수가 저장되어 있다고 해보자.  
밑과 같이 Catch2를 이용해 단위 테스트를 진행해보자.  
```c++
TEST_CASE("Total Population Computation...", "[total_population]") {
    REQUIRE(SingletonRecordFinder::get().total_population({"Korea", "Mexico"}) == (17000 + 23000));
}
```
문제는 SingletonPeopleData 싱글턴 클래스의 멤버 변수인 countries 값들을 데이터베이스에서 끌어오는 경우이다.  
데이터베이스에 저장된 국가별 인구수가 변경될 때마다 테스트 코드도 그에 따라 바뀌어야 한다.  
이러한 소모적인 행위를 어떻게 해결해야 할까?  

&nbsp;  

이를 해결하기 위한 여러 방법이 존재하겠지만 싱글턴에서 싱글턴을 참조하고 있는 관계를 끊어주는 것이 제일 쉽고 명확하다.  
SingletonRecordFinder 클래스를 밑과 같이 수정해준다.  
```c++
class SingletonRecordFinder
{
    PeopleData *peopledata = nullptr;
    SingletonRecordFinder() {}

public:
    static SingletonRecordFinder &get(PeopleData *peopledata = nullptr)
    {
        static SingletonRecordFinder singleton;
        singleton.peopledata = peopledata;
        return singleton;
    }
    SingletonRecordFinder(SingletonRecordFinder const &) = delete;
    SingletonRecordFinder(SingletonRecordFinder &&) = delete;
    SingletonRecordFinder &operator=(SingletonRecordFinder const &) = delete;
    SingletonRecordFinder &operator=(SingletonRecordFinder &&) = delete;

    unsigned int total_population(const std::vector<std::string> &countries)
    {
        unsigned int result = 0;

        if (peopledata)
            for (const auto &country_name : countries)
                result += peopledata->get_population(country_name);
        else
            for (const auto &country_name : countries)
                result += SingletonPeopleData::get().get_population(country_name);

        return result;
    }
};
```
일단 get() 함수에서 PeopleData 포인터를 인자로 받을 수가 있다.  
멤버 변수 peopledata 포인터 유무에 따라서 total_population 방식이 유동적으로 변한다.  
이렇게 바꾼 이유는 더미 데이터를 만들어 테스트에 사용하기 위함이다.  
&nbsp;  

밑과 같이 PeopleData를 상속하는 더미 데이터를 만들자.  
```c++
class DummyPeopleData : public PeopleData
{
    std::unordered_map<std::string, unsigned int> countries;

public:
    DummyPeopleData()
    {
        countries["Korea"] = 17000;
        countries["America"] = 89000;
    }

    unsigned int get_population(const std::string &country_name)
    {
        return countries[country_name];
    }
};
```
이제 해당 더미 데이터를 프로그래머가 임의로 수정해주면서 편하게 테스트를 진행할 수가 있다.  
&nbsp;  

밑은 실제 테스트가 진행되는 코드이다.  
```c++
static DummyPeopleData dummy;

TEST_CASE("Total Population Computation...", "[total_population]") {
    REQUIRE(SingletonRecordFinder::get(&dummy).total_population({"Korea", "America"}) == (17000 + 89000));
}
```
dummy 데이터를 사용해서 싱글턴에서 싱글턴을 참조하고 있는 관계를 끊어주니 데이터베이스에 저장된 값이 어떻게 바뀌던 테스트 코드는 바뀔 일이 없다.  
이렇게 되면 테스트 코드는 total_population 로직에 이상이 있는지 없는지에 집중할 수 있다.  
&nbsp;  

## 싱글턴과 제어 역전  

