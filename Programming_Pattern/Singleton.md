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
협업 개발자가 주석에 있는 말을 무시하고 여러 개의 객체를 만들 수도 있다.  
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
발전했지만 아직 여러 문제가 남아있는데 그 중 두가지만 먼저 살펴보자.  
1. 사용자들은 전역 객체 singleton이 존재하는지 알기 어렵다.  

2. 전역 객체의 초기화 시점은 무작위로 결정되기에 프로그래머가 통제할 수 없다.  

첫번째 문제는 작아보이지만 전역 객체 singleton의 존재를 사용자가 모르고 Singleton 객체를 여러개 생성해버린다면... 의도에도 맞지않고 비효율적이다.  
두번째 문제는 특정 전역 객체의 생성자에서 전역 객체 singleton을 사용할 때 무슨 일이 일어날지 프로그래머는 예측할 수 없기에 굉장히 위험하다.  
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
get() 함수를 사용할 때 전역 Singleton 객체가 명시적으로 초기화되기에 적어도 생성 시점은 알 수 있다. (C++11 미만 버전에서는 static 변수에 대한 스레드 안정성 보장이 안되기 때문에 mutex를 통한 코드가 추가적으로 필요하다.)  
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
    char* str;

    Singleton() { str = new char[100]{"Hello World"}; }
    ~Singleton() { delete str; }

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

    void print() { std::cout << "Called by Singleton! Str: " << str << "\n"; }
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
프로그램이 돌아가는 순서를 한번 분석해보자.  
1. StaticObj 자료형인 전역 변수 obj가 초기화된다.  
   
2. main() 함수에서 호출한 Singleton::get().print() 함수에 의해 지역적으로 선언된 전역 변수 singleton이 초기화되면서 ```Called by Singleton! Str: Hello World\n```가 출력된다.  

3. main() 함수가 종료되면서 전역 변수들을 정리하는데 초기화의 역순으로 정리되기에 singleton이 소멸된 후 obj가 소멸된다.  

4. obj가 소멸될 때 소멸자가 호출되며 singleton 객체를 사용하는데 문제는 singleton은 이미 소멸되었기에 Singleton 객체의 print() 함수가 호출되어도 정상적인 내용은 출력되지 않는다.  

이를 해결하려면 소멸된 객체를 되살려줘야 하는데... 정적인 전역 변수로는 해결할 수 없고 포인터와 동적 할당을 이용해야 한다.  
이에 대한 세부적인 구현은 피닉스 싱글턴 패턴 항목에서 알아보자.  
&nbsp;  

## 포인터 싱글턴  

전역 객체를 사용하지 않고 전역 포인터에 객체를 동적 할당하는 싱글턴 패턴이다.  
포인터를 사용하기에 thread-safe를 보장하기 위한 추가 로직이 붙는다.  
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

std::shared_ptr<Singleton> Singleton::singleton = nullptr;
std::once_flag Singleton::once;
```
만약 해당 싱글턴 클래스를 .h, .cpp로 분리시켜서 사용할 것이라면 헤더 파일이 아니라 소스 파일에서 ```std::shared_ptr<Singleton> Singleton::singleton; std::once_flag Singleton::once;```를 진행해줘야 한다.  
once_flag와 call_once를 이용해서 포인터 방식의 싱글턴 클래스를 thread-safe하게 만들어주고 있다.  
문제는 소멸자가 싱클턴 클래스 사용자들에게 공개되어 있다는 것이다.  
소멸자를 숨기면 스마트 포인터의 Deleter가 싱글턴 객체의 소멸자에 접근할 수 없어 컴파일이 안된다.  
소멸자를 없애면 포인터 할당 해제를 OS에게 맡겨버리게 된다.  
물론 싱글턴 객체는 애플리케이션 시작과 끝을 모두 함께하기에 따로 할당 해제를 해주지 않아도 운영체제가 알아서 힙 메모리 영역을 정리해주긴 할 것이다. (단순한 Embedded OS에서는 아닌 경우도 있다.)  
&nbsp;  

소멸자를 숨기기 위해서는 사용자 정의 Deleter를 구현해주고 이를 friend 처리하면 된다.  
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

std::shared_ptr<Singleton> Singleton::singleton = nullptr;
std::once_flag Singleton::once;
```
소멸자를 숨겨 사용자가 싱글턴 클래스를 올바르게 사용하도록 유도했다.  
정적 객체를 이용한 싱글턴과 다른 점이라면 ```std::shared_ptr<Singleton> Singleton::singleton = nullptr;``` 요렇게 전역 포인터가 밖으로 나와있다는 것이다.  
포인터를 이용한 동적 할당을 통해 초기화 시점은 알 수 있지만 전역 포인터를 사용했기에 소멸 시점은 제어할 수 없다...  
결국 정적 객체를 이용한 싱글턴의 단점은 포인터를 이용한 싱글턴에서도 해결하지 못했다.  
&nbsp;  

## 피닉스 싱글턴  

전역 객체 싱글턴과 포인터 싱글턴 모두 대부분의 문제는 해결했지만 전역 객체의 소멸자에서 싱글턴이 사용될 때 소멸 순서가 꼬여 발생하는 문제는 해결하지 못했다.  
피닉스 싱글턴에서는 소멸 순서가 꼬이더라도 죽은 싱글턴 객체가 호출되면 다시 되살리는 방식으로 해당 문제를 해결한다.  
&nbsp;  

피닉스 싱글턴은 싱글턴 객체가 소멸된 후에 다시 생성해야 하기에 포인터를 사용한다.    
밑은 C++17 이하에서 작동하는 피닉스 싱글턴 예시이다.  
```c++
class Singleton
{
    struct Deleter
    {
        void operator()(Singleton *ptr)
        {
            delete ptr;
            singleton.reset();
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

std::shared_ptr<Singleton> Singleton::singleton = nullptr;
std::mutex Singleton::mut;
```
C++20에서 atomic_load, atomic_store 등이 Deprecated 처리되었기에 위 코드는 작동하지 않는다.  
&nbsp;  

대신 ```std::atomic<std::shared_ptr<Type>>```을 지원한다.  
밑은 C++20 이상에서 작동하는 피닉스 싱글턴 패턴이다.  
```c++
class Singleton
{
    struct Deleter
    {
        void operator()(Singleton *ptr)
        {
            delete ptr;
            singleton.store(nullptr);
        }
    };
    friend Deleter;

    static inline std::atomic<std::shared_ptr<Singleton>> singleton = nullptr;
    static inline std::mutex mut;

    Singleton() {}
    ~Singleton() {}

public:
    static Singleton &get()
    {
        if (!singleton.load())
        {
            std::lock_guard<std::mutex> lock(mut);
            if (!singleton.load())
                singleton.store(std::shared_ptr<Singleton>(new Singleton(), Deleter{}));
        }
        return *singleton.load();
    }

    Singleton(Singleton const &) = delete;
    Singleton(Singleton &&) = delete;
    Singleton &operator=(Singleton const &) = delete;
    Singleton &operator=(Singleton &&) = delete;
};
```
C++17 이하에서 작동하는 피닉스 싱글턴 코드를 기준으로 설명하겠다.  
구현이 어려워보이는 이유는 thread-safe하게 만들기 위해 atomic과 mutex를 사용했기 때문이다.  
그런 부분들을 제외하고 중요한 점은 Deleter에서 singleton 포인터를 nullptr로 만들어 주는 ```singleton.reset()```이 추가되었다는 점이다.  
이 때문에 singleton 객체가 해제되었는지를 nullptr 유무를 통해 확인할 수 있다.  
get() 함수가 호출될 때 처음 객체를 생성하거나 객체가 소멸된 상태라면 singleton이 nullptr이기 때문에 동적 할당으로 객체가 새로 생성된다.  
따라서 다른 전역 객체의 생성자, 소멸자 어디든지 피닉스 싱글턴을 사용하면 싱글턴 객체가 죽어있는 경우가 없다.  
&nbsp;  

이러한 피닉스 싱글턴도 단점이 있다.  
**첫번째**는 다른 전역 객체의 소멸자에 피닉스 싱글턴을 사용한 경우 피닉스 싱글턴이 되살린 객체에 대한 소멸자는 따로 호출되지 않아서 힙 영역에 할당된 싱글턴 객체에 대한 할당 해제는 운영체제가 해줘야 한다는 것이다.  
전에 설명했듯이 대부분의 운영체제에서는 프로세스가 종료되면 그 프로세스에 딸려있던 힙 메모리도 정리하기에 특정 Embedded OS가 아닌이상 문제가 되지 않는다.  
**두번째**는 되살린 싱글턴 객체는 모든 값이 초기화되기에 예전 싱글턴 객체에 저장해놓던 값을 다시 이용하지 못한다는 것이다.  
이는 프로그래머가 유의하여 로직을 구현하면 충분히 피해갈 수 있는 문제다.  
이러한 문제는 모두 전역 객체의 소멸 시점을 프로그래머가 통제할 수 없기 때문에 발생된 것이라 이를 해결하기 위해서는 프로그래머가 싱글턴 객체의 생명주기를 직접 관리하는 IoC 컨테이너 로직을 따로 구현하던지 전역 객체의 사용을 최소화하던지 하는 방향으로 나아가야 할 것이다.  
&nbsp;  

## 범용적인 싱글턴  

싱글턴을 좀 더 generic하게 만들어보자.  
밑에서 소개할 범용적인 싱글턴들은 전역 멤버 변수를 inline으로 초기화하기에 C++17 이상부터 사용가능하다. (C++20 이상에서 사용하려면 atomic_load, atomic_store에 대한 수정이 이뤄져야 한다.)  
&nbsp;  

밑은 CRTP 기법을 이용한 템플릿 싱글턴이다.  
```c++
template <typename T>
class Singleton
{
    static inline std::shared_ptr<T> singleton = nullptr;
    static inline std::mutex mut;

    struct Deleter
    {
        void operator()(T *ptr)
        {
            delete ptr;
            singleton.reset();
        }
    };
    friend Deleter;

protected:
    Singleton() {}
    ~Singleton() {}

public:
    static T &get()
    {
        if (!std::atomic_load(&singleton))
        {
            std::lock_guard<std::mutex> lock(mut);
            if (!std::atomic_load(&singleton))
                std::atomic_store(&singleton, std::shared_ptr<T>(new T(), Deleter{}));
        }
        return *singleton;
    }

    Singleton(Singleton const &) = delete;
    Singleton(Singleton &&) = delete;
    Singleton &operator=(Singleton const &) = delete;
    Singleton &operator=(Singleton &&) = delete;
};
```
해당 클래스를 상속한 클래스는 싱글턴 역할을 수행하게 된다.  
&nbsp;  

사용법은 밑과 같다.  
```c++
class SomeObj : public Singleton<SomeObj>
{
    friend Singleton;

    SomeObj() { /* 생성자 로직 */ }
    ~SomeObj() { /* 소멸자 로직 */ }

public:
    // 각종 필요한 로직
};
```
중요한 점은 Singleton 클래스를 친구 클래스로 등록해줘야 private에 존재하는 SomeObj의 생성자와 소멸자를 Singleton 클래스에서 활용할 수 있게 되어 정상적인 빌드가 가능하다.  
&nbsp;  

매크로를 이용한 싱글턴 사용법도 알아보자.  
```c++
#define DELARE_SINGLETON(type)                                                               \
public:                                                                                      \
    static type &get()                                                                       \
    {                                                                                        \
        if (!std::atomic_load(&singleton))                                                   \
        {                                                                                    \
            std::lock_guard<std::mutex> lock(mut);                                           \
            if (!std::atomic_load(&singleton))                                               \
                std::atomic_store(&singleton, std::shared_ptr<type>(new type(), Deleter{})); \
        }                                                                                    \
        return *singleton;                                                                   \
    }                                                                                        \
    type(type const &) = delete;                                                             \
    type(type &&) = delete;                                                                  \
    type &operator=(type const &) = delete;                                                  \
    type &operator=(type &&) = delete;                                                       \
                                                                                             \
private:                                                                                     \
    static inline std::shared_ptr<type> singleton = nullptr;                                 \
    static inline std::mutex mut;                                                            \
    struct Deleter                                                                           \
    {                                                                                        \
        void operator()(type *ptr)                                                           \
        {                                                                                    \
            delete ptr;                                                                      \
            singleton.reset();                                                               \
        }                                                                                    \
    };                                                                                       \
    friend Deleter;
```
&nbsp;  

실제 사용법은 밑과 같다.  
```c++
class SomeObj
{
    DELARE_SINGLETON(SomeObj)

    SomeObj() { /* 생성자 로직 */ }
    ~SomeObj() { /* 소멸자 로직 */ }

public:
    // 각종 필요한 로직
};
```
DELARE_SINGLETON 매크로를 클래스 내부에 선언해주면 된다.  
확장성이나 유연성 모두 템플릿 싱글턴이 우세하기 때문에 왠만하면 매그로를 활용하기 보다는 상속을 이용한 템플릿 싱글턴을 사용하자.  
&nbsp;  

## 싱글턴 단위 테스트  

싱글턴 클래스가 이용된 모듈들은 싱글턴 클래스와 의존성이 강해지기에 단위 테스트 코드를 구현하기 번거로워진다.  
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
    SingletonPeopleData(SingletonPeopleData const &) = delete;
    SingletonPeopleData(SingletonPeopleData &&) = delete;
    SingletonPeopleData &operator=(SingletonPeopleData const &) = delete;
    SingletonPeopleData &operator=(SingletonPeopleData &&) = delete;

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

이를 해결하기 위한 여러 방법이 존재하겠지만 싱글턴에서 싱글턴을 참조하고 있는 관계를 느슨하게 만드는 것이 제일 쉽고 명확하다.  
SingletonRecordFinder 클래스를 밑과 같이 수정해준다.  
```c++
class SingletonRecordFinder
{
    PeopleData *peopledata = nullptr;
    SingletonRecordFinder() {}

public:
    static SingletonRecordFinder &get(PeopleData *peopledata)
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
        for (const auto &country_name : countries)
            result += peopledata->get_population(country_name);
        return result;
    }
};
```
일단 get() 함수에서 PeopleData 포인터를 인자로 받을 수가 있다.  
멤버 변수 peopledata 포인터 값에 따라서 total_population 방식이 유동적으로 변한다.  
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
dummy 데이터를 사용해서 싱글턴에서 싱글턴을 참조하고 있는 관계를 약화시키니 데이터베이스에 저장된 값이 어떻게 바뀌던 테스트 코드는 바뀔 일이 없다.  
이렇게 되면 테스트 코드는 total_population 로직에 이상이 있는지 없는지에 집중할 수 있다.  
&nbsp;  

## 의존성 주입  

싱글턴 패턴을 잘 사용하면 많은 생산성이 올라가지만 사용할 수록 종속성이 깊어진다는 문제가 있다.  
[싱글턴 단위 테스트](#싱글턴-단위-테스트) 목차에서 싱글턴과 싱글턴 사이의 의존성을 느슨하게는 해주어 해당 문제를 해결하였다.  
여기서 더 나아가 의존성 주입 프레임워크를 사용해 싱글턴을 직접 구현하지 않지만 테스트 기능은 [싱글턴 단위 테스트](#싱글턴-단위-테스트) 목차의 것과 동일한 코드를 구현해보자.  
의존성 주입 프레임워크는 https://github.com/boost-ext/di 라이브러리를 이용한다.  
자세한 설명은 https://boost-ext.github.io/di/user_guide.html 링크에 모두 쓰여있으니 Boost.DI를 깊게 사용해보고 싶다면 참고하자.  
&nbsp;  

먼저 Boost.DI를 간단히 사용해보며 의존성 주입이 무엇인지에 대해 알아보자.  
밑과 같이 간단한 인터페이스가 있다.  
```c++
struct ILogger
{
    virtual void log(const std::string &s) = 0;
};
```
&nbsp;  

ILogger를 사용하는 두 클래스가 있다.  
```c++
class Warning : public ILogger
{
public:
    void log(const std::string &s) override
    {
        std::cout << "WARNING: " << s.c_str() << std::endl;
    }
};

class Fatal : public ILogger
{
public:
    void log(const std::string &s) override
    {
        std::cout << "FATAL: " << s.c_str() << std::endl;
    }
};
```
&nbsp;  

ILogger를 멤버 변수로 갖는 클래스가 밑과 같이 존재한다.  
```c++
class Logger
{
    ILogger &logger;

public:
    Logger(ILogger &logger) : logger(logger) {}
    void print(const std::string &s) { logger.log(s); }
};
```
Logger는 어떤 종류의 ILogger를 생성자에 넘겨 받느냐에 따라 print() 함수의 작동 방식이 달라진다.  
예를 들어 경고 로그를 찍고 싶다면 ```Warning warning_log; Logger logger(warning_log);``` 이렇게 해줘야 한다.  
&nbsp;  

Boost.DI에서는 생성자를 직접 호출하지 않고 밑과 같이 의존성 주입을 통해 객체를 생성한다.  
```c++
auto injector = boost::di::make_injector(boost::di::bind<ILogger>().to<Warning>());
```
만약 경로 로그 대신에 치명적 오류 로그를 Logger에 주입하고 싶다면 ```.to<Warning>()``` 부분은 ```.to<Fatal>()```로 변경하면 된다.  
Boost.DI에서는 사용된 자료형에 따라 객체의 생명주기가 달라진다.  
지금 Logger의 logger 멤버 변수는 ```ILogger &``` 자료형이라 Boost.DI는 해당 멤버 변수에 주입되는 객체를 싱글턴으로 생성한다.  
이렇게 생성된 싱글턴 객체의 생명주기는 Boost.DI가 어플리케이션 시작부터 끝까지 관리하게 된다. (```std::shared_ptr<ILogger>```도 싱글턴 객체를 생성한다.)   
멤버 변수 자료형에 참조나 포인터가 쓰이지 않았다면 Boost.DI는 객체를 복사 생성하여 해당 변수에 주입해준다.  
&nbsp;  

이는 주입기로 객체를 획득할 때도 마찬가지다.  
```c++
injector.create<Logger>();
injector.create<Logger &>();
```
```create<Logger>```는 복사 생성된 Logger 객체가 반환된다.  
```create<Logger&>```는 싱글턴 Logger 객체가 반환된다.  
&nbsp;  

만약 생성자 파라메터가 여럿이면 밑과 같이 대처한다.  
```c++
class Logger
{
    ILogger &logger;
    int start_line = 0;

public:
    Logger(ILogger &logger, int start_line) : logger(logger), start_line(start_line) {}
    void print(const std::string &s)
    {
        std::cout << start_line++ << ": ";
        logger.log(s);
    }
};

auto injector = boost::di::make_injector(boost::di::bind<ILogger>().to<Warning>(),
                                         boost::di::bind<int>().to(0));
```
주입기를 생성할 때 ```boost::di::bind<int>().to(0)```를 추가해서 넘겨주었다.  
이러면 start_line 멤버 변수가 0으로 초기화된다.  
&nbsp;  

만약 ILogger를 상속하는 클래스도 멤버 변수가 있다면 밑과 같이 Annotation을 사용해 대처한다.  
```c++
auto w_cnt = [] {};
class Warning : public ILogger
{
    int warning_cnt = 0;

public:
    BOOST_DI_INJECT(Warning, (named = w_cnt) int cnt) : warning_cnt(cnt) {}
    void log(const std::string &s) override
    {
        std::cout << "WARNING: " << s.c_str() << "/ Warning Counter: " << warning_cnt++ << std::endl;
    }
};

auto f_cnt = [] {};
class Fatal : public ILogger
{
    int fatal_cnt = 0;

public:
    BOOST_DI_INJECT(Fatal, (named = f_cnt) int cnt) : fatal_cnt(cnt) {}
    void log(const std::string &s) override
    {
        std::cout << "FATAL: " << s.c_str() << "/ Fatal Counter: " << fatal_cnt++ << std::endl;
    }
};

// Logger 정의부 생략

auto injector = boost::di::make_injector(boost::di::bind<int>().named(w_cnt).to(0),
                                         boost::di::bind<ILogger>().to<Warning>(),
                                         boost::di::bind<int>().to(0));
```
의존성 주입을 할 때 사용할 생성자를 ```BOOST_DI_INJECT()``` 매크로를 이용해 정의해준다.  
주입기를 만들 때 ```boost::di::bind<int>().named(w_cnt).to(0)```를 추가하여 w_cnt 별명이 붙은 생성자 인자에 해당 값을 넘겨준다.  
&nbsp;  

Boost.DI를 이용하기 위해 SingletonPeopleData, SingletonRecordFinder 클래스를 밑과 같이 변경해보자.  
```c++
class SingletonPeopleData : public PeopleData
{
    std::unordered_map<std::string, unsigned int> countries;

public:
    SingletonPeopleData() {}

    unsigned int get_population(const std::string &country_name)
    {
        return countries[country_name];
    }
};

class SingletonRecordFinder
{
    std::shared_ptr<PeopleData> peopledata = nullptr;

public:
    SingletonRecordFinder(std::shared_ptr<PeopleData> peopledata = nullptr)
    {
        this->peopledata = peopledata;
    }

    unsigned int total_population(const std::vector<std::string> &countries)
    {
        unsigned int result = 0;
        for (const auto &country_name : countries)
            result += peopledata->get_population(country_name);
        return result;
    }
};
```
싱글턴을 갖추기 위한 구현부를 전부 날렸다.  
멤버 변수 peopledata가 shared_ptr 자료형이기 때문에 Boost.DI는 싱글턴 객체를 생성해 해당 변수에 주입할 것이다.  
&nbsp;  

Boost.DI를 사용한 테스트 코드는 밑과 같다.  
```c++
auto injector = boost::di::make_injector(boost::di::bind<PeopleData>().to<DummyPeopleData>());

TEST_CASE("Total Population Computation...", "[total_population]") {
    REQUIRE(injector.create<SingletonRecordFinder &>().total_population({"Korea", "America"}) == (17000 + 89000));
}
```
만약 더미 데이터 말고 실제 사용하는 데이터로 테스트하고 싶다면 ```.to<DummyPeopleData>()```를 ```.to<SingletonPeopleData>()```로 바꾸면 된다.  
이렇게 Boost.DI와 같은 의존성 주입 라이브러리를 이용하면 따로 싱글턴 패턴을 구현하지 않아도 동일한 기능을 사용할 수 있다.  
&nbsp;  

## 모노스테이트  

싱글턴 패턴의 변형인 모노스테이트에 대해 알아보자.  
&nbsp;  

밑과 같은 녀석을 모노스테이트라고 한다.  
```c++
class Monostate
{
    static int m_state;

public:
    const int &state() const { return m_state; }
    int &state() { return m_state; }
};
```
싱글턴은 아닌데 멤버 변수 state가 정적 클래스 멤버 변수라 Monostate를 상속한 녀석이던 새로 생성된 Monostate던 모두 같은 녀석을 가리키고 있어 마치 싱글턴과 같은 효과가 발생한다.  
&nbsp;  

모노스테이트는 장단점이 확실하기에 해당 내용만 정리하고 넘어간다.  

**장점**

1. 상속이 쉬워 다형성을 활용하기 좋다.  

2. 이미 존재하는 객체를 다시 활용하기 좋다.  
   별다른 코드 없이 모노스테이트를 상속하거나 새로 생성하면 이미 존재하는 객체를 활용할 수 있다.  

3. 정적 변수이기에 대부분의 경우에서 적절한 생존주기를 유지한다.  

**단점**

1. getter / setter 를 통해서만 멤버 변수 접근이 가능하다.  

2. 정적 변수라 어느 정도의 메모리를 차지하고 있다.  

3. 상속이나 객체 생성을 통해 이용되기에 의존성이 커진다.  

4. 일반 객체를 모노스테이트로 변환하는 것은 어렵다.  
&nbsp;  

## 요약  

1. 싱글턴 패턴을 사용할 때 테스트와 리펙터링 용이성을 해치지만 않는다면 괜찮다.  

2. ```Singleton::get().do_something()```과 같은 직접적인 호출로 싱글턴을 사용하는 것은 피하자.  

3. 싱글턴 패턴을 꼭 사용해야 한다면 생성자 인자로 객체를 넘겨 의존성을 약화시켜주던지, Boost.DI와 같은 라이브러리로 종속성을 주입하는 방식 등을 활용하자.  
