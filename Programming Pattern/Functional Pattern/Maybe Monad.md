# Maybe Monad Pattern  

특정 객체에 어떤 값이 존재하지 않다는 것을 알려주기 위해선 다양한 방법이 있다.  
대표적으로 nullptr, ```std::optional<T>```의 std::nullopt 등이 많이 쓰인다.  
일단 nullptr 방식이 채택되었다고 가정하고 예시를 보자.  
```c++
struct Address
{
    std::string *house_location = nullptr;
};

struct Person
{
    Address *address = nullptr;
};
```
Person은 Address 포인터를 품고 있다.  
&nbsp;  

house_location을 출력하는 함수는 밑과 같다.  
```c++
void print_house_location(Person *p)
{
    if (p && p->address && p->address->house_location)
        std::cout << p->address->house_location;
}
```
nullptr 확인을 포인터마다 해줘야 해서 번거롭고 너저분하다.  
이렇게 데이터를 깊게 파고드는 현상을 Drill-Down이라고 한다.  
&nbsp;  

이러한 현상을 직관적으로 바꾸기 위해 Maybe 템플릿 클래스를 정의한다.  
```c++
template <typename T>
struct Maybe
{
    T *context;
    Maybe(T *context)
        : context{context}
    {
    }
};
```
포인터를 감싸는 것 외에는 아무것도 하지 않는다.  
게다가 생성자로는 템플릿 인자를 추론하지 못한다.  
&nbsp;  

템플릿 인자를 자동으로 추론할 수 있도록 Maybe를 감싸는 함수를 만들어준다.  
```c++
template <typename T>
struct Maybe;

template <typename T>
Maybe<T> maybe(T *context)
{
    return Maybe<T>(context);
}
```
&nbsp;  

```Maybe<T>``` 클래스에 포인터 유효성을 검사하는 멤버 함수를 추가해보자.  
```c++
template <typename T>
struct Maybe
{
    // 동일 구현부 생략

    template <typename Func>
    auto With(Func func)
    {
        return context ? maybe(func(context)) : nullptr;
    }
};
```
포인터가 유효하다면 Drill-Down이 진행된다.  
유효하지 않다면 nullptr을 반환하고 있는데 실제로는 ```maybe(func(context))```의 반환형에 따라 결정된다.  
```maybe(func(context))```의 반환형이 ```Maybe<Address>```라면 ```Maybe<Address>(nullptr)```가 반환될 것이다.  
이렇게 반환형을 직접 적어주기 어려운 경우 auto를 사용하여 컴파일러가 추론하게 만드는 것이 바람직하다.  
&nbsp;  

포인터가 유효하다면 특정 동작을 수행해야 할 것이다.  
```c++
template <typename T>
struct Maybe
{
    // 동일 구현부 생략

    template <typename Action>
    auto Do(Action act)
    {
        if (context)
            act(context);
        return *this;
    }
};
```
동작을 수행한 뒤 자기 자신을 반환해 다음 작업을 추가할 수 있도록 설계한다.  
&nbsp;  

print_house_location() 함수는 밑과 같이 변한다.  
```c++
void print_house_location(Person *p)
{
    maybe(p)
        .With([](auto x) { return x->address; })
        .With([](auto x) { return x->house_location; })
        .Do([](auto x) { std::cout << *x; });
}
```
굉장히 직관적이다.  
한 가지 단점이라면 With, Do가 람다 함수를 이용한다는 것이다.  
함수형 프로그래밍이 언어적으로 지원되는 Kotlin, Swift의 경우는 ```With{x->address}.With{x->house_location}``` 이러한 문법을 지원한다.  

## 요약  

1. Drill-Down을 진행할 때 Maybe Monad 패턴을 이용하면 직관적인 코드를 작성할 수 있다.  