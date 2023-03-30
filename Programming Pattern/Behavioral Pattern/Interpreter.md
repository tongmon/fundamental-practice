# Interpreter Pattern  

인터프리터를 직역하면 ```해석자```이다.  
프로그래밍 언어 자체는 그냥 텍스트일 뿐이다.  
따라서 사람만 이해할 수 있고 컴퓨터는 무슨 말인지 못알아 먹는다.  
인터프리터를 이용해 컴퓨터 언어로 번역을 해줘야 비로소 컴퓨터가 그 뜻을 이해할 수 있다.  
```3 + (50 % 3) - 23 x 12```는 단순한 계산식이다.  
수식을 안배운 사람이 저 식이 의미하는 바를 알 수 있을까?  
저 식이 의미하는 바를 해석하기 위해 계산기라는 인터프리터를 사용할 수 있다.  
&nbsp;  

## 산술 표현식의 계산  

인터프리터는 상황마다 다양한 형태를 취하며 복잡하다.  
그리고 대부분의 인터프리터는 만들어져 있기에 직접 구현해 사용하는 경우도 드물다.  
따라서 패턴 이해를 돕기 위해 계산기 정도의 예시만 구현하고 넘어간다.  
&nbsp;  

### Lexing  

표현식을 해석하는 첫 단계는 렉싱이다.  
문자열 입력을 토큰 단위로 끊어 나열하는 단계다.  
여기서 말하는 토큰이란 ```의미를 가지는 최소 단위```이다.  
산술 표현식에서는 ```정수 [ex. 2, 9]```, ```연산자 [ex. +, -]```, ```괄호 [ex. (, )]```가 토큰이 될 수 있다.  
이러한 토큰을 구현해보자.  
```c++
struct Token
{
    enum Type
    {
        integer,
        plus,
        minus,
        slash,
        asterisk,
        left_bracket,
        right_bracket
    } type;
    std::string text;

    explicit Token(Type type, const std::string &text)
        : type{type}, text{text}
    {
    }
};
```
Type 열거형을 통해 토큰의 타입을 구분한다.  
예시를 간단하게 만들기 위해 토큰은 ```숫자, +, -, *, /, (, )```만 다룬다.  
실제 토큰의 문자열은 text에 보관한다.  
&nbsp;  

```c++
std::vector<Token> lexing(const std::string &input)
{
    std::vector<Token> result;

    for (int i = 0; i < input.size(); ++i)
    {
        switch (input[i])
        {
        case '+':
            result.push_back(Token{Token::plus, "+"});
            break;
        case '-':
            result.push_back(Token{Token::minus, "-"});
            break;
        case '*':
            result.push_back(Token{Token::asterisk, "*"});
            break;
        case '/':
            result.push_back(Token{Token::slash, "/"});
            break;
        case '(':
            result.push_back(Token{Token::left_bracket, "("});
            break;
        case ')':
            result.push_back(Token{Token::right_bracket, ")"});
            break;
        default:
            std::string number;
            for (; i < input.size(); i++)
            {
                if ('0' <= input[i] && input[i] <= '9')
                    number += input[i];
                else
                {
                    i--;
                    break;
                }
            }
            result.push_back(Token{Token::integer, number});
        }
    }

    return result;
}
```
숫자 이외의 다른 토큰들은 별도의 처리없이 그대로 넣으면 된다.  
숫자는 '123'과 같이 연속된 문자열이 하나의 숫자를 구성할 수 있으므로 숫자가 아닌 문자열이 등장할 때까지 수식을 검사한다.  
&nbsp;  

### Parsing   

파싱은 토큰을 의미있는 단위로 변환한다.  
토큰의 종류가 여럿이기에 토큰들을 묶어 처리하기 위해 밑과 같은 인터페이스를 둔다.  
```c++
struct Element
{
    virtual int evaluation() = 0;
};
```
evaluation() 함수에서 각 토큰의 의미가 해석되고 그에 따른 결과가 도출된다.    
&nbsp;  

숫자에 대한 파싱 단위이다.  
```c++
struct Integer : Element
{
    int value;
    explicit Integer(const std::string &value)
        : value(std::stoi(value))
    {
    }
    int evaluation()
    {
        return value;
    }
};
```
주어진 문자열을 숫자로 변환하여 저장하고 evaluation() 호출시 반환해주면 된다.  
그저 문자열이였던 ```"13"```가 정수형 ```13```으로 해석된다.  
&nbsp;  

다음은 이항 연산자다.  
사칙연산을 모두 다룬다.  
```c++
struct BinaryOperation : Element
{
    enum Type
    {
        addition,
        subtraction,
        multiply,
        division
    } type;
    std::shared_ptr<Element> left, right;

    BinaryOperation(BinaryOperation::Type type)
        : left{nullptr}, right{nullptr}, type{type}
    {
    }

    int evaluation()
    {
        switch (type)
        {
        case addition:
            return left->evaluation() + right->evaluation();
            break;
        case subtraction:
            return left->evaluation() - right->evaluation();
            break;
        case division:
            return left->evaluation() / right->evaluation();
            break;
        default:
            return left->evaluation() * right->evaluation();
            break;
        }
    }
};
```
중요한 것은 해당 이항 연산자 파싱 단위는 트리 노드 형태를 갖추고 있다는 것이다.  
따라서 left, right 멤버 포인터가 존재한다.  
이항 연산자 노드는 추후에 등장할 parse() 함수에서 수식 트리(Expression Tree)를 구성하는 데 핵심적인 역할을 한다.  
수식 트리의 예시를 간단히 보자면 ```(1 + 3) - (7 - 11)``` 이러한 식은 밑과 같이 구성된다.  
```tree
-
├── +
│   ├── 1
│   └── 3
└── -
    ├── 7
    └── 11
```
evaluation() 함수에서는 주어진 type에 따라 사칙연산을 진행하면 된다.  
&nbsp;  

밑은 파싱 함수이다.  
```c++
std::shared_ptr<Element> parse(const std::vector<Token> &tokens)
{
    std::vector<Token> post;

#pragma region Infix To Postfix
    std::stack<Token> stack;
    std::map<Token::Type, char> priority{{Token::plus, 1},
                                         {Token::minus, 1},
                                         {Token::slash, 2},
                                         {Token::asterisk, 2},
                                         {Token::left_bracket, 0}};

    // 중위 표현식을 후위 표현식으로 변환
#pragma endregion

#pragma region Make Expression Tree
    std::stack<std::shared_ptr<Element>> nodes;

    // 수식 트리 생성
#pragma endregion

    return nodes.top();
}
```
수식 트리를 만들기 위해 먼저 중위 표현식을 후위 표현식으로 변환을 한다.  
그 뒤에 획득한 후위 표현식을 토대로 수식 트리를 구성하고 해당 트리의 root 노드를 반환한다.  
&nbsp;  

중위 표현식을 후위 표현식으로 바꾸는 세부 로직은 밑과 같다.  
```c++
#pragma region Infix To Postfix
    std::stack<Token> stack;
    std::map<Token::Type, char> priority{{Token::plus, 1},
                                         {Token::minus, 1},
                                         {Token::slash, 2},
                                         {Token::asterisk, 2},
                                         {Token::left_bracket, 0}};

    for (const auto &token : tokens)
    {
        switch (token.type)
        {
        case Token::integer:
            post.push_back(token);
            break;
        case Token::left_bracket:
            stack.push(token);
            break;
        case Token::right_bracket:
            while (!stack.empty() && stack.top().type != Token::left_bracket)
            {
                post.push_back(stack.top());
                stack.pop();
            }
            if (!stack.empty())
                stack.pop();
            break;
        default:
            while (!stack.empty() && priority[stack.top().type] >= priority[token.type])
            {
                post.push_back(stack.top());
                stack.pop();
            }
            stack.push(token);
            break;
        }
    }

    while (!stack.empty())
    {
        post.push_back(stack.top());
        stack.pop();
    }
#pragma endregion
```
인터넷에 후위, 중위, 전위 표기법 변환과 관련한 정보는 널렸으니 대충 이러한 절차를 거친다는 것만 알고 넘어가자.  
중요한 것은 세부적인 구현부가 아니라 인터프리터 패턴의 전체적인 구조를 이해하는 것이다.  
&nbsp;  

밑은 수식 트리를 구현하는 세부 로직이다.  
```c++
#pragma region Make Expression Tree
    std::stack<std::shared_ptr<Element>> nodes;

    for (auto &token : post)
    {
        if (token.type == Token::integer)
        {
            nodes.push(std::make_shared<Integer>(token.text));
            continue;
        }

        std::shared_ptr<BinaryOperation> root = nullptr;
        switch (token.type)
        {
        case Token::plus:
            root = std::make_shared<BinaryOperation>(BinaryOperation::Type::addition);
            break;
        case Token::minus:
            root = std::make_shared<BinaryOperation>(BinaryOperation::Type::subtraction);
            break;
        case Token::slash:
            root = std::make_shared<BinaryOperation>(BinaryOperation::Type::division);
            break;
        default:
            root = std::make_shared<BinaryOperation>(BinaryOperation::Type::multiply);
            break;
        }

        root->right = nodes.top();
        nodes.pop();
        root->left = nodes.top();
        nodes.pop();
        nodes.push(root);
    }
#pragma endregion
```
후위 표기식을 순차적으로 읽어나가면 된다.  
숫자가 나타나면 바로 스택에 저장한다.  
이항 연산자가 나타나면 트리 노드를 생성하여 스택에 저장한다.  
현재 파싱 함수는 ```(11-4))-3``` 이러한 비정상적인 식에 대해 대처를 할 수가 없다.  
즉 예외 처리에 대한 로직이 없다는 것이다.  
실제 사용할 인터프리터의 파싱 부분을 구현할 때는 예외 처리 방식을 어떻게 구성할 것인지에 대한 부분도 매우 중요하기에 다양한 예외 사항에 대처하기 위해 많이 고민해봐야 할 것이다.  
&nbsp;  

사용법은 밑과 같다.  
```c++
auto token = lexing("10-((13-4)*(9+1))/5");
auto parsed = parse(token);
if (parsed)
    std::cout << parsed->evaluation();
```
evaluation() 함수를 호출하면 트리를 타고 내려가면서 괄호 우선 순위에 맞춰 계산을 수행한다.  
다시 말하지만 세부적인 구현은 인터프리터가 무엇을 해석하는지에 따라 천차만별이기에 별로 중요하지 않고 렉싱에서 파싱으로 이어지는 전체적인 흐름을 이해하는 것이 중요하다.  
&nbsp;  

## Boost를 이용한 인터프리터 패턴  

Boost 라이브러리에는 인터프리터 구현은 도와주는 boost::spirit 모듈이 존재한다.  
템플릿 기법이 난무하는 모듈이기에 컴파일 시간이 늘어나고 사용법도 까다로운 편이다.  
게다가 다른 Boost 모듈들과 함께 맞물려 작동하기에 다른 모듈들에 대한 이해도 필요하다.  
그래도 사용하는 이유는 매우 강력한 기능을 제공하기 때문이다.  
&nbsp;  

### Boost.Variant  

boost::variant는 std::variant의 상위호환이라고 보면 된다.  
boost::spirit을 편리하게 사용하기 위해 boost::variant가 자주 활용되기에 이해가 필요하다.  
밑은 boost::variant의 간단한 예시이다.  
```c++
struct Num_With_Diversiform;
struct String_With_Diversiform;

using Diversiform = boost::variant<char, int, std::string, boost::recursive_wrapper<Num_With_Diversiform>, boost::recursive_wrapper<String_With_Diversiform>>;

struct Num_With_Diversiform
{
    int number;
    Diversiform diversiform;
};

struct String_With_Diversiform
{
    std::string str;
    Diversiform diversiform;
};
```
std::variant와 다르게 ```Num_With_Diversiform <-> Diversiform``` 요렇게 재귀적으로 형식을 담을 수 있다.  
이를 잘 활용하면 트리 구조를 형성할 수도 있다.  
&nbsp;  

값 획득시에는 boost::get을 사용한다.  
```c++
Num_With_Diversiform nwd{1, "one"}, nwd_clone;
Diversiform df = nwd;
nwd_clone = boost::get<Num_With_Diversiform>(df);
```
&nbsp;  

boost:apply_visitor를 사용하면 적은 코드로 방문자 패턴을 구현할 수 있다.  
```c++
struct printer
{
    template <typename T>
    void operator()(const T &t)
    {
        std::cout << t;
    }

    template <>
    void operator()(const Num_With_Diversiform &t)
    {
        std::cout << t.number << " ";
        boost::apply_visitor(*this, t.diversiform);
    }

    template <>
    void operator()(const String_With_Diversiform &t)
    {
        std::cout << t.str << " ";
        boost::apply_visitor(*this, t.diversiform);
    }
};

int main()
{
    std::vector<Diversiform> vec{1, "hello world", 'A', Num_With_Diversiform{777, 'B'}, String_With_Diversiform{"hi", Num_With_Diversiform{123, "bye"}}};

    for (const auto &item : vec)
    {
        boost::apply_visitor(printer(), item);
        std::cout << "\n";
    }

    return 0;
}
```  
boost::apply_visitor() 함수에 functor or 람다 함수와 boost:variant 값을 넣어주면 자료형에 알맞는 함수를 호출해준다.  
&nbsp;  

### Boost.Fusion  

boost::fusion은 구조체, 클래스를 좀 더 쉽게 다룰 수 있도록 다양한 확장 기능을 제공한다.  
boost::spirit에서 커스텀 구조체나 클래스에 파싱 정보를 담고자할 때 같이 사용된다.  
일단 밑과 같은 구조체가 존재한다.  
```c++
struct Object
{
    std::string str;
    int integer;
    bool boolean;
};
```
요 녀석의 멤버 변수들을 boost::fusion을 사용하여 배열처럼 순회할 수 있다.  
&nbsp;  

밑과 같이 Object 구조체를 BOOST_FUSION_ADAPT_STRUCT 매크로를 사용해 fusion 구조체 형식으로 등록해준다.  
```c++
BOOST_FUSION_ADAPT_STRUCT(Object, (std::string, str)(int, integer)(bool, boolean))

struct print
{
    template <typename T>
    void operator()(T &t)
    {
        std::cout << t << " ";
    }

    template <>
    void operator()(std::string &t)
    {
        t += " world";
        std::cout << t << " ";
    }

    template <>
    void operator()(int &t)
    {
        std::cout << t << " ";
    }

    template <>
    void operator()(bool &t)
    {
        std::cout << t << " ";
    }
};
```
print functor도 위와 같이 구현했다.  
std::string을 인자로 받는 템플릿 특수화 함수만 로직이 살짝 다르다.  
&nbsp;  

밑과 같이 fusion::for_each() 함수를 이용하면 주어진 functor나 람다함수를 이용하여 멤버 변수를 이용할 수 있다.  
중요한 것은 Object 구조체 멤버 변수들의 모든 자료형을 처리할 수 있는 functor나 람다함수여야 한다.  
예를 들어 print functor에서 ```operator()(T &t)```와 ```operator()(bool &t)```가 정의되지 않았다면 컴파일이 되지 않는다.  
```c++
Object obj{"hello", 10, false};
boost::fusion::for_each(obj, print());
```
결과적으로 fusion::for_each() 함수가 수행되고 obj.str은 "hello world" 값을 저장하게 된다.  
위 예시에서 출력값은 ```hello world 10 0```이 된다.  
&nbsp;  

좀 더 나아가 boost::mpl을 같이 사용해 필터링을 할 수도 있다.  
```c++
boost::fusion::for_each(boost::fusion::filter_if<boost::is_same<boost::mpl::_, std::string>>(obj), print());
```
```fusion::filter_if<>```를 통해 필터링이 가능하고 ```boost::is_same<boost::mpl::_, std::string>``` 구문을 통해 자료형이 std::string인 멤버 변수만 추려 print functor가 호출된다.  
주의할 점은 ```fusion::filter_if<>```가 필터링 조건에 알맞은 객체를 복사하여 const 형으로 반환한다는 것이다.  
따라서 함수 내부에서 참조로 받은 인자를 수정할 수 없다.  
그리고 무조건 템플릿 원본 함수만 호출된다.  
위 예시에서의 출력값은 ```hello```가 된다.  
&nbsp;  

밑은 다른 필터링 예시이다.  
```c++
boost::fusion::for_each(boost::fusion::filter_if<boost::mpl::not_<boost::is_class<boost::mpl::_>>>(obj), print());
```
```boost::is_class<boost::mpl::_>```를 통해 클래스 형태의 멤버 변수를 추려낼 수 있다.  
```boost::mpl::not_<>```를 통해 반대의 결과를 추려낼 수 있다.  
종합하면 클래스가 아닌 형태의 멤버 변수를 추려내는 로직이다.  
위 예시 출력값은 ```10 0```이 된다.  
자세한 내용은 https://www.boost.org/doc/libs/1_81_0/libs/fusion/doc/html/index.html 링크를 참조하자.  
&nbsp;  

### Boost.Spirit  

boost::spirit 모듈을 사용하는 간단한 예시부터 살펴보자.  
아래는 주어진 문자열에서 숫자를 파싱하는 예시이다.  
```c++
std::string str = " 11";
auto it_start = str.begin();
auto it_end = str.end();

int parsed;
bool success = boost::spirit::qi::phrase_parse(it_start, it_end, boost::spirit::qi::int_, boost::spirit::ascii::space, parsed);

if (success)
    std::cout << parsed << '\n';
```
phrase_parse() 함수는 인자로 다음 녀셕들을 받는다.  
```1: 문자열 시작 iterator, 2: 문자열 끝 iterator, 3: 파싱할 규칙, 4: 파싱할 때 무시할 문자, 5: 파싱한 값을 저장할 변수들...```  
phrase_parse() 함수는 파싱하면서 iterator를 수정할 수 있기 때문에 위 예시와 같이 iterator 복사본을 넘기는 것이 좋다.  
파싱할 규칙은 사용자가 정하기 나름이다.  
해당 예시에서는 ```qi::int_```를 사용했기에 정수형을 파싱하였다.  
```qi::char_```, ```qi::float_``` 등 여러가지가 있는데 자세한 내용은 https://www.boost.org/doc/libs/1_81_0/libs/spirit/doc/html/spirit/qi/quick_reference/qi_parsers.html 링크를 참조하자.  
```ascii::space```를 사용하여 공백 문자는 무시한다.  
숫자 11이 파싱되어 parsed 변수에 저장된다.  
phrase_parse() 함수는 주어진 문자열에 대해 유효성 검사를 진행해 파싱이 성공하면 true, 아니면 false를 반환한다.  
&nbsp;  

다음 예시는 여러 항목을 파싱하는 예시이다.  
```c++
std::string str = "71.45, 11.12";
auto it_start = str.begin();
auto it_end = str.end();
std::vector<double> parsed;

bool success = boost::spirit::qi::phrase_parse(it_start, it_end, boost::spirit::qi::double_ >> *(',' >> boost::spirit::qi::double_), boost::spirit::ascii::space, parsed);

if (success)
    std::cout << parsed[0] << ", " << parsed[1] << '\n';
```
double 형 두 숫자를 파싱하려고 한다.  
파싱할 규칙이 생소할 수 있는데 EBNF에 대한 사전 지식이 요구된다.  
EBNF에 대한 설명은 https://en.wikipedia.org/wiki/Extended_Backus%E2%80%93Naur_form 링크를 참고하자.  
```boost::spirit::qi::double_ >> *(',' >> boost::spirit::qi::double_)```를 EBNF로 표기하면 ```rule := double { "," double }```와 같다.  
boost::spirit에서는 이러한 표현을 간소화 하기 위해 ```boost::spirit::qi::double_ % ','``` 표현식도 제공한다.  
표현식 규칙에 대한 더 자세한 정보는 https://www.boost.org/doc/libs/1_81_0/libs/spirit/doc/html/spirit/qi/quick_reference/qi_parsers/operator.html 링크를 참고하자.  
그리고 중요한 점은 ',' 요렇게 따옴표, 큰따옴표로만 감싸여 있는 것들은 구분자로만 사용되고 파싱에서 제외된다.  
만약 ','도 파싱하고 싶다면 ```boost::spirit::qi::char_(',')``` 이렇게 표현해야 한다.  
&nbsp;  

다음은 여러개의 규칙이 복합적으로 작용해야 하는 경우 boost::spirit 사용 예시이다.  
일단 밑과 같이 ```boost::spirit::qi::grammar```를 상속하는 클래스를 만들어준다.  
```c++
template <typename Iterator, typename Skipper>
struct my_grammar : boost::spirit::qi::grammar<Iterator, std::vector<std::variant<int, std::string>>, Skipper>
{
    my_grammar()
        : my_grammar::base_type{values}
    {
        value = boost::spirit::qi::int_ | boost::spirit::qi::as_string[boost::spirit::qi::lexeme[+(boost::spirit::qi::char_ - boost::spirit::qi::char_(",0-9"))]];
        values = value % ',';
    }

    boost::spirit::qi::rule<Iterator, std::variant<int, std::string>, Skipper> value;
    boost::spirit::qi::rule<Iterator, std::vector<std::variant<int, std::string>>, Skipper> values;
};
```
하나씩 살펴보자.  
qi::rule과 qi::grammar에는 템플릿 인자로 반복자, 파싱할 자료형, 파싱 건너뛸 문자 타입이 들어간다.  
my_grammar 클래스 내부에서는 ```value := int | ((char - ("," | digit) { (char - ("," | digit) })```, ```values := value | { "," value }``` 이러한 파싱 규칙을 정의하였다.  
그리고 생성자에서 base_type을 정하여 파싱 시작 규칙이 무엇인지 알려줘야 한다.  
boost::spirit에선 모든 문자열을 기본적으로 ```std::vector<char>```에 파싱하여 담으려한다.  
하지만 qi::as_string를 사용하면 문자열을 std::string 형태로 파싱한다. (std::wstring을 위한 qi::as_wstring도 존재한다.)  
qi::lexeme은 감싸진 영역에 한하여 Skipper를 무시한다.  
예를 들어 ```This is cool```라는 문자열을 파싱할 때 Skipper가 공백이라면 ```Thisiscool``` 요렇게 공백은 무시되어 파싱된다.  
qi::lexeme을 사용하면 공백까지 파싱하여 ```This is cool``` 요렇게 파싱된다.  
이 외에도 많은 지시어가 존재하니 https://www.boost.org/doc/libs/1_81_0/libs/spirit/doc/html/spirit/qi/quick_reference/qi_parsers/directive.html 링크를 참조하자.  
&nbsp;  

파싱 규칙 클래스를 만들었으니 적용해보자.  
```c++
std::string str = "11, hello world, 45, tongstar";
auto it_start = str.begin();
auto it_end = str.end();

std::vector<std::variant<int, std::string>> parsed;
my_grammar<std::string::iterator, boost::spirit::ascii::space_type> gram;
bool success = boost::spirit::qi::phrase_parse(it_start, it_end, gram, boost::spirit::ascii::space, parsed);

if (success)
    std::cout << std::get<int>(parsed[0]) << ", "
              << std::get<std::string>(parsed[1]) << ", "
              << std::get<int>(parsed[2]) << ", "
              << std::get<std::string>(parsed[3]);
```
my_grammar 클래스를 선언하고 qi::phrase_parse() 함수에 규칙으로 넣어주면 된다.  
지금까지의 예시들을 보면 알겠지만 int, std::vector, std::variant 등 c++에 원래 존재했던 자료형에만 파싱된 자료를 저장하고 있다.  
그렇다면 커스텀 클래스에 파싱된 자료형을 넣으려면 어떻게 해야 할까?  
&nbsp;  

밑은 커스텀 클래스에 파싱된 자료형을 넣는 예시이다.   
```c++
struct Object
{
    std::string name;
    std::variant<int, bool> int_or_bool;
    std::vector<double> vec;
};

BOOST_FUSION_ADAPT_STRUCT(Object, name, int_or_bool, vec)
```
일단 위와 같이 Object 구조체를 fusion 구조체에 등록해준다.  
&nbsp;  

Object 파싱을 위한 grammer 클래스를 작성해준다.  
```c++
template <typename Iterator, typename Skipper>
struct my_grammar : boost::spirit::qi::grammar<Iterator, Object, Skipper>
{
    my_grammar()
        : my_grammar::base_type{value}
    {
        int_or_bool_rule = boost::spirit::qi::int_ | boost::spirit::qi::bool_;
        vec_rule = boost::spirit::qi::double_ % ',';
        value = boost::spirit::qi::as_string[boost::spirit::qi::lexeme[+(boost::spirit::qi::char_ - boost::spirit::qi::char_(",0-9"))]] >> ',' >> int_or_bool_rule >> ',' >> vec_rule;
    }

    boost::spirit::qi::rule<Iterator, std::variant<int, bool>, Skipper> int_or_bool_rule;
    boost::spirit::qi::rule<Iterator, std::vector<double>, Skipper> vec_rule;
    boost::spirit::qi::rule<Iterator, Object, Skipper> value;
};
```
파싱할 때 사용할 문자열은 ```object name, 777, 10.139, 34.3, 56.82``` 이렇게 생겼다.  
```문자열, [int | bool], double, double...``` 이러한 규칙이기에 이에 맞는 파싱 규칙을 짜주었다.  
&nbsp;  

아래 코드로 진행해보면 파싱이 잘 되는 것을 확인할 수 있다.  
```c++
std::string str = "object name, 777, 10.139, 34.3, 56.82";
auto it_start = str.begin();
auto it_end = str.end();
Object parsed;

my_grammar<std::string::iterator, boost::spirit::ascii::space_type> gram;
bool success = boost::spirit::qi::phrase_parse(it_start, it_end, gram, boost::spirit::ascii::space, parsed);

if (success)
{
    std::cout << parsed.name << "\n"
              << "int: " << std::get<int>(parsed.int_or_bool) << "\n";
    std::cout << parsed.vec[0] << ", " << parsed.vec[1] << ", " << parsed.vec[2];
}
```
&nbsp;  

그러면 마지막으로 boost::spirit을 통해 수식을 파싱하고 계산을 수행하는 예시를 보자.  
이해하기가 살짝 까다롭기에 여러번 봐야할 것이다.  
먼저 수식 구성에 필요한 다음과 같은 구조체들이 필요하다.  
```c++
struct Number;
struct Expression;

using Factor = boost::variant<boost::blank, unsigned int, boost::recursive_wrapper<Number>, boost::recursive_wrapper<Expression>>;

struct Number
{
    char _sign;
    Factor _operand;
};

struct Operation
{
    char _operator;
    Factor _operand;
};

struct Expression
{
    Factor _first;
    std::list<Operation> _rest;
};

BOOST_FUSION_ADAPT_STRUCT(Number, _sign, _operand)

BOOST_FUSION_ADAPT_STRUCT(Operation, _operator, _operand)

BOOST_FUSION_ADAPT_STRUCT(Expression, _first, _rest)
```
Number는 숫자다.  
수식이 ```+7+-10+4``` 이러한 경우 +7, -10과 같은 숫자들을 다루기 위해 존재한다.  
Operation은 연산자다.  
사칙연산 부호들과 우측 나머지 수식이 저장된다.  
Expression는 수식이다.  
만약 ```10-40+10``` 이러한 식이라면 first에 10이 저장되고 _rest[0]에 (-, 40), _rest[1]에 (+, 10)이 저장된다.  
Factor는 수식을 구성하는 노드라고 보면 된다.  
숫자나 또 다른 수식이 될 수 있다.  
또 다른 수식이 되는 경우는 괄호 속 수식인 경우다.  
파싱을 위해 Number, Operation, Expression 구조체를 fusion 구조체로 등록해준다.  
&nbsp;  

다음으로 파싱 규칙을 보자.  
```c++
template <typename Iterator>
struct Calculator : boost::spirit::qi::grammar<Iterator, Expression, boost::spirit::ascii::space_type>
{
    Calculator()
        : Calculator::base_type(expression)
    {
        boost::spirit::qi::uint_type uint_;
        boost::spirit::qi::char_type char_;

        expression = term >> *((char_('+') >> term) | (char_('-') >> term));

        term = factor >> *((char_('*') >> factor) | (char_('/') >> factor));

        factor = uint_ | '(' >> expression >> ')' | (char_('-') >> factor) | (char_('+') >> factor);
    }

    boost::spirit::qi::rule<Iterator, Expression, boost::spirit::ascii::space_type> expression;
    boost::spirit::qi::rule<Iterator, Expression, boost::spirit::ascii::space_type> term;
    boost::spirit::qi::rule<Iterator, Factor, boost::spirit::ascii::space_type> factor;
};
```
파싱 규칙을 EBNF로 표현하면 밑과 같다.  
```ebnf 
expression = term { ("-" term) | ("+" term) }
term = factor { ("*" factor) | ("/" factor) }
factor = unsigned int | ( "(" expression ")" ) | ("-" factor) | ("+" factor)
```
사칙연산의 우선 순위를 생각하면 이해하기 쉽다.  
괄호 속에 담긴 수식이 최우선이고 그 다음 곱셈, 나눗셈이고 제일 낮은 우선순위는 덧셈, 뺄셈이다.  
그래서 파싱 시작 규칙에 덧셈, 뺄셈이 존재하고 하위 규칙으로 곱셈, 뺄셈이 있고 제일 하위에 숫자 or 괄호 속 수식 규칙이 위치한다.  
파싱이 되면 높은 계산 우선순위일수록 잎 노드에 가까워지는 수식 트리가 Expression에 담기게 된다.  
&nbsp;  

파싱을 통해 만들어진 수식 트리인 Expression 구조체를 계산하는 functor이다.  
```c++
struct Evaluation
{
    int operator()(boost::blank) const
    {
        BOOST_ASSERT(0);
        return 0;
    }

    int operator()(unsigned int const &n) const
    {
        return n;
    }

    int operator()(Operation const &x, int left) const
    {
        int right = boost::apply_visitor(*this, x._operand);
        switch (x._operator)
        {
        case '+':
            return left + right;
        case '-':
            return left - right;
        case '*':
            return left * right;
        case '/':
            return left / right;
        }
        BOOST_ASSERT(0);
        return 0;
    }

    int operator()(Number const &x) const
    {
        int right = boost::apply_visitor(*this, x._operand);
        switch (x._sign)
        {
        case '-':
            return -right;
        case '+':
            return +right;
        }
        BOOST_ASSERT(0);
        return 0;
    }

    int operator()(Expression const &x) const
    {
        int left = boost::apply_visitor(*this, x._first);
        for (auto const &oper : x._rest)
            left = (*this)(oper, left);
        return left;
    }
};
```
boost::apply_visitor()를 사용하여 수식 트리를 재귀적으로 순회하면서 계산을 진행한다.  
&nbsp;  

밑과 같이 만들어둔 규칙을 사용하여 수식 계산을 진행한다.  
```c++
std::string str = "10-((13-4)*(9+1))/5";
    
Calculator<std::string::iterator> calc;
Expression parsed;
Evaluation evaluation;
    
auto it_start = str.begin();
auto it_end = str.end();
bool success = boost::spirit::qi::phrase_parse(it_start, it_end, calc, boost::spirit::ascii::space, parsed);
    
if (success)
   std::cout << evaluation(parsed);
```
```-8```이 올바르게 출력되는 것을 확인할 수 있다.  
&nbsp;  

## 요약  

1. 파서를 직접 만들어야 하는 경우가 보통 없기에 인터프리터 패턴은 그렇게 많이 쓰이지 않는다.  

2. 파서를 만드는데 Boost.Spirit과 같은 라이브러리를 사용한다면 코드를 많이 줄일 수 있다.  

3. 인터프리터는 컴퓨터 과학의 한 분야이기에 매우 방대하므로 관심이 있다면 Lex/Yacc, ANTLR, AST 등을 공부해보자.  