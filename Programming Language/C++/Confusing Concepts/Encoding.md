# Encoding  

C++에서는 **std::string**, **char**, **std::wstring**, **wchar_t**가 자동으로 인코딩되지 않는다.  
그리고 인코딩 방식도 사용자의 OS, 컴파일러 설정 등에 따라 상이하게 다르다.  
이렇게 유추하기 힘든 C++의 인코딩 방식을 알아보자.  
&nbsp;  

## Windows에서의 인코딩  

Windows에서는 **std::string**, **char**에 문자가 들어가는 경우 ANSI 방식이 사용된다.  
ANSI 방식은 국가마다 다르다는 점이 특징인데 이로 인해 특이한 문제가 발생할 수 있다.  
예를 들어 일본 Windows PC에서 빌드된 프로그램을 한국 Windows PC에서 실행시켜보면 글자가 깨진다.  
이유는 한국의 ANSI는 EUC-KR 혹은 CP949로 확장되고 일본의 ANSI는 EUC-JP로 확장되어 같은 바이트의 문자가 다르게 해석되기 때문이다.  

한국 Windows PC에서 빌드되는 경우 밑 글자가 어떻게 다뤄지는지 한 번 따져보자.  
```c++
const char text[] = "한글";

std::cout << "sizeof(char)    : " << sizeof(char) << "\n";
std::cout << "text            : " << text << "\n";
std::cout << "sizeof(text)    : " << sizeof(text) << "\n";
std::cout << "strlen(text)    : " << strlen(text) << std::endl;
```

출력 결과는 밑과 같다.  
```
sizeof(char)    : 1
text            : 한글
sizeof(text)    : 5
strlen(text)    : 4
```
글자 개수를 유의해야 하는데 EUC-KR 혹은 CP949 방식의 경우 한글이 글자당 2byte로 고정이기에 ```한글```은 4글자로 출력된다.  
&nbsp;  

**std::wstring**, **wchar_t**에 문자가 들어가는 경우 Unicode의 UTF-16 인코딩 방식이 사용된다.  
ANSI와는 다르게 다른 국가의 Windows를 이용해도 호환에 문제가 없다.  
밑의 코드를 돌려보자.  
```c++
std::locale::global(std::locale("kor")); // 콘솔창에 한글을 띄우기 위함
const wchar_t text[] = L"한글";

std::wcout << L"sizeof(wchar_t) : " << sizeof(wchar_t) << L"\n";
std::wcout << L"text            : " << text << L"\n";
std::wcout << L"sizeof(text)    : " << sizeof(text) << L"\n";
std::wcout << L"wcslen(text)    : " << wcslen(text) << std::endl;
```

출력 결과는 밑과 같다.  
```
sizeof(wchar_t) : 2
text            : 한글
sizeof(text)    : 6
wcslen(text)    : 2
```
null 문자도 UTF-16 인코딩의 경우 2byte이기에 ```한글```의 문자열 크기는 6byte가 나온다.  
&nbsp;  

정리해보면 밑과 같다.  
**char**의 경우 **ANSI** 인코딩이 사용되며 한국의 경우 **ANSI**가 확장된 **EUC-KR**(혹은 **EUC-KR**이 확장된 **CP949**) 방식이 사용된다.  
**wchar_t**의 경우 **UNICODE** 인코딩이 사용되며 그중 **UTF-16** 방식이 사용된다.  
&nbsp;  

## Linux, Unix 계열에서의 인코딩  

Windows보다 훨씬 간단하다.  
**char**의 경우 **UNICODE** 인코딩이 사용되며 그중 **UTF-8** 방식이 사용된다.  
**wchar_t**의 크기가 4byte이므로 **wchar_t**의 경우 **UNICODE** 인코딩이 사용되며 그중 **UTF-32** 방식이 사용된다.  
**wchar_t**의 크기가 Windows와 상이하기도 하고 **UTF-32** 방식이 선호되는 방식도 아니고 **char**만 이용해도 **UNICODE**를 다룰 수 있기에 Linux나 Mac에서는 굳이 **std::wstring**을 사용할 이유가 없다.  
&nbsp;  

## 컴파일러 인코딩 옵션  

gcc, msvc와 같은 표준적인 컴파일러에는 인코딩과 관련한 옵션을 제공한다.  
**Source Character Set**, **Execution Character Set** 이렇게 크게 2가지로 나뉜다.  
&nbsp;  

### Source Character Set  

컴파일러가 소스 파일을 읽을 때 어떻게 읽어야 하는지 명시하기 위한 옵션이다.  
주석에 특이한 유니코드가 적혀있으면 가끔 warning이 뜨는데 이를 해결하기 위해 사용할 때가 있다.  
msvc에서는 ```/source-charset```로 설정이 가능하고 gcc에서는 ```-finput-charset```로 설정할 수 있다.  
기본적으로 UTF-8이 권장된다.  
&nbsp;  

### Execution Character Set  

전처리 단계를 거친 후 컴파일 단계를 수행할 때 입력되는 문자열의 인코딩 방식을 명시하기 위한 옵션이다.  
즉 문자열 리터럴의 인코딩 방식을 결정하기 위한 옵션이라고 보면 된다.  
msvc에서는 ```/execution-charset```로 설정이 가능하고 gcc에서는 ```-finput-charset=charset```, ```-fwide-exec-charset=charset```로 각각 char, wide-char에 대한 인코딩 설정이 가능하다.  
전체적인 흐름을 보면 **Source Character Set**에 설정된 인코딩 방식으로 읽고 해석하여 전처리를 진행하고 **Execution Character Set**에 설정된 인코딩 방식으로 문자열, 문자열 리터럴을 인코딩하여 컴파일을 진행한다.  

Windows에서 msvc로 컴파일하는 경우를 생각해보자.  
옵션은 ```/source-charset:euc-kr /execution-charset:utf-8```이렇게 설정되어 있다고 하자.  
먼저 소스 코드 파일은 ```/source-charset:euc-kr```이기에 euc-kr로 저장이 되어 있어야 한다.    
```std::string str = "한글";```이 컴파일되려고 하면 ```한글```은 euc-kr에서 ```/execution-charset:utf-8```에 지정된 utf-8로 인코딩되어 str에 저장이 된다.  
&nbsp;  

## C++의 Unicode 지원   

C++은 완벽하지는 않지만 Unicode 인코딩에 필요한 몇가지 String Literal 기호와 특정 클래스를 제공한다.  

UTF-8에 대한 기법은 C++20 이후부터 사용이 가능하다.  
```std::u8string = u8"이것은 한글이다."```  
std::u8string과 u8을 사용한 것을 알 수 있다.  

UTF-16은 밑과 같다.  
```std::u16string = u"이것은 한글이다."```  

UTF-32은 밑과 같다.  
```std::u32string = U"이것은 한글이다."```  

이렇게 String Literal 전용 기호를 사용하면 **Execution Character Set**과 상관없이 지정된 기호 방식으로 인코딩이 된다.  
&nbsp;  

## 해결법  

그렇다면 Windows, Linux, Mac을 모두 지원해야 하는 크로스 플랫폼 프로젝트에서는 문자열을 어떻게 다뤄야 할까?  
많은 방법이 있겠지만 가장 좋은 방법은 ```std::string```을 UTF-8 인코딩 방식으로 이용하는 것이다.  
Linux, Mac은 이미 UTF-8 인코딩 방식을 이용하고 있고 Windows에서 코드를 짜는 경우 문자열을 다룰 때 유의하면 된다.  

다른 방법은 C++이 제공하는 ```std::u16string```처럼 플랫폼에 따라 크기가 변동되지 않는 클래스를 이용하는 것이다.  
```std::u16string```를 이용하고 UTF-16 인코딩을 사용하는 것으로 통일해도 크로스 플랫폼 프로젝트를 개발하는 것에 문제는 없을 것이다.  