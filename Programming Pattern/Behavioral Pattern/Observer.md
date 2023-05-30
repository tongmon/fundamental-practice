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
    Person(int age = 0)
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
    void notify(T &source, const std::string &field_name) { /* something */ };
    void subscribe(Observer<T> *f) { /* something */ };
    void unsubscribe(Observer<T> *f) { /* something */ };
};
```
여러 개의 관찰자들이 담길 observer 배열이 존재한다.  
크게 3개의 기능이 있다.  

```notify()```는 특정 객체가 관찰자에게 "자신이 변했다."라는 것을 알리기 위해 사용된다.  
등록된 모든 이벤트(```Observer<T>```)를 호출한다.  
```c++
void notify(T &source, const std::string &field_name)
{
    for (auto ptr : observer)
        ptr->field_changed(source, field_name);
}
```
현재 필드 값의 변화를 관찰하는 예시를 들기 위해 ```notify()```의 인자가 두 개인 것이지 인자의 설정은 사용자가 지정하기 나름이다.  

```subscribe()```는 이벤트를 등록하기 위한 함수이다.  
```c++
void subscribe(Observer<T> *f)
{
    observer.push_back(f);
}
```
observer에 이벤트를 추가하기만 하면 된다.  

```unsubscribe()```는 등록했던 이벤트를 제거하기 위한 함수다.  
제거할 이벤트를 인자로 받는다.  
```c++
void unsubscribe(Observer<T> *f)
{
    observer.erase(std::remove(observer.begin(), observer.end(), f), observer.end());
}
```
remove()는 지울 원소를 실제로 제거하지 않고 앞 원소를 땡겨 덮어씌우는 방식이므로 erase()와 함께 사용하여 제거해준다.  
remove()의 반환 값이 ```제일 마지막에 땡겨 이동한 원소의 한 칸 뒤 반복자```이기에 위와 같은 표현이 가능하다.  
&nbsp;  

## 객체와 Observable의 연결  

이제 Person과 BirthDayObserver를 연동할 준비는 끝났다.  
일단 Person은 Observable를 상속해야 한다.  
```c++
struct Person : public Observable<Person>
{
    // 구현부 생략
};
```
이러면 Person에서 Observable이 제공하는 함수들을 이용할 수 있다.  

그 뒤 Person의 age가 변경될 때 호출되는 함수인 set_age()의 구현부를 밑과 같이 바꿔준다.  
```c++
struct Person : public Observable<Person>
{
    // 동일 구현부 생략

    void set_age(const int &value)
    {
        if (age == value)
            return;
        age = value;
        notify(*this, "age");
    }
};
```
나이가 같으면 변경 사항이 없기에 그대로 함수를 끝낸다.  
```notify(*this, "age");```를 통해 관찰자가 age 값 변화에 반응하게 된다.  

밑과 같이 활용이 가능하다.  
```c++
Person p;

BirthDayObserver bo;
p.subscribe(&bo);

p.set_age(7);
p.set_age(16); // 여기서만 생일 축하하게 됨.
```
다중 쓰레드, 종속성을 고려하지 않는다면 지금 상태의 Observable를 사용해도 무방하다.  
하지만 코드의 세계에는 복잡한 상황이 더 많다.  
&nbsp;  

## 종속성 문제  

장난감 선물은 나이가 7세 이하여야 받을 수 있다고 하자.  
Person에 해당 조건을 검사하기 위해 밑과 같은 함수가 추가되었다.  
```c++
struct Person : public Observable<Person>
{
    // 동일 구현부 생략  

    bool get_can_toy_gifted()
    {
        return age <= 7;
    }
};
```
장난감 선물 여부는 age를 통해 간접적으로 알 수 있기 때문에 따로 멤버 변수는 없고 멤버 함수만 존재한다.  

따라서 장난감 선물 여부의 변경을 관찰하기 위해서는 set_age()를 변경해야 한다.  
```c++
struct Person : public Observable<Person>
{
    // 동일 구현부 생략  

    void set_age(const int &value)
    {
        if (age == value)
            return;

        bool old_toy_gifted = get_can_toy_gifted();

        age = value;
        notify(*this, "age");

        if (old_toy_gifted != get_can_toy_gifted())
            notify(*this, "can_toy_gifted");
    }
};
```
하지만 위의 set_age() 함수는 구현은 잘 되겠지만 단단히 잘못되었다.  
만약 장난감 선물 여부에 영향을 미치는 값에 나이말고 성별, 이름까지 있다면 어떻게 될까?  
set_gender(), set_name() 함수까지 모두 바꿔줘야 하기에 유지보수가 굉장히 어려워진다.  
set_age()는 이름 그대로 age만 변경하는 역할을 해야 맞다.  

확장을 하려면 can_toy_gifted라는 bool 변수를 따로 만들고 notify() 함수를 set_can_toy_gifted() 함수에서 진행하는 것이 맞다.  
아니면 특정 속성 간의 종속성을 ```std::map<std::string, std::vector<std::string>>``` 자료형으로 관리해도 된다.  
하지만 이 방식은 코드 변경 마다 해당 ```std::map```을 업데이트해야 되기에 번거롭다.  
&nbsp;  

## 다중 쓰레드 대처  

다중 쓰레드에서 현재 Observable은 사용할 수 없다.  
```notify()```, ```subscribe()```, ```unsubscribe()``` 모두 observer라는 thread-safe하지 않은 std::vector 자료형을 이용하기에 std::mutex를 이용해 잠금을 걸어야 한다.  

일단 Observable에 std::mutex를 추가한다.  
```c++
template <typename T>
class Observable
{
    std::mutex mut;

    // 생략
}
```

각 함수는 밑과 같이 변경될 수 있다.  
```c++
void notify(T &source, const std::string &field_name)
{
    std::unique_lock<std::mutex> ul{mut};
    // 생략
}
void subscribe(Observer<T> *f)
{
    std::unique_lock<std::mutex> ul{mut};
    // 생략
}
void unsubscribe(Observer<T> *f)
{
    std::unique_lock<std::mutex> ul{mut};
    // 생략
}
```
각 함수 수행 도중 다른 함수가 끼어들지 못하게 만들면 된다.  
std::mutex를 이용하기 싫다면 외부 라이브러리를 이용해 thread-safe한 배열 자료형을 이용하면 될 것이다.  
&nbsp;  

### 재진입 문제  

std::mutex는 잘못사용하면 deadlock이 발생할 수 있다.  
이벤트가 스스로 자기 자신을 제거하는 상황을 생각해보자.  
```c++
struct ToyGiftedQualificationObserver : public Observer<Person>
{
    void field_changed(Person &source, const std::string &field_name)
    {
        if (field_name == "age")
        {
            if (source.age <= 7)
                std::cout << "Happy BirthDay~, Get this toy gift for you!\n";
            else
            {
                std::cout << "Ah... You are too old to get this toy gift!\n";
                source.unsubscribe(this);
            }
        }
    }
};
```
나이가 7살이 넘으면 ```source.unsubscribe(this)```로 자신을 이벤트 리스트에서 삭제한다.  

밑과 같은 상황을 생각해보자.  
```c++
Person p;

ToyGiftedQualificationObserver tgqo;
p.subscribe(&tgqo);

p.set_age(16);
```
set_age() 함수부터 호출 순서를 따져보자.  
```set_age() -> notify() -> field_changed() -> unsubscribe()``` 순으로 진행된다.  
문제는 notify()에서 lock을 했는데 unsubscribe()에서 lock을 또 수행하여 deadlock 현상이 발생한다.  
&nbsp;  

해당 문제를 해결하기 위한 가장 간단한 방법은 std::recursive_mutex를 이용하는 것이다.  
```c++
template <typename T>
class Observable
{
    // 동일 구현부 생략  

    std::recursive_mutex mut;

  public:
    void notify(T &source, const std::string &field_name)
    {
        std::unique_lock<std::recursive_mutex> ul{mut};
        // 생략
    }
    void subscribe(Observer<T> *f)
    {
        std::unique_lock<std::recursive_mutex> ul{mut};
        // 생략
    }
    void unsubscribe(Observer<T> *f)
    {
        std::unique_lock<std::recursive_mutex> ul{mut};
        // 생략
    }
};
```
단지 std::mutex를 std::recursive_mutex로 교체해주면 된다.  
단점이라면 std::recursive_mutex가 동시성의 관점에서 그닥 좋은 방식이 아니라 많은 개발자가 기피한다는 것이다.  
특정 쓰레드가 lock의 소유를 오래 할수록 멀티 쓰레드의 장점은 사라지기 마련이다.  
ToyGiftedQualificationObserver 이벤트 예시처럼 하나의 쓰레드가 한 번에 lock을 두 번 이상 수행하는 것은 바람직하지 않다.  

복사를 하여 처리하는 방식도 있다.  
```c++
void notify(T &source, const std::string &field_name)
{
    mut.lock();
    std::vector<Observer<T> *> copied{observer};
    mut.unlock();

    for (auto ptr : copied)
        ptr->field_changed(source, name);
}
```
notify()에서 observer 내용을 복사한 후 lock을 바로 해제하기에 field_changed()에서 호출하는 unsubscribe() 함수에서 다시 lock을 획득할 수 있다.  
&nbsp;  

## 개선점  

관찰자 패턴도 다양한 상황에 따라 모습이 천차만별이다.  
밑과 같은 상황들이 추가적으로 고려될 수 있다.  

1. 같은 관찰자가 두 번 추가되는 경우 어떻게 다룰 것인가? 또 삭제는 어떻게 할 것인가?  

2. std::vector가 아닌 std::set이나 std::unordered_set을 이용하면 어떤 차이가 생길까?  

3. 관찰자들 사이에 우선 순위가 있는 경우 어떻게 고려해야 하는가?  

당연하겠지만 모든 상황에서 이상적인 패턴은 없다.  
몇 개의 장점을 취하면 몇 개의 단점이 따라오기 마련이다.  
&nbsp;  

## Boost.Signals2 적용  

관찰자 패턴을 이용할 때 도움을 주는 라이브러리 중 가장 널리 알려진 Boost.Signals2를 이용해보자.  

먼저 Observable은 밑과 같이 생겼다.  
```c++
template <typename T>
struct Observable
{  
    boost::signals2::signal<void(T &, const std::string &)> notify;
};
```
Callable로 접근할 것이기에 Observer 구조체는 추가적으로 만들지 않는다.  
Person 클래스의 구조는 위 Observable 클래스를 상속한 것 말고는 모두 동일하다.  

활용은 밑과 같이 가능하다.  
```c++
Person p;

auto bo = [](Person &source, const std::string &field_name) -> void {
    if (field_name == "age")
    {
        if (source.age == 16)
            std::cout << "16th BirthDay Happen! Happy BirthDay~\n";
    }
};

auto conn = p.notify.connect(bo);

p.set_age(16);

conn.disconnect(); // 더 이상 bo 이벤트가 필요없다면 해제
```
활용 방식에 큰 차이는 없다.  
다만 Boost.Signals2은 thread-safe 하기에 다중 쓰레드 처리를 위한 추가적인 노력을 덜 수 있다.  
&nbsp;  

## 요약    

1. 클래스 전체를 관찰자로 등록하기 위해 이벤트 배열을 상속할 것인지 아니면 단순하게 이벤트 몇 개만 상속할 것인지 고려해봐야 한다.  
    클래스에서 다룰 이벤트의 개수가 적다면 클래스를 굳이 관찰자로 만들 이유가 없다.  

2. 관찰자의 알림 수신 해제 기법을 고려할 필요가 있다.  
    - 일단 수신 해제 기능이 필요없는 상황이 가장 좋다.  
    - 수신 해제 기능(unsubscribe)이 필요하다면 즉시 삭제하기보다 nullptr 처리를 하여 삭제를 미루는 편이 좋다.  

3. 관찰자를 thread-safe하게 만들기 위해서는 모든 관찰자 함수에 Mutex를 이용하거나 thread-safe한 자료구조에서 이벤트를 관리해야 한다.  

4. 이벤트가 저장되는 자료구조 특성에 따라 관찰자의 작동 방식이 달라진다.  
    std::set를 이용하면 중복된 이벤트를 거를 수 있다.  