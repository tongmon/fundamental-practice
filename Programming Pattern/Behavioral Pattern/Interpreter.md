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

## Boost.Spirit  

```c++
#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <random>
#include <regex>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/bimap/bimap.hpp>
#include <boost/config/warning_disable.hpp>
#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include <boost/foreach.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/include/push_back.hpp>
#include <boost/fusion/include/remove_if.hpp>
#include <boost/gil.hpp>
#include <boost/noncopyable.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/singleton.hpp>
#include <boost/signals2/signal.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/recursive_variant.hpp>

namespace client
{
namespace ast
{
///////////////////////////////////////////////////////////////////////////
//  The AST
///////////////////////////////////////////////////////////////////////////

struct signed_;
struct program;

typedef boost::variant<boost::blank, unsigned int, boost::recursive_wrapper<signed_>, boost::recursive_wrapper<program>> operand;

struct signed_
{
    char sign;
    operand operand_;
};

struct operation
{
    char operator_;
    operand operand_;
};

struct program
{
    operand first;
    std::list<operation> rest;
};
} // namespace ast
} // namespace client

BOOST_FUSION_ADAPT_STRUCT(
    client::ast::signed_,
    (char, sign)(client::ast::operand, operand_))

BOOST_FUSION_ADAPT_STRUCT(
    client::ast::operation,
    (char, operator_)(client::ast::operand, operand_))

BOOST_FUSION_ADAPT_STRUCT(
    client::ast::program,
    (client::ast::operand, first)(std::list<client::ast::operation>, rest))

namespace client
{
namespace ast
{
///////////////////////////////////////////////////////////////////////////
//  The AST Printer
///////////////////////////////////////////////////////////////////////////
struct printer
{
    void operator()(boost::blank) const
    {
    }

    void operator()(unsigned int n) const
    {
        std::cout << n;
    }

    void operator()(operation const &x) const
    {
        boost::apply_visitor(*this, x.operand_);
        switch (x.operator_)
        {
        case '+':
            std::cout << " add";
            break;
        case '-':
            std::cout << " subt";
            break;
        case '*':
            std::cout << " mult";
            break;
        case '/':
            std::cout << " div";
            break;
        }
    }

    void operator()(signed_ const &x) const
    {
        boost::apply_visitor(*this, x.operand_);
        switch (x.sign)
        {
        case '-':
            std::cout << " neg";
            break;
        case '+':
            std::cout << " pos";
            break;
        }
    }

    void operator()(program const &x) const
    {
        boost::apply_visitor(*this, x.first);
        BOOST_FOREACH (operation const &oper, x.rest)
        {
            std::cout << ' ';
            (*this)(oper);
        }
    }
};

///////////////////////////////////////////////////////////////////////////
//  The AST evaluator
///////////////////////////////////////////////////////////////////////////
struct eval
{
    int operator()(boost::blank) const
    {
        BOOST_ASSERT(0);
        return 0;
    }

    int operator()(unsigned int n) const
    {
        return n;
    }

    int operator()(operation const &x, int lhs) const
    {
        int rhs = boost::apply_visitor(*this, x.operand_);
        switch (x.operator_)
        {
        case '+':
            return lhs + rhs;
        case '-':
            return lhs - rhs;
        case '*':
            return lhs * rhs;
        case '/':
            return lhs / rhs;
        }
        BOOST_ASSERT(0);
        return 0;
    }

    int operator()(signed_ const &x) const
    {
        int rhs = boost::apply_visitor(*this, x.operand_);
        switch (x.sign)
        {
        case '-':
            return -rhs;
        case '+':
            return +rhs;
        }
        BOOST_ASSERT(0);
        return 0;
    }

    int operator()(program const &x) const
    {
        int state = boost::apply_visitor(*this, x.first);
        BOOST_FOREACH (operation const &oper, x.rest)
        {
            state = (*this)(oper, state);
        }
        return state;
    }
};
} // namespace ast
} // namespace client

namespace client
{
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

///////////////////////////////////////////////////////////////////////////////
//  The calculator grammar
///////////////////////////////////////////////////////////////////////////////
template <typename Iterator>
struct calculator : qi::grammar<Iterator, ast::program(), ascii::space_type>
{
    calculator()
        : calculator::base_type(expression)
    {
        qi::uint_type uint_;
        qi::char_type char_;

        expression =
            term >> *((char_('+') >> term) | (char_('-') >> term));

        term =
            factor >> *((char_('*') >> factor) | (char_('/') >> factor));

        factor =
            uint_ | '(' >> expression >> ')' | (char_('-') >> factor) | (char_('+') >> factor);
    }

    qi::rule<Iterator, ast::program(), ascii::space_type> expression;
    qi::rule<Iterator, ast::program(), ascii::space_type> term;
    qi::rule<Iterator, ast::operand(), ascii::space_type> factor;
};
} // namespace client

///////////////////////////////////////////////////////////////////////////////
//  Main program
///////////////////////////////////////////////////////////////////////////////
int main()
{
    std::cout << "/////////////////////////////////////////////////////////\n\n";
    std::cout << "Expression parser...\n\n";
    std::cout << "/////////////////////////////////////////////////////////\n\n";
    std::cout << "Type an expression...or [q or Q] to quit\n\n";

    typedef std::string::const_iterator iterator_type;
    typedef client::calculator<iterator_type> calculator;
    typedef client::ast::program ast_program;
    typedef client::ast::printer ast_print;
    typedef client::ast::eval ast_eval;

    std::string str;
    while (std::getline(std::cin, str))
    {
        if (str.empty() || str[0] == 'q' || str[0] == 'Q')
            break;

        calculator calc;     // Our grammar
        ast_program program; // Our program (AST)
        ast_print print;     // Prints the program
        ast_eval eval;       // Evaluates the program

        std::string::const_iterator iter = str.begin();
        std::string::const_iterator end = str.end();
        boost::spirit::ascii::space_type space;
        bool r = boost::spirit::qi::phrase_parse(iter, end, calc, space, program);

        if (r && iter == end)
        {
            std::cout << "-------------------------\n";
            std::cout << "Parsing succeeded\n";
            print(program);
            std::cout << "\nResult: " << eval(program) << std::endl;
            std::cout << "-------------------------\n";
        }
        else
        {
            std::string rest(iter, end);
            std::cout << "-------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "stopped at: \" " << rest << "\"\n";
            std::cout << "-------------------------\n";
        }
    }

    std::cout << "Bye... :-) \n\n";
    return 0;
}
```