# Observer Pattern  

패턴의 이름 답게 특정 객체를 관찰하고 있다가 그 객체의 상태가 변하면 어떤 동작을 취하는 패턴이다.  
C# 등 다른 언어들은 언어적인 차원에서 관찰자 패턴을 지원할 정도로 굉장히 유용한 패턴이다.  
C++은 따로 제공되는 것이 없기에 직접 구현해야 한다.  
&nbsp;  

## 속성 관찰자  

보통 자신의 생일이라면 생일 파티를 할 것이다.  
특정 사람의 나이가 생일인 경우 파티가 열리는 예제를 살펴보자.  
```c++
struct Person
{
    int age;
    Person(int age)
        : age{age}
    {
    }
};
```
위와 같은 사람 클래스가 있다.  
해당 객체의 변화를 어떻게 알 수 있을까?  
가장 간단하게 100ms마다 체크하는 pooling 기법으로 접근할 수도 있다.  
하지만 매우 비효율적이다.  

age의 값을 건드리는 경우 이를 알아차릴 수 있다면 효율적일 것이다.  
```c++
struct Person
{
    // 동일 구현부 생략

    int get_age() const
    {
        return age;
    }
    void set_age(const int &value)
    {
        age = value;
    }
};
```
그러기 위해선 읽기, 쓰기 함수가 위와 같이 구비되어야 한다.  
&nbsp;  

## Observer 템플릿  

한번 Person의 age가 수정되면, 좀 더 generic하게 멤버 변수가 수정되면 반응하는 Observer 템플릿 클래스를 만들어보자.  
```c++
template <typename T>
struct Observer
{
    virtual void field_changed(T &source, const std::string &field_name) = 0;
};
```
일단 위와 같은 가상 템플릿 인터페이스가 필요하다.  
가상 함수인 ```field_changed()```에는 필드 수정에 필수적인 정보인 원본, 수정이 필요한 필드명 정도가 인자로 들어있지만 원한다면 다른 인자를 더 늘려도 된다.  

그리고 생일 파티를 이벤트를 발생시키는 관찰자를 만들어보자.  
어떤 Person이 16살인 경우 생일을 축하하는 관찰자 클래스는 밑과 같다.  
```c++
struct BirthDayObserver : public Observer<Person>
{
    void field_changed(Person &source, const std::string &field_name)
    {
        if (field_name == "age")
        {
            if (source.age == 16)
                std::cout << "16th BirthDay Happen! Happy BirthDay~\n";
        }
    }
};
```
생일 파티 이벤트는 나이를 기준으로 발생하기에 ```field_name == "age"```라는 조건이 붙어있다.  

사람만 생일 파티를 하는 것이 아닐 수 있다.  
이런 경우 템플릿의 강력함이 나타난다.  
```c++
struct BirthDayObserver : public Observer<Person>, public Observer<Dog>, public Observer<Cat>
{
    void field_changed(Person &source, const std::string &field_name);
    void field_changed(Dog &source, const std::string &field_name);
    void field_changed(Cat &source, const std::string &field_name);
    // ...
};
```
위와 같이 다중 상속으로 다양한 자료형을 손쉽게 다룰 수 있다.  
&nbsp;  

## Observable 템플릿  

위에서 만든 BirthDayObserver를 이용해 어떻게 Person 객체의 변화를 알아챌까?  
BirthDayObserver를 바로 이용하기는 어렵고 추가적인 작업이 남았다.  
Observable이라는 관찰자 무리를 관리하는 템플릿 클래스를 만들어 줘야 관찰자 패턴이 완성된다.  
&nbsp;  

Observable은 기본적으로 밑과 같이 생겼다.  
```c++
template <typename T>
class Observable
{
    std::vector<Observer<T> *> observer;

  public:
    void notify(T &source, const std::string &field_name);
    void subscribe(Observer<T> *f);
    void unsubscribe(Observer<T> *f);
};
```
여러 개의 관찰자들이 담길 observer 배열이 존재한다.  
크게 3개의 기능이 있다.  

```notify()```는 관찰자에게 특정 객체가 자신이 변했다라는 것을 알리기 위해 사용된다.  
현재 필드 값의 변화를 관찰하는 예시를 들기 위해 ```notify()```의 인자가 두 개인 것이지 인자의 설정은 사용자가 지정하기 나름이다.  

```subscribe()```는 이벤트를 등록하기 위한 함수이다.  
여기선 ```Observer<T>```를 상속하고 있다면 이벤트라고 할 수 있다.  

```unsubscribe()```는 등록했던 이벤트를 제거하기 위한 함수다.  
제거할 이벤트를 인자로 받는다.  

각 함수의 구현을 알아보자.  
&nbsp;  
