# Encoding  

C++에서는 **std::string**, **char**, **std::wstring**, **wchar_t**가 자동으로 인코딩되지 않는다.  
이렇게 유추할 수 없는 C++의 인코딩 방식을 알아보자.  
&nbsp;  

## Multibyte Project  

만약 프로젝트 속성 중 문자열 속성이 멀티바이트라면 기본적으로 ASCII 인코딩 방식이 사용되었을 것이다.  
물론 이것도 OS마다 다른데 Windows라면 해당 Windows의 사용 국가에 해당되는 ANSI 인코딩 방식이 사용된다.  
일본 Windows와 한국 Windows의 ANSI 인코딩 방식이 다르기에 같은 프로젝트여도 일본 Windows가 설치된 PC에서 빌드한 프로젝트를 한국 Windows가 설치된 PC에서 실행시키면 글자가 무조건 깨진다.  
&nbsp;  

멀티바이트라고 **std::wstring**을 쓰지 말라는 법도 없다.  
하지만 **std::wstring**이라고 해서 무조건 UTF-16 인코딩을 사용하는가?  
OS와 사용자의 컴퓨터 환경에 따라 달라지기에 정답은 **NO**다.  
결국 **std::string**, **std::wstring** 모두 인코딩 방식이 명확하지 않다.   
&nbsp;  

## UNICODE Project  

만약 프로젝트 속성 중 문자열 속성이 유니코드라면 기본적으로 UTF-16 방식이 사용된다.  
하지만 무조건 UTF-16이라고 보장할 수도 없는 것이 사용자의 컴퓨터 환경에 따라 달라질 수 있기 때문이다.  
&nbsp;  

유니코드 프로젝트에서도 **std::string**을 사용하지 말라는 법은 없다.  
**std::string**의 인코딩 방식은 멀티바이트 프로젝트와 마찬가지로 PC 환경에 따라 각기 다르기에 정해진 것이 없다.  
결국 유니코드 프로젝트도 **std::string**, **std::wstring** 모두 인코딩 방식이 명확하지 않다.   
&nbsp;  

## 해결법  

그렇다면 변덕스러운 인코딩 방식을 통합하려면 어떻게 해야 하는가?  
그냥 인코딩 방식을 하나 잡고 모든 문자열을 다룰 때 해당 인코딩 방식을 이용하면 된다.  
보통 UTF-8, UTF-16, UTF-32가 많이 채택된다.  
C++에서는 해당 인코딩을 기본 전제로 하는 **String literal**을 제공한다.    
**String literal**을 제공하는 것이지 ```ANSI -> UTF-16``` 이러한 변환 함수를 제공하는 것은 아니기에 인코딩 함수들은 직접 짜줘야 한다.  

### Encoding literal  

UTF-8에 대한 기법은 C++20 이후부터 사용이 가능하다.  
```std::u8string = u8"이것은 한글이다."```  
std::u8string과 u8을 사용한 것을 알 수 있다.  

UTF-16은 밑과 같다.  
```std::u16string = u"이것은 한글이다."```  

UTF-32은 밑과 같다.  
```std::u32string = U"이것은 한글이다."```  
&nbsp;  
