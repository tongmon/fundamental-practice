# Decorator Pattern  

이미 존재하는 타입에 대해 새로운 기능을 추가하기 위한 패턴이다.  
쉽게 말하면 크리스마스 트리에 장식품 추가하듯이 기능 확장에 중점을 둔 패턴이다.  
장점이라면 프로그램 실행 중에 동적으로 기능을 추가하거나 뺄 수가 있어서 유연하다.  
&nbsp;  

데코레이터 패턴을 어느 경우에 사용해야 하는지 이해하기 위한 상황을 가정해보자.  
일단 밑과 같은 모양 인터페이스가 존재한다.  
```c++
struct Shape
{
    virtual std::string str() = 0;
};
```
&nbsp;  

색상을 가지는 모양은 밑과 같이 확장할 수 있다.  
```c++
struct ColoredShape : public Shape
{
    std::tuple<unsigned char, unsigned char, unsigned char> rgb;
    std::string str() { return "Colored!\n"; }
};
```
&nbsp;  

투명도를 가지는 모양도 밑과 같이 확장 가능하다.  
```c++
struct TransparentShape : public Shape
{
    unsigned char alpha;
    std::string str() { return "Transparent!\n"; }
};
```

그렇다면 투명도와 색상을 동시에 가지는 클래스는 어떻게 처리할까?  
두가지 접근법이 있다.  
하나는 밑과 같이 두 특성을 합친 클래스를 새로 만드는 것이다.  
```c++
struct ColoredAndTransparentShape : public Shape
{
    std::tuple<unsigned char, unsigned char, unsigned char, unsigned char> rgba;
    std::string str() { return "Colored And Transparent!\n"; }
};
```
&nbsp;  

나머지 하나는 여러 클래스를 조합하여 상속하는 것이다.  
```c++
struct ColoredAndTransparentShape : public ColoredShape, public TransparentShape
{
    std::string str() { return "Colored And Transparent!\n"; }
};
```
어느 방식을 선택하던 조합을 할 때마다 새로운 자료형을 만들어야 한다.  
&nbsp;  

좀 더 나아가 Shape을 상속하는 원 클래스를 만들어보자.  
```c++
struct Circle : public Shape
{
    float radius;
    std::string str() { return "Circle!\n"; }
};
```
&nbsp;  

색상과 투명도 속성을 가진 원을 만들고 싶다면 밑과 같이 만들어줘야 한다.  
```c++
struct ColoredAndTransparentCircle : public ColoredAndTransparentShape, public Circle
{
    std::string str() { return "Colored And Transparent Circle!\n"; }
};
```
이쯤되면 감이 올 것이다.  
Shape의 속성인 Circle, Colored, Transparent 들을 조합할 때마다 클래스가 계속 늘어난다.  
만약 Square라는 속성이 더 추가된다면 다양한 조합에 의해 더 많은 클래스를 생성해야 할 것이다.  
그리고 상속을 통해 이를 해결하다보면 관계가 복잡해져서 문제 파악이 어려워진다.  
ColoredAndTransparentCircle 클래스만 해도 이미 다이아몬드 상속 구조를 갖추고 있어 모호한 함수 호출이 가능하다.  
&nbsp;  

## 동적 데코레이터  

위에서 발생된 문제를 동적 데코레이터 패턴으로 해결해보자.  
