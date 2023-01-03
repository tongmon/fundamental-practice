# Builder Pattern  
  
빌더 패턴은 객체를 쉽게 처리하기 위한 패턴이다.  
여러가지 빌더 패턴 스타일이 존재한다.  
&nbsp;  
일단 밑과 같이 간단한 XmlWriter 클래스가 있다고 하자. (xml을 실제 std::string으로 변환해주는 str() 함수 내부 로직은 지금 중요하지 않으니 신경쓸 필요 없다.)  
```c++
class XmlWriter {
    std::string content;
    std::string tag;

  public:
    std::vector<XmlWriter> element;

    XmlWriter(const std::string &tag = "", const std::string &content = "") {
        this->tag = tag, this->content = content;
    }
    ~XmlWriter() {}

    std::string str(const std::string &tabs = "") const {
        std::string content_from_element, content_modified;

        if (!element.empty()) {
            for (const auto &item : element)
                content_from_element += item.str(tabs + "\t") + "\n";
            content_from_element.pop_back();
        } else
            content_modified = std::regex_replace(tabs + "\t" + content, std::regex("\n"), "\n" + tabs + "\t");

        return tabs + "<" + tag + ">\n" + (element.empty() ? content_modified : content_from_element) + "\n" + tabs + "</" + tag + ">";
    }
};
```
&nbsp;  
이 상태에서 XmlWriter를 활용하려면 밑과 같이 코드를 구성해야 할 것이다.  
```c++
XmlWriter xml{"Zoo", ""};
xml.element.push_back(XmlWriter{"Water", "Fish"});
xml.element.push_back(XmlWriter{"Ground", XmlWriter("Horse", "Zebra").str()});
std::cout << xml.str() << "\n";
```
&nbsp;  
그러면 대략 밑과 같이 출력이 될 것이다.
```xml
<Zoo>
        <Water>
                Fish
        </Water>
        <Ground>
                <Horse>
                        Zebra
                </Horse>
        </Ground>
</Zoo>
```
&nbsp;  
XmlWriter 클래스를 활용하는 코드의 구성을 보면 xml 객체에서 element를 가져와서 push_back을 하는 코드도 난잡해 보이고, 겹겹이 쌓이는 정보를 넣을 때 ```XmlWriter("Something", XmlWriter("Something", XmlWriter("Something", "Something").str()).str()).str()``` 요런식으로 넣어줘야 하기 때문에 산만하다.  
이를 해결하는 방법들을 알아보자  

&nbsp;  
## 단순한 빌더  
  
객체 생성 역할을 맡는 다른 클래스를 별도로 만들어서 처리한다.  
&nbsp;  
Xml 객체 생성을 해주는 XmlBuilder 클래스를 밑과 같이 정의한다.  
```c++
class XmlBuilder {
    XmlWriter root;

  public:
    XmlBuilder(std::string root_tag) { root = XmlWriter(root_tag, ""); }
    ~XmlBuilder() {}
	
    void add_child(const std::string &tag, const std::string &content) {
        root.element.push_back(XmlWriter{tag, content});
    }
    std::string str() { return root.str(); }
};
```
&nbsp;  
빌더 클래스를 활용해 xml 스트링 값을 출력하는 코드를 보면 밑과 같다.  
```c++
XmlBuilder builder("Zoo");
builder.add_child("Water", "Fish");
builder.add_child("Ground", XmlWriter("Horse", "Zebra").str());
std::cout << builder.str() << "\n";
```
조금 간결하고 직관적이게 되었지만 아직 난잡해 보인다.  

&nbsp;  
## 흐름식 빌더  

객체 생성을 하는 함수에서 객체를 반환하는 형태를 갖춘다.  
  
XmlBuilder 클래스에서 add_child() 함수를 밑과 같이 변형시켜준다.  
```c++
XmlBuilder &XmlBuilder::add_child(const std::string &tag, const std::string &content) {
    root.element.push_back(XmlWriter{tag, content});
    return *this;
}
```
&nbsp;  
이렇게 되면 밑과 같이 xml 스트링 값을 출력할 수 있다.  
```c++
XmlBuilder builder("Zoo");
builder.add_child("Water", "Fish").add_child("Ground", XmlWriter{"Horse", "Zebra"}.str());
std::cout << builder.str() << "\n";
```
Xml 정보 추가를 연달아 할 수 있어 단순 빌더 방식보다 호출 코드도 짧고 직관적이다.  

&nbsp;  
### 사용자 인터페이스 통합하기  
  
사용자가 xml 클래스를 사용할 때 XmlWriter도 사용하고 XmlBuilder도 사용할 수 있으면 혼동이 올 수 있다.  
사용자가 xml 정보를 생성하고 출력하는데만 집중할 수 있도록 직관적으로 인터페이스를 제공해야한다.  
  
생각보다 좀 복잡한 단계를 거쳐야 한다.  
일단 기존에 main.cpp에서 모두 처리하던 코드들을 .h, .cpp 파일들로 전방선언, 불완전한 반환값 문제를 방지하기 위해 분리해야 한다.  

&nbsp;  
xmlwriter.h의 코드 내용이다. (헤더 가드와 각종 #include 들은 제외한다.)  
```c++
class XmlBuilder;

class XmlWriter {
    std::string content;
    std::string tag;
    friend class XmlBuilder;

  protected:
    XmlWriter(const std::string &tag = "", const std::string &content = "");

  public:
    ~XmlWriter() {}

    std::vector<XmlWriter> element;

    std::string str(const std::string &tabs = "") const;

    static XmlBuilder build(const std::string &tag);

    static std::string str(const std::string &tag, const std::string &content);
};
```
일단 잘 봐야되는 것은 생성자가 protected로 사용자가 못쓰게 가려졌다는 것이다.   
이것으로 인해 사용자는 강제로 특정 인터페이스를 통해서만 xml 정보를 구축할 수 있다.  
반면에 XmlBuilder 클래스는 친구 클래스로 선언 되었기에 XmlWriter의 생성자를 이용할 수 있다.  
또 다른 중요한 점은 전역 클래스 멤버 함수가 build, str 두개 있는데 사용자가 사용할 수 있는 xml 생성 인터페이스가 build()이고 자식 노드를 추가하기 위한 인터페이스가 str()이다.   
이제 xml 정보를 생성할 때 ```XmlWriter::build("Zoo")``` 요런식으로 접근하게 된다.  
xml 자식 노드를 생성할 때 ```XmlWriter::str("Horse", "Zebra")``` 이렇게 접근해야 한다.  
&nbsp;  
xmlwriter.cpp의 코드 내용이다.
```c++
XmlWriter::XmlWriter(const std::string &tag, const std::string &content) {
    this->tag = tag, this->content = content;
}

std::string XmlWriter::str(const std::string &tabs) const {
    std::string content_from_element, content_modified;

    if (!element.empty()) {
        for (const auto &item : element)
            content_from_element += item.str(tabs + "\t") + "\n";
        content_from_element.pop_back();
    } else
        content_modified = std::regex_replace(tabs + "\t" + content, std::regex("\n"), "\n" + tabs + "\t");

    return tabs + "<" + tag + ">\n" + (element.empty() ? content_modified : content_from_element) + "\n" + tabs + "</" + tag + ">";
}

XmlBuilder XmlWriter::build(const std::string &tag) {
    XmlWriter *writer = new XmlWriter(tag, "");
    return XmlBuilder(writer);
}

std::string XmlWriter::str(const std::string &tag, const std::string &content) {
    return XmlWriter(tag, content).str();
}
```
build 함수의 구현부는 별 특이한게 없이 간단한데 추후에 설명하겠지만 build() 함수에서 볼 수 있듯이 XmlBuilder의 생성자가 바뀌었다.  
사용자는 XmlWriter 생성자에 접근할 수 없기 때문에 자식 노드를 만들기 위한 str() 함수를 따로 만들어 준다.  
&nbsp;  
xmlbuilder.h의 코드 내용이다.
```c++
class XmlBuilder {
    XmlWriter *root;

  public:
    XmlBuilder(XmlWriter *writer) {
        root = writer;
    }
    ~XmlBuilder() { delete root; }
    operator XmlWriter() const { return *root; }
    XmlBuilder &add_child(const std::string &tag, const std::string &content);
    std::string str() {
        return root->str();
    }
};
```
객체 생성 역할만을 위한 XmlBuilder 클래스를 사용자로부터 숨기기 위해 XmlBuilder 클래스의 생성자를 사용자가 직접 사용하지 못하게 XmlWriter 클래스를 생성해야만 XmlBuilder를 생성할 수 있도록 형식을 바꾼다.  
사용자는 이제 XmlBuilder를 이용해서 xml 정보를 구축하는 것이 아니라 ```XmlWriter::build()``` 함수를 통해 xml 정보를 구축하게 된다.   
그리고 연산자 재정의 부분도 새로 추가되었는데 이를 통해 완벽하게 사용자는 XmlBuilder 클래스를 신경쓸 필요가 없어진다. 만약 add_child() 함수를 이용한다고 해도 XmlBuilder 자료형으로 반환이 될텐데 이를 그냥 XmlWriter 자료형으로 받고 str() 함수를 실행해도 XmlBuilder 클래스에서 직접 str() 함수를 실행한 것과 결과는 동일하다.  
&nbsp;  
xmlbuilder.cpp의 코드 내용이다.  
```c++
XmlBuilder &XmlBuilder::add_child(const std::string &tag, const std::string &content) {
    root->element.push_back(XmlWriter{tag, content});
    return *this;
}
```
XmlWriter 클래스를 친구 클래스를 선언했기에 XmlBuilder 클래스에서 XmlWriter 생성자에 접근이 가능하다.  
&nbsp;  
실제 사용자가 XmlWriter와 XmlBuilder를 활용한 예시는 밑과 같다.
```c++
XmlWriter writer = XmlWriter::build("Zoo").add_child("Water", "Fish").add_child("Ground", XmlWriter::str("Horse", "Zebra"));
std::cout << writer.str() << "\n";
```
코드를 보면 사용자는 XmlBuilder가 어디서 어떻게 쓰였는지 알 필요가 없다.  
단지 XmlWriter의 build(), str() 인터페이스를 이용하고 add_child()로 XmlWriter 객체를 생성하고 해당 값을 XmlWriter 클래스로 받아 활용할 뿐이다.  
XmlBuilder 클래스는 묵묵히 숨어서 객체 생성과 관련된 작업을 진행할 뿐이다.  

&nbsp;  
## 컴포지트 빌더  

특정 클래스에 여러가지 데이터가 있는데 이러한 각 데이터마다 빌더를 따로 두고 싶을 때 컴포지트 빌더를 사용한다.  
&nbsp;  

다음과 같은 Person 클래스 객체가 있다고 하자.  
```c++
class Person {
    // 주소
    std::string street_address;
    std::string post_code;
    std::string city;

    // 직장
    std::string company_name;
    std::string position;
    int annual_income = 0;

    Person() {
        std::cout << "Person created\n";
    }

  public:
    ~Person() {
        std::cout << "Person destroyed\n";
    }

    static PersonBuilder create();

    Person(Person &&other)
        : street_address{std::move(other.street_address)},
          post_code{std::move(other.post_code)},
          city{std::move(other.city)},
          company_name{std::move(other.company_name)},
          position{std::move(other.position)},
          annual_income{other.annual_income} {
    }

    Person &operator=(Person &&other) {
        if (this == &other)
            return *this;
        street_address = std::move(other.street_address);
        post_code = std::move(other.post_code);
        city = std::move(other.city);
        company_name = std::move(other.company_name);
        position = std::move(other.position);
        annual_income = other.annual_income;
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const Person &obj) {
        return os
               << "street_address: " << obj.street_address
               << "\n post_code: " << obj.post_code
               << "\n city: " << obj.city
               << "\n company_name: " << obj.company_name
               << "\n position: " << obj.position
               << "\n annual_income: " << obj.annual_income << std::endl;
    }

    friend class PersonBuilder;
    friend class PersonAddressBuilder;
    friend class PersonJobBuilder;
};
```  
생성자, 소멸자, 연산자 재정의 같은 세세한 구현부는 무시하고 Person 클래스에 주소와 직장 관련 데이터가 있다는 점에 주목하자.  
친구 클래스로 PersonBuilder, PersonAddressBuilder, PersonJobBuilder를 선언한 것은 추후에 설명한다.  
여기서 핵심은 개발자가 주소 데이터들에 대한 빌더와 직장 데이터들에 대한 빌더를 따로 만들어 구성하고 싶다면 컴포지트 빌더 패턴이 적합하다는 것이다.   
&nbsp;  

일단 PersonBuilderBase라는 주소 빌더, 직장 빌더, 사람 빌더에게 모두 필요한 기저 빌더 클래스를 밑과 같이 만들어 준다.  
```c++
class PersonBuilderBase {
  protected:
    Person &person;
    explicit PersonBuilderBase(Person &person)
        : person{person} {
    }

  public:
    operator Person() const {
        return std::move(person);
    }

    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;
};
```
이 녀석은 실제 Person 객체를 들고 있지 않고 단지 참조만 할 뿐이다.  
그리고 해당 빌더 베이스를 사용하면 형변환 연산 재정의 구현부에서 알 수 있듯이 ```std::move()```를 사용해 참조했던 녀석을 다른 곳으로 옮겨버린다.  
주소 빌더의 인터페이스가 되는 lives() 함수와 직장 빌더의 인터페이스가 되는 works() 함수를 구현해준다.  
&nbsp; 

lives(), works() 함수 구현부는 다음과 같다.  
```c++
PersonAddressBuilder PersonBuilderBase::lives() const {
    return PersonAddressBuilder{person};
}

PersonJobBuilder PersonBuilderBase::works() const {
    return PersonJobBuilder{person};
}
```
PersonAddressBuilder, PersonJobBuilder에서 구현된 빌더 인터페이스를 사용하기 위해 PersonAddressBuilder, PersonJobBuilder 객체를 그대로 반환해준다.  



&nbsp;  
## 그루비-스타일 빌더  

