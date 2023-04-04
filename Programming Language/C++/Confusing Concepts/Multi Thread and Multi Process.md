# 멀티 쓰레드와 멀티 프로세스  

멀티 쓰레드와 멀티 프로세스의 사용 이유와 장단점을 비교해보고 C++에서 어떻게 이를 활용할 수 있는지 예제를 통해 알아보자.  
&nbsp;  

## 사용 이유  

왜 멀티 쓰레드와 멀티 프로세스를 사용할까?  
밑과 같은 맥락을 이해하면 왜 사용하는지 알 수 있다.  

>하나의 프로세스에서는 여러 개의 쓰레드를 할당하여 활용이 가능하다.   
>  
>하나의 CPU 코어는 동시에 단 하나의 쓰레드만을 수행할 수 있다.  

위의 말을 토대로 코어가 많은 CPU에서는 쓰레드를 동시에 여러개 굴릴 수 있다는 것을 알 수 있다.  
CPU가 점점 진보할수록 동시에 여러 개의 일을 시켜 더 효율적이고 빡세게 노동 시킬 수 있다는 것이다.  
&nbsp;  

그렇다면 CPU의 코어가 하나인 경우 멀티 쓰레드와 멀티 프로세스를 사용할 필요가 없냐?  
전혀 아니다.  
다량의 문서를 서버에서 다운받는 상황을 생각해보자.  
요청을 보내면 대략 3분 뒤부터 답변이 도착해 다운로드가 시작되는 서버라고 가정하자.  
그러면 요청을 보내고 CPU의 코어는 3분 동안 아무것도 안하고 대기를 해야할까?  
```
--------------------------------------------------------------------------------------
파일 1 요청 |    대기...    | 파일 1 다운로드 | 파일 2 요청 |    대기...    | 파일 2 다운로드
--------------------------------------------------------------------------------------
```
위 도식을 보면 알겠지만 비효율적이다.  
&nbsp;  

반면에 다량의 문서를 서버에서 다운받는 작업을 쓰레드에 할당해 분할 작업하면 어떻게 될까?  
최신의 운영체제들은 프로세스 단위뿐 아니라 쓰레드 단위로도 CPU 스케쥴링을 해주기 때문에 밑과 같은 도식이 나온다.  
```
------------------------------------------------------------------------------------
파일 1 요청 | 파일 2 요청 | 파일 3 요청 | 파일 1 다운로드 | 파일 2 다운로드 | 파일 3 다운로드
------------------------------------------------------------------------------------
```
즉 서버에 파일 다운로드 요청을 보낸 후 대기 상태가 발생하면 문맥 교환(쓰레드 교체)을 통해 다른 쓰레드가 그 시간에 일을 할 수 있도록 작업을 분배한다.  
이는 멀티 프로세스에서도 동일하게 작용한다.  
결과적으로 CPU 코어의 수가 어떻든 멀티 쓰레드, 멀티 프로세스를 적용할 수 있는 작업이라면 속도적인 측면에서 적용하는 것이 이득이다.  
&nbsp;  

## 멀티 쓰레드  

```#include <thread>```를 포함하여 사용할 수 있다.  
쓰레드 생성부터 다뤄보자.  
```c++
void func_val(int p)
{
    p++;
}

int num = 10;
auto thread_func = std::thread(func_val, num);
```
위와 같이 ```std::thread(함수 이름, 함수 인자들...)```로 쓰레드 생성을 하면 된다.  
&nbsp;  

참조의 경우 밑과 같다.
```c++
void func_ref(int &p)
{
    p++;
}

int num = 10;
auto thread_func = std::thread(func_ref, std::ref(num));
```
값으로 넘기는 게 아니라는 걸 std::ref()를 통해 알려줘야 한다.  
&nbsp;  

포인터는 밑과 같다.  
```c++
void func_pt(int *p)
{
    (*p)++;
}

int num = 10;
auto thread_func = std::thread(func_pt, &num);
```
쓰레드만으로는 함수가 반환하는 값을 획득할 수 없기에 보통 포인터나 참조를 사용한 인자를 통해 값을 획득한다.  
&nbsp;  

클래스나 구조체에서는 밑과 같이 사용한다.  
```c++
struct Number
{
    int num = 0;

    void Addition(int amount)
    {
        num += amount;
    }
};

Number num;
auto thread_struct = std::thread(&Number::Addition, &num, 100);
```
함수 포인터, 객체 포인터, 인자값 순으로 들어간다.  
&nbsp;  

Functor도 된다.  
```c++
struct Printer
{
    void operator()()
    {
        std::cout << "Hello World";
    }
};

auto thread_functor = std::thread(Printer());
```
그냥 Callable이면 모두 쓰레드에 작업 할당이 가능하다.  

&nbsp;  
쓰레드는 생성만 하면 반드시 오류가 발생한다.  
따라서 생성한 쓰레드는 무조건 join()이나 detach()를 해줘야 한다.  
join()이나 detach()를 하는 시점부터 쓰레드에 할당된 작업이 진행된다.  
둘의 차이점을 알아보자.  
&nbsp;  

join()은 밑과 같이 동작한다.  
```c++
void func(int *p)
{
    (*p)++;
}

int main()
{
    int age = 27;
    auto thread_func = std::thread(func, &age);
    thread_func.join();

    std::cout << "My Age: " << age;
}
```
join() 함수는 동기 작업을 처리할 때 쓰인다.  
무조건 쓰레드에 할당된 작업이 마무리되어야 다음 라인이 진행된다.  
물론 다른 쓰레드를 join() 시키는 라인은 수행된다.  
위 예시에서는 ```My Age: 28```이 출력되는 것을 보장할 수 있다.  
&nbsp;  

detach()는 밑과 같이 동작한다.  
```c++
void func(int *p)
{
    (*p)++;
}

int main()
{
    int age = 27;
    auto thread_func = std::thread(func, &age);
    thread_func.detach();
    std::cout << "My Age: " << age;
}
```
detach() 함수는 비동기 작업을 처리할 때 쓰인다.  
쓰레드에 할당된 작업을 백그라운드에서 수행하기 때문에 작업의 마무리 유무와 상관없이 바로 다음 라인이 진행된다.  
위 예시에서는 쓰레드 작업 속도가 매우매우 빠르다면 ```My Age: 28```이 출력되겠지만 대부분의 경우 ```My Age: 27```이 출력될 것이다.  
&nbsp;  

밑은 싱글 쓰레드와 멀티 쓰레드의 연산 속도 차이 측정 예시이다.  
```c++
const int destin = 2100000000;

void func(int &s)
{
    for (int i = 0; i < destin; i++)
        s++;
}

void th_func(int &s)
{
    int sum = 0;
    for (int i = 0; i < destin / 3; i++)
        sum++;
    s += sum;
}

int main()
{
    clock_t start_time, end_time;
    double result = 0;
    int sum = 0;

    start_time = clock();
    func(sum);
    end_time = clock();

    result = (double)(end_time - start_time) / 1e3;
    std::cout << "Sum Result : " << sum << '\n';
    std::cout << "Normal Func Time : " << result << "s\n\n";

    sum = 0;

    start_time = clock();
    std::thread th_1 = std::thread(th_func, std::ref(sum));
    std::thread th_2 = std::thread(th_func, std::ref(sum));
    std::thread th_3(th_func, std::ref(sum));
    th_1.join();
    th_2.join();
    th_3.join();
    end_time = clock();

    result = (double)(end_time - start_time) / 1e3;
    std::cout << "Sum Result : " << sum << '\n';
    std::cout << "Thread Func Time : " << result << "s\n";
}
```
2100000000번의 순회를 돌면서 sum에 더한다.  
&nbsp;  

출력 결과는 밑과 같다.  
```
Sum Result : 2100000000
Normal Func Time : 1.477s

Sum Result : 2100000000
Thread Func Time : 0.456s
```
멀티 쓰레드를 적용한 것이 많이 빠른 것을 확인할 수 있다.  
&nbsp;  

위 구현을 유심히 보면 func()와 th_func() 구현이 다른 것을 볼 수 있다.  
th_func()에서 굳이 sum이란 변수를 따로 두어 마지막에 변수 s에 더하는 이유가 무엇일까?  
한번 th_func()를 밑과 같이 변경하고 돌려보자.  
```c++
void th_func(int &s)
{
    for (int i = 0; i < destin / 3; i++)
        s++;
}
```
&nbsp;  

밑은 출력값이다.  
```
Sum Result : 2100000000
Normal Func Time : 1.462s

Sum Result : 824726985
Thread Func Time : 2.577s
```
... 말도 안되는 결과가 나왔다.  
결과도 이상한데 경과 시간도 느리다.    
&nbsp;  

### 경쟁 상태   

위와 같은 결과가 발생한 이유는 파고들면 굉장히 복잡하지만 간단하게 말하자면 같은 변수를 서로 다른 쓰레드에서 동시에 사용하여 그렇다.  
우리가 볼 땐 ```sum++;``` 명령은 단순히 1을 증가시키는 명령이지만 CPU는 해당 명령을 더 작은 단위로 쪼개 처리한다.  
예를 들어 1을 증가시키는 명령이 A, B, C, D 이렇게 4개로 쪼개져 있다고 하자.  
D가 끝나는 시점에 실제 sum 변수에 변경이 적용될 것이다.  
밑의 경우를 보자.  
```
A(쓰레드 1)
    ↓
B(쓰레드 1)
    ↓
A(쓰레드 2)
    ↓
C(쓰레드 1)
    ↓
A(쓰레드 3)
    ↓
D(쓰레드 1, sum 변수에 값 적용)
    ↓
B(쓰레드 2)
    .
    .
    .
```
쓰레드 1이 D 명령을 수행하기 전에 다른 쓰레드들이 끼어들어 쓰레드 1이 진행하던 연산 빌드업을 흐트려 놓았다.  
이 경우 쓰레드 1에서 D 명령이 수행되어 sum 변수에 값이 적용될 때 어떤 결과가 도출될지 예측하기 어렵다.   
항상 예측할 수 있는 결과값을 도출하려면 특정 쓰레드가 연산을 처리할 때 다른 쓰레드에서 끼어드는 일을 방지할 수 있어야 한다.  
&nbsp;  

C++에서는 std::mutex와 std::atomic을 통해 이를 방지할 수 있다.    
이 두가지에 대해 한번 알아보자.  
&nbsp;  

### Mutex  

```#include <mutex>```를 포함하여 사용할 수 있다.  
std::mutex는 특정 쓰레드에게 다른 쓰레드가 끼어들 수 없는 공간(임계 영역)을 제공한다.  
임계 영역의 시작은 lock()으로 알리며 끝은 unlock()으로 알린다.  
한번 위에서 다뤘던 예시를 std::mutex를 사용하여 바꿔보자.  
```c++
// 동일 구현부 생략

void th_func(int &s, std::mutex &mut)
{
    for (int i = 0; i < destin / 3; i++)
    {
        mut.lock();
        s++;
        mut.unlock();
    }
}

int main()
{
    // 동일 구현부 생략

    sum = 0;
    std::mutex mut;

    start_time = clock();
    std::thread th_1 = std::thread(th_func, std::ref(sum), std::ref(mut));
    std::thread th_2 = std::thread(th_func, std::ref(sum), std::ref(mut));
    std::thread th_3(th_func, std::ref(sum), std::ref(mut));
    th_1.join();
    th_2.join();
    th_3.join();
    end_time = clock();

    // 동일 구현부 생략
}
```
s++ 연산을 처리할 때 다른 쓰레드가 접근하지 못하게 std::mutex를 이용하여 감싸고 있다.  
&nbsp;  

출력 결과는 밑과 같다.  
```
Sum Result : 2100000000
Normal Func Time : 1.456s

Sum Result : 2100000000
Thread Func Time : 71.374s
```
연산의 결과는 잘 나왔지만 수행 속도가 매우 느려졌다.  
이는 임계 구역의 생성과 해제가 많은 오버헤드를 발생하기 때문이다.  
임계 구역 내에서 특정 쓰레드가 연산을 수행하고 있다면 다른 쓰레드들은 임계 구역이 반환(unlock)될 때까지 그저 대기하고 있어야 한다.  
따라서 std::mutex를 사용할 때는 신중해야 한다.  
&nbsp;  

C++에서는 굳이 unlock()을 명시적으로 하지 않아도 되는 ```std::lock_guard<>```를 제공한다.  
```c++
void th_func(int &s, std::mutex &mut)
{
    for (int i = 0; i < destin / 3; i++)
    {
        std::lock_guard<std::mutex> lock(mut);
        s++;
    }
}
```
마치 스마트 포인터와 비슷하게 블록을 빠져나오면 알아서 해제된다.  
&nbsp;  

더 많은 기능을 제공하는 ```std::unique_lock<>```도 존재한다.  
```c++
void th_func(int &s, std::mutex &mut)
{
    for (int i = 0; i < destin / 3; i++)
    {
        std::unique_lock<std::mutex> lock(mut);
        s++;
        lock.unlock();
        lock.lock();
    }
}
```
std::mutex의 스마트 포인터 형식이라고 생각하면 좋다.  
위에서 볼 수 있듯이 원하는 때에 unlock(), lock()이 자유롭다.  
물론 블록을 빠져나오면 알아서 해제된다.  
&nbsp;  

추가적인 인자를 같이 넘겨 lock 시점을 미룰 수도 있다.  
```c++
void lock_sample(std::mutex &mut_1, std::mutex &mut_2)
{
    std::unique_lock<std::mutex> lock_1(mut_1, std::defer_lock);
    std::unique_lock<std::mutex> lock_2(mut_2, std::defer_lock);

    // do something...

    std::lock(lock_1, lock_2); // 실제 잠금 시점
}
```
std::defer_lock를 이용해 잠금 시점을 뒤로 미루고 std::lock()을 통해 mut_1, mut_2를 동시에 잠구는 것을 볼 수 있다.  
&nbsp;  

std::mutex를 사용할 때는 유의할 점이 있는데 바로 데드락 현상이다.  
밑 예시를 보자.  
```c++
void thread_one(int &sum, std::mutex &mut_1, std::mutex &mut_2)
{
    for (int i = 0; i < 100; i++)
    {
        std::lock_guard<std::mutex> lock_1(mut_1);
        std::lock_guard<std::mutex> lock_2(mut_2);

        sum++;
    }
}

void thread_two(int &sum, std::mutex &mut_1, std::mutex &mut_2)
{
    for (int i = 0; i < 100; i++)
    {
        std::lock_guard<std::mutex> lock_2(mut_2);
        std::lock_guard<std::mutex> lock_1(mut_1);

        sum++;
    }
}

int main()
{
    int sum = 0;
    std::mutex mut_1, mut_2;

    std::thread t1(thread_one, std::ref(sum), std::ref(mut_1), std::ref(mut_2));
    std::thread t2(thread_two, std::ref(sum), std::ref(mut_1), std::ref(mut_2));

    t1.join();
    t2.join();

    std::cout << "Sum: " << sum << std::endl;
}
```
위 예시는 ```Sum: 200```이 출력되지 않는다.  
각 std::mutex의 순서를 분석해보면 이유를 알 수 있다.  
이해를 쉽게 하기 위해 코어 두개에서 동시에 쓰레드 1, 쓰레드 2가 수행되는 상황을 생각해보자.  
```
            -----------------------------------------------------------------------------
CPU 코어 1 → 쓰레드 1 수행 | mut_1을 잠금 | mut_2를 잠그려하는데 쓰레드 2에서 사용하므로 대기... 
            -----------------------------------------------------------------------------

            -----------------------------------------------------------------------------
CPU 코어 2 → 쓰레드 2 수행 | mut_2을 잠금 | mut_1를 잠그려하는데 쓰레드 1에서 사용하므로 대기... 
            -----------------------------------------------------------------------------
```
위 상황을 보면 서로 lock을 누가 풀어주기를 바라면서 계속 대기하고 있다.  
이렇게 무한정 대기만 하다보니 ```Sum: 200``` 출력 라인으로 넘어갈 수가 없다.  
&nbsp;  

이를 해결하기 위해서 쓰레드끼리 우선순위를 정해놔야 한다.  
thread_two() 함수의 구현을 밑과 같이 바꿔보자.  
```c++
void thread_two(int &sum, std::mutex &mut_1, std::mutex &mut_2)
{
    for (int i = 0; i < 100; i++)
    {
        while (true)
        {
            mut_2.lock();

            if (!mut_1.try_lock())
            {
                mut_2.unlock();
                continue;
            }

            sum++;

            mut_1.unlock();
            mut_2.unlock();
            break;
        }
    }
}
```
try_lock()을 통해 mut_1에 lock() 가능 유무를 체크하고 lock()이 실패한다면 mut_2를 unlock()하여 다른 쓰레드에서 mut_2를 사용할 수 있도록 양보한다.  
이를 도식으로 풀어보면 밑과 같다.  
```
            ---------------------------------------------------------------------------------------------------------------------------------
CPU 코어 1 → 쓰레드 1 수행 | mut_1을 잠금 | mut_2를 잠그려하는데 쓰레드 2에서 사용하므로 대기......................... | mut_2 잠금 성공 | 로직 진행 ...
            ---------------------------------------------------------------------------------------------------------------------------------

            --------------------------------------------------------------------------------------------------------------------------------------------
CPU 코어 2 → 쓰레드 2 수행 | mut_2을 잠금 | mut_1의 try_lock()을 통해 잠금 시도 | mut_1 잠금 실패 | mut_2을 잠금 해제 | mut_2를 쓰레드 1에서 사용하므로 잠금 대기... 
            --------------------------------------------------------------------------------------------------------------------------------------------
```
쓰레드 2가 양보를 하여 작업이 멈추는 현상이 없어졌다.  
한가지 문제라면 thread_two() 함수에서 while() 문을 계속 돌면서 try_lock()의 성공 여부를 계속해서 체크하는 곳에서 오버헤드가 발생한다는 것이다.  
따라서 데드락 현상을 풀어주는 코드를 구현하기 보다는 데드락 현상이 발생할 여지를 완전히 없애는 것이 바람직하다.  

데드락 현상을 피하기 위한 가이드는 다음과 같다.  

> 1. 중접된 lock을 피해라  
>대부분의 상황에서 1개의 lock도 충분하다.  
>  
> 2. 무조건 lock은 정해진 순서대로 획득해라.    
>예시에서도 mut_1, mut_2의 획득 순서가 꼬여서 데드락 현상이 발생했다.  
&nbsp;  

#### Condition Variable  

위에서 말한 ```try_lock()의 성공 여부를 계속 체크하는 곳에서 발생하는 오버헤드```를 최소화할 수 있는 방법이 존재한다.  
while() 문을 계속 돌면서 try_lock() 함수를 호출하는 것이 아니라 쉬고 있다가 확실히 mut_1을 잠금 처리할 수 있는 경우에 try_lock() 함수를 호출하면 오버헤드가 많이 줄어들 것이다.  
```std::condition_variable```은 이를 가능하게 해준다.  
```#include <condition_variable>```를 포함하여 사용할 수 있다.  
&nbsp;  

먼저 예시를 수정해보자.  
