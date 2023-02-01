# Singleton Pattern  

매우 유명하지만 미움도 많이 받는 싱글턴 패턴이다.  
애플리케이션 전체에서 단 하나만 존재해야 하는 상황을 처리하기 위해 탄생했다.  
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
protected:  
    Singleton() {}

public:
    static Singleton &get()
    {
        static Singleton singleton;
        return singleton;
    }
};
```
사용자는 get 함수만을 이용해 Singleton 객체에 접근할 수 있어 알아차리기 쉽다.  
get 함수에서 전역 Singleton 객체가 명시적으로 초기화되기에 다른 전역 객체가 get 함수를 통해 전역 Singleton 객체를 참조해도 문제가 없다. (C++11 미만 버전에서는 static 변수에 대한 스레드 안정성이 보장이 안되기 때문에 mutex를 통한 코드가 추가적으로 필요하다.)  
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
protected:
    Singleton() {}

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

위에서 get 함수만 밑과 같이 바꿔줘도 된다.  
```c++
static Singleton &get()
{
    static Singleton *singleton = new Singleton();
    return *singleton;
}
```
이제 Singleton 객체는 힙 메모리에 올라가게 된다.  
해당 Singleton 포인터는 한번 할당 되면 애플리케이션 끝까지 남아있는 녀석이기에 따로 소멸시켜주지 않는다.  
즉 운영체제에게 메모리 해제를 맡기는 것이다.  
대부분의 현대적인 OS(ex. Windows, Linux, Mac)에서는 프로세스가 종료되면 점유하고 있던 힙 메모리를 해제해주지만 단순한 Embedded OS에서는 아닐 수도 있기 때문에 썩 추천되는 방식은 아니다.  
&nbsp;  

## 싱글턴의 문제  

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
protected:
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
protected:
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
protected:
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
일단 get 함수에서 PeopleData 포인터를 인자로 받을 수가 있다.  
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

