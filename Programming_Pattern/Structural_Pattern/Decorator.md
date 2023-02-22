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
먼저 Circle 클래스를 밑과 같이 바꿔보자.  
```c++
class Circle : public Shape
{
    float radius;

public:
    Circle() {}

    explicit Circle(const float radius)
        : radius{radius}
    {
    }

    std::string str()
    {
        std::ostringstream oss;
        oss << "A circle of radius " << radius;
        return oss.str();
    }
};
```
거의 같다고 봐도 무방할 정도로 달라진 것이 없다.  
생성자와 str() 함수의 구현이 살짝 변했을 뿐이다.  
&nbsp;  

그 다음 ColoredShape 클래스를 밑과 같이 변경해보자.  
```c++
class ColoredShape : public Shape
{
    using Color = std::tuple<unsigned char, unsigned char, unsigned char>;
    Color rgb;
    Shape &shape;

public:
    ColoredShape(Shape &shape, const Color &rgb)
        : shape{shape},
          rgb{rgb}
    {
    }

    std::string str()
    {
        std::ostringstream oss;
        oss << shape.str() << " has the color"
            << " R: " << static_cast<short>(std::get<0>(rgb))
            << " G: " << static_cast<short>(std::get<1>(rgb))
            << " B: " << static_cast<short>(std::get<2>(rgb));
        return oss.str();
    }
};
```
다른 자잘한 구현부는 신경쓰지말고 생성자를 유심히 봐라.  
ColoredShape 클래스는 자기 자신도 Shape를 상속하고 있는데 생성자로 Shape을 받고 그 참조를 자기가 들고 있는다.  
&nbsp;  

왜 이런 구조를 취하는지에 대한 궁금증은 뒤로하고 TransparentShape 클래스도 밑과 같이 바꿔보자.  
```c++
class TransparentShape : public Shape
{
    Shape &shape;
    unsigned char alpha;

public:
    TransparentShape(Shape &shape, const unsigned char alpha)
        : shape{shape},
          alpha{alpha}
    {
    }

    std::string str()
    {
        std::ostringstream oss;
        oss << shape.str() << " has "
            << static_cast<float>(alpha) / 255.f
            << "% transparency";
        return oss.str();
    }
};
```
이 녀석도 마찬가지로 생성자로 Shape을 받고 그 참조를 들고 있는다.  
&nbsp;  

이런 구조가 갖춰지면 밑과 같은 행위가 가능해진다.  
```c++
// 그냥 원
Circle circle{5};

// 빨간색 원
ColoredShape red_circle{circle, {255, 0, 0}};

// 반투명 빨간색 원
TransparentShape red_half_visible_circle{red_circle, 128};
```
반투명 빨간색 원을 ColoredAndTransparentCircle와 같은 새로운 자료형을 만들지 않고도 생성해냈다.  
즉 추가적인 자료형 생성 없이 기존에 있던 베이스 속성들로만 조합을 나타낼 수 있다.  
&nbsp;  

하지만 문제가 없는 것은 아니다.  
밑은 봐보자.  
```c++
// 그냥 원
Circle circle{5};

// 빨간색 원
ColoredShape red_circle{circle, {255, 0, 0}};

// 빨간색이면서 녹색 원
ColoredShape green_red_circle{red_circle, {0, 255, 0}};
```
마지막에 빨간색이면서 녹색 원이 말이 되는가?  
이런 말도 안되는 조합을 만들 수 있다는 것이 문제가 된다.  
물론 이러한 문제는 프로그래머가 상식적으로 데코레이터 패턴을 이용한다면 발생하지 않을 것이다.  
&nbsp;  

## 정적 데코레이터  

만약 Circle에 resize()라는 멤버 함수가 있다고 해보자.  
```c++
class Circle : public Shape
{
    // 나머지 구현부 생략

    void resize(float factor)
    {
        radius *= factor;
    }
};
```
&nbsp;  

밑 상황을 보자.  
```c++
// 그냥 원
Circle circle{5};

// 빨간색 원
ColoredShape red_circle{circle, {255, 0, 0}};

// red_circle.resize()를 어떻게 쓸 수 있을까...?
```
주석에서도 쓰여있듯이 resize() 함수는 Circle 클래스의 멤버 함수이기에 ColoredShape에서는 호출할 수가 없다.  
&nbsp;  

