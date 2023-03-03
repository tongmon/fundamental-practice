# Façade Pattern  

복잡한 서브 시스템 앞에 단순한 인터페이스를 두기 위한 패턴이다.  
말보다 예시가 더 간단할 정도로 단순한 패턴이다.  
&nbsp;  

일단 필자는 집을 나갈 때 전등을 껏는지 컴퓨터를 껏는지 여름에는 에어컨을 껏는지 겨울에는 히터를 껏는지를 확인한다.  
집에 돌아올 때에도 전등 키고 컴퓨터 키고 여름에는 에어컨을, 겨울에는 히터를 작동시킨다.  
이러한 상황을 코드로 구현해보자.  
&nbsp;  

전등 클래스는 밑과 같다.  
```c++
class Light
{
    int brightness;
    bool on;

public:
    Light(bool on = false, int brightness = 10) : on{on}, brightness{brightness} {}
    bool is_on() { return on; }
    void light_on()
    {
        on = true;
        std::cout << "Light On!, Brightness: " << brightness << std::endl;
    }
    void light_off()
    {
        on = false;
        std::cout << "Light Off!\n";
    }
};
```
&nbsp;  

컴퓨터와 에어컨, 히터 클래스도 밑과 같다.  
```c++
class Computer
{
    int core_num;
    bool on;

public:
    Computer(bool on = false, int core_num = 8) : on{on}, core_num{core_num} {}
    bool is_on() { return on; }
    void computer_on()
    {
        on = true;
        std::cout << "Computer On!\n";
    }
    void computer_off()
    {
        on = false;
        std::cout << "Computer Off!\n";
    }
};

class AirConditioner
{
    bool on;
    float celsius_setting;

public:
    AirConditioner(bool on = false, float celsius_setting = 23) : on{on}, celsius_setting{celsius_setting}
    {
    }
    bool is_on() { return on; }
    void airconditioner_on()
    {
        on = true;
        std::cout << "AirConditioner On! Current Temperature Setting:" << celsius_setting << " celsius.\n";
    }
    void airconditioner_off()
    {
        on = false;
        std::cout << "AirConditioner Off!\n";
    }
    void set_temperature(float celsius)
    {
        celsius_setting = celsius;
        std::cout << "Temperature setted to " << celsius << " celsius.\n";
    }
};

class Heater
{
    bool on;
    float celsius_setting;

public:
    Heater(bool on = false, float celsius_setting = 19) : on{on}, celsius_setting{celsius_setting} {}
    bool is_on() { return on; }
    void heater_on()
    {
        on = true;
        std::cout << "Heater On! Current Temperature Setting:" << celsius_setting << " celsius.\n";
    }
    void heater_off()
    {
        on = false;
        std::cout << "Heater Off!\n";
    }
    void set_temperature(float celsius)
    {
        celsius_setting = celsius;
        std::cout << "Temperature setted to " << celsius << " celsius.\n";
    }
};
```
구현은 별거 없다.  
히터와 에어컨은 추가적으로 온도 조절 함수가 멤버로 존재한다.  
&nbsp;  

이제 여름에 외출 하는 상황을 생각해보자.  
필자의 루틴 대로 전등을 키고 컴퓨터를 키고 에어컨을 켜보자.  
```c++
std::string season = "summer";

Light light;
Computer computer;
AirConditioner airconditioner;
Heater heater;

if (!light.is_on())
    light.light_on();

if (!computer.is_on())
    computer.computer_on();

if (season == "summer")
    if (!airconditioner.is_on())
    {
        airconditioner.airconditioner_on();
        airconditioner.set_temperature(23);
    }

if (season == "winter")
    if (!heater.is_on())
    {
        heater.heater_on();
        airconditioner.set_temperature(19);
    }
```
외출이라는 동작을 할 때마다 난잡하게 해당 코드 블럭을 사용해야 한다.  
&nbsp;  

겨울에 집에 오는 상황도 한 번 고려해보자.  
```c++
std::string season = "winter";

Light light;
Computer computer;
AirConditioner airconditioner;
Heater heater;

if (light.is_on())
    light.light_off();

if (computer.is_on())
    computer.computer_on();

if (season == "summer")
    if (airconditioner.is_on())
        airconditioner.airconditioner_off();

if (season == "winter")
    if (heater.is_on())
        heater.heater_off();
```
집에 오는 상황이 발생할 때마다 이러한 코드 블럭을 계속 구성해야 한다.  
집에서 나가거나 들어올 상황이 생길 때마다 비효율적이게 비슷한 코드 블럭이 늘어난다.  
&nbsp;  

## 단순한 인터페이스  

퍼사드 패턴을 사용해보자.  
```c++
class Home
{
    std::string season;

    Light light;
    Computer computer;
    AirConditioner airconditioner;
    Heater heater;

public:
    Home(const std::string &season, Light &light, Computer &computer, AirConditioner &airconditioner, Heater &heater)
        : season{season}, light{light}, computer{computer}, airconditioner{airconditioner}, heater{heater} {}

    void home_out()
    {
        if (light.is_on())
            light.light_off();

        if (computer.is_on())
            computer.computer_off();

        if (season == "summer")
            if (airconditioner.is_on())
                airconditioner.airconditioner_off();

        if (season == "winter")
            if (heater.is_on())
                heater.heater_off();
    }

    void home_in()
    {
        if (!light.is_on())
            light.light_on();

        if (!computer.is_on())
            computer.computer_on();

        if (season == "summer")
            if (!airconditioner.is_on())
            {
                airconditioner.airconditioner_on();
                airconditioner.set_temperature(23);
            }

        if (season == "winter")
            if (!heater.is_on())
            {
                heater.heater_on();
                airconditioner.set_temperature(19);
            }
    }
};
```
여기서 Home은 퍼사드 클래스이다.  
비슷한 코드 블럭을 다시 사용할 필요 없이 집을 나갈 때는 home_out() 함수를, 들어올 때는 home_in() 함수를 사용하면 된다.  
즉 home_out(), home_in()으로 인터페이스를 단순화 한 것이다.  
사용자는 home_out(), home_in() 함수 내부에서 복잡하게 돌아가는 과정을 신경 쓸 필요가 없다.  
&nbsp;  

Home의 생성자를 보면 넘기는 인자들이 많은데 이 경우 구조체를 정의해 사용하면 편하다.  
```c++
struct Objects
{
    std::string season;
    Light light;
    Computer computer;
    AirConditioner airconditioner;
    Heater heater;

    Objects()
    {
        season = "summer";
        light = {false, 20};
        computer = {true, 16};
        airconditioner = {true, 24.f};
        heater = {false, 20.f};
    }
};
```
이렇게 디폴트 값을 한 곳에서 관리할 수 있어서 좋다.  
&nbsp;  

Home 클래스에는 추가적으로 밑과 같은 생성자가 필요할 것이다.  
```c++
class Home
{
    // 나머지 구현부 생략

public:
    Home(const Objects &obj = Objects())
    {
        season = obj.season;
        light = obj.light;
        computer = obj.computer;
        airconditioner = obj.airconditioner;
        heater = obj.heater;
    }
};
```
&nbsp;  

## 요약  

1. 퍼사드 패턴은 복잡한 라이브러리와 API, 서브 클래스들 사이의 통합 인터페이스를 제공할 때 용이하다.    

2. 퍼사드 패턴으로 제공한 인터페이스에 구조체를 이용해 인자를 넘기는 방식도 고려해보자.  