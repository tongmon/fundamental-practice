# Proxy Pattern  

프록시 패턴도 데코레이터 패턴과 비슷하게 객체의 기능을 수정하거나 확장하는 것에 중점을 둔다.  
하지만 데코레이터 패턴과 달리 프록시 패턴은 기존의 인터페이스 사용 방식을 동일하게 가져간다.  
따라서 코드 변동은 최소화 하면서 목적만 바꿀 수 있다.  
&nbsp;  

## 스마트 포인터  

C++의 스마트 포인터가 프록시 패턴의 가장 대표적인 예이다.  
포인터, 스마트 포인터 모두 밑과 같이 동일한 방식으로 사용이 가능하다.  
```c++
std::vector<int> *ptr = new std::vector<int>();
ptr->size();
delete ptr;

std::shared_ptr sh_ptr = std::make_shared<std::vector<int>>();
sh_ptr->size();
```
물론 스마트 포인터는 delete를 명시할 필요가 없고 참조 횟수를 내부적으로 관리한다는 차이점이 있지만 최대한 기존 포인터와 유사하게 작동하도록 구현되어 있다.   
&nbsp;  

## 속성 프록시  

대부분의 프로그래밍 언어는 get / set 메서드를 언어적인 차원에서 지원하지만 C++은 그렇지 않다.  
물론 Clang, MSVC 등의 컴파일러에서는 ```__declspec(property())```를 사용하여 지정할 수 있지만 비표준이다.  
따라서 속성 프록시를 통해 get / set 메서드를 접근해보자.  
```c++
template <typename T>
struct Property
{
    T value;
    Property(const T init_val) { *this = init_val; }
    operator T()
    {
        // getter가 수행할 구현부를 적으면 된다.

        return value;
    }
    T operator=(T new_val)
    {
        // setter가 수행할 구현부를 적으면 된다.

        return value = new_val;
    }
};
```
형변환을 재정의하여 getter를, ```=``` 연산자를 재정의하여 setter를 정의하였다.  
&nbsp;  

밑과 같이 int형으로 사용되었을 때 마치 자신이 int인 것 마냥 사용이 된다.  
```c++
// int 처럼 사용이 가능함.  
Property<int> a = 1;
int b = a;

// 하지만 밑과 같은 상황에서 getter / setter 로직 수행 안됨.
Property<int> c = 2;
Property<int> d = c;
```
문제가 하나 있는데 위 예시에서 보이듯이 ```Property<int>``` 사이에 값 할당이 이루어지면 getter / setter 로직이 수행이 안된다는 것이다.  
&nbsp;  

이를 해결하기 위해 연산자 재정의 구현을 추가해보자.  
```c++
template <typename T>
struct Property
{
    T value;

    T get()
    {
        // getter가 수행할 구현부를 적으면 된다.

        return value;
    }
    T set(const T &new_val)
    {
        // setter가 수행할 구현부를 적으면 된다.

        return value = new_val;
    }
    Property(const T &init_val)
    {
        *this = init_val;
    }
    Property(Property<T> &init_val)
    {
        *this = init_val;
    }
    T operator=(Property<T> &new_val)
    {
        return set(new_val.get());
    }
    T operator=(const T &new_val)
    {
        return set(new_val);
    }
    operator T()
    {
        return get();
    }
};
```
이제 값을 획득하거나 할당하는 과정에서 getter / setter 로직이 잘 작동할 것이다.  
```T```에서 ```Property<T>```를 참조로 사용하게 될 경우에는 직접 멤버 변수 value를 사용하면 될 것이다.  
&nbsp;  

## 가상 프록시  

동영상을 읽어오는 프로그램이 있다고 하자.  
해당 프로그램을 작동 시키자 마자 준비된 영상을 로드하는 방식이 있고 프로그램을 작동할 때는 가만히 있다가 플레이 버튼을 눌러야 영상을 로드하는 방식이 있다.  
전자를 ```성급한 인스턴스화```라고 하고 후자를 ```느긋한 인스턴스화```라고 한다.  
```성급한 인스턴스화``` 방식으로 구현된 인터페이스를 ```느긋한 인스턴스화```로 바꾸려면 어떻게 해야 할까?  
&nbsp;  

밑과 같은 영상 처리 인터페이스가 존재한다.  
```c++
struct Video
{
    virtual void play() = 0;
};
```
&nbsp;  

성급한 비디오 플레이어 클래스는 밑과 같다.  
```c++
struct VideoPlayer : public Video
{
    VideoPlayer(const std::string &filename)
    {
        std::cout << "Load Video from file: " << filename << "\n";
    }

    void play()
    {
        std::cout << "Play Video...\n";
    }
};

// 밑과 같이 초기화 할 때 영상을 로드해버림
VideoPlayer video_player{"baseball.mp4"};
```
인스턴스를 생성할 때 동영상을 같이 로드해버린다.  
&nbsp;  

가상 프록시 패턴을 사용해 비디오 플레이어를 느긋하게 바꿔보자.  
```c++
struct LazyVideoPlayer : public Video
{
    LazyVideoPlayer() : filename{filename}, video{nullptr} {}
    ~LazyVideoPlayer() { delete video; }

    void play()
    {
        if (!video)
            video = new VideoPlayer(filename);
        video->play();
    }

private:
    std::string filename;
    Video *video;
};
```
play() 함수가 작동해야만 동영상 로드를 시작하기에 느긋해졌다.  
중요한 점은 성급했던 인스턴스화가 느려졌다 뿐이지 기존 VideoPlayer 클래스와 인터페이스 사용 방식은 똑같다는 것이다.  
&nbsp;  

## 커뮤니케이션 프록시  

싱글 플레이어 게임을 멀티 플레이어 게임으로 만들기는 쉽지 않다.  
이는 대부분 기존 로직들을 클라이언트 <-> 서버 간의 소통을 위해 많이 바꿔야 하기 때문인데 이를 커뮤니케이션 프록시를 통해 완화할 수 있다.  
&nbsp;  

간단한 핑-퐁 로직을 예로 들어보자.  
별거 없다.  
내가 ```핑!``` 하면 너는 ```퐁!``` 하는 것이다.  
&nbsp;  

먼저 밑과 같은 인터페이스가 있다.  
```c++
struct Pingable
{
    virtual std::string ping(const std::string &str) = 0;
};
```
&nbsp;  

싱글 퐁 클래스는 밑과 같다.  
```c++
struct SinglePong : public Pingable
{
    std::string ping(const std::string &str)
    {
        return str + "pong";
    }
};
```
클라이언트 끼리 소통이 필요없는 하나의 컴퓨터에서 모든 것이 돌아가는 퐁 클래스이다.  
단순히 넘겨준 문자열에 pong을 붙여 반환한다.  
&nbsp;  

밑과 같이 SinglePong 클래스를 활용한 로직이 있다.  
```c++
void pingpong(Pingable &pingpong)
{
    std::cout << pingpong.ping("ping") << std::endl;
}

int main()
{
    SinglePong sp;
    for (int i = 0; i < 3; i++)
        pingpong(sp);
    return 0;
}
```
결과는 예측하기 쉽다.  
pingpong 세 번이 출력될 것이다.  
만약 클라이언트 <-> 서버 간의 소통이 필요한 핑-퐁 클래스를 구현하고 싶다면 어떻게 해야 할까?  
&nbsp;  

기존의 SinglePong 클래스의 ping() 함수가 맡고 있었던 역할을 이제 서버 쪽에서 해야 한다.  
해당 서버는 C#으로 구성되었다고 하자.  
밑과 같은 C#으로 구현된 ServerPong이 있다.  
```c#
public class ServerPong : Pingable
{
    public string ping(string msg)
    {
        return msg + "pong";
    }
};
```
이제 C#에서 구현된 ping() 함수로 만들어진 문자열을 클라이언트가 받아 활용해야 한다.  
&nbsp;  

C++ 클라이언트의 Pong 클래스는 밑과 같다.  
```c++
struct MultiPong : public Pingable
{
    std::string ping(const std::string &str)
    {
        std::string result;

        // C# 서버 ServerPong 클래스의 ping() 함수로 생성된 문자열을 가져오는 로직
        result = get_pong_msg_from_csharp_server(str);

        return result;
    }
};
```
```get_pong_msg_from_csharp_server(const std::string &str)``` 함수는 인자로 주어진 문자열을 C# 서버의 ping() 함수로 넘겨주고 그 결과 값을 반환하는 역할을 해야 한다.  
이 때 REST SDK 혹은 Boost.Asio 등을 이용할 수 있겠다.  
&nbsp;  

이제 우리는 개인 클라이언트에서만 작동하던 로직을 클라이언트 <-> 서버 간 통신에서 작동하는 로직으로 바꿔줄 수가 있다.  
```c++
int main()
{
    MultiPong mp;
    for (int i = 0; i < 3; i++)
        pingpong(mp);
    return 0;
}
```
단순히 SinglePong으로 선언되어 있던 클래스를 MultiPong으로 교체하여 이를 해결했다.  
이는 동일한 인터페이스를 제공한다는 프록시 패턴의 특징 덕분이다.  
프로그래머는 단지 Pingable을 상속하는 새로운 클래스에서 ping() 함수를 목적에 맞게 구현했을 뿐이다.  
&nbsp;  

## 요약  

1. 속성 프록시를 이용하면 특정 객체로 접근 / 대입 연산자가 구동될 때 추가적인 작업을 수행할 수 있게 한다.  

2. 가상 프록시는 감싸고 있는 객체에 가상으로 접근할 수 있게 하여 감싸고 있는 객체의 초기화 시점을 임의로 정할 수 있다.  

3. 커뮤니케이션 프록시는 특정 객체의 통신 방식을 바꿔도 그 객체를 사용하는 코드를 거의 동일하게 유지할 수 있게 해준다.  

4. 이외에도 프록시는 로깅 등 다양한 상황에 사용될 수 있고 틀에 박혀있는 패턴이 아니기에 유동적으로 구현해야 한다.  