# Proxy Pattern  

프록시 패턴도 데코레이터 패턴과 비슷하게 객체의 기능을 수정하거나 확장하는 것에 중점을 둔다.  
하지만 데코레이터 패턴과 달리 프록시 패턴은 기존의 인터페이스 사용 방식을 정확히 동일하게 가져간다.  
즉 내부 구현만 달라질 뿐이다.  
&nbsp;  

## 스마트 포인터  

C++의 스마트 포인터가 프록시 패턴의 가장 대표적인 예이다.  
포인터, 스마트 포인터 모두 밑과 같이 동일한 방식으로 사용이 가능하다.  
```c++
std::vector<int> *ptr = new std::vector<int>();
ptr->size();
delete ptr;

std::shared_ptr sh_ptr = std::make_shared<std::vector<int>>();
sh_ptr->size();
```
물론 스마트 포인터는 delete를 명시할 필요가 없고 참조 횟수를 내부적으로 관리한다는 차이점이 있지만 최대한 기존 포인터와 유사하게 작동하도록 구현되어 있다.   
&nbsp;  

## 속성 프록시  

대부분의 프로그래밍 언어는 get / set 메서드를 언어적인 차원에서 지원하지만 C++은 그렇지 않다.  
물론 Clang, MSVC 등의 컴파일러에서는 ```__declspec(property())```를 사용하여 지정할 수 있지만 비표준이다.  
따라서 속성 프록시를 통해 get / set 메서드를 접근해보자.  
```c++
template <typename T>
struct Property
{
    T value;
    Property(const T init_val) { *this = init_val; }
    operator T()
    {
        // getter가 수행할 구현부를 적으면 된다.

        return value;
    }
    T operator=(T new_val)
    {
        // setter가 수행할 구현부를 적으면 된다.

        return value = new_val;
    }
};
```
형변환을 재정의하여 getter를, ```=``` 연산자를 재정의하여 setter를 정의하였다.  
&nbsp;  

밑과 같이 int형으로 사용되었을 때 마치 자신이 int인 것 마냥 사용이 된다.  
```c++
// int 처럼 사용이 가능함.  
Property<int> a = 1;
int b = a;

// 하지만 밑과 같은 상황에서 getter / setter 로직 수행 안됨.
Property<int> c = 2;
Property<int> d = c;
```
문제가 하나 있는데 위 예시에서 보이듯이 ```Property<int>``` 사이에 값 할당이 이루어지면 getter / setter 로직이 수행이 안된다는 것이다.  
&nbsp;  

이를 해결하기 위해 연산자 재정의 구현을 추가해보자.  
```c++
template <typename T>
struct Property
{
    T value;

    T get()
    {
        // getter가 수행할 구현부를 적으면 된다.

        return value;
    }
    T set(const T &new_val)
    {
        // setter가 수행할 구현부를 적으면 된다.

        return value = new_val;
    }
    Property(const T &init_val)
    {
        *this = init_val;
    }
    Property(Property<T> &init_val)
    {
        *this = init_val;
    }
    T operator=(Property<T> &new_val)
    {
        return set(new_val.get());
    }
    T operator=(const T &new_val)
    {
        return set(new_val);
    }
    operator T()
    {
        return get();
    }
};
```
이제 값을 획득하거나 할당하는 과정에서 getter / setter 로직이 잘 작동할 것이다.  
```T```에서 ```Property<T>```를 참조로 사용하게 될 경우에는 직접 멤버 변수 value를 사용하면 될 것이다.  
&nbsp;  

## 가상 프록시  

