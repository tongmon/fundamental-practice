# Visitor Pattern  

특정 자료형에 따라 처리 방식이 달라지는 방문자를 이용해 일을 처리하는 패턴이다.  
실제 처리 로직만 방문자에 담기고 데이터 구조는 따로 관리되기에 특정 데이터에 대한 로직 확장이 유연하다.  
&nbsp;  

## 방문자 사용 이유  

해당 패턴을 왜 이용하는지 알기 위해 수식 처리와 관련된 예시를 하나 보자.  
먼저 밑과 같은 인터페이스가 있다.  
```c++
struct Expression
{
    virtual void print(std::ostringstream &oss) = 0;
};
```
일단 인터페이스부터 [열림-닫힘 원칙](https://github.com/tongmon/fundamental-practice/blob/master/Programming%20Pattern/SOLID.md#%EC%97%B4%EB%A6%BC-%EB%8B%AB%ED%9E%98-%EC%9B%90%EC%B9%99-ocp)을 위배하고 있다.  
print() 함수말고 eval()과 같은 다른 로직이 필요할 때 Expression을 수정해줘야 하기에 손이 많이 간다.  
설명을 위해 계속 진행한다.  
&nbsp;  

덧셈 계산식에 대한 클래스다.  
```c++
struct AdditionExpression : Expression
{
    Expression *left, *right;

    AdditionExpression(Expression *const left, Expression *const right)
        : left{left}, right{right}
    {
    }

    ~AdditionExpression()
    {
        delete left;
        delete right;
    }

    void print(std::ostringstream &oss) override
    {
        oss << "(";
        left->print(oss);
        oss << "+";
        right->print(oss);
        oss << ")";
    }
};
```
덧셈은 우항과 좌항에 대한 처리가 필요하다.  
&nbsp;  

제일 말단부인 숫자에 대한 클래스는 밑과 같다.  
```c++
struct NumberExpression : Expression
{
    double value;
    explicit NumberExpression(const double value)
        : value{value}
    {
    }

    void print(std::ostringstream &oss) override
    {
        oss << value;
    }
};
```
자신의 값을 출력할 뿐이다.  
&nbsp;  

활용은 밑과 같다.  
```c++
auto e = new AdditionExpression{
    new NumberExpression{1},
    new AdditionExpression{
        new NumberExpression{2},
        new NumberExpression{3}}};

std::ostringstream oss;
e->print(oss);

std::cout << oss.str() << std::endl;

// 출력 결과: (1+(2+3))
```
잘 작동은 하지만 문제가 있다.  

Expression 클래스는 [열림-닫힘 원칙](https://github.com/tongmon/fundamental-practice/blob/master/Programming%20Pattern/SOLID.md#%EC%97%B4%EB%A6%BC-%EB%8B%AB%ED%9E%98-%EC%9B%90%EC%B9%99-ocp)를 위배하고 있다.  
print()말고 eval()과 같이 식의 계산 값을 반환해주는 함수를 추가해야 한다면 Expression도 수정해야 하고 AdditionExpression, NumberExpression도 수정해야 한다.  
CharExpression, MultiplyExpression과 같이 다양한 수식 클래스가 이미 존재하고 있었다면 문제는 더 커진다.  

[단일 책임 원칙](https://github.com/tongmon/fundamental-practice/blob/master/Programming%20Pattern/SOLID.md#%EB%8B%A8%EC%9D%BC-%EC%B1%85%EC%9E%84-%EC%9B%90%EC%B9%99-srp)도 위배하고 있다.  
eval() 함수가 추가되면 Expression은 출력과 계산 두 가지의 일을 모두 처리하게 된다.  
이렇게 하나의 클래스를 만능으로 만들지 말고 ExpressionPrinter, ExpressionEvaluator로 나누는 것이 바람직하다.  
&nbsp;  

## Reflective 방문자  

dynamic_cast를 이용한 방문자를 만들어보자.  
일단 수식 인터페이스는 밑과 같이 바뀐다.  
```c++
struct Expression
{
    virtual ~Expression() = default;
};
```
수식의 종류는 다양하지만 **수식**이라는 공통점이 있기에 Expression은 남아있어야 한다.  
dynamic_cast는 기본적으로 자식 클래스에서 부모 클래스로의 **업 캐스팅**은 허용하지만 그 반대인 **다운 캐스팅**은 금지한다.  
하지만 한 가지 예외가 있는데 부모 클래스가 다형성을 갖춘 경우에는 다운 캐스팅도 허용된다.  
Reflective 방문자는 다운 캐스팅을 이용하기에 Expression에 가상 소멸자를 만들어 다형성을 부여한다.  
&nbsp;  

각 수식은 밑과 같다.  
```c++
struct DoubleExpression : Expression
{
    double value;
    explicit DoubleExpression(const double value)
        : value{value}
    {
    }
};

struct AdditionExpression : Expression
{
    Expression *left, *right;

    AdditionExpression(Expression *const left, Expression *const right)
        : left{left}, right{right}
    {
    }

    ~AdditionExpression()
    {
        delete left;
        delete right;
    }
};
```
print()에 대한 구현은 방문자가 처리하기에 필요없다.  
&nbsp;  

다음은 출력에 대한 방문자다.  
```c++
struct ExpressionPrinter
{
    std::ostringstream oss;

    void print(Expression *e)
    {
        if (auto de = dynamic_cast<DoubleExpression *>(e))
        {
            oss << de->value;
        }
        else if (auto ae = dynamic_cast<AdditionExpression *>(e))
        {
            oss << "(";
            print(ae->left);
            oss << "+";
            print(ae->right);
            oss << ")";
        }
    }

    std::string str() const
    {
        return oss.str();
    }
};
```
dynamic_cast를 사용해 어떤 수식인지 분류하여 처리한다.  
해당 방식의 큰 단점은 런타임에 타입 체크를 진행하는 것이다.  
새로운 수식 CharExpression가 추가되더라도 print() 함수에 CharExpression에 맞는 분기 처리가 되어있지 않으면 무시된다.  
또 다른 단점은 로직이 분기로 늘어지게 되어 너저분하다는 것이다.  
&nbsp;  

실제 사용법을 보면 방문자 패턴이 대략 어떻게 쓰이는지 알 수 있다.  
```c++
auto e = new AdditionExpression{
    new DoubleExpression{1},
    new AdditionExpression{
        new DoubleExpression{2},
        new DoubleExpression{3}}};

std::ostringstream oss;
ExpressionPrinter ep;

ep.print(e);
std::cout << ep.str() << std::endl;
```
출력 처리를 방문자가 진행하기에 수식을 생성해놓고 방문자에게 전달한다.  
&nbsp;  

## Dispatch  

앞으로 살펴볼 순환, 비순환 방문자 기법을 이해하기 위해 Dispatch라는 것을 알아야 한다.  
일단 예시부터 보자.  
```c++
struct Something
{
    virtual ~Something() = default; // 다형성 부여를 위해 추가함
};
struct Foo : Something
{
    void print()
    {
        std::cout << "Foo\n";
    }
};
struct Bar : Something
{
    void print()
    {
        std::cout << "Bar\n";
    }
};

void func(Foo *foo)
{
    foo->print();
}
void func(Bar *bar)
{
    bar->print();
}
```
위와 같이 구조체, 함수들이 정의되어 있다.  
&nbsp;  

일단 밑의 예시는 잘 작동한다.  
```c++
Foo *foo = new Foo;
func(foo);
```
Foo가 잘 출력된다.  
&nbsp;  

하지만 밑 예시는 컴파일되지 않는다.  
```c++
Something *something = new Foo; // 업 캐스팅
func(something);
```
문제는 업 캐스팅이다.  
업 캐스팅이 된 후 something 포인터를 바로 ```Foo *``` 자료형으로 사용할 수는 없다.  
따라서 ```func(dynamic_cast<Foo *>(something));``` 이렇게 바꿔야만 컴파일이 수행된다.  
별도의 형변환 없이 원본 객체 유형을 파악하여 해당 자료형을 인자로 받는 func() 함수를 호출하는 방법이 있을까?   
&nbsp;  

**이중 디스패치**를 이용하면 가능하다.  
해당 기법은 두 가지 원리를 이용한다.  

1. 다형성 클래스에 대해 가상 함수 호출 시 원본 객체에 대한 함수가 호출된다.  
    예를 들어 보자.  
    ```c++
    struct Something
    {
        virtual void print(){};
    };

    Something *something = new Foo;
    something->print();
    ```
    print() 함수가 위와 같이 가상 함수로 바뀌었다고 해보자.  
    가상 함수가 존재하는 Something 클래스는 다형성 클래스다.  
    위에서 호출한 print() 함수는 Foo::print() 함수다.  

2. this 포인터는 해당 객체의 형식을 가진다.  
    Foo 클래스 내부적으로 이용되는 this 포인터는 Something형이 아니라 명확하게 Foo형이다.  

위 두 원리를 이용해 **이중 디스패치** 예시를 구현해보자.  
먼저 상호 참조를 방지하기 위해 .hpp, .cpp로 나누어야 한다.  
&nbsp;  

some_func.hpp, some_func.cpp는 밑과 같다.  
```c++
// some_func.hpp
struct Foo;
struct Bar;

void func(Foo *foo);
void func(Bar *bar);

// some_func.cpp
void func(Foo *foo)
{
    foo->print();
}
void func(Bar *bar)
{
    bar->print();
}
```
분할을 했을 뿐, 별 다를 것이 없다.  
&nbsp;  

some_class.hpp는 밑과 같다.  
```c++
struct Something
{
    virtual void call() = 0;
};

struct Foo : Something
{
    void call() override;
    void print();
};

struct Bar : Something
{
    void call() override;
    void print();
};
```
순수 가상 함수 call()가 새로 생겼다.  
Foo, Bar에서 call() 함수를 재정의해준다.  
&nbsp;  

중요한 some_class.cpp이다.  
```c++
void Foo::call()
{
    func(this);
}
void Foo::print()
{
    std::cout << "Foo\n";
}
void Bar::call()
{
    func(this);
}
void Bar::print()
{
    std::cout << "Bar\n";
}
```
핵심적인 부분은 call()의 내부 구현이다.  
Foo 내부에서 ```func(this);```를 하면 this 포인터의 자료형이 명확하기에 ```void func(Foo *foo)```가 호출될 것이다.  
&nbsp;  

결과적으로 밑과 같이 사용이 가능하다.  
```c++
Something *something_1 = new Foo;
something_1->call(); // Foo::print() 호출

Something *something_2 = new Bar;
something_2->call(); // Bar::print() 호출
```
단순히 call() 함수의 호출만으로 원본 객체에 알맞은 print() 함수를 호출할 수 있다.  
이것이 굉장히 유용한 이유는 print() 함수가 가상 함수가 아니기 때문이다.  
따라서 Foo, Bar에 기능이 확장되어도 부모 클래스인 Something은 수정이 필요없다.  
&nbsp;  

## 순환 방문자  

해당 방문자 기법은 **이중 디스패치**를 활용한다.  
따라서 구현을 .hpp, .cpp로 나눠야 한다.  
방문자 기법은 전통적으로 다음 이름 규칙을 따른다.  

* 방문자의 멤버 함수는 visit()이다.  

* 방문자를 이용할 클래스마다 구현될 멤버 함수는 accept()다.  

먼저 Expression을 바꿔보자.  
```c++
// expression.hpp
struct ExpressionVisitor;

struct Expression
{
    virtual void accept(ExpressionVisitor *visitor) = 0;
};
```
일단 수식 클래스는 모두 자신만의 accept() 함수가 구현되어야 한다.  
accept() 함수는 방문자를 인자로 들인다.  
&nbsp;  

각 수식은 다음과 같이 구현된다.  
```c++
// expression.hpp
struct NumberExpression : Expression
{
    double value;
    explicit NumberExpression(const double value)
        : value{value}
    {
    }

    void accept(ExpressionVisitor *visitor) override;
};

struct AdditionExpression : Expression
{
    Expression *left, *right;

    AdditionExpression(Expression *const left, Expression *const right)
        : left{left}, right{right}
    {
    }

    ~AdditionExpression()
    {
        delete left;
        delete right;
    }

    void accept(ExpressionVisitor *visitor) override;
};
```
accept() 함수를 제외한 구현은 [Reflective 방문자](#reflective-방문자)와 동일하다.  
&nbsp;  

accept() 함수의 구현은 밑과 같다.  
```c++
// expression.cpp
void NumberExpression::accept(ExpressionVisitor *visitor)
{
    visitor->visit(this);
}

void AdditionExpression::accept(ExpressionVisitor *visitor)
{
    visitor->visit(this);
}
```
단순히 visit() 함수만 호출하는 용도이기에 한 번만 정의해놓고 다시 건드릴 필요가 없다.  
즉 세부적인 처리는 방문자가 진행한다.  
각 visit()은 전달된 this 포인터의 자료형에 따라 각기 다른 로직을 처리하게 된다.   
&nbsp;  

방문자의 Base 자료형은 밑과 같다.  
```c++
// expression_visitor.hpp
struct DoubleExpression;
struct AdditionExpression;

struct ExpressionVisitor
{
    virtual void visit(DoubleExpression *de) = 0;
    virtual void visit(AdditionExpression *ae) = 0;
};
```
다양한 기능을 처리하는 방문자를 만들기 위해 필요하다.  
&nbsp;  

출력 기능을 가진 방문자는 밑과 같다.  
```c++
// expression_visitor.hpp
struct ExpressionPrinter : ExpressionVisitor
{
    std::ostringstream oss;
    std::string str() const
    {
        return oss.str();
    }
    void visit(NumberExpression *de) override;
    void visit(AdditionExpression *ae) override;
};
```
출력을 위한 문자열 스트림이 존재한다.  
&nbsp;  

각 visit 함수의 세부 구현이다.  
```c++
// expression_visitor.cpp
void ExpressionPrinter::visit(NumberExpression *de)
{
    oss << de->value;
}

void ExpressionPrinter::visit(AdditionExpression *e)
{
    oss << "(";
    e->left->accept(this);
    oss << "+";
    e->right->accept(this);
    oss << ")";
}
```
```ExpressionPrinter::visit()``` 함수를 보면 알겠지만 ```visit() --> accept() --> visit()...``` 와 같은 호출이 이루어질 것이다.  
&nbsp;  

활용은 밑과 같다.  
```c++
auto e = new AdditionExpression{
    new NumberExpression{1},
    new AdditionExpression{
        new NumberExpression{2},
        new NumberExpression{3}}};

std::ostringstream oss;
ExpressionPrinter printer;

printer.visit(e);
std::cout << printer.str() << std::endl;
```
해당 방식의 주요 장점은 컴파일 시간에 방문자 구현이 무결한지 확인이 가능하다는 것이다.  
빼기 수식인 SubtractionExpression가 추가되었다면 SubtractionExpression 자료형에 대한 visit() 함수도 구현해줘야 컴파일이 되기에 안전하다.  
그리고 세부 로직이 각 자료형에 따른 visit() 함수로 묶이기에 분기 처리로 늘어지는 [Reflective 방문자](#reflective-방문자) 방식보다 직관적이다.  
&nbsp;  

### 방문자 추가하기  

방문자 패턴의 강점은 확장성이다.  
해당 수식 클래스에 계산 기능을 확장해보자.  
밑은 계산 기능을 수행하는 방문자다.  
```c++
// expression_visitor.hpp
struct ExpressionEvaluator : ExpressionVisitor
{
    double result;
    void visit(NumberExpression *de) override;
    void visit(AdditionExpression *ae) override;
};
```
결과 값 저장을 위한 double 변수가 존재한다.  
&nbsp;  

visit 함수의 세부 구현은 밑과 같다.  
```c++
// expression_visitor.cpp
void ExpressionEvaluator::visit(NumberExpression *de)
{
    result = de->value;
}

void ExpressionEvaluator::visit(AdditionExpression *ae)
{
    ae->left->accept(this);
    auto temp = result;
    ae->right->accept(this);
    result += temp;
}
```
이렇게 ExpressionVisitor를 상속하는 방문자에 대한 코드만 추가해주면 끝이다.  
이미 구현되어 있는 Expression 구조체들은 수정할 것이 없기에 확장이 편하다.  
&nbsp;  

활용은 밑과 같다.  
```c++
auto e = new AdditionExpression{/* 동일 수식 */};

ExpressionEvaluator evaluator;

evaluator.visit(e);
std::cout << evaluator.result << std::endl;
```
방문자만 바꿔주면 새로운 기능을 이용할 수 있다.  
&nbsp;  

## 비순환 방문자  