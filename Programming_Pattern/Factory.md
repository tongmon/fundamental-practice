# Factory Pattern  

객체 생성과 관련된 코드를 깔끔하게 작성하는 데 도움을 주는 팩터리 패턴이다.  
&nbsp;  

일단 팩터리 패턴을 대략 이해하기 위해 밑과 같이 좌표점 정보를 표현해보기로 한다.  
```c++
class Point {
  public:
    float x, y;
    Point(float x, float y) : x(x), y(y) {}
};
```
2차원 좌표계를 직교 좌표계로 표현하는 것이라면 완벽하다.  
하지만 극좌표계라는 원의 반지름과 각도를 이용해 2차원을 표현하는 방식은 어떻게 다룰 것인가?  
극좌표계를 위한 클래스를 따로 만드는 것은 좀 껄끄럽다.  
&nbsp;  

일단 밑과 같은 enum 클래스를 통해 해결하는 방향으로 가보자.  
```c++
enum class PointType {
    cartesian,
    polar
};
```
&nbsp;  

그러면 Point 클래스는 밑과 같이 바뀌어야 한다.  
```c++
class Point {
  public:
    float x, y;
    Point(float a, float b, PointType type = PointType::cartesian) {
        if (type == PointType::cartesian) {
            x = a;
            y = b;
        } else {
            x = a * cos(b);
            y = a * sin(b);
        }
    }
};
```
일단 생성자의 인자 이름이 보편성을 위해 a, b로 바뀌었다. (기존의 x, y는 너무 직교 좌표계의 이름 같다...)  
기능적으로는 다 갖춰졌지만... 좋은 코드라고 말하기엔 부족하다.  
&nbsp;  

## 팩터리 메서드  

일단 앞에서 본 Point 클래스 생성자의 인자들은 a, b로 해당 클래스를 사용하는 사용자들에게 아무런 정보도 주지 못한다.  
x, y 면 직교 좌표계, r, theta 면 극좌표계라고 알텐데 이런 게 없다...  
객체 생성을 위한 팩터리 함수를 따로 만들어 이러한 Point 클래스의 문제를 개선해보자.  
&nbsp;  

static 함수들을 추가해 밑과 같이 Point 클래스를 만들어보자.  
```c++
class Point {
  protected:
    Point(const float x, const float y) : x{x}, y{y} {}

  public:
    float x, y;
    static Point NewCartesian(float x, float y) {
        return {x, y};
    }
    static Point NewPolar(float r, float theta) {
        return {r * cos(theta), r * sin(theta)};
    }
};
```
생성자를 숨기고 대신에 팩토리 메서드들을 제공해 객체를 초기화하게 만들었다.  
어떤 좌표계를 사용할 것인지 함수의 이름도 명확하고 함수 인자들도 명확하게 정보를 제공하고 있다.  
&nbsp;  

실제 사용은 밑과 같다.  
```c++
Point ptCartesian = Point::NewCartesian(1, 4);
Point ptPolar = Point::NewPolar(5, 3.14159265);
```
&nbsp;  

## 팩터리  

빌더 패턴에서 했던 것 처럼 클래스를 생성하는 로직 부분을 별도의 클래스에 몰아넣을 수 있다.  
이러한 클래스를 팩터리라고 한다.  
&nbsp;  

Point 클래스를 밑과 같이 바꿔준다.  
```c++
class Point {
    Point(float x, float y) : x(x), y(y) {}

  public:
    float x, y;
    friend class PointFactory;
};
```
주요하게 볼 점은 PointFactory라는 팩터리 클래스가 친구 함수로 들어갔다는 것이다.  
PointFactory라는 객체 생성을 담당하는 녀석이 존재하기 때문에 Point의 기존 생성자는 숨긴다.  
&nbsp;  

PointFactory 객체는 밑과 같다.  
```c++
class PointFactory {
  public:
    static Point NewCartesian(float x, float y) {
        return Point{x, y};
    }

    static Point NewPolar(float r, float theta) {
        return Point{r * cos(theta), r * sin(theta)};
    }
};
```
&nbsp;  

실제 사용할 때는 밑과 같다.
```c++
Point ptCartesian = PointFactory::NewCartesian(1, 4);
Point ptPolar = PointFactory::NewPolar(5, 3.14159265);
```
&nbsp;  

## 내부 팩터리  

별건 없고 팩터리 클래스를 내부에 위치 시키는 방법이다.  
C++에서는 굳이 사용 안해도 되지만 friend 문법이 없는 C#, Java에서는 꽤 쓰인다.  
&nbsp;  

밑 코드는 Point 클래스에 내부 팩터리 패턴을 적용한 모습이다.  
```c++
class Point {
    Point(float x, float y) : x(x), y(y) {}

    class PointFactory {
        PointFactory() {}

      public:
        static Point NewCartesian(float x, float y) {
            return {x, y};
        }
        static Point NewPolar(float r, float theta) {
            return {r * cos(theta), r * sin(theta)};
        }
    };

  public:
    float x, y;
    static PointFactory Factory;
};
```
PointFactory 클래스가 Point 클래스 내부로 들어오고 static 클래스 멤버 변수인 Factory가 추가되었다.  
&nbsp;  

실제 사용 방법은 밑과 같다.  
```c++
Point ptCartesian = Point::Factory.NewCartesian(1, 3);
Point ptPolar = Point::Factory.NewPolar(5, 3.14159265);
```
&nbsp;  

Factory 뒤에 . 이 붙고 함수가 호출되는 문법이 싫다면 Point 클래스를 다음과 같이 바꿔보자.  
```c++
class Point {
    Point(float x, float y) : x(x), y(y) {}

  public:
    class PointFactory {
        PointFactory() {}

      public:
        static Point NewCartesian(float x, float y) {
            return {x, y};
        }
        static Point NewPolar(float r, float theta) {
            return {r * cos(theta), r * sin(theta)};
        }
    };

    float x, y;
};
```
PointFactory 클래스를 public으로 바꾸고 Factory 멤버 변수를 제거하였다.  
&nbsp;  

이러면 실제 사용 방법이 이렇게 된다.  
```c++
Point ptCartesian = Point::PointFactory::NewCartesian(1, 3);
Point ptPolar = Point::PointFactory::NewPolar(5, 3.14159265);
```
&nbsp;  

클래스 관리를 할 때 클래스 내부에 모든 것을 넣어 관리하는 것이 편하다면 내부 팩터리 패턴을 사용하면 된다.  
&nbsp;  

## 추상 팩터리  


