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
[ 0x002  a ] null | [ 0x004  b ] (1, 7.77)
------------------------------------------                  
```
```(1, 7.77)``` 값은 그대로인데 이 녀석이 딸려있는 주소 값이 변경되었다.  
Object 구조체의 크기가 커질수록 복사보다 이동이 더 빠르게 수행될 것이다.  
&nbsp;  

## 값 분류  

C++11 이후에는 우측값 참조가 도입되면서 값이 다양하게 분류된다.  
lvalue, xvalue, prvalue, glvalue, rvalue, 그외 이렇게 6개로 나뉜다.  
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

int add(int c, int d)
{
    return c + d;
}
```
위에서 등장한 10, 'c' 값은 prvalue이다.  
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

중요한 것은 xvalue가 이동이 가능한 시점은 바로 그 표현식이 사용되는 시점이다.  
```c++
std::string org_str = "hello world";
std::string &&lvalue_str = static_cast<std::string &&>(org_str);

// 이동이 안되고 복사됨.
std::string copied_str = lvalue_str;

// 이동되어 org_str은 만료됨.  
std::string moved_str = static_cast<std::string &&>(org_str);
// 혹은
std::string moved_str = std::move(lvalue_str);
```
우측값 참조인 lvalue_str 변수로 org_str를 받았다해도 이동, 복사 아무것도 발생하지 않는다.  
그냥 ```std::string &lvalue_str = org_str```와 동일한 효과이다.  
lvalue_str은 그저 org_str의 주소를 개인공간으로 가지는 lvalue이다.  
따라서 이동을 시키려면 xvalue를 바로 이용하거나 ```std::move()``` 함수를 이용해 lvalue를 xvalue로 변환해야 한다.  
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
```
b는 그냥 a와 일심동체다.  
c도 b와 같지만 수정을 못할 뿐이다.  
중요한 점은 a, b, c 모두 lvalue이기에 좌측값 참조가 가능한 것이다.  
```int &d = 10``` 이런 표현은 10은 prvalue이기 때문에 불가능하다.  
참조는 그냥 포인터와 비슷하게 동작하기에 복사가 발생하지 않는다.  

## rvalue 참조  

## universal 참조  

