# Decorator Pattern  

이미 존재하는 타입에 대해 새로운 기능을 추가하기 위한 패턴이다.  
원래 타입의 코드는 건드리지 않으면서 기능만 추가되기 때문에 단일 책임 원칙이 준수된다.  
&nbsp;  

데코레이터 패턴을 이해하기 위한 상황을 가정해보자.  
일단 밑과 같은 모양 인터페이스가 존재한다.  
```c++
struct Shape
{
    virtual std::string str() const = 0;
};
```
&nbsp;  


