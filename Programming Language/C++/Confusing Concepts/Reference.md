# Reference  

C++에서 변수가 어떻게 분류되고 그 분류가 참조에 어떻게 이용되는지 알아보자.  
&nbsp;  

## Move vs Copy  

변수에 분류에 앞서 이동과 복사의 사이를 알아야 한다.  

일단 복사는 이미 알고 있을 것이다.  
```c++
struct Object
{
    int id;
    double accuracy;
};

Object a{1, 7.77}, b;
b = a;
```
```b = a;```에서 발생한 것이 복사다.  

a의 주소를 0x002, b의 주소를 0x004라고 하자.  
저장 상태는 밑과 같이 흘러간다.  
```
------------------------------------------
[ 0x002  a ] (1, 7.77) | [ 0x004  b ] null
------------------------------------------
                    ↓
-----------------------------------------------
[ 0x002  a ] (1, 7.77) | [ 0x004  b ] (1, 7.77)
-----------------------------------------------            
```
&nbsp;  

이동은 단지 메모리의 값이 다른 곳으로 움직이기만 한다.  
```c++
Object *a = new Object{1, 7.77}, *b = nullptr;
b = a;
a = nullptr;
```
따라서 이동을 논할 때는 반드시 메모리 주소의 변경이 있어야 한다.  

a 포인터 주소를 0x002, b 포인터 주소를 0x004라고 하자.  
저장 상태는 밑과 같이 흘러간다.  
```
------------------------------------------
[ 0x002  a ] (1, 7.77) | [ 0x004  b ] null
------------------------------------------
                    ↓
------------------------------------------
[ 0x000  a ] null | [ 0x002  b ] (1, 7.77)
------------------------------------------                  
```
```(1, 7.77)``` 값은 그대로인데 이 녀석이 딸려있는 주소 값이 변경되었다.  
Object 구조체의 크기가 커질수록 복사보다 이동이 더 빠르게 수행될 것이다.  
&nbsp;  

## 값 분류  

C++11 이후에는 우측값 참조가 도입되면서 값이 다양하게 분류된다.  
lvalue, xvalue, prvalue, glvalue, rvalue 이렇게 5개로 나뉜다. (물론 예외적인 녀석들은 따로 분류되지만 여기선 다루지 않는다.)  
밑에서 계속 등장할 단어인 식별자는 ```자기만의 개인적인 공간을 가지고 있는 녀석``` 정도로 생각하면 된다.  
주의할 점은 ```int &&```, ```int &```, ```int *```, ```int```는 모두 타입이지 값이 아니다. (혼동하지 말자)  
&nbsp;  

### lvalue  

left value, 좌측값이다.  
식별자를 가지면서 이동할 수 없는 값들이다.  
즉 자기 소유의 주소를 가지고 있고 그 주소에 상주하며 바꾸려하지 않는 값이라고 보면 된다.  
```c++
int a = 1;

int &foo()
{
    return a;
}

int main()
{
    int b = 2, c = 3;
    int *ptr = &a;
    foo() = 4;
}
```
위 예시에서 a, b, c, foo()는 lvalue이다.  
이외에도 전위 증감 연산자 ```++a```, ```"hello world"```와 같은 문자열 [literal](https://www.geeksforgeeks.org/literals-in-c-cpp-with-examples/) 등 많은 것들이 lvalue이다.  
lvalue는 보통 좌측에 위치하고 ```&``` 연산자를 통해 주소 값을 획득할 수 있다.  
```&```를 통해 주소 값을 획득하는 특징은 lvalue에만 적용되기에 어떤 값이 어떤 분류에 속하는지 헷갈린다면 ```&```를 붙여보자.  
&nbsp;  

### prvalue  

pure right value의 줄임말이다.  
식별자가 없고 이동할 수 있는 값이다.  
표현식이 사용될 때 컴파일러가 즉시 만들고 쓰인 후 표현식이 끝나면 즉시 소멸되는 임시 변수들이다. (물론 참조로 수명 연장을 할 순 있다.)   
대표적으로 ```"hello world"```와 같은 문자열 [literal](https://www.geeksforgeeks.org/literals-in-c-cpp-with-examples/)을 제외한 모든 [literal](https://www.geeksforgeeks.org/literals-in-c-cpp-with-examples/)은 prvalue이다.  
```c++
int a = 10;
char b = 'c';
std::string("temporary");

int add(int c, int d)
{
    return c + d;
}
```
위에서 등장한 10, 'c' 값은 prvalue이다.  
```std::string("temporary")```와 같은 임시 객체도 prvalue이다.  
add()와 같이 참조가 아닌 함수의 반환 값도 prvalue이다.  
```a < b```, ```a++```의 결과로 얻어지는 값들도 prvalue이다.  
&nbsp;  

### xvalue  

식별자를 가지면서 이동할 수 있는 값들이다.  
expire의 x에서 따온 이름이기에 만료되어 가는 값이라고도 한다.  
만료되면 쓸 수 없기에 해당 값이 사라지기 전에 ```가로채기``` 위해 이용된다.  
대표적으로 **우측값 참조**를 반환하는 함수의 반환 값, **우측값 참조**로 형변환되는 표현식이 이에 해당된다.  
[우측값 참조](#rvalue-참조)에 대한 설명을 보면 이해가 더 쉬울 것이다.  
```c++
std::move("hello world");

char x = 'c';
char &&y = static_cast<char &&>(x);
```
```std::move()```는 우측값 참조를 반환하는 대표적인 함수다.  
**우측값 참조**로 형변환한 ```static_cast<char &&>(x)```는 xvalue이다.  
혼동하지 말아야 할 것은 ```static_cast<char &&>(x)```가 xvalue라는 것이지 y는 lvalue이다.  
따라서 y는 이동하지 못한다.  
&nbsp;  

### glvalue  

generalized left value의 줄임말이다.  
xvalue 혹은 lvalue를 칭한다. (즉 prvalue를 제외한 모든 값이다.)  
식별자가 있는 값이다.  
식별자가 있기에 표현식이 종료되어도 수명이 유지된다.  
```c++
int i = 0; // i -> lvalue, 0 -> prvalue
int *ptr = &i; // *ptr -> lvalue
std::move(i); // xvalue
```
위에서 prvalue인 ```0```을 제외하고 ```i```, ```*ptr```, ```std::move(i)```는 모두 glvalue이다.  
&nbsp;  

### rvalue  

right value, 우측 값이다.  
xvalue 혹은 prvalue를 칭한다. (즉 lvalue를 제외한 모든 값이다.)  
이동할 수 있는 모든 값이라고 보면 된다.  
```c++
int num = 10;
std::move(num);
100 - num;
```
num을 제외한 ```10```, ```std::move(num)```, ```100 - num```는 모두 rvalue이다.  
&nbsp;  

## lvalue 참조  

그냥 별명이다.  
```c++
int a = 1;
int &b = a; 
const int &c = b;
const int &d = 3;
```
b는 그냥 a와 일심동체다.  
c도 b와 같지만 수정을 못할 뿐이다.  
중요한 점은 a, b, c 모두 lvalue이기에 좌측값 참조가 가능한 것이다.  
```int &e = 10``` 이런 표현은 10이 prvalue이기 때문에 불가능하다.  
const lvalue 참조를 이용하면 lvalue뿐만 아니라 rvalue 변수도 참조가 가능하다.  
참조는 포인터와 비슷하게 동작하기에 복사가 발생하지 않는다.  
&nbsp;  

## rvalue 참조  

우측값 참조는 rvalue만 참조할 수 있고 좌측값 참조의 한계를 보완하기 위해 탄생했다.  
이동이라는 행위를 [여기](#move-vs-copy)에서 알아봤다.  
좌측값 참조는 단지 특정 객체를 부를 수 있는 이름이 추가될 뿐이지 실제 소유권이 이동되는 것이 아니다.  
C++에서는 실제 소유권이 이동될 것이라는 표식으로 rvalue 참조를 사용한다.  
```c++
int &&a = 1;
std::string &&str = "temporary";
```
위 표현 모두 우측값 참조를 이용하고 있다.  
```"temporary"```는 문자열 literal인데 우측값 참조가 되고 있다...?  
이는 그저 ```"temporary"```가 암시적으로 ```std::string("temporary")```로 바뀌어 rvalue로 판단되었기에 가능한 것이다.  
```int &&a = b```와 같이 우측값 참조에서 lvalue를 참조할 수는 없다.  
&nbsp;  

[xvalue](#xvalue)에서 알아봤듯이 우측값 참조로 받은 값은 다시 lvalue가 된다.  
```c++
void set_x(Object &&val)
{
    Object x = val;
}
```
위에서 val은 이름도 있고 특정 공간을 소유하기에 lvalue이다.  
따라서 val를 x에 할당하면 복사가 발생한다.  

이동을 수행하고 싶다면 밑과 같이 ```std::move()``` 함수를 이용하면 된다.  
물론 이동과 관련된 함수가 구현되지 않았다면 복사가 수행된다.  
```c++
void set_x(Object &&val)
{
    Object x = std::move(val);
}
```
lvalue였던 val을 ```std::move()```가 rvalue로 바꿔주기에 이동이 수행된다.  
```std::move()```는 복잡한 함수가 아니고 그저 lvalue인 녀석을 rvalue로 정적 변환을 해주는 녀석이다.  
&nbsp;  

여기까지 읽어봐도 rvalue 참조가 뭐하러 있는지 이해가 안될 수 있다.  
구체적인 예시를 통해 알아보자.  
```c++
class Object
{
    int id;
    char *name;
  public:
    Object(int id = 0, const char *str = "\0")
    {
        this->id = id;
        name = new char[std::strlen(str) + 1]{
            0,
        };
        std::strcpy(name, str);
    }
    Object(const Object &obj)
    {
        id = id;
        name = new char[std::strlen(obj.name) + 1]{
            0,
        };
        std::strcpy(name, obj.name);
    }
    ~Object()
    {
        delete name;
    }
    Object &operator=(const Object &other)
    {
        if (this != &other)
        {
            delete name;
            name = new char[std::strlen(other.name) + 1]{
                0,
            };
            std::strcpy(name, other.name);
            id = other.id;
        }
        return *this;
    }
};
```
위와 같은 Object 클래스가 있다.  
id와 name을 가지고 있으며 name은 동적 할당되어 특정 문자열이 저장된다.  
&nbsp;  

밑과 같은 코드가 있다.  
```c++
Object a(1, "hello");
Object b = a, c;
c = a;

// 밑은 어떻게 수행될까...?
Object d = std::move(a), e;
e = a;
```
```b = a```가 수행되면 ```Object(const Object &obj)``` 복사 생성자가 수행될 것이다.  
```c = a```는 ```Object &operator=(const Object &other)``` 대입 연산자가 수행될 것이다.  
위 둘은 그냥 복사가 수행된다.  
그렇다면 ```c = std::move(a)```, ```e = a;```는 어떻게 될까?  
이들도 마찬가지로 ```Object(const Object &obj)```, ```Object &operator=(const Object &other)```가 수행된다.  
아직 이동과 관련된 함수가 없기 때문이다.  
&nbsp;  

밑과 같이 복사 이동 생성자, 대입 이동 연산자가 추가되었다.  
```c++
class Object
{
    // 동일 구현부 생략 

    Object(Object &&obj)
    {
        id = id;
        name = obj.name;
        obj.name = nullptr;
    }

    Object &operator=(Object &&other)
    {
        if (this != &other)
        {
            delete name;
            name = other.name;
            id = other.id;
            other.name = nullptr;
        }
        std::cout << "Object &&other\n";
        return *this;
    }
};
```
함수 인자도 ```Object &&```로 다르고 세부 구현도 다르다.  
동적 할당이 새로 발생하지 않고 주소 값만 주고 받는다.  
우측값을 **참조**로 받기 때문에 other 값을 바꾸면 원본 rvalue 값도 바뀐다.  
따라서 ```other.name = nullptr;```와 같은 표현식이 가능하다.  
이동된 객체는 name이 nullptr이기에 껍데기일 뿐이다.  

밑에서 a는 속이 빈 객체가 된다.  
```c++
Object a(1, "hello");
Object d = std::move(a), e;
e = a;
```
```d = std::move(a)```가 수행되면 a는 껍데기일 뿐이기에 그 후에 ```e = a```를 하는 것은 의미가 없다.  
&nbsp;  

이렇게 ```Object &&```, ```const Object &```에 대한 함수가 구비되면 rvalue와 lvalue를 적절히 처리할 수 있다.  
하지만 문제가 남았는데 바로 템플릿과 함께 사용되는 경우이다.    
```c++
Object obj;

template <typename T>
void set_object(T var)
{
    obj = var;
}

int main()
{
    Object a(1, "hello");
    set_object(a); // ①
    set_object(Object(1, "hello")); // ②
}
```
①, ② 모두 T가 Object로 추론된다.  
따라서 이동이 아닌 복사만 발생한다.  
lvalue, rvalue 상관없이 함수 인자의 형태가 ```T var```이기에 무조건 Object로 추론된다.  
이러한 규칙을 **템플릿 타입 추론**이라고 한다.  
&nbsp;  

## universal 참조  

위에서 알 수 있듯이 템플릿 인자는 특정 규칙을 기반으로 추론된다.  
해당 규칙은 [여기](https://en.cppreference.com/w/cpp/language/template_argument_deduction)에 설명되어 있다.  
템플릿과 우측값 참조가 같이 사용되면 각종 장점이 발생하는데 이를 **보편 참조**라고 한다.  
**템플릿 타입 추론**은 **보편 참조**에서 중요한 역할을 한다.  

**보편 참조**를 설명하기 전에 일단 위에서 다뤘던 예시에 대해 좀 더 생각해보자.  
복사만 발생하는 것을 방지하기 위해 Object 클래스를 구성하던 방식을 따라해 밑과 같이 구현할 수 있다.  
```c++
template <typename T>
void set_object(const T &var)
{
    obj = var;
}

template <typename T>
void set_object(T &&var)
{
    obj = std::move(var);
}
```
하지만 이 상태에서 ```set_object()```를 호출해보면 인자가 rvalue던 lvalue던 ```void set_object(T &&var)``` 이 녀석만 호출되는 것을 볼 수 있다.  
따라서 복사를 하고 싶어도 이동만 발생하기에 문제다.  
이는 템플릿과 우측값 참조 기호가 같이 사용되어 **보편 참조**가 되고 있기 때문이다.  
기존에 자료형이 확정되어 있던 ```int &&``` 요런 녀석들과 다르게 ```T &&```는 rvalue가 오던 lvalue가 오던 모두 받아들인다.    

그렇다면 ```void set_object(const T &var)```만 사용하자니 rvalue를 통해 이동을 수행할 수 없고, ```void set_object(T &&var)```를 사용하자니 함수 내부에서 사용되는 var는 결국 lvalue이기에 복사, 이동 중 한가지 선택이 강제된다.  
set_object()가 올바르게 구현된다면 ```set_object(A)```면 복사가 수행되고, ```set_object(Object(1, "hello"))```면 이동이 수행되어야 한다.  
&nbsp;  

### 완벽한 전달  

템플릿에서 판단한 값 분류를 완벽하게 전달해주는 함수가 ```std::forward()```이다.  
```<utility>```를 포함하여 사용가능하다.  

```std::forward()```를 이해하기 위해서는 먼저 보편 참조가 정확히 어떻게 작동하는지 알아야 한다.  
```void set_object(T &&var)``` 템플릿 함수는 rvalue, lvalue에 따라 T가 다음과 같이 치환된다.  

- rvalue  
    ```void set_object(Object(1, "hello"))``` 사용시 ```void set_object(Object &&var)```로 치환  
    즉 T는 ```T```로 변환 (```Object``` 자료형)  

- lvalue  
    ```void set_object(A)``` 사용시 ```void set_object(Object & &&var)```로 치환  
    즉 T는 ```T &```로 변환 (```Object &``` 자료형)   

lvalue에서 눈치를 챘겠지만 ```Object & &&``` 이게 가능한 자료형인가?  
```c++
int &&&a = 3; // 이런 문법은 불가능하다.  

// 하지만 밑과 같은 문법은 가능하다.  
int a = 3;

using ref_type_01 = int &&;
ref_type_01 &b = a;
ref_type_01 &&c = 3;

using ref_type_02 = int &;
ref_type_02 &d = a;
ref_type_02 &&e = a;
```
C++11에서 레퍼런스 겹침 규칙이라는 것이 생겼다.  
물론 바로 그냥 ```&&&&&...``` 이렇게 참조 기호를 달 수는 없다.  
하지만 사용자 지정 타입을 이용하면 위 예시에서 보이듯이 가능해진다.  

```&```가 1, ```&&```가 0이고 or 연산을 한다고 보면 된다.  
위 예시에서 ```b```는 ref_type_01이 ```int &&```로 치환되어 최종적으로 ```int && &``` 자료형이 되었다. (```&``` 사이 띄어쓰기 구분 중요하다.)  
그러면 ```0 | 1```은 1이니 ```b```의 자료형 ```ref_type_01 &```은 ```int &```가 된다.  
하나만 더 해보면 ```d```는 ```ref_type_02 &``` -> ```int & &``` -> ```1 | 1``` -> 1 -> ```int &```가 된다.  

이를 토대로 판단해보면 ```void set_object(Object & &&var)```는 ```void set_object(Object &var)```와 같다.  
&nbsp;  

좀 헷갈릴 수 있는 것은 타입 자체에 참조가 붙어있는 경우다.  
```c++
Object &a = ref_obj;
Object &&b = Object(1, "hello");

// 밑의 경우는 어떻게 되는가?  
set_object(a);
set_object(b);
```
복잡하게 생각할 것 없이 a, b는 lvalue이기에 결국 ```set_object(a)```, ```set_object(b)``` 모두 ```void set_object(Object &var)```로 추론된 함수를 이용하게 된다.   
따라서 T도 ```Object &```다.  
&nbsp;  

var의 자료형이 어떻게 추론되는지는 알았지만 set_object() 함수 내부에서 쓰인 var가 lvalue라는 사실은 여전하다.  
var를 ```std::forward()```와 함께 사용한다면 값 분류 형태를 그대로 유지할 수 있다.  
```c++
template <typename T>
void set_object(T&& var)
{
    obj = std::forward<T>(var);
}
```
T의 추론과 연관지어 ```std::move(var)```를 할지 그냥 ```var```를 할지 결정하기 때문에 ```std::forward()```의 템플릿 인자는 생략할 수 없다.  
위 함수 하나로 rvalue인 경우 이동, lvalue인 경우 복사를 모두 수행할 수 있다.  
&nbsp;  

이동, 복사를 값 분류에 따라 유동적으로 수행할 수 있다는 장점말고도 보편 참조는 구현부를 줄여준다.  
```c++
void some_func(const Object& a, const Object& b)
{
    copied_01 = a;
    copied_02 = b;
}

void some_func(Object&& a, const Object& b)
{
    moved = std::move(a);
    copied = b;
}

void some_func(const Object& a, Object&& b)
{
    copied = a;
    moved = std::move(b);
}

void some_func(Object&& a, Object&& b)
{
    moved_01 = std::move(a);
    moved_02 = std::move(b);
}
```
위와 같이 인자가 2개인 함수만 봐도 구현을 4개해야 모든 경우의 lvalue, rvalue를 대처할 수 있다.  
인자가 3개라면... 8개나 구현해야 된다.  

반면 보편 참조와 std::foward()를 이용하면 단 하나의 구현으로 끝난다.  
```c++
template <typename T>
void some_func(T&& a, T&& b)
{
    copied_or_moved_01 = std::foward<T>(a);
    copied_or_moved_02 = std::foward<T>(b);
}
```
&nbsp;  

### 주의점  

밑의 경우는 보편 참조가 아니다.  
```c++
template <typename T>
void func(std::vector<T>&& vec)
{
    // something...
}
```
```T &&```를 추론하는 것이지 ```std::vector<T> &&```를 추론하는 것이 아니다.  
반드시 보편 참조의 인자 형태는 ```T &&```여야 한다.  
&nbsp;  

밑의 경우도 헷갈린다.  
```c++
template <typename T>
struct Array
{
    // 생략...

    void add(T &&var)
    {
    }
};
```
이 경우 인자 형태가 ```T &&```라고 해도 보편 참조가 아니다.  
Array를 선언할 때 이미 T의 추론이 끝났기 때문이다.  

add() 함수에 보편 참조를 적용하려면 밑과 같이 템플릿을 또 써줘야 한다.  
```c++
template <typename T>
struct Array
{
    // 생략

    template <typename R>
    void add(R &&var)
    {
    }
};
```

