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
                if ('1' <= input[i] && input[i] <= '9')
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