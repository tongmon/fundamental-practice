# Prototype Pattern   

완전히 새로운 프로젝트를 만드는 경우는 빌더나 팩터리 패턴을 사용하여 객체 생성 방식을 구현하고 새로운 객체들을 만들어가면 될 것이다.   
하지만 기존에 방대하게 짜여진 프로젝트에서 기존에 생성되어있는 객체들을 활용하려면 어떻게 해야 할까?  
이 경우 프로토타입 패턴을 이용한다.  
프로토타입 패턴을 이해 하기 위해 밑의 간단한 예시를 살펴보자.  
&nbsp;  

일단 밑과 같이 연락처 관련 클래스가 있다.  
```c++
class Address
{
public:
    Address(const std::string street = "", const std::string city = "", const int suite = -1)
    {
        this->street = street;
        this->city = city;
        this->suite = suite;
    }
    std::string street;
    std::string city;
    int suite;
};

class Contact
{
public:
    Contact(const std::string name = "", Address address = Address())
    {
        this->name = name;
        this->address = address;
    }
    std::string name;
    Address address;
};
```
&nbsp;  

Contact 클래스를 사용하여 객체를 만들어보자.  
```c++
Contact Odin{"Lord of Asgard", Address{"459 Wood Town", "Asgard", 10}};
Contact Thor{"Thunder God", Address{"459 Wood Town", "Asgard", 11}};
```
영화 어벤져스에 등장하는 인물인 토르와 그의 아버지 오딘에 대한 정보를 담고 있는 클래스이다.  
Odin, Thor 클래스가 생성되는 것을 보면 많은 부분이 중복되고 있다.  
이런 중복된 값을 가지는 객체들을 생성하는 코드를 줄여주는 패턴이 프로토타입 패턴이다.  
즉 프로토타입 패턴에서 주로 다루게 되는 것은 객체를 **복제**하는 방식이다.   
&nbsp;  

## 평범한 중복 처리  

일단 중복되는 코드를 간단히 제거해보자.  
```c++
Contact Asgardian{"", Address{"459 Wood Town", "Asgard", 0}};
Contact Odin, Thor;
Odin = Thor = Asgardian;

Odin.name = "Lord of Asgard";
Odin.address.suite = 10;

Thor.name = "Thunder God";
Thor.address.suite = 11;
```
위에 코드는 Asgardian이라는 객체를 재사용하여 중복되는 코드 내용을 줄였다.  
&nbsp;  

하지만 만약 Contact 클래스의 구조가 밑과 같이 변한다면?  
```c++
class Contact
{
public:
    Contact(const std::string name = "", Address *address = nullptr)
    {
        this->name = name;
        this->address = address;
    }
    std::string name;
    Address *address;
};
```
전에 사용하던 방법처럼 Asgardian과 같은 객체를 재사용하여 복제를 한다면 포인터를 공유하기 때문에 한쪽에서 값을 바꾸면 다른 객체의 값도 같이 바뀌는 문제가 발생할 것이다.  
&nbsp;  

해당 문제를 해결하기 위한 가장 간단한 방법은 밑과 같이 복사 생성자 정의해주는 것이다.  
```c++
class Contact
{
public:
    Contact(const std::string name = "", Address *address = nullptr)
    {
        this->name = name;
        this->address = address;
    }
    Contact(const Contact &contact) : name(contact.name)
    {
        address = new Address();
        address->city = contact.address->city;
        address->street = contact.address->street;
        address->suite = contact.address->suite;
    }
    ~Contact() { delete address; }
    std::string name;
    Address *address;
};
```
하지만 범용적이지가 않다.
Address에 멤버 변수가 추가되면 Address 클래스의 구조가 바뀌는 것은 당연하고 추가적으로 Contact의 복사 생성자의 구조도 바뀌어야 하기에 번거롭다.
&nbsp;  

그러면 일을 줄이기 위해 밑과 같이 Address에 복제 생성자를 정의하는 방식으로 해결해보자.  
```c++
class Address
{
public:
    Address(const std::string street = "", const std::string city = "", const int suite = -1)
    {
        this->street = street;
        this->city = city;
        this->suite = suite;
    }
    Address(const Address &other)
        : street{other.street},
          city{other.city},
          suite{other.suite}
    {
    }
    std::string street;
    std::string city;
    int suite;
};
```
&nbsp;  

Address 클래스가 바뀜에 따라 Contact 클래스는 밑과 같이 변할 것이다.  
```c++
class Contact
{
public:
    Contact(const std::string name = "", Address *address = nullptr)
    {
        this->name = name;
        this->address = address;
    }
    Contact(const Contact &contact) : name(contact.name)
    {
        if (address)
            delete address;
        address = new Address(*contact.address);
    }
    ~Contact() { delete address; }
    std::string name;
    Address *address;
};
```
중요한 건 Address 내부 구조가 어떻게 바뀌던 이제 Contact 내부 구조는 바뀌지 않는다.  
&nbsp;  

조금 더 나아가 대입 연산자까지 확장해보면 밑과 같다.  
```c++
class Contact
{
public:
    Contact(const std::string name = "", Address *address = nullptr)
    {
        this->name = name;
        this->address = address;
    }
    Contact(const Contact &contact) : name(contact.name)
    {
        if (address)
            delete address;
        address = new Address(*contact.address);
    }
    ~Contact() { delete address; }
    Contact &operator=(const Contact &other)
    {
        if (this == &other)
            return *this;
        name = other.name;
        if (address)
            *address = *other.address;
        else
            address = new Address(*other.address);
        return *this;
    }
    std::string name;
    Address *address;
};
```
이렇게 Address 클래스의 기반이 갖춰져 있기에 Address 클래스를 활용하는 Contact 클래스도 확장하기 매우 편해진다.  
&nbsp;  

밑과 같은 모습으로 중복을 최소화하게 된다.  
```c++
Contact Asgardian{"", new Address("459 Wood Town", "Asgard", 0)};
Contact Odin, Thor;
Odin = Thor = Asgardian;

Odin.name = "Lord of Asgard";
Odin.address->suite = 10;

Thor.name = "Thunder God";
Thor.address->suite = 11;
```
해당 방법은 매우 잘 작동한다.  
문제라면 Address와 같은 포인터 멤버 변수로 활용하게 되는 클래스들에 일일이 복제 생성자를 정의해줘야 한다는 것이다.  
대형 프로젝트에서는 이러한 클래스들이 매우 많을 것이기에 귀찮아질 수 있다.  
&nbsp;  

## 직렬화

