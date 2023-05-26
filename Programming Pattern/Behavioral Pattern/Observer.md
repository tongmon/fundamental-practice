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
    observer.erase(remove(observer.begin(), observer.end()), observer.end());
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

std::mutex는 deadlock이 발생할 수 있다는 문제가 있다.  
다음과 같은 상황을 생각해보자.  


