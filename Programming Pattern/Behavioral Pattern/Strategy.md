# Strategy Pattern  

특정 객체가 할 수 있는 행위들을 전략적으로 나누어 놓는 패턴이다.  
예를 들어 종이 클래스가 있다고 하자.  
종이로 종이 접기도 할 수 있고 특정 내용을 적어놓아 보관할 수도 있다.  
전략 패턴을 활용하면 종이 클래스에서 ```종이 접기```와 ```내용 필기 및 보관```이라는 두 가지 행위를 손쉽게 관리할 수 있다.  
```종이 찢기```와 같은 새로운 행위를 다루고 싶을 때 확장하기도 쉽다.  
&nbsp;  

## 동적 전략  

특정 텍스트가 주어지면 Html과 MarkDown 두 가지 포맷으로 출력해주는 전략 클래스를 만들어보자.  
먼저 밑과 같은 enum 클래스를 구현한다.  
```c++
enum class OutputFormat
{
    Markdown,
    Html
};
```
&nbsp;  

전략 패턴은 각 전략 행위에 대한 동일한 인터페이스를 필요로 한다.  
```c++
struct ListStrategy
{
    virtual ~ListStrategy() = default;
    virtual void add_list_item(std::ostringstream &oss, const std::string &item){};
    virtual void start(std::ostringstream &oss){};
    virtual void end(std::ostringstream &oss){};
};
```
oss에 특정 텍스트가 담긴 문자열 스트림을 넘긴다.  
&nbsp;  

먼저 MarkDown에 대한 전략 행위를 보자.  
```c++
struct MarkdownListStrategy : ListStrategy
{
    void add_list_item(std::ostringstream &oss, const std::string &item) override
    {
        oss << " * " << item << std::endl;
    }
};
```
MarkDown 포맷에는 딱히 시작과 끝에 특정 문구를 달아줘야 하는 규칙이 없기 때문에 start(), end() 함수는 따로 재정의하지 않았다.  
&nbsp;  

Html에 대한 전략 행위는 밑과 같다.  
```c++
struct HtmlListStrategy : ListStrategy
{
    void start(std::ostringstream &oss) override
    {
        oss << "<ul>" << std::endl;
    }

    void end(std::ostringstream &oss) override
    {
        oss << "</ul>" << std::endl;
    }

    void add_list_item(std::ostringstream &oss, const std::string &item) override
    {
        oss << "<li>" << item << "</li>" << std::endl;
    }
};
```
Html은 시작과 끝에 항상 태그를 달아줘야 한다.  
&nbsp;  

전략 패턴의 핵심인 여러 전략 행위들을 다루는 클래스는 밑과 같다.  
```c++
class TextProcessor
{
    std::ostringstream oss;
    std::unique_ptr<ListStrategy> list_strategy;

  public:
    void clear()
    {
        oss.str("");
        oss.clear();
    }
    void append_list(const std::vector<std::string> items)
    {
        list_strategy->start(oss);
        for (auto &item : items)
            list_strategy->add_list_item(oss, item);
        list_strategy->end(oss);
    }
    void set_output_format(const OutputFormat format)
    {
        switch (format)
        {
        case OutputFormat::Markdown:
            list_strategy = std::make_unique<MarkdownListStrategy>();
            break;
        case OutputFormat::Html:
            list_strategy = std::make_unique<HtmlListStrategy>();
            break;
        default:
            throw std::runtime_error("Unsupported strategy.");
        }
    }
    std::string str() const
    {
        return oss.str();
    }
};
```
append_list() 함수로 여러 문자열을 특정 포맷으로 변환하여 std::ostringstream 자료형에 보관한다.  
set_output_format() 함수로 format이 어떻게 지정되느냐에 따라 list_strategy에 할당되는 컴포넌트가 달라져 TextProcessor의 행동 방식이 결정된다.  
포인터 캐스팅을 이용하기에 런타임에 포맷을 변경할 수 있다.  
&nbsp;  

활용은 밑과 같다.  
```c++
// markdown
TextProcessor tp;
tp.set_output_format(OutputFormat::Markdown);
tp.append_list({"foo", "bar", "baz"});
std::cout << tp.str() << std::endl;

// html
tp.clear();
tp.set_output_format(OutputFormat::Html);
tp.append_list({"foo", "bar", "baz"});
std::cout << tp.str();
```
&nbsp;  

출력은 밑과 같다.  
```
 * foo      
 * bar      
 * baz      

<ul>        
<li>foo</li>
<li>bar</li>
<li>baz</li>
</ul>
```
&nbsp;  

### std::variant 활용  

따로 enum을 정의하기 싫은 경우도 있을 것이다.  
그런 경우 밑과 같이 만들어 줄 수도 있다.  
```c++
class TextProcessor
{
    // 동일 구현부 생략

    void set_output_format(std::unique_ptr<ListStrategy> format)
    {
        list_strategy = std::move(format);
    }
};
```
이래도 되긴 하지만 사용자에게 허용되지 않은 XmlListStrategy 같은 전략 행위를 인자로 넘기는 경우 문제가 발생할 수 있다.  
&nbsp;  

위와 같은 문제를 방지하기 위해 std::variant를 사용하여 enum과 같은 효과를 취할 수 있다.  
```c++
class TextProcessor
{
    // 동일 구현부 생략

    void set_output_format(std::variant<std::unique_ptr<MarkdownListStrategy>, std::unique_ptr<HtmlListStrategy>> format)
    {
        switch (format.index())
        {
        case 0:
            list_strategy = std::move(std::get<0>(format));
            break;
        case 1:
            list_strategy = std::move(std::get<1>(format));
            break;
        default:
            throw std::runtime_error("Unsupported strategy.");
        }
    }
};
```
특정 전략 행위만 사용하도록 컴파일 시간에 제한할 수 있다.  
&nbsp;  

밑과 같이 이용할 수 있다.  
```c++
// markdown
TextProcessor tp;
tp.set_output_format(std::make_unique<MarkdownListStrategy>());
tp.append_list({"foo", "bar", "baz"});
std::cout << tp.str() << std::endl;

// html
tp.clear();
tp.set_output_format(std::make_unique<HtmlListStrategy>());
tp.append_list({"foo", "bar", "baz"});
std::cout << tp.str();
```
달라진 점은 set_output_format() 함수 인자로 스마트 포인터를 넘겨야 한다는 것이다.  
&nbsp;  

## 정적 전략  

런타임에 포맷을 바꿀 필요가 없다면 템플릿을 이용해 더 빠른 전략 패턴을 취할 수도 있다.  
[동적 전략 패턴](#동적-전략)의 예시 코드에서 TextProcessor 클래스만 변경해주면 된다.  
```c++
template <typename Strategy>
struct TextProcessor
{
    void clear()
    {
        oss.str("");
        oss.clear();
    }
    void append_list(const std::vector<std::string> items)
    {
        list_strategy.start(oss);
        for (auto &item : items)
            list_strategy.add_list_item(oss, item);
        list_strategy.end(oss);
    }
    std::string str() const
    {
        return oss.str();
    }

  private:
    std::ostringstream oss;
    Strategy list_strategy;
};
```
스마트 포인터를 이용하지 않고 템플릿 인자를 이용해 전략 행위를 지정한다.  
동적으로 포맷 지정이 안되기에 set_output_format() 함수는 필요없다.  
&nbsp;  

사용법은 밑과 같다.  
```c++
// markdown
TextProcessor<MarkdownListStrategy> tpm;
tpm.append_list({"foo", "bar", "baz"});
std::cout << tpm.str() << std::endl;

// html
TextProcessor<HtmlListStrategy> tph;
tph.append_list({"foo", "bar", "baz"});
std::cout << tph.str();
```
동적으로 포맷 지정이 불가하여 TextProcessor 객체를 포맷마다 따로 만들어줘야 한다.  
출력 결과는 [동적 전략](#동적-전략)의 결과와 동일하다.  
&nbsp;  

## 요약  

1. 전략 패턴에서 각 행위에 대한 세부 구현은 전략 인터페이스를 상속한 전략 클래스에 위치한다.  

2. 동적 전략, 정적 전략 중 어떤 것을 선택할 지는 개발자의 선택에 달렸다.  

3. 특정 전략 행위만 사용하도록 사용자에 강제하기 위해 enum, std::variant 등을 이용할 수 있다.  