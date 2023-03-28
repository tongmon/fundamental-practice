# Interpreter Pattern  

���������͸� �����ϸ� ```�ؼ���```�̴�.  
���α׷��� ��� ��ü�� �׳� �ؽ�Ʈ�� ���̴�.  
���� ����� ������ �� �ְ� ��ǻ�ʹ� ���� ������ ���˾� �Դ´�.  
���������͸� �̿��� ��ǻ�� ���� ������ ����� ��μ� ��ǻ�Ͱ� �� ���� ������ �� �ִ�.  
```3 + (50 % 3) - 23 x 12```�� �ܼ��� �����̴�.  
������ �ȹ�� ����� �� ���� �ǹ��ϴ� �ٸ� �� �� ������?  
�� ���� �ǹ��ϴ� �ٸ� �ؼ��ϱ� ���� ������ ���������͸� ����� �� �ִ�.  
&nbsp;  

## ��� ǥ������ ���  

���������ʹ� ��Ȳ���� �پ��� ���¸� ���ϸ� �����ϴ�.  
�׸��� ��κ��� ���������ʹ� ������� �ֱ⿡ ���� ������ ����ϴ� ��쵵 �幰��.  
���� ���� ���ظ� ���� ���� ���� ������ ���ø� �����ϰ� �Ѿ��.  
&nbsp;  

### Lexing  

ǥ������ �ؼ��ϴ� ù �ܰ�� �����̴�.  
���ڿ� �Է��� ��ū ������ ���� �����ϴ� �ܰ��.  
���⼭ ���ϴ� ��ū�̶� ```�ǹ̸� ������ �ּ� ����```�̴�.  
��� ǥ���Ŀ����� ```���� [ex. 2, 9]```, ```������ [ex. +, -]```, ```��ȣ [ex. (, )]```�� ��ū�� �� �� �ִ�.  
�̷��� ��ū�� �����غ���.  
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
Type �������� ���� ��ū�� Ÿ���� �����Ѵ�.  
���ø� �����ϰ� ����� ���� ��ū�� ```����, +, -, *, /, (, )```�� �ٷ��.  
���� ��ū�� ���ڿ��� text�� �����Ѵ�.  
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
���� �̿��� �ٸ� ��ū���� ������ ó������ �״�� ������ �ȴ�.  
���ڴ� '123'�� ���� ���ӵ� ���ڿ��� �ϳ��� ���ڸ� ������ �� �����Ƿ� ���ڰ� �ƴ� ���ڿ��� ������ ������ ������ �˻��Ѵ�.  
&nbsp;  

### Parsing   

�Ľ��� ��ū�� �ǹ��ִ� ������ ��ȯ�Ѵ�.  
��ū�� ������ �����̱⿡ ��ū���� ���� ó���ϱ� ���� �ذ� ���� �������̽��� �д�.  
```c++
struct Element
{
    virtual int evaluation() = 0;
};
```
evaluation() �Լ����� �� ��ū�� �ǹ̰� �ؼ��ǰ� �׿� ���� ����� ����ȴ�.    
&nbsp;  

���ڿ� ���� �Ľ� �����̴�.  
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
�־��� ���ڿ��� ���ڷ� ��ȯ�Ͽ� �����ϰ� evaluation() ȣ��� ��ȯ���ָ� �ȴ�.  
���� ���ڿ��̿��� ```"13"```�� ������ ```13```���� �ؼ��ȴ�.  
&nbsp;  

������ ���� �����ڴ�.  
��Ģ������ ��� �ٷ��.  
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
�߿��� ���� �ش� ���� ������ �Ľ� ������ Ʈ�� ��� ���¸� ���߰� �ִٴ� ���̴�.  
���� left, right ��� �����Ͱ� �����Ѵ�.  
���� ������ ���� ���Ŀ� ������ parse() �Լ����� ���� Ʈ��(Expression Tree)�� �����ϴ� �� �ٽ����� ������ �Ѵ�.  
���� Ʈ���� ���ø� ������ ���ڸ� ```(1 + 3) - (7 - 11)``` �̷��� ���� �ذ� ���� �����ȴ�.  
```tree
-
������ +
��   ������ 1
��   ������ 3
������ -
    ������ 7
    ������ 11
```
evaluation() �Լ������� �־��� type�� ���� ��Ģ������ �����ϸ� �ȴ�.  
&nbsp;  

���� �Ľ� �Լ��̴�.  
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

    // ���� ǥ������ ���� ǥ�������� ��ȯ
#pragma endregion

#pragma region Make Expression Tree
    std::stack<std::shared_ptr<Element>> nodes;

    // ���� Ʈ�� ����
#pragma endregion

    return nodes.top();
}
```
���� Ʈ���� ����� ���� ���� ���� ǥ������ ���� ǥ�������� ��ȯ�� �Ѵ�.  
�� �ڿ� ȹ���� ���� ǥ������ ���� ���� Ʈ���� �����ϰ� �ش� Ʈ���� root ��带 ��ȯ�Ѵ�.  
&nbsp;  

���� ǥ������ ���� ǥ�������� �ٲٴ� ���� ������ �ذ� ����.  
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
���ͳݿ� ����, ����, ���� ǥ��� ��ȯ�� ������ ������ �η����� ���� �̷��� ������ ��ģ�ٴ� �͸� �˰� �Ѿ��.  
�߿��� ���� �������� �����ΰ� �ƴ϶� ���������� ������ ��ü���� ������ �����ϴ� ���̴�.  
&nbsp;  

���� ���� Ʈ���� �����ϴ� ���� �����̴�.  
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
���� ǥ����� ���������� �о���� �ȴ�.  
���ڰ� ��Ÿ���� �ٷ� ���ÿ� �����Ѵ�.  
���� �����ڰ� ��Ÿ���� Ʈ�� ��带 �����Ͽ� ���ÿ� �����Ѵ�.  
���� �Ľ� �Լ��� ```(11-4))-3``` �̷��� ���������� �Ŀ� ���� ��ó�� �� ���� ����.  
�� ���� ó���� ���� ������ ���ٴ� ���̴�.  
���� ����� ������������ �Ľ� �κ��� ������ ���� ���� ó�� ����� ��� ������ �������� ���� �κе� �ſ� �߿��ϱ⿡ �پ��� ���� ���׿� ��ó�ϱ� ���� ���� ����غ��� �� ���̴�.  
&nbsp;  

������ �ذ� ����.  
```c++
auto token = lexing("10-((13-4)*(9+1))/5");
auto parsed = parse(token);
if (parsed)
    std::cout << parsed->evaluation();
```
evaluation() �Լ��� ȣ���ϸ� Ʈ���� Ÿ�� �������鼭 ��ȣ �켱 ������ ���� ����� �����Ѵ�.  
�ٽ� �������� �������� ������ ���������Ͱ� ������ �ؼ��ϴ����� ���� õ�������̱⿡ ���� �߿����� �ʰ� ���̿��� �Ľ����� �̾����� ��ü���� �帧�� �����ϴ� ���� �߿��ϴ�.  
&nbsp;  

## Boost.Spirit  

Boost ���̺귯������ ���������� ������ �����ִ� Spirit ����� �����Ѵ�.  
���ø� ����� �����ϴ� ����̱⿡ ������ �ð��� �þ�� ������ ��ٷο� ���̴�.  
Spirit ����� ����ϴ� ������ ���ú��� ���캸��.  
&nbsp;  

�Ʒ��� �־��� ���ڿ����� ���ڸ� �Ľ��ϴ� �����̴�.  
```c++
std::string str = " 11";
auto it_start = str.begin();
auto it_end = str.end();

int parsed;
bool success = boost::spirit::qi::phrase_parse(it_start, it_end, boost::spirit::qi::int_, boost::spirit::ascii::space, parsed);

if (success)
    std::cout << parsed << '\n';
```
phrase_parse() �Լ��� ���ڷ� ���� ��Ƶ��� �޴´�.  
```1: ���ڿ� ���� iterator, 2: ���ڿ� �� iterator, 3: �Ľ��� ��Ģ, 4: �Ľ��� �� ������ ����, 5: �Ľ��� ���� ������ ������...```  
phrase_parse() �Լ��� �Ľ��ϸ鼭 iterator�� ������ �� �ֱ� ������ �� ���ÿ� ���� iterator ���纻�� �ѱ�� ���� ����.  
�Ľ��� ��Ģ�� ����ڰ� ���ϱ� �����̴�.  
�ش� ���ÿ����� ```qi::int_```�� ����߱⿡ �������� �Ľ��Ͽ���.  
```qi::char_```, ```qi::float_``` �� ���������� �ִµ� �ڼ��� ������ https://www.boost.org/doc/libs/1_81_0/libs/spirit/doc/html/spirit/qi/quick_reference/qi_parsers.html ��ũ�� ��������.  
```ascii::space```�� ����Ͽ� ���� ���ڴ� �����Ѵ�.  
���� 11�� �Ľ̵Ǿ� parsed ������ ����ȴ�.  
phrase_parse() �Լ��� �־��� ���ڿ��� ���� ��ȿ�� �˻縦 ������ �Ľ��� �����ϸ� true, �ƴϸ� false�� ��ȯ�ϴ�.  
&nbsp;  

���� ���ô� ���� �׸��� �Ľ��ϴ� �����̴�.  
```c++
std::string str = "71.45, 11.12";
auto it_start = str.begin();
auto it_end = str.end();
std::vector<double> parsed;

bool success = boost::spirit::qi::phrase_parse(it_start, it_end, boost::spirit::qi::double_ >> *(',' >> boost::spirit::qi::double_), boost::spirit::ascii::space, parsed);

if (success)
    std::cout << parsed[0] << ", " << parsed[1] << '\n';
```
double �� �� ���ڸ� �Ľ��Ϸ��� �Ѵ�.  
�Ľ��� ��Ģ�� ������ �� �ִµ� EBNF�� ���� ���� ������ �䱸�ȴ�.  
EBNF�� ���� ������ https://en.wikipedia.org/wiki/Extended_Backus%E2%80%93Naur_form ��ũ�� ��������.  
```boost::spirit::qi::double_ >> *(',' >> boost::spirit::qi::double_)```�� EBNF�� ǥ���ϸ� ```rule := double { "," double }```�� ����.  
boost::spirit������ �̷��� ǥ���� ����ȭ �ϱ� ���� ```boost::spirit::qi::double_ % ','``` ǥ���ĵ� �����Ѵ�.  
ǥ���� ��Ģ�� ���� �� �ڼ��� ������ https://www.boost.org/doc/libs/1_81_0/libs/spirit/doc/html/spirit/qi/quick_reference/qi_parsers/operator.html ��ũ�� ��������.  
�׸��� �߿��� ���� ',' �䷸�� ����ǥ, ū����ǥ�θ� ���ο� �ִ� �͵��� �����ڷθ� ���ǰ� �Ľ̿��� ���ܵȴ�.  
���� ','�� �Ľ��ϰ� �ʹٸ� ```boost::spirit::qi::char_(',')``` �̷��� ǥ���ؾ� �Ѵ�.  
&nbsp;  

������ �������� ��Ģ�� ���������� �ۿ��ؾ� �ϴ� ��� boost::spirit ��� �����̴�.  
�ϴ� �ذ� ���� ```boost::spirit::qi::grammar```�� ����ϴ� Ŭ������ ������ش�.  
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
�ϳ��� ���캸��.  
qi::rule�� qi::grammar���� ���ø� ���ڷ� �ݺ���, �Ľ��� �ڷ���, �Ľ� �ǳʶ� ���� Ÿ���� ����.  
my_grammar Ŭ���� ���ο����� ```value := int | ((char - ("," | digit) { (char - ("," | digit) })```, ```values := value | { "," value }``` �̷��� �Ľ� ��Ģ�� �����Ͽ���.  
�׸��� �����ڿ��� base_type�� ���Ͽ� �Ľ� ���� ��Ģ�� �������� �˷���� �Ѵ�.  
boost::spirit���� ��� ���ڿ��� �⺻������ ```std::vector<char>```�� �Ľ��Ͽ� �������Ѵ�.  
������ qi::as_string�� ����ϸ� ���ڿ��� std::string ���·� �Ľ��Ѵ�. (std::wstring�� ���� qi::as_wstring�� �����Ѵ�.)  
qi::lexeme�� ������ ������ ���Ͽ� Skipper�� �����Ѵ�.  
���� ��� ```This is cool```��� ���ڿ��� �Ľ��� �� Skipper�� �����̶�� ```Thisiscool``` �䷸�� ������ ���õǾ� �Ľ̵ȴ�.  
qi::lexeme�� ����ϸ� ������� �Ľ��Ͽ� ```This is cool``` �䷸�� �Ľ̵ȴ�.  
�� �ܿ��� ���� ���þ �����ϴ� https://www.boost.org/doc/libs/1_81_0/libs/spirit/doc/html/spirit/qi/quick_reference/qi_parsers/directive.html ��ũ�� ��������.  
&nbsp;  

�Ľ� ��Ģ Ŭ������ ��������� �����غ���.  
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
my_grammar Ŭ������ �����ϰ� qi::phrase_parse() �Լ��� ��Ģ���� �־��ָ� �ȴ�.  
���ݱ����� ���õ��� ���� �˰����� int, std::vector, std::variant �� c++�� ���� �����ߴ� �ڷ������� �Ľ̵� �ڷḦ �����ϰ� �ִ�.  
�׷��ٸ� Ŀ���� Ŭ������ �Ľ̵� �ڷ����� �������� ��� �ؾ� �ұ�?  
&nbsp;  

���׸����� �ϴ� boost::fusion�� ������ �˾ƾ� �Ѵ�.  
�ϴ� �ذ� ���� ����ü�� �����Ѵ�.  
```c++
struct Object
{
    std::string str;
    int integer;
    bool boolean;
};
```
�� �༮�� ��� �������� boost::fusion�� ����Ͽ� �迭ó�� ��ȸ�� �� �ִ�.  
&nbsp;  

�ذ� ���� Object ����ü�� BOOST_FUSION_ADAPT_STRUCT ��ũ�θ� ����� fusion ����ü �������� ������ش�.  
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
print functor�� ���� ���� �����ߴ�.  
std::string�� ���ڷ� �޴� ���ø� Ư��ȭ �Լ��� ������ ��¦ �ٸ���.  
&nbsp;  

�ذ� ���� fusion::for_each() �Լ��� �̿��ϸ� �־��� functor�� �����Լ��� �̿��Ͽ� ��� ������ �̿��� �� �ִ�.  
�߿��� ���� Object ����ü ��� �������� ��� �ڷ����� ó���� �� �ִ� functor�� �����Լ����� �Ѵ�.  
���� ��� print functor���� ```operator()(T &t)```�� ```operator()(bool &t)```�� ���ǵ��� �ʾҴٸ� �������� ���� �ʴ´�.  
```c++
Object obj{"hello", 10, false};
boost::fusion::for_each(obj, print());
```
��������� fusion::for_each() �Լ��� ����ǰ� obj.str�� "hello world" ���� �����ϰ� �ȴ�.  
�� ���ÿ��� ��°��� ```hello world 10 0```�� �ȴ�.  
&nbsp;  

�� �� ���ư� boost::mpl�� ���� ����� ���͸��� �� ���� �ִ�.  
```c++
boost::fusion::for_each(boost::fusion::filter_if<boost::is_same<boost::mpl::_, std::string>>(obj), print());
```
```fusion::filter_if<>```�� ���� ���͸��� �����ϰ� ```boost::is_same<boost::mpl::_, std::string>``` ������ ���� �ڷ����� std::string�� ��� ������ �߷� print functor�� ȣ��ȴ�.  
������ ���� ```fusion::filter_if<>```�� ���͸� ���ǿ� �˸��� ��ü�� �����Ͽ� const ������ ��ȯ�Ѵٴ� ���̴�.  
���� �Լ� ���ο��� ������ ���� ���ڸ� ������ �� ����.  
�׸��� ������ ���ø� ���� �Լ��� ȣ��ȴ�.  
�� ���ÿ����� ��°��� ```hello```�� �ȴ�.  
&nbsp;  

���� �ٸ� ���͸� �����̴�.  
```c++
boost::fusion::for_each(boost::fusion::filter_if<boost::mpl::not_<boost::is_class<boost::mpl::_>>>(obj), print());
```
```boost::is_class<boost::mpl::_>```�� ���� Ŭ���� ������ ��� ������ �߷��� �� �ִ�.  
```boost::mpl::not_<>```�� ���� �ݴ��� ����� �߷��� �� �ִ�.  
�����ϸ� Ŭ������ �ƴ� ������ ��� ������ �߷����� �����̴�.  
�� ���� ��°��� ```10 0```�� �ȴ�.  
�ڼ��� ������ https://www.boost.org/doc/libs/1_81_0/libs/fusion/doc/html/index.html ��ũ�� ��������.  
&nbsp;  

boost::fusion�� �˾����� boost::spirit�� ���� Ŀ���� Ŭ������ �Ľ̵� �ڷ����� �ִ� ���ø� ���캸��.  
```c++
struct Object
{
    std::string name;
    std::variant<int, bool> int_or_bool;
    std::vector<double> vec;
};

BOOST_FUSION_ADAPT_STRUCT(Object, name, int_or_bool, vec)
```
�ϴ� ���� ���� Object ����ü�� fusion ����ü�� ������ش�.  
&nbsp;  

Object �Ľ��� ���� grammer Ŭ������ �ۼ����ش�.  
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
�Ľ��� �� ����� ���ڿ��� ```object name, 777, 10.139, 34.3, 56.82``` �̷��� �����.  
```���ڿ�, [int | bool], double, double...``` �̷��� ��Ģ�̱⿡ �̿� �´� �Ľ� ��Ģ�� ¥�־���.  
&nbsp;  

�Ʒ� �ڵ�� �����غ��� �Ľ��� �� �Ǵ� ���� Ȯ���� �� �ִ�.  
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

�׷��� ���������� boost::spirit�� ���� ������ �Ľ��ϰ� ����� �����ϴ� ���ø� ����.  
```c++

```
&nbsp;  


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
//  The AST

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

BOOST_FUSION_ADAPT_STRUCT(client::ast::signed_, sign, operand_)

BOOST_FUSION_ADAPT_STRUCT(client::ast::operation, operator_, operand_)

BOOST_FUSION_ADAPT_STRUCT(client::ast::program, first, rest)

namespace client
{
namespace ast
{
//  The AST Printer
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

//  The AST evaluator
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
        for (auto const &oper : x.rest)
            state = (*this)(oper, state);
        return state;
    }
};
} // namespace ast
} // namespace client

namespace client
{
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

//  The calculator grammar
template <typename Iterator>
struct calculator : qi::grammar<Iterator, ast::program, ascii::space_type>
{
    calculator()
        : calculator::base_type(expression)
    {
        qi::uint_type uint_;
        qi::char_type char_;

        expression = term >> *((char_('+') >> term) | (char_('-') >> term));

        term = factor >> *((char_('*') >> factor) | (char_('/') >> factor));

        factor = uint_ | '(' >> expression >> ')' | (char_('-') >> factor) | (char_('+') >> factor);
    }

    qi::rule<Iterator, ast::program, ascii::space_type> expression;
    qi::rule<Iterator, ast::program, ascii::space_type> term;
    qi::rule<Iterator, ast::operand, ascii::space_type> factor;
};
} // namespace client

int main()
{
    typedef std::string::const_iterator iterator_type;
    typedef client::calculator<iterator_type> calculator;
    typedef client::ast::program ast_program;
    typedef client::ast::printer ast_print;
    typedef client::ast::eval ast_eval;

    std::string str = "10-((13-4)*(9+1))/5";

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
        print(program);
        std::cout << "\n"
                  << eval(program);
    }

    return 0;
}
```