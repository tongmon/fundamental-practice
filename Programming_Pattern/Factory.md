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

## 팩터리  

빌더 패턴에서 했던 것 처럼 클래스를 생성하는 로직 부분을 별도의 클래스에 몰아넣을 수 있다.  
이러한 클래스를 팩터리라고 한다.  

