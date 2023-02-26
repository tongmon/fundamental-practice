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
    Circle(const float radius = 0)
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

이를 해결하기 위해 MixIn 상속 방식을 이용한다.  
밑과 같이 ColoredShape과 TransparentShape을 템플릿 클래스로 바꿔보자.  
```c++
template <typename T>
class ColoredShape : public T
{
    using Color = std::tuple<unsigned char, unsigned char, unsigned char>;
    Color rgb;

public:
    ColoredShape(const Color &rgb = {0, 0, 0})
        : rgb{rgb}
    {
    }

    std::string str()
    {
        std::ostringstream oss;
        oss << T::str() << " has the color"
            << " R: " << static_cast<short>(std::get<0>(rgb))
            << " G: " << static_cast<short>(std::get<1>(rgb))
            << " B: " << static_cast<short>(std::get<2>(rgb));
        return oss.str();
    }
};

template <typename T>
class TransparentShape : public T
{
    unsigned char alpha;

public:
    TransparentShape(const unsigned char alpha = 0)
        : alpha{alpha}
    {
    }

    std::string str()
    {
        std::ostringstream oss;
        oss << T::str() << " has "
            << static_cast<float>(alpha) / 255.f
            << "% transparency";
        return oss.str();
    }
};
```
동적으로 속성을 추가하는 상황에 대한 고려를 할 필요가 없기에 멤버 변수에서 ```Shape& shape```가 제거되었고 생성자도 그에 맞춰서 바뀌었다.  
str() 함수에서도 ```shape.str()```이 ```T::str()```로 바뀌었다.  
&nbsp;  

이렇게 되면 밑과 같이 사용이 가능하다.  
```c++
ColoredShape<TransparentShape<Circle>> blue_circle{{0, 0, 255}};
red_circle.resize(10);
```
```ColoredShape<TransparentShape<Circle>>```처럼 여러 속성이 조합된 자료형을 손쉽게 정의할 수 있다.  
게다가 해당 자료형은 Circle을 상속하고 있는 구조를 취하므로 Circle의 멤버 함수인 resize()도 호출할 수 있다.  
주의할 점은 템플릿 클래스에서 상속할 자료형 T는 무조건 Shape 자료형을 품고 있어야 한다는 것이다.  
해당 주의사항을 조합 자료형 선언 과정에 녹여내고 싶다면 Circle 클래스도 MixIn 상속 방식의 템플릿 클래스로 바꿔주면 된다.   
그러면 ```ColoredShape<TransparentShape<Circle<Shape>>>```, ```Circle<TransparentShape<ColoredShape<Shape>>>``` 이렇게 속성 순서와 무관하게 조합 자료형을 만들 수 있다.  
&nbsp;  

아직 문제가 하나 남았다.  
사용 예시에서 blue_circle은 색상과 투명도 그리고 원이라는 특성이 있는 모양인데 생성자를 보니 색상만 초기화하고 있다.  
다른 속성 클래스의 생성자들을 이용하고 싶어도 현재 구현 상태로는 힘들어보인다.  
생성자도 템플릿을 이용해 바꿔보자.  
```c++
template <typename T>
class ColoredShape : public T
{
public:
    ColoredShape(const Color &rgb = {0, 0, 0}) : rgb{rgb}
    {
    }

    template <typename... Args>
    ColoredShape(const Color &rgb, Args... args)
        : T(std::forward<Args>(args)...), rgb{rgb}
    {
    }

    // 구현부 생략
};

template <typename T>
class TransparentShape : public T
{
public:
    TransparentShape(const unsigned char alpha = 0)
        : alpha{alpha}
    {
    }

    template <typename... Args>
    TransparentShape(const unsigned char alpha, Args... args)
        : T(std::forward<Args>(args)...), alpha{alpha}
    {
    }

    // 구현부 생략
};
```
템플릿 파라메터팩을 이용해 생성자에 여러 인자들이 전달되는 상황에 대처할 수 있다.  
템플릿을 이용한 가변 인자를 생성자 인자로 사용하기에 타입 추론이 발생한다.  
따라서 생성자 인자를 참조 연산자인 &&로 받을 때 보편 참조가 발생하기 때문에 기존 참조 방식 그대로를 유지하면서 부모의 생성자 인자로 넘겨주기 위해 ```std::forward()```를 사용했다.  
&nbsp;  

최종적으로 밑과 같이 사용할 수 있다.  
```c++
ColoredShape<TransparentShape<Circle>> blue_half_visible_circle{{0, 0, 255}, 128, 5.f};
TransparentShape<Circle> transparent_circle = {255, 10.f};
```
너무 손쉽고 깔끔하게 속성을 조합할 수 있다.  
해당 방식의 한 가지 유의점은 암시적 형변환을 방지하는 explicit 키워드를 속성으로 사용되는 클래스의 생성자에 사용하면 안된다는 것이다.  
&nbsp;  

## 함수형 데코레이터  

클래스말고 함수에도 기능을 부착할 수 있다.  
만약에 밑과 같은 함수가 있다고 하자.  
```c++
void print_million_hello_world()
{
    for (int i = 0; i < 1000000; i++)
        std::cout << "hello world\n";
}
```
hello world를 백만번 출력하는 함수다.  
&nbsp;  

해당 함수가 작동하는 데 걸리는 시간을 알고 싶다면 밑과 같이 구현해야 할 것이다.  
```c++
void print_million_hello_world(int cnt, const std::string &repeat)
{
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now(), end;

    for (int i = 0; i < 1000000; i++)
        std::cout << "hello world" << std::endl;

    end = std::chrono::system_clock::now();
    std::cout << (end - start).count() * 1e-9 << "s" << std::endl;
}
```
하지만 함수 작동 시간을 알려주는 기능까지 print_million_hello_world() 함수에 포함하는 것이 맞을까?  
이는 단일 책임 원칙을 위배하기 때문에 추후 코드 유지보수를 생각해서라도 바꿔줘야 한다.  
&nbsp;  

먼저 밑과 같은 함수형 데코레이터 클래스를 정의한다.  
```c++
class BenchMarking
{
    std::function<void()> func;
    std::string name;

public:
    BenchMarking(const std::function<void()> &func, const std::string &name)
        : func{func}, name{name}
    {
    }

    void operator()() const
    {
        std::cout << "BenchMark of " << name << " Function" << std::endl;
        std::chrono::system_clock::time_point start = std::chrono::system_clock::now(), end;

        func();

        end = std::chrono::system_clock::now();
        std::cout << (end - start).count() * 1e-9 << "s" << std::endl;
    }
};
```
std::function과 연산자```()```를 오버로딩한 Functor를 이용한 벤치마킹 클래스이다.  
Functor가 실행될 때 함수 앞 뒤로 시간 측정을 위한 로직을 수행한다.  
&nbsp;  

실제 사용법은 밑과 같다.  
```c++
// 객체 생성하면서 바로 Functor 수행
BenchMarking(print_million_hello_world, "print_million_hello_world()")();

// 객체 생성하고 필요할 때 Functor 수행
auto benchmarker = BenchMarking(print_million_hello_world, "print_million_hello_world()");
benchmarker();
```
하지만 해당 벤치마크 클래스는 고정된 ```std::function<void()>``` 자료형을 이용하기 때문에 반환 값이 존재하거나 인자가 존재하는 함수가 전달되었을 경우 대처하기 까다롭다.  

&nbsp;  

예를 들어 밑과 같은 상황이 있다.  
```c++
bool is_prime(unsigned long long num)
{
    if (num <= 1)
        return false;

    if (!(num % 2))
        return num == 2;

    for (unsigned long long i = 3; i <= sqrt(num); i += 2)
    {
        if (!(num % i))
            return false;
    }

    return true;
}

// 사용법
unsigned long long num = 79554645354252345;
bool result;
BenchMarking([&]() -> void { result = is_prime(num); }, "is_prime()")();
```
특정 숫자가 소수인지 아닌지 판별해주는 함수는 bool 형을 반환하고 숫자를 인자로 받기 때문에 람다 함수를 따로 구현하여 BenchMarking 클래스에 전달해야 한다.  
&nbsp;  

이러한 번거로운 문제를 밑과 같은 템플릿 클래스를 만들어 해결이 가능하다.  
템플릿 명시화와 함수 자료형에 대한 학습이 안되어 있다면 문법이 다소 난해하게 느껴질 수 있다.  
```c++
template <typename>
struct BenchMarking;

template <typename Return, typename... Args>
class BenchMarking<Return(Args...)>
{
    std::function<Return(Args...)> func;
    std::string name;

public:
    BenchMarking(std::function<Return(Args...)> func, const std::string &name)
        : func{func}, name{name}
    {
    }

    Return operator()(Args... args)
    {
        std::cout << "BenchMark of " << name << " Function" << std::endl;
        std::chrono::system_clock::time_point start = std::chrono::system_clock::now(), end;

        Return ret = func(args...);

        end = std::chrono::system_clock::now();
        std::cout << (end - start).count() * 1e-9 << "s" << std::endl;

        return ret;
    }
};
```
먼저 템플릿 명시화를 하려면 본래의 템플릿 클래스 원형이 필요하기에 ```template <typename> struct BenchMarking;```를 위에 선언해준다.  
그 다음 BenchMarking 클래스를 보면 템플릿 인자 Return, Args를 조합한 새로운 자료형인 Return(Args...)를 명시화하고 있다.  
```Return(Args...)```는 ```std::function<>```과 함께 사용되어 다양한 형태의 함수가 생성자 인자로 들어와도 유연한 대처가 가능하다.  
&nbsp;  

문제는 BenchMarking 클래스를 사용할 때 컴파일러가 템플릿 인수를 추론할 수 없어 번거롭게 밑과 같이 함수 형태를 명시해줘야 한다.  
```c++
// 밑은 템플릿 인수를 추론할 수 없기에 컴파일 과정에서 에러가 발생함.
BenchMarking(is_prime, "is_prime()")(13);

// 밑과 같은 명시적 인수 사용은 번거로움.
BenchMarking<bool(int)>(is_prime, "is_prime()")(7);
```
&nbsp;  

이러한 문제를 해결하기 위해 추가적인 함수를 만들어 준다.  
```c++
template <typename Return, typename... Args>
auto make_benchmarking(Return (*func)(Args...), const std::string &name)
{
    return BenchMarking<Return(Args...)>(std::function<Return(Args...)>(func), name);
}
```
&nbsp;  

사용법은 밑과 같다.  
```c++
auto benchmark = make_benchmarking(is_prime, "is_prime()");
benchmark(5);

make_benchmarking(is_prime, "is_prime()")(23);
```
&nbsp;  

아니면 그냥 바로 함수 포인터를 이용한 템플릿 클래스를 사용해도 된다.  
```c++
template <typename Return, typename... Args>
class BenchMarking
{
    Return (*func)(Args...);
    std::string name;

public:
    BenchMarking(Return (*func)(Args...), const std::string &name)
        : func{func}, name{name}
    {
    }

    Return operator()(Args... args)
    {
        std::cout << "BenchMark of " << name << " Function" << std::endl;
        std::chrono::system_clock::time_point start = std::chrono::system_clock::now(), end;

        Return ret = func(args...);

        end = std::chrono::system_clock::now();
        std::cout << (end - start).count() * 1e-9 << "s" << std::endl;

        return ret;
    }
};
```