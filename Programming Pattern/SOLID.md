# SOLID 원칙

&nbsp;  

## 단일 책임 원칙 (SRP)  
  
메모장 프로그램을 예시로 들어보자.   
일단 메모장에서 텍스트 편집에 관여하는 기능을 담당하는 클래스가 있어야 할 것이다.  
저장 기능도 있어야 할 것이다.   
텍스트 편집 클래스에 저장 기능을 넣어야 할까?   
저장이라는 것이 하드디스크에 저장하는 것 뿐만 아니라 클라우드에 올릴 수도 있지 않은가?  
만약 저장 기능을 텍스트 편집 클래스에 넣게 되면 저장 방식이 추가될 때마다 확장하기도 귀찮고 직관적으로 구성하기도 힘들 것이다.  
이런 경우에는 그냥 편집 관련 작업만 해주는 텍스트 편집 클래스와 저장 관련 작업만 해주는 저장 클래스를 따로 나누어 상호작용 시키는 것이 좋다.  
&nbsp;  

밑은 단일 책임 원칙 위배 예시  
```c++
class NotePad {
    Editor edit;
};

class Editor {
   public:
    void DoEdit();
    void SaveToDisk();
    void SaveToCloud();
    void SaveToCustomServer();
};
```
&nbsp;  

밑은 단일 책임 원칙을 준수하는 예시
```c++
class NotePad {
    Editor editor;
    Saver saver;
};

class Editor {
  public:
    void DoEdit();
};

class Saver {
  public:
    void SaveToDisk(Editor& edit);
    void SaveToCloud(Editor& edit);
    void SaveToCustomServer(Editor& edit);
};
```
&nbsp;  

## 열림 닫힘 원칙 (OCP)  
  
확장에는 열려있지만 수정에는 닫혀있어야 하는 원칙이다.  
필터링을 해주는 프로그램을 개발한다고 해보자.  
코드는 일단 밑과 같다.  
```c++
enum class Color { Red, Green, Blue };
enum class Size { Small, Medium, Large };

class Product {
  public:
    Color color;
    Size size;
};
```
&nbsp;  

여기서 고객은 색상으로 물건을 나누길 원한다.  
그러면 함수는 밑과 같은 형태를 취할 것이다.  
```c++
std::vector<Product> filter_by_color(const std::vector<Product>& items, Color color) {
    std::vector<Product> ret_items;
    std::for_each(items.begin(), items.end(),
                  [&](const auto& item) -> void {
                      if (item.color == color)
                          ret_items.push_back(item);
                  });
    return ret_items;
}
```
&nbsp;  

그런데 고객이 크기에 따라 물건을 나누길 원한다.  
함수를 추가해야 한다.
```c++
std::vector<Product> filter_by_size(const std::vector<Product>& items, Size size) {
    std::vector<Product> ret_items;
    std::for_each(items.begin(), items.end(),
                  [&](const auto& item) -> void {
                      if (item.size == size)
                          ret_items.push_back(item);
                  });
    return ret_items;
}
```
&nbsp;  

그런데 고객이 크기와 색상을 동시에 따져 물건을 나누길 원한다.  
또 함수를 추가해야 한다...  
```c++
std::vector<Product> filter_by_color_and_size(const std::vector<Product>& items, Color color, Size size) {
    std::vector<Product> ret_items;
    std::for_each(items.begin(), items.end(),
                  [&](const auto& item) -> void {
                      if (item.size == size && item.color == color)
                          ret_items.push_back(item);
                  });
    return ret_items;
}
```
&nbsp;  

만약 물건에 색상과 크기 말고 다른 속성이 생기고 고객이 또 그에 따른 필터 요구사항을 추가한다면 점점 더 복잡해질 뿐이다.  
이는 지금 현재 코드 구조가 열림 닫힘 원칙을 지키지 않아서이다.  
밑의 코드는 열림 닫힘 원칙을 지킨 예시이다.  
&nbsp;  

일단 색상에 따라, 크기에 따라, 색상과 크기에 따라... 이렇게 나눠지는 현상을 직관화하기 위해서 명세라는 템플릿 클래스로 따로 뺀다.  
```c++
template <typename T>
class Sepcification {
  public:
    virtual bool is_specified(const T &item) = 0;
};
```
&nbsp;  

필터를 더 유연하게 만든 템플릿 필터 클래스를 만든다.  
```c++
template <typename T>
class Filter {
  public:
    virtual std::vector<T> filter(const std::vector<T> &items, Sepcification<T> &spec) = 0;
};
```
&nbsp;  
위 두 템플릿을 이용해 필터를 짜보면 밑과 같다.  
```c++
class BetterFilter : public Filter<Product> {
  public:
    std::vector<Product> filter(const std::vector<Product> &items, Sepcification<Product> &spec) {
        std::vector<Product> ret_items;
        std::for_each(items.begin(), items.end(),
                      [&](const auto &item) -> void {
                          if (spec.is_specified(item))
                              ret_items.push_back(item);
                      });
        return ret_items;
    }
};
```
이렇게 하면 예전에 함수 인자와 내부 로직이 난잡하게 계속 변했던 것과 비교하면 명세와 필터의 기능이 명확하게 분리가 되어 코드 짜기가 수월해진다.  
filter 함수는 그대로고 필터링할 물건과 그 물건에 따른 명세 로직만 바꿔주면 된다.  
예시를 보면 알겠지만 명세가 복잡해질수록 OCP 원칙의 유용성은 점점 더 강력해진다.  
&nbsp;  

일단 색상을 선별하는 명세를 짜보면 밑과 같다.  
is_specified 함수를 보면 item에서 color값만을 비교한다.  
```c++
class ColorSpec : public Sepcification<Product> {
  public:
    Color color;
    ColorSpec(Color color) { this->color = color; }
    ~ColorSpec() {}
    bool is_specified(const Product &item) {
        return item.color == color;
    }
};
```
&nbsp;  

위에서 새로 정의한 명세와 필터를 이용해보면 밑과 같다.  
```c++
BetterFilter betterfilter;
ColorSpec only_green(Color::Green);
auto green_product_list = betterfilter.filter(/*Product 리스트*/, only_green);
```
이러면 green_product_list에 녹색의 물건들만 담길 것이다.  
확장이 굉장히 유연하다.   
&nbsp;  

크기와 색상을 동시에 비교하고 싶다면 밑과 같이 ```Sepcification<Product>```를 상속하는 다른 명세 클래스를 만들고 is_specified 함수만 재정의하면 된다.  
```c++
class ColorAndSizeSpec : public Sepcification<Product> {
  public:
    Color color;
    Size size;
    ColorAndSizeSpec(Color color, Size size) {
        this->color = color;
        this->size = size;
    }
    ~ColorAndSizeSpec() {}
    bool is_specified(const Product &item) {
        return item.color == color && item.size == size;
    }
};
```
&nbsp;  

아직 먼가 부족하다... 복합 조건을 많이 따질수록 명세 클래스의 수는 많아질 것이다.  
이를 획기적으로 줄이고 더 편하고 유연하게 쓰기 위해서 && 연산자를 재정의하겠다.  
일단 Specification 클래스의 && 연산자 재정의를 확장하기 위해 밑과 같이 AndSpecification 클래스를 만든다.  
```c++
template <typename T>
class AndSepcification : public Sepcification<T> {
    Sepcification<T> *first;
    Sepcification<T> *second;

  public:
    AndSepcification(Sepcification<T> *one, Sepcification<T> *two) {
        first = one;
        second = two;
    }
    ~AndSepcification() {}

    bool is_specified(const T &item) {
        return first->is_specified(item) && second->is_specified(item);
    }
};
```
&nbsp;  

그리고 AndSepcification을 이용해서 Sepcification에 && 연산자 재정의를 확장한다.  
```c++
template <typename T>
class Sepcification {
  public:
    virtual bool is_specified(const T &item) = 0;
    AndSepcification<T> operator&&(Sepcification<T> &&other) {
        return AndSepcification<T>(this, &other);
    }
};
```
이렇게 하면 ```auto only_green_small = ColorSpec(Color::Green) && SizeSpec(Size::Small);``` 이러한 표현만으로 복합 조건 필터링이 가능해진다.  
지금 변경한 코드들을 보면 기본적인 기저 클래스인 Sepcification, Filter의 변경없이 기능 확장이 가능했다.  
즉 OCP 원칙을 잘 지킨 코드는 확장은 매우 쉬운데 막상 기저에 깔린 구조를 바꾸기는 매우 어렵다.  
&nbsp;  

## 리스코프 치환 원칙 (LSP)  
  
자식 객체에 접근할 때 부모 객체의 인터페이스, 함수로 접근하더라도 문제가 없어야 한다는 원칙이다.   
말이 어려울 수 있는데 밑의 코드를 통해 설명하겠다.    
&nbsp;  

일단 밑과 같은 사각형 클래스가 있다.  
```c++
class Rectangle {
  protected:
    int width;
    int height;

  public:
    Rectangle(const int width, const int height) : width{width}, height{height} {};
    ~Rectangle(){};

    int get_width() { return width; }
    int get_height() { return height; }
    virtual void set_width(const int width) { this->width = width; }
    virtual void set_height(const int height) { this->height = height; }
    int area() const { return width * height; }
};
```
&nbsp;  

또 밑과 같이 사각형의 특성을 가지는 정사각형 클래스가 있다.  
```c++
class Square : public Rectangle {
  public:
    Square(int size) : Rectangle(size, size) {}
    ~Square() {}
    void set_width(const int width) { this->height = this->width = width; }
    void set_height(const int height) { this->width = this->height = height; }
};
```
&nbsp;  

만약 밑과 같은 함수가 있다고 하자.  
```c++
void process(Rectangle &rect) {
    int w = rect.get_width();
    rect.set_height(10);

    std::cout << "expected area: " << w * 10 << " real area: " << rect.area();
}
```
해당 함수에 Square 객체를 넣을 때와 그 부모 객체인 Rectangle 객체를 넣을 때 과연 결과가 똑같이 나올까?  
다르다.   
&nbsp;  

먼저 Rectangle인 경우부터 살펴보자
```c++
Rectangle rect{5, 5};
process(rect);
```
-> expected area: 50 real area: 50  
&nbsp;  

그 다음 Square인 경우를 살펴보자  
```c++
Square sq{5};
process(sq);
```
-> expected area: 50 real area: 100  
&nbsp;  

결과적으로 Square 객체의 set_height과 Rectangle 객체의 set_height의 작동 방식이 달라서 LSP 원칙을 위배하고 있다.  
이러한 경우 Square 클래스에서 set_width, set_height을 제거하고 정사각형 답게 set_size 함수 하나만 정의하는 것으로 해결할 수 있다.  
아니면 Square 클래스를 Rectangle 클래스 자식으로 삼지 말고 독립적이게 따로 만드는 방법도 있다.  
&nbsp;  

## 인터페이스 분리 원칙(ISP)  

구현하지 않는 가상함수 껍데기를 만들지 말자는 원칙이다.  
&nbsp;  

예를 들어 복합기의 기반을 다지는 IMachine 인터페이스를 살펴보자.  
```c++
struct Document {
    int index;
    std::string content;
};

class IMachine {
  public:
    virtual void print(std::vector<Document> &docs) = 0;
    virtual void fax(std::vector<Document> &docs) = 0;
    virtual void scan(std::vector<Document> &docs) = 0;
};
```
IMachine을 상속하기만 하면 print, fat, scan 등을 재정의하여 사용할 수 있다.  
그런데 만약 만드려는 복합기가 fax 지원을 안한다면 어떻게 할까? 그냥 fax 함수를 껍데기인 채로 놓아두어야 할까?  
정리정돈이 안되어 있기 때문에 별로다.  
&nbsp;  

밑의 예시처럼 ISP 원칙을 지키기위해 모든 인터페이스를 분리시킨다.  
```c++
class IPrinter {
  public:
    virtual void print(std::vector<Document> &docs) = 0;
};

class IScanner {
  public:
    virtual void scan(std::vector<Document> &docs) = 0;
};

class IFaxMachine {
  public:
    virtual void fax(std::vector<Document> &docs) = 0;
};
```
&nbsp;  

이렇게 하면 밑과 같이 입맛대로 팩스 기능이 없는 복합기의 IMachine 인터페이스를 조합할 수 있다.  
```c++
class IMachine : public IPrinter, public IScanner {};
```
&nbsp;  

실제로 IMachine을 상속하는 복합기 클래스 구조 예시는 밑과 같다.  
```c++
class Machine : public IMachine {
    IPrinter *printer;
    IScanner *scanner;

  public:
    Machine(IPrinter *printer, IScanner *scanner) {
        this->printer = printer;
        this->scanner = scanner;
    }
    ~Machine() {
        if (printer)
            delete printer;
        if (scanner)
            delete scanner;
    }

    void print(std::vector<Document> &docs) {
        printer->print(docs);
    }

    void scan(std::vector<Document> &docs) {
        scanner->scan(docs);
    }
};
```
위에서 ```이미 클래스 멤버 변수로 IPrinter와 IScanner가 있는데 왜 IMachine을 또 상속한거지?```라는 의문이 들수 있는데 Machine에서 print, scan 함수에 대한 재정의를 강제하기 위해서 상속한 것이다.  
&nbsp;  

밑과 같이 인터페이스를 상속한 클래스를 만들고 입맛대로 print 함수와 scan 함수를 재작성한다.  
```c++
class Printer : public IPrinter {
  public:
    Printer() {}
    void print(std::vector<Document> &docs) {
        std::cout << "I print something!\n";
    }
};

class Scanner : public IScanner {
  public:
    Scanner() {}
    void scan(std::vector<Document> &docs) {
        std::cout << "I scan something!\n";
    }
};
```
&nbsp;  

밑과 같이 복합기 클래스를 생성하고 사용하면 된다.   
```c++
Machine machine(new Printer(), new Scanner());
machine.print(doc);
```

&nbsp;  
## 의존성 역전 원칙(DIP)  
  
일단 두가지 정의가 있다.  
하나는 상위 모듈(자식 클래스 같은 느낌)가 하위 모듈(부모 클래스 같은 느낌)에 종속성을 가져서는 안되고 상위, 하위 클래스 모두 추상화에 의존해야 한다이고 나머지 하나는 추상화가 세부사항에 의존하는 것이 아니라 세부 사항이 추상화에 의존해야 한다는 것이다.  
&nbsp;  

밑과 같이 동물원 클래스가 존재한다.  
동물원에 존재하는 동물들의 종류도 출력해주는 함수도 같이 있다.  
```c++
class Zoo {
  public:
    void print_animals() {
    }
};
```
&nbsp;  

동물원에 원숭이가 들어왔다.   
```c++
class Monkey {
    int tail_lengh;

  public:
    void print_monkey() { std::cout << "Monkey's tail lengh: " << tail_lengh; }
};
```
&nbsp;  

동물원 클래스 내부 로직이 바뀌어야 한다.  
```c++
class Zoo {
    Monkey monkey;

  public:
    void print_animals() {
        monkey.print_monkey();
    }
};
```
&nbsp;  

동물원에 호랑이와 코끼리가 추가되었다.  
```c++
class Tiger {
    int tooth_lengh;

  public:
    void print_tiger() { std::cout << "Tiger's tooth lengh: " << tooth_lengh; }
};

class Elephant {
    int nose_lengh;

  public:
    void print_elephant() { std::cout << "Elephant's nose lengh: " << nose_lengh; }
};
```
&nbsp;  

동물원 클래스는 이에 맞춰 또 바뀌어야 한다.  
```c++
class Zoo {
    Monkey monkey;
    Tiger tigher;
    Elephant elephant;

  public:
    void print_animals() {
        monkey.print_monkey();
        tigher.print_tiger();
        elephant.print_elephant();
    }
};
```
동물이 추가될 때마다 상위 모듈인 동물원 클래스가 계속 바뀌어야 한다.  
이미 DIP 원칙에서 ```상위 모듈은 하위 모듈에 종속성을 가지면 안된다.```를 위배하고 있다.  
위 예시에서 추상화의 개념도 없고 세부 사항인 출력 멤버 함수들은 모두 자신의 클래스에 의존적이기 때문에 ```추상화가 세부사항에 의존하는 것이 아니라 세부 사항이 추상화에 의존해야 한다```도 위배하고 있다.  
&nbsp;  

이를 해결하려면 모든 동물들의 공통된 추상 클래스인 Animal을 만든다.  
```c++
class Animal {
    int type;

  public:
    virtual void print_animal() = 0;
};
```
&nbsp;  

모든 각각의 동물 클래스들은 Animal에 의존한다.  
```c++
class Monkey : public Animal {
    int tail_lengh;

  public:
    void print_animal() { std::cout << "Monkey's tail lengh: " << tail_lengh; }
};

class Tiger : public Animal {
    int tooth_lengh;

  public:
    void print_animal() { std::cout << "Tiger's tooth lengh: " << tooth_lengh; }
};

class Elephant : public Animal {
    int nose_lengh;

  public:
    void print_animal() { std::cout << "Elephant's nose lengh: " << nose_lengh; }
};
```
&nbsp;  

마지막으로 동물원 클래스는 이제 어떤 동물이 와도 클래스 구조에 변함이 없다.  
```c++
class Zoo {
    std::vector<Animal> animals;

  public:
    void print_animals() {
        std::for_each(animals.begin(), animals.end(), [](auto &animal) -> void {
            animal.print_animal();
        });
    }
};
```
한번 구조를 다시 봐보면 지금 현재 상태는 ```Zoo -> Animal <- Monkey, Tiger, Elephant``` 이러한 의존 관계로 되어있다.  
하위 모듈, 상위 모듈 모두 추상화 Animal에 의존하는 바람직한 구조를 갖추고 있다.  
세부 사항인 print_animal 함수 조차 추상화인 Animal에 의존하기 때문에 DIP 원칙이 모두 지켜지고 있는 코드 구조다.  