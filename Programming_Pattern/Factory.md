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

여러 연관된 객체들을 생성하는 복잡한 코드 구조에 사용되는 패턴이다.  
일단 예시로 탈 것에 대한 클래스를 만들어 보기로 하자.  
&nbsp;  

밑은 탈 것에 대한 클래스이다.  
```c++
class Vehicle {
  public:
    Vehicle() {}
    virtual void drive(std::string oil_type, int oil_amount) = 0;
};
```
Vehicle을 상속하면 drive를 재정의 해줘야 한다.  
&nbsp;  

자동차와 비행기에 대한 클래스이다.  
```c++
class Car : public Vehicle {
  public:
    Car() : Vehicle() {}
    void drive(std::string oil_type, int oil_amount) {
        std::cout << "Car needs " << oil_amount << " liter of " << oil_type << " oil for riding the road!\n";
    }
};

class Airplane : public Vehicle {
  public:
    Airplane() : Vehicle() {}
    void drive(std::string oil_type, int oil_amount) {
        std::cout << "Airplane needs " << oil_amount << " liter of " << oil_type << " oil for fly to the air!\n";
    }
};
```
&nbsp;  

해당 두 클래스를 이용한 주유된 탈 것을 반환하는 함수를 만들어준다.    
```c++
std::unique_ptr<Vehicle> oiling(const std::string &vehicle_type) {
    std::unique_ptr<Vehicle> vehicle;
    if (vehicle_type == "car") {
        vehicle = std::make_unique<Car>();
        vehicle->drive("Gasoline", 100);
    } else {
        vehicle = std::make_unique<Airplane>();
        vehicle->drive("Kerosene", 300);
    }
    return vehicle;
}
```
일단 자동차와 비행기 이렇게 두 종류 밖에 없어서 분기 처리가 쉬웠지만 탈 것의 종류가 많아지면 많아질 수록 코드가 더러워질 것이다.  
그리고 제일 중요한 것은 비행기와 자동차는 같은 곳에서 주유하지 않는다...  
&nbsp;  

위 처럼 함수만 달랑 있는 oiling() 대신에 추상 팩터리를 이용한 oiling() 함수를 만들어보자.  
우선 탈 것에 따른 주유소를 나누기 위해 밑과 같은 팩터리 기저 클래스를 만든다.  
```c++
class VehicleGasStation {
  public:
    virtual std::unique_ptr<Vehicle> make() const = 0;
};
```
위와 같은 클래스를 추상 팩터리라고 한다.  
&nbsp;  

추상 팩터리를 이용해서 밑과 같이 다른 팩터리 클래스들을 만들자.  
```c++
class CarGasStation : public VehicleGasStation {
  public:
    std::unique_ptr<Vehicle> make() const {
        return std::make_unique<Car>();
    }
};

class AirplaneGasStation : public VehicleGasStation {
  public:
    std::unique_ptr<Vehicle> make() const {
        return std::make_unique<Airplane>();
    }
};
```
이렇게 하면 자동차와 비행기가 주유하는 곳이 나뉘어서 직관적으로 이해된다.  
이 클래스들은 지금 객체는 생성하고 있지만 주유는 해주지 않는다.   
&nbsp;  

실제 주유를 해주는 클래스를 밑과 같이 만들어 보자.  
```c++
class GasStation {
    std::unordered_map<std::string, std::unique_ptr<VehicleGasStation>> vehicle_gas_station;
    std::unordered_map<std::string, std::pair<std::string, int>> vehicle_param;

  public:
    GasStation() {
        vehicle_gas_station["car"] = std::make_unique<CarGasStation>();
        vehicle_param["car"] = {"Gasoline", 100};

        vehicle_gas_station["airplane"] = std::make_unique<AirplaneGasStation>();
        vehicle_param["airplane"] = {"Kerosene", 300};
    }
    std::unique_ptr<Vehicle> oiling(const std::string &vehicle_type) {
        std::unique_ptr<Vehicle> vehicle = vehicle_gas_station[vehicle_type]->make();
        vehicle->drive(vehicle_param[vehicle_type].first, vehicle_param[vehicle_type].second);
        return vehicle;
    }
};
```
이렇게 만들면 좋은 점은 oiling() 함수 내부 구조는 유지해도 된다는 것이다.  
그래서 if()문을 주렁주렁 달 필요가 없어 코드가 직관적이다.  
새로운 탈 것에 대한 정보가 생긴다면 GasStation의 생성자 부분에서 초기화를 적절히 해주고 VehicleGasStation를 상속하는 새로운 주유소 클래스를 만들면 된다.  
&nbsp;  

## 함수형 팩터리  

추상 팩터리가 기저 클래스를 활용해 확장해 나가는 팩터리 패턴이였다면 함수형 팩터리는 따로 기저 클래스를 만들지 않고 함수를 이용하는 패턴이다.  
보통 함수 포인터나 ```std::function```을 이용한다.  
&nbsp;  

추상 팩터리로 만들었던 GasStation 클래스를 함수형 팩터리를 이용해 다시 만들어보면 밑과 같다.  
```c++
class GasStation {
    std::unordered_map<std::string, std::function<std::unique_ptr<Vehicle>()>> vehicle_gas_station;

  public:
    GasStation() {
        vehicle_gas_station["car"] = [] {
            auto car = std::make_unique<Car>();
            car->drive("Gasoline", 100);
            return car;
        };

        vehicle_gas_station["airplane"] = [] {
            auto car = std::make_unique<Airplane>();
            car->drive("Kerosene", 300);
            return car;
        };
    }
    std::unique_ptr<Vehicle> oiling(const std::string &vehicle_type) {
        return vehicle_gas_station[vehicle_type]();
    }
};
```
이 방식도 oiling() 함수 내부 구조가 유지된다.  
게다가 CarGasStation, AirplaneGasStation와 같은 팩터리 클래스를 따로 안만들어줘도 되기 때문에 필요한 코드 라인이 더 적다.  
하지만 car, airplane 같은 탈 것 종류들이 많아지고 각 탈 것마다 확연하게 다른 객체 생성 로직이 필요하다면 추상 팩터리 패턴을 사용하는 것이 더 직관적인 코드를 작성하는 데 좋을 것이다.  
&nbsp;  

## 요약  

1. 팩터리 