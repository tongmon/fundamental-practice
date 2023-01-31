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

