# Composite Pattern  

다양한 자료형들에게 동일한 인터페이스를 제공하는 패턴이다.  
보통 각기 다른 자료형을 묶어서 순회 처리하기 위해 많이 사용된다.  
배열을 이용한 방법, ```begin() / end()``` 함수를 재정의하는 방법, ```std::vector<T>```를 상속하는 방법 등 여러가지가 존재한다.  
이 방식 중... ```begin() / end()``` 함수를 재정의하는 덕 타이핑 기법은 숨겨진 인터페이스에 의존하는 것이기에 위험한 상황이 발생될 수 있어서 추천되지 않는다.   
&nbsp;  

## 배열에 기반한 속성  

생명체 클래스를 컴포지트 패턴을 이용하여 개선해보자.  
밑과 같은 생명체 클래스가 존재한다.  
```c++
class Creature
{
    int _strength, _agility, _intelligence;

public:
    const int &strength() const { return _strength; }
    int &strength() { return _strength; }
    const int &agility() const { return _agility; }
    int &agility() { return _agility; }
    const int &intelligence() const { return _intelligence; }
    int &intelligence() { return _intelligence; }
};
```
```getter / setter```가 정의되어 있는 평범한 클래스이다.  
별 문제가 보이지 않는다.  
&nbsp;  

하지만 문제는 필드들을 집합적으로 사용할 때 발생한다.  
```c++
class Creature
{
    int _strength, _agility, _intelligence;

public:
    // getter / setter 생략

    int sum() const
    {
        return _strength + _agility + _intelligence;
    }

    double average() const
    {
        return sum() / 3.0;
    }

    int max() const
    {
        return std::max(std::max(_strength, _agility), _intelligence);
    }
};
```
만약 생명체에 근력, 민첩성, 지능 외의 health라는 건강 멤버 변수가 추가된다면 어떻게 될까?  
sum(), average(), max()의 구현부는 그에 맞춰 모두 변해야 하는데... 최악이다.  
새로운 능력치가 추가될 때 마다 함수의 구현부를 맨날 바꾸는 것은 굉장히 비효율적이고 개발자가 수정하면서 실수할 확률도 높다.  
&nbsp;  

Creature에서 멤버 변수를 밑과 같이 바꿔보자.  
```c++
enum Abilities
{
    _strengh,
    _agility,
    _intelligence,
    _count
};
std::array<int, _count> abilities;
```
enum을 사용하여 배열의 특정 원소를 참조할 수 있다.  
&nbsp;  

멤버 변수의 형태가 변한 Creature 클래스는 밑과 같을 것이다.  
```c++
class Creature
{
    // 멤버 변수 생략

public:
    const int &strength() const { return abilities[_strengh]; }
    int &strength() { return abilities[_strengh]; }
    const int &agility() const { return abilities[_agility]; }
    int &agility() { return abilities[_agility]; }
    const int &intelligence() const { return abilities[_intelligence]; }
    int &intelligence() { return abilities[_intelligence]; }

    int sum() const
    {
        return std::accumulate(abilities.begin(), abilities.end(), 0);
    }

    double average() const
    {
        return sum() / (double)_count;
    }

    int max() const
    {
        return *std::max_element(abilities.begin(), abilities.end());
    }
};
```
이제 새로운 능력치가 생겨 멤버 변수가 늘어나도 sum(), average(), max()의 구현부를 그대로 써먹을 수 있다.  
프로그래머는 새로운 멤버 변수에 대한 getter / setter 만 정의해주면 된다.  
&nbsp;  

## 그루핑  

서로 다른 자료형의 객체들을 컴포지트 패턴을 이용하여 묶음 처리하는 방법을 알아보자.  
다양한 그래픽 객체들을 그리는 상황을 예시로 들어 설명하겠다.  
&nbsp;  

서로 다른 자료형에 공통점을 부여할 인터페이스를 만들어보자.  
```c++
struct GraphicObject
{
    virtual void draw() = 0;
};
```
&nbsp;  

원, 사각형 클래스를 만들어보자.  
```c++
class Circle : public GraphicObject
{
public:
    void draw() { std::cout << "This is Circle\n"; }
};

class Square : public GraphicObject
{
public:
    void draw() { std::cout << "This is Square\n"; }
};
```
그리기 함수를 정의해준다.  
&nbsp;  

그래픽 객체들을 묶음 처리하는 그룹 클래스도 만들어주자.  
```c++
class Group : public GraphicObject
{
    std::string group_name;
    std::vector<GraphicObject *> objects;

public:
    Group(const std::string &name = "") : group_name{name} {}

    for (auto &obj : objects)
    {
        std::cout << group_name << ": ";
        obj->draw();
    }

    void add(GraphicObject &obj) { objects.push_back(&obj); }
};
```
draw() 함수에서 그루핑된 객체들의 draw() 함수들을 호출하는 것을 볼 수 있다.  
&nbsp;  

이렇게 만들어진 클래스들을 활용해보자.  
```c++
Group group_1("first group");
Circle circle_1;
Square square_1;
group_1.add(circle_1);
group_1.add(square_1);

Group group_2("second group");
Circle circle_2;
group_2.add(circle_2);

group_1.add(group_2);

group_1.draw();
```
draw() 인터페이스는 모두 동일하기에 위 예시처럼 그룹에 그룹을 추가하는 것도 가능해진다.  
&nbsp;  

출력 결과는 밑과 같다.    
```
This is first group
first group: This is Circle
first group: This is Square
first group: This is second group
second group: This is Circle
```
GraphicObject 인터페이스를 사용하는 객체들은 서로 자료형이 달라도 draw() 함수라는 공통점이 생겨 묶음 처리가 가능해진다.  
&nbsp;  

## 동일한 구현부  

이전 예시는 인터페이스는 모두 동일하지만 자료형에 따라 인터페이스의 구현부가 모두 달랐다.  
이번에는 각기 다른 자료형이 똑같은 구현부를 가진 인터페이스를 사용한다.  
&nbsp;  

생명체의 몸은 여러 기관들이 역할을 나누어 맡아 돌아간다.  
기관은 여러 조직들이 합쳐져 돌아간다.  
이런 생명체 기관, 조직들을 이용한 예시로 설명하겠다.  
먼저 밑과 같은 인터페이스를 만들자.  
```c++
struct Interactor
{
    virtual void connect_to(Interactor &) = 0;
};
```
&nbsp;  

밑과 같은 조직 클래스도 있다.  
모든 구현은 종속성이 꼬이지 않도록 .h, .cpp로 나누어 전방 선언 등을 이용해 진행한다.  
```c++
// 헤더 파일 구현부
class Tissue : public Interactor
{
    int id;

public:
    std::vector<Tissue *> in, out;

    Tissue();
    void connect_to(Interactor &);
};

// 소스 파일 구현부
Tissue::Tissue()
{
    static int id = 1;
    this->id = id++;
}

void Tissue::connect_to(Interactor &other)
{
    Tissue *tissue = dynamic_cast<Tissue *>(&other);
    if (tissue)
    {
        out.push_back(tissue);
        tissue->in.push_back(this);
    }
}
```
조직을 생성할 때마다 각 조직을 구별하기 위한 고유한 id가 매겨진다.  
서로 다른 두 조직을 연결하기 위해 connect_to() 함수를 구현한다.  
&nbsp;  

생명체 기관인 심장 클래스를 만들어보자.  
```c++
// 헤더 파일 구현부
class Heart : public Interactor, public std::vector<Tissue>
{
    int pump_count;

public:
    Heart(const std::vector<Tissue> &tissues = {});
    void connect_to(Interactor &other);
};

// 소스 파일 구현부
Heart::Heart(const std::vector<Tissue> &tissues)
{
    pump_count = 0;
    this->assign(tissues.begin(), tissues.end());
}

void Heart::connect_to(Interactor &other)
{
    Heart *heart = dynamic_cast<Heart *>(&other);
    if (heart)
    {
        for (auto &in : *this)
            for (auto &out : *heart)
                in.connect_to(out);
        return;
    }

    Tissue *tissue = dynamic_cast<Tissue *>(&other);
    if (tissue)
    {
        for (auto &in : *this)
            in.connect_to(*tissue);
    }
}

void Heart::pump()
{
    std::cout << "Current Pump Count: " << ++pump_count << std::endl;
}
```
std::vector<>를 상속하는 덕 타이핑은 그닥 좋진 않지만 이번 예시에서는 사용한다.  
Heart의 connect_to 함수를 보면 Heart.connect_to(Tissue), Heart.connect_to(Heart) 두 가지를 고려해야 하기에 구현부가 비대해졌다.  
&nbsp;  

문제는 Tissue의 connect_to 함수도 Tissue.connect_to(Heart) 상황을 추가적으로 고려해줘야 하기에 밑과 같이 변경해야 한다.  
```c++
void Tissue::connect_to(Interactor &other)
{
    Tissue *tissue = dynamic_cast<Tissue *>(&other);
    if (tissue)
    {
        out.push_back(tissue);
        tissue->in.push_back(this);
        return;
    }

    Heart *heart = dynamic_cast<Heart *>(&other);
    if (heart)
        heart->connect_to(*this);
}
```
&nbsp;  

여기서 폐 기관 클래스를 추가해보자.  
```c++
// 헤더 파일 구현부
class Lung : public Interactor, public std::vector<Tissue>
{
    float oxygen_content;

public:
    Lung(const std::vector<Tissue> &tissues = {});
    void connect_to(Interactor &other);
    void Inhale(float);
    void Exhale(float);
};

// 소스 파일 구현부
Lung::Lung(const std::vector<Tissue> &tissues)
{
    oxygen_content = 0.f;
    this->assign(tissues.begin(), tissues.end());
}

void Lung::connect_to(Interactor &other)
{
    std::vector<Tissue> *vec = dynamic_cast<std::vector<Tissue> *>(&other);
    if (vec)
    {
        for (auto &in : *this)
            for (auto &out : *vec)
                in.connect_to(out);
        return;
    }

    Tissue *tissue = dynamic_cast<Tissue *>(&other);
    if (tissue)
    {
        for (auto &in : *this)
            in.connect_to(*tissue);
    }
}

void Lung::Inhale(float oxygen_from_outside)
{
    oxygen_content += oxygen_from_outside;
    std::cout
        << "Inhale... " << oxygen_from_outside
        << "amount of oxygen from outside.\nTotal Oxygen in body: "
        << oxygen_content << std::endl;
}

void Lung::Exhale(float amount_of_oxygen_for_exhale)
{
    oxygen_content = std::max(oxygen_content - amount_of_oxygen_for_exhale, 0.f);
    std::cout << "Exhale... Total Oxygen in body: " << oxygen_content << std::endl;
}
```
구현 상태를 보면 connect_to() 함수에서 std::vector<>를 공통적으로 상속하고 있는 Heart, Lung 자료형을 묶어서 처리하는 것을 볼 수 있다.  
&nbsp;  

클래스 Lung이 추가됨에 따라 Tissue, Heart 클래스의 connect_to() 함수 구현부도 밑처럼 바뀌어야 한다.  
```c++
void Tissue::connect_to(Interactor &other)
{
    Tissue *tissue = dynamic_cast<Tissue *>(&other);
    if (tissue)
    {
        out.push_back(tissue);
        tissue->in.push_back(this);
        return;
    }

    Heart *heart = dynamic_cast<Heart *>(&other);
    if (heart)
    {
        heart->connect_to(*this);
        return;
    }

    Lung *lung = dynamic_cast<Lung *>(&other);
    if (lung)
        lung->connect_to(*this);
}

void Heart::connect_to(Interactor &other)
{
    std::vector<Tissue> *vec = dynamic_cast<std::vector<Tissue> *>(&other);
    if (vec)
    {
        for (auto &in : *this)
            for (auto &out : *vec)
                in.connect_to(out);
        return;
    }

    Tissue *tissue = dynamic_cast<Tissue *>(&other);
    if (tissue)
    {
        for (auto &in : *this)
            in.connect_to(*tissue);
    }
}
```
Heart 클래스의 connect_to() 구현부는 Lung 클래스와 동일하다.  
문제는 Tissue 클래스인데 해당 클래스는 std::vector<>를 상속하는 것이 아니기에 Lung, Heart 클래스의 connect_to() 함수와 구현부가 달라질 수 밖에 없다.  
게다가 std::vector<>에는 connect_to() 멤버 함수가 없기 때문에 Lung, Heart 클래스를 묶어 처리할 방법이 없다.  
결국엔 ```std::vector<Tissue>```를 상속하는 새로운 클래스가 탄생할 수록 Tissue의 connect_to() 함수 구현부는 새로운 연결 상황을 고려하기 위해 비대해질 수 밖에 없다.  
&nbsp;  

이를 해결하기 위해 밑과 같이 템플릿을 이용해 인터페이스 구조를 바꿔준다.   
```c++
class Tissue;

template <typename Self>
struct Interactor
{
    template <typename T>
    void connect_to(T &other)
    {
        for (Tissue &from : *static_cast<Self *>(this))
        {
            for (Tissue &to : other)
            {
                from.out.push_back(&to);
                to.in.push_back(&from);
            }
        }
    }
};
```
위 코드는 굉장히 교묘하게 각종 문제들을 잘 피해가고 있다.  
일단 Interactor는 이제 인터페이스에서 추상 클래스로 바뀌었다.  
connect_to()를 템플릿 함수로 구현해서 다양한 자료형으로 전달되는 함수 인자를 동일한 방식으로 처리한다.  
어떤 자료형이 오던 범위 기반 for문을 이중으로 돌릴 뿐이다.  
&nbsp;  

첫번째 교묘한 점은 템플릿의 특성을 이용한 것이다.  
템플릿 함수는 컴파일이 진행되면서 생성되는 함수이기에 실제 사용되지 않으면 껍데기만 존재한다.  
따라서 내부에 말도 안되는 문법이 적혀있어도 함수가 실제 사용되지만 않으면 컴파일이 정상적으로 처리된다! (예를 들어 ```Tissue tissue = 1;```과 같은 구문)  
물론 ```"특정 자료형이 존재는 한다."```라는 것을 증명해야 하여 ```class Tissue;``` 전방 선언을 해야 한다.  
이와 같은 특성 덕분에 ```#include "Tissue.h"```를 하지 않고 전방 선언만 해도 컴파일 에러가 발생하지 않는다.  
즉 connect_to() 함수의 구현부에서 Tissue의 멤버 변수로 out, in이 존재하는지 여부는 별로 중요하지 않다.  
중요한 것은 connect_to() 함수가 사용되는 순간으로 그 때 컴파일러가 Tissue 클래스에 대한 정보를 알고 있으면 코드가 정상적으로 작동하게 된다.    
&nbsp;  

두번째 교묘한 점은 ```static_cast<Self *>(this)``` 부분이다.  
Interactor 클래스 자체는 범위 기반 for문이 순회할 때 미리 정의된 begin(), end() 함수가 없어 대응이 불가능하다.  
따라서 자식 클래스 자료형으로 형변환을 시켜 ```begin() / end()``` 함수 구현부를 자식 클래스에게 떠넘기기 위해 Interactor 클래스를 템플릿 클래스로 만들었다.  
즉 자식 클래스들은 begin(), end() 함수가 구비되어 있어야 connect_to()를 사용할 수 있다.  
&nbsp;  

먼저 Tissue 클래스의 변화를 살펴보자.  
```c++
class Tissue : public Interactor<Tissue>
{
    int id;

public:
    std::vector<Tissue *> in, out;

    Tissue();
    Tissue *begin() { return this; }
    Tissue *end() { return this + 1; }
};
```
이제 Interactor를 상속할 때 템플릿 타입에 자신의 타입을 넘겨준다.  
connect_to() 함수의 구현부도 없어졌다.  
그리고 배열형이 아닌 Tissue 클래스는 기본적으로 구비되어 있는 begin(), end() 함수가 따로 없기 때문에 따로 구현해준다.  
이렇게 begin(), end()를 정의해주면 Tissue 객체를 이용하여 배열처럼 범위 기반 for문을 돌릴 수 있다.    
특이한 점은 ```this + 1``` 부분일 텐데 얼핏보면 이상한 주소값을 참조할 수 있는 위험한 구현(UB : Undefined Behavior)으로 보이지만 실상은 아니다.  
```this + 1```은 단지 다음 객체를 가리키는 역할을 하는데 Tissue 자료형은 배열 형태가 아니라 ```this + 1```은 바로 배열의 끝을 나타낸다.  
즉 범위 기반 for의 마침표를 찍기 위한 표현일 뿐이다.  
&nbsp;  

Lung, Heart 클래스의 변화를 살펴보자.  
```c++
class Lung : public Interactor<Lung>, public std::vector<Tissue>
{
    float oxygen_content;

public:
    Lung(const std::vector<Tissue> &tissues = {});
    void Inhale(float);
    void Exhale(float);
};

class Heart : public Interactor<Heart>, public std::vector<Tissue>
{
    int pump_count;

public:
    Heart(const std::vector<Tissue> &tissues = {});
    void pump();
};
```
Interactor를 상속할 때 템플릿 타입에 자신의 타입을 넘겨주었고 connect_to() 함수의 구현부도 없다.  
Lung, Heart 클래스는 애초에 std::vector<> 형을 상속하였기에 따로 begin(), end() 함수를 정의할 필요가 없다.  
&nbsp;  

밑은 실제 사용 예시이다.  
```c++
Tissue tissue_01, tissue_02, tissue_03;
Heart heart({Tissue{}, Tissue{}, Tissue{}});
Lung lung({Tissue{}, Tissue{}});

tissue_01.connect_to(tissue_02);
tissue_02.connect_to(tissue_03);

heart.connect_to(tissue_01);
lung.connect_to(heart);

tissue_03.connect_to(heart);
```
하나의 템플릿 함수만 잘 구현하여 다양한 상황에 써먹을 수 있다.  

## 요약  

1. 컴포지트 패턴은 여러 자료형에게 동일한 인터페이스를 제공하는 패턴이다.  

2. 명시적으로 인터페이스 멤버를 두는 방식이 있다.  

3. begin(), end() 멤버 함수를 이용해 덕-타이핑하는 방식이 있는데 특히 이 경우에 단일 객체를 배열처럼 다루는 기법이 유용하게 사용된다.  

4. 같은 자료형의 멤버 변수를 배열로 묶어 처리하는 방식이 있다.  