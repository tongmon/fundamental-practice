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
예시를 간단하게 만들기 위해 토큰은 ```숫자, +, -, (, )```만 다룬다.  
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
evaluation() 함수는 각 토큰이 수행할 고유한 동작이 구현되어야 한다.  
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
&nbsp;  

다음은 이항 연산자다.  
```+, -```를 모두 다룬다.  
```c++
struct BinaryOperation : Element
{
    enum Type
    {
        addition,
        subtraction
    } type;
    std::shared_ptr<Element> left, right;

    BinaryOperation()
        : left{nullptr}, right{nullptr}
    {
    }

    int evaluation()
    {
        if (type == addition)
            return left->evaluation() + right->evaluation();
        return left->evaluation() - right->evaluation();
    }
};
```
중요한 것은 해당 이항 연산자 파싱 단위는 트리 구조를 형성한다.  
따라서 left, right 멤버 포인터가 존재한다.  
예를 들어 ```(1 + 3) - (7 - 11)``` 이러한 식은 밑과 같이 구성된다.  
```tree
-
├── +
│   ├── 1
│   └── 3
└── -
    ├── 7
    └── 11
```
evaluation() 함수에서는 주어진 type에 따라 ```+, -``` 역할을 하면 된다.  
&nbsp;  

괄호는 연산의 순서를 결정하여 재귀적으로 처리해야 하기에 파싱 단계에서 따로 처리한다.  
밑은 파싱 함수다.  
```c++
std::shared_ptr<Element> parse(const std::vector<Token> &tokens)
{
    auto root = std::make_unique<BinaryOperation>();
    for (int i = 0; i < tokens.size(); i++)
    {
        auto token = tokens[i];
        switch (token.type)
        {
        case Token::integer: 
        {
            auto integer = std::make_shared<Integer>(token.text);
            if (!root->left)
                root->left = integer;
            else
                root->right = integer;
            break;
        }
        case Token::plus:
            root->type = BinaryOperation::addition;
            break;
        case Token::minus:
            root->type = BinaryOperation::subtraction;
            break;
        case Token::left_bracket: 
        {
            // 괄호 처리 로직은 추후에 다룬다.  
            break;
        }
        default:
            return nullptr;
        }
    }
    return root;
}
```
파싱 함수는 수식의 트리 구조를 형성하고 그 root를 반환한다.  
이항 연산자 토큰이 트리 노드를 담당하므로 root의 자료형은 이항 연산자 토큰이다.  
계산이 좌측부터 진행되어야 하기에 root->left의 유무를 먼저 체크하고 좌측 노드부터 채운다.   
이항 연산자 토큰이 오면 타입만 구분해준다.  
&nbsp;  

밑은 괄호 처리 로직이다.  
따로 다룰 만큼 구현에 있어서 예외 사항이 많다.  
```c++
case Token::left_bracket: 
{
    std::stack<char> bracket;
    int j = i;
    for (; j < tokens.size(); j++)
    {
        if (tokens[j].type == Token::left_bracket)
            bracket.push('(');
        else if (tokens[j].type == Token::right_bracket && !bracket.empty())
        {
            bracket.pop();
            if (bracket.empty())
                break;
        }
    }
    if (!bracket.empty())
        return nullptr;
    std::vector<Token> subexpression(&tokens[i + 1], &tokens[j]);
    auto element = parse(subexpression);
    if (!element || (!i && j == tokens.size() - 1))
        return element;
    else if (!root->left)
        root->left = element;
    else
        root->right = element;
    i = j;
    break;
}
```
자료구조에서 트리 노드를 연결하는 것과 같은 로직이다.  
최상위 괄호들의 인덱스를 찾아 내부 토큰들을 재귀적으로 파싱한다.  
재귀적으로 구성된 하위 트리의 root를 좌측부터 연결해주면 된다.  
예외 사항이 몇 가지 있는데 ```((1+3)-(4-7))```와 같이 불필요한 괄호가 식 전체를 덮고 있다면 좌측 노드만 채워져 있는 이상한 트리가 형성되므로 ```(1+3)-(4-7)``` 이러한 괄호 내부 식을 바로 반환해줘야 한다.  
그리고 ```(1+3)-(4-7))``` 이렇게 괄호 쌍이 맞지 않는 경우 nullptr을 반환해줘야 한다.  
&nbsp;  

사용법은 밑과 같다.  
```c++
auto token = lexing("10-((13-4)-(12+1))+5");
auto parsed = parse(token);
if (parsed)
    std::cout << parsed->evaluation();
```
evaluation() 함수를 호출하면 트리를 타고 내려가면서 괄호 우선 순위에 맞춰 계산을 수행한다.  















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

struct Element
{
    virtual int evaluation() = 0;
};

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

    BinaryOperation()
        : left{nullptr}, right{nullptr}
    {
    }

    int evaluation()
    {
        auto eleft = left->evaluation();
        auto eright = right->evaluation();
        if (type == addition)
        {
            std::cout << eleft << " + " << eright << " = " << eleft + eright << "\n";
            return eleft + eright;
            // return left->evaluation() + right->evaluation();
        }
        std::cout << eleft << " - " << eright << " = " << eleft - eright << "\n";
        return eleft - eright;
        // return left->evaluation() - right->evaluation();
    }
};

std::shared_ptr<Element> parse(const std::vector<Token> &tokens)
{
    std::stack<Token> stack;
    std::map<Token::Type, char> priority{{Token::plus, 0},
                                         {Token::minus, 0},
                                         {Token::slash, 1},
                                         {Token::asterisk, 1},
                                         {Token::left_bracket, 2}};
    std::vector<Token> post;
    for (const auto &token : tokens)
    {
        switch (token.type)
        {
        case Token::integer:
            post.push_back(token);
            break;
        case Token::right_bracket:
            while (!stack.empty() && stack.top().type != Token::left_bracket)
            {
                stack.pop();
            }
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
}
```
