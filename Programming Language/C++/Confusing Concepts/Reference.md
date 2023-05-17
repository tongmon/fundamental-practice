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
밑에서 계속 등장할 단어인 식별자는 ```자신의 개인적인 공간을 가지고 있는 녀석``` 정도로 생각하면 된다.  
&nbsp;  

### lvalue  

left value, 좌측값이다.  
식별자를 가지면서 이동할 수 없는 값들이다.  
즉 자기 소유의 주소를 가지고 있고 그 주소에 상주하며 가만히 있는거라고 생각하면 된다.  
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
```"hello world"```와 같은 문자열 [literal](https://www.geeksforgeeks.org/literals-in-c-cpp-with-examples/)도 lvalue이다.  
이들의 값을 가리키는 주소를 다른 곳으로 보내버릴 수 없다.  
lvalue는 보통 좌측에 위치하고 ```&``` 연산자를 통해 주소 값을 획득할 수 있다.  
```&```를 통해 주소 값을 획득하는 특징은 lvalue에만 적용되기에 어떤 값이 어떤 분류에 속하는지 헷갈린다면 ```&```를 붙여보자.  
&nbsp;  

### xvalue  

식별자를 가지면서 이동할 수 있는 값들이다.  
expire의 x에서 따온 이름이기에 만료되어 가는 값이라고도 한다.  
프로그래머가 직접 사용할 수는 없고 컴파일러가 사용한다.  
```c++
std::string get_empty_name()
{
    return std::string();
}

int main()
{
    get_empty_name();
}
```
위 예시에서 ```get_empty_name();```이 수행된 이후 ```std::string()``` 객체가 저장되어 있던 주소를 확인해보면 해당 값이 아직 남아있을 수도 있고 사라졌을 수도 있다.  
이렇게 특정 라인이 ```;```으로 마무리되어 끝날 때 값이 만료되어 간다면 xvalue이다.  
추후에 등장할 ```std::move()``` 함수의 반환 값도 위와 같은 이유로 xvalue이다.  
&nbsp;  

### prvalue  

pure right value의 줄임말이다.  
식별자가 없는데 이동할 수 있는 값이다.  
```x++```와 같은 후위 증감 연산자의 반환 값, ```"hello world"```와 같은 문자열 [literal](https://www.geeksforgeeks.org/literals-in-c-cpp-with-examples/)을 제외한 모든 [literal](https://www.geeksforgeeks.org/literals-in-c-cpp-with-examples/)은 prvalue이다.  
```c++
int a = 10;
bool b = true;
char c = 'c';
float d = 1.384;
```
위에서 등장한 ```10, true, 'c', 1.384```는 모두 prvalue이다.  
```a < b```의 결과로 얻어지는 bool 값도 literal이기에 prvalue이다.  
literal이기에 따로 주소가 없다.  
&nbsp;  

### glvalue  

xvalue 혹은 lvalue를 칭한다.  
식별자가 있는 값이다.  









lvalue 참조
rvalue 참조
보편 참조

https://dydtjr1128.github.io/cpp/2019/06/10/Cpp-values.html