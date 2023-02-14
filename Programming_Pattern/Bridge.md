# Bridge Pattern  

브릿지 패턴은 접착제처럼 두 가지를 함께 연결해주는 패턴이다.  
&nbsp;  

원을 그리는 상황을 생각해보자.  
일단 화면에 그리기 위한 렌더러 인터페이스를 만들자.  
```c++
struct Renderer
{
    virtual void render_circle(float center_x, float center_y, float radius) = 0;
};
```
원의 중심과 반지름을 인자로 받는 순수 가상 함수를 만들었다.  
&nbsp;  

화면에 나타내는 방식은 벡터 방식과 레스터 방식이 있다.  
대부분의 PDF 파일은 벡터 기반의 벡터 그래픽 방식이다.  
모든 비트맵 파일은 픽셀 기반의 레스터 그래픽 방식이다.  
이 둘을 나눠 구현해보자.  
```c++
struct VectorRenderer : Renderer
{
    void render_circle(float center_x, float center_y, float radius)
    {
        /* 벡터 그래픽으로 원 그리는 구현부 */
    }
};

struct RasterRenderer : Renderer
{
    void render_circle(float center_x, float center_y, float radius)
    {
        /* 레스터 그래픽으로 원 그리는 구현부 */
    }
};
```
패턴에 대해 다루기 때문에 실제 구현부는 생략한다.  
&nbsp;  

도형을 그리기 위해 상속해야 하는 Shape 인터페이스를 만들자.  
```c++
class Shape
{
protected:
    Renderer &renderer;
    Shape(Renderer &renderer) : renderer{renderer} {}

public:
    virtual void draw() = 0;
    virtual void resize(float factor) = 0;
};
```
어떤 렌더러를 참조하는지만 알고 나머지 구현은 자식 클래스가 해줘야한다.  
&nbsp;  

원 클래스를 생성한다.  
```c++
class Circle : public Shape
{
    float x, y, radius;

public:
    Circle(Renderer &renderer, float x, float y, float radius)
        : Shape{renderer}, x{x}, y{y}, radius{radius}
    {
    }

    void draw() { renderer.render_circle(x, y, radius); }
    void resize(float factor) { radius *= factor; }
};
```
원 클래스는 간단하다.  
인터페이스가 필수적으로 요구한 것들만 구현해주면 된다.  
그 중 핵심적인 것은 draw() 함수로 생성자에서 받은 Renderer의 종류에 따라 원이 그려지는 방식이 상이해진다.  
```[Circle] ------연결------ [VectorRenderer / RasterRenderer] ------연결------ [Renderer]``` 이렇게 VectorRenderer 혹은 RasterRenderer가 브릿지 역할을 하여 연결하고 있다.  
해당 패턴의 장점은 연결되는 컴포넌트들이 상세 구현을 알 필요가 없다는 것이다.  
해당 예시에서도 상세한 작동 로직은 브릿지 역할을 하는 ```[VectorRenderer / RasterRenderer]``` 부분에 구현되어 있다.  
&nbsp;  

## Pimpl

Pimpl... 브릿지 패턴을 이용한 기법으로 Pointer to Implementation의 약자이다.  
즉 구현부를 포인터로 참조하겠다는 것이다.  
해당 기법의 장점은 추후에 알아보고 일단 예시를 보자.  
&nbsp;  

밑과 같은 Person 클래스가 있다.  
```c++
class Person
{
    class PersonImpl;
    PersonImpl *impl;

    std::string name;
public:
    Person();
    ~Person();

    void greet();
};
```
클래스 내부에 PersonImpl 클래스 선언이 존재하고 더 특이한 것은 PersonImpl에 대한 포인터 멤버 변수가 있다는 점이다.  
&nbsp;  

다음으로 구현부를 보자.  
```c++
class Person::PersonImpl
{
public:
    void greet(Person *p);
};

void Person::PersonImpl::greet(Person *p)
{
    printf("hello %s", p->name.c_str());
}

Person::Person() : impl(new PersonImpl)
{
}

Person::~Person()
{
    delete impl;
}

void Person::greet()
{
    impl->greet(this);
}
```
구현부에서 모든 의문이 풀린다.  
PersonImpl에 대한 정의가 되어있고 해당 클래스는 greet(Person *p) 라는 멤버 함수를 갖는다.  
Person의 생성자에서는 PersonImpl 포인터 멤버 변수에 값을 할당한다.  
Person의 소멸자에서는 PersonImpl 포인터 멤버 변수를 해제한다. (따라서 스마트 포인터를 사용해도 된다.)  
Person의 greet() 함수에서는 PersonImpl::greet(Person *p) 함수를 호출한다.  
모든 상세 구현은 브릿지 역할을 해주고 있는 PersonImpl 내부에 존재하기에 Person은 상세 구현에 대해 생각할 필요가 없다.  
&nbsp;  

그러면 Pimpl을 왜 쓸까?  
다음과 같은 3가지 장점이 대표적이다.  

1. 클래스의 상세 구현부를 숨길 수가 있다.  

2. 바이너리 호환성을 보증하기 쉬워진다.  

3. 헤더 파일에서 멤버 선언에 필요한 헤더들만 포함하는 것이 가능하다.  

Pimpl의 주된 장점은 .h, .cpp 파일로 나누어 클래스 구현을 저장하는 경우 나타난다.  
