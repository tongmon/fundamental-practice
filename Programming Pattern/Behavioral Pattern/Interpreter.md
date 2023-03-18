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
        lparen,
        rparen
    } type;
    std::string text;

    explicit Token(Type type, const std::string &text)
        : type{type}, text{text}
    {
    }

    friend std::ostream &operator<<(std::ostream &os, const Token &obj)
    {
        return os << "`" << obj.text << "`";
    }
};
```


### Parsing  

