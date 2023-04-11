# 멀티 쓰레드

멀티 쓰레드의 사용 이유와 장단점을 비교해보고 C++에서 어떻게 이를 활용할 수 있는지 예제를 통해 알아보자.  
&nbsp;  

## 사용 이유  

왜 멀티 쓰레드를 사용할까?  
밑과 같은 맥락을 이해하면 왜 사용하는지 알 수 있다.  

>하나의 프로세스에서는 여러 개의 쓰레드를 할당하여 활용이 가능하다.   
>  
>하나의 CPU 코어는 동시에 단 하나의 쓰레드만을 수행할 수 있다.  

위의 말을 토대로 코어가 많은 CPU에서는 쓰레드를 동시에 여러개 굴릴 수 있다는 것을 알 수 있다.  
CPU가 점점 진보할수록 동시에 여러 개의 일을 시켜 더 효율적이고 빡세게 노동 시킬 수 있다는 것이다.  
이것은 멀티 쓰레드의 **병렬성**으로 인한 장점이다.  
&nbsp;  

그렇다면 CPU의 코어가 하나인 경우 멀티 쓰레드를 사용할 필요가 없냐?  
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
이것은 멀티 쓰레드의 **동시성**으로 인한 장점이다.  
결과적으로 CPU 코어의 수가 어떻든 멀티 쓰레드를 적용할 수 있는 작업이라면 속도적인 측면에서 적용하는 것이 이득이다.  
&nbsp;  

## Thread  

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
쓰레드는 생성된 시점부터 작업을 수행할 수 있지만 생성된 여러 쓰레드 간 작업 순서는 CPU에 따라 달라지기에 보장할 수 없다.  
그리고 main 함수가 종료되었는데도 쓰레드가 백그라운드에서 계속 실행되는 것을 정상으로 처리할 것인지 아니면 특정 코드 라인 전까지 쓰레드 작업이 종료되어야 하는지에 대한 명확한 정의가 없기 때문에 쓰레드를 생성만 해놓으면 오류가 발생한다.  
따라서 생성한 쓰레드는 무조건 join()이나 detach()를 통해 쓰레드 특성을 지정해줘야 한다.  
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
join() 함수는 특정 부분까지 쓰레드 작업이 끝나는 것을 보장하기 위해 사용한다.  
무조건 쓰레드에 할당된 작업이 마무리되어야 join() 함수가 반환되고 다음 라인이 진행된다.  
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
위 예시에서는 쓰레드 작업 속도가 미친듯이 빠르다면 ```My Age: 28```이 출력되겠지만 대부분의 경우 ```My Age: 27```이 출력될 것이다.  
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
앞서 말했듯이 th_1, th_2, th_3의 작업 수행 순서는 보장할 수 없다.  
th_3, th_2가 th_1보다 늦게 생성되었어도 먼저 작업이 수행될 수 있다.  
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
쓰레드 2가 양보를 하여 작업이 멈추는 현상이 없어져 ```Sum: 200```이 정상적으로 출력된다.  
한가지 문제라면 thread_two() 함수에서 while() 문을 계속 돌면서 try_lock()의 성공 여부를 계속해서 체크하는 곳에서 오버헤드가 발생한다는 것이다.  
따라서 데드락 현상을 풀어주는 코드를 구현하기 보다는 데드락 현상이 발생할 여지를 완전히 없애는 것이 바람직하다.  

데드락 현상을 피하기 위한 가이드는 다음과 같다.  

> 1. 중접된 lock을 피해라  
>대부분의 상황에서 1개의 lock도 충분하다.  
>  
> 2. 무조건 lock은 정해진 순서대로 획득해라.    
>예시에서도 mut_1, mut_2의 획득 순서가 꼬여서 데드락 현상이 발생했다.  
&nbsp;  

### Condition Variable  

위에서 말한 ```try_lock()의 성공 여부를 계속 체크하는 곳에서 발생하는 오버헤드```를 최소화할 수 있는 방법이 존재한다.  
while() 문을 계속 돌면서 try_lock() 함수를 호출하는 것이 아니라 쉬고 있다가 확실히 mut_1을 잠금 처리할 수 있는 경우에 try_lock() 함수를 호출하면 오버헤드가 많이 줄어들 것이다.  
```std::condition_variable```은 이를 가능하게 해준다.  
```#include <condition_variable>```를 포함하여 사용할 수 있다.  
&nbsp;  

먼저 수정한 데드락 예시를 보고 ```std::condition_variable```의 용도를 파악해보자.  
```c++
void thread_one(int &sum, std::mutex &mut_1, std::mutex &mut_2, std::condition_variable &cv)
{
    for (int i = 0; i < 100; i++)
    {
        std::unique_lock<std::mutex> lock_1(mut_1);
        std::unique_lock<std::mutex> lock_2(mut_2);
        sum++;
        lock_2.unlock();
        lock_1.unlock();
        cv.notify_one();
    }
}

void thread_two(int &sum, std::mutex &mut_1, std::mutex &mut_2, std::condition_variable &cv)
{
    for (int i = 0; i < 100; i++)
    {
        std::unique_lock<std::mutex> lock(mut_2);
        cv.wait(lock, [&]() -> bool { return mut_1.try_lock(); });
        sum++;
        mut_1.unlock();
    }
}

int main()
{
    int sum = 0;
    std::mutex mut_1, mut_2;
    std::condition_variable cv;

    std::thread t1(thread_one, std::ref(sum), std::ref(mut_1), std::ref(mut_2), std::ref(cv));
    std::thread t2(thread_two, std::ref(sum), std::ref(mut_1), std::ref(mut_2), std::ref(cv));

    t1.join();
    t2.join();

    std::cout << "Sum: " << sum << std::endl;
}
```
해당 예시는 ```Sum: 200```이 기존과 같이 출력된다.  
먼저 ```std::condition_variable```에서 핵심이 되는 ```wait()``` 함수부터 알아보자.  
해당 함수는 인자로 ```std::unique_lock<>```과 Callable을 받는데 동작 절차는 밑과 같다.  

1. wait() 함수가 쓰인 라인이 수행되거나 수면 상태의 쓰레드가 깨어나면 밑의 절차를 수행한다.    
2. 인자로 주어진 ```std::unique_lock<>```이 lock() 되어있지 않다면 lock()을 한다.  
3. 만약 lock()이 안되면 lock()이 가능할 때까지 대기한다.  
4. lock()이 성공했다면 밑 절차를 수행한다.   
5. Callable 함수의 반환값이 false라면 인자로 주어진 ```std::unique_lock<>```을 unlock() 한 후에 수면 상태로 돌아간다.  
    이때 수면 쓰레드 리스트에 추가된다.  
6. Callable 함수의 반환값이 true라면 wait() 함수 밑 로직을 수행한다.  

```notify_all()```, ```notify_one()```을 보자.  
이 둘이 하는 일은 간단하다.  
수면 쓰레드 리스트에 추가된 쓰레드를 깨우는 일을 수행한다.  
```notify_all()```은 이름 그대로 수면 쓰레드 리스트에 추가된 모든 쓰레드를 깨운다.  
```notify_one()```은 CPU 구조에 따라 임의로 하나의 수면 쓰레드를 깨운다.  
&nbsp;  

이러한 동작을 알았다면 해당 예시를 이해할 수 있다.  
```cv.wait(lock, [&]() -> bool { return mut_1.try_lock(); });``` 라인을 통해 쓰레드 2는 mut_1의 잠금이 가능하지 않으면 mut_2를 잠금 해제하고 수면 상태로 들어간다.  
쓰레드 1은 자신의 작업이 끝난 경우에 mut_1, mut_2의 잠금을 해제하고 ```notify_one()```로 쓰레드 2를 깨우기에 데드락 현상이 발생하지 않는다.  
&nbsp;  

좀 더 나아가 생산자-소비자 패턴에서 ```std::condition_variable```의 쓰임을 알아보자.  
먼저 밑과 같은 Content 클래스가 존재한다.  
```c++
class Content
{
    std::string title;

  public:
    std::string name;
    std::string id;
    std::string pw;

    Content(const std::string &title = "")
        : title{title}
    {
    }
    void print_title()
    {
        std::string result = std::regex_replace(title, std::regex("%NAME%"), name);
        result = std::regex_replace(result, std::regex("%ID%"), id);
        result = std::regex_replace(result, std::regex("%PASSWORD%"), pw);
        std::cout << result << std::endl;
    }
};
```
title 문자열의 일부를 치환하여 출력하는 print_title() 함수가 존재한다.  
&nbsp;  

다음은 일거리를 제공하는 생산자 함수이다.  
```c++
void producer(std::queue<Content> &contents, std::mutex &mut, std::condition_variable &cv)
{
    for (int i = 0; i < 40; i++)
    {
        std::string title = "My Name: %NAME%, My ID: %ID%, My Password: %PASSWORD%";

        mut.lock();
        contents.push(Content(title));
        mut.unlock();

        cv.notify_one();
    }
}
```
각 생산자마다 40개의 일거리를 제공하고 일거리가 추가될 때마다 notify_one() 함수를 통해 소비자를 호출한다.  
contents를 처리하는 도중 다른 쓰레드가 끼어들면 안되기에 mutex로 임계 구역을 설정했다.  
&nbsp;  

밑은 일거리를 처리하는 소비자 함수이다.  
```c++
void consumer(std::queue<Content> &contents, std::mutex &mut, std::condition_variable &cv, int &completed)
{
    while (completed < 200)
    {
        std::unique_lock<std::mutex> lock(mut);

        cv.wait(lock, [&]() -> bool { return !contents.empty() || completed == 200; });

        if (completed == 200)
            return;

        auto content = contents.front();
        contents.pop();

        completed++;

        lock.unlock();

        content.name = "kyungjoonlee";
        content.id = "tongstar";
        content.pw = "my_secret";
        std::cout << "Content is Consumed by " << std::this_thread::get_id() << "\n";
        content.print_title();
    }
}
```
```completed < 200```을 체크하는 이유는 생산자가 5개이고 각 생산자마다 40개의 일을 만들어내기 때문이다.  
소비자 함수는 wait() 함수의 Callable 조건을 보면 알겠지만 일거리가 없으면 수면 상태에 들어간다.  
수면 상태에서 깨어난 경우 다른 쓰레드에서 모든 일들을 다 마쳐놓은 상태일 수도 있기에 completed가 200개인지 체크하여 함수를 종료해야 한다.  
content 획득 후 completed 카운트를 1 증가시킨 후에는 미리 unlock()을 한다.  
왜냐하면 받은 content를 처리하는 것은 쓰레드간 충돌이 발생하지 않기 때문이다.  
&nbsp;  

마지막으로 활용 코드는 밑과 같다.  
```c++
int main()
{
    std::queue<Content> contents;
    std::mutex mut;
    std::condition_variable cv;
    int completed = 0;

    std::vector<std::thread> producers;
    for (int i = 0; i < 5; i++)
        producers.push_back(std::thread(producer,
                                        std::ref(contents),
                                        std::ref(mut),
                                        std::ref(cv)));

    std::vector<std::thread> consumers;
    for (int i = 0; i < 8; i++)
        consumers.push_back(std::thread(consumer,
                                        std::ref(contents),
                                        std::ref(mut),
                                        std::ref(cv),
                                        std::ref(completed)));

    for (auto &prod : producers)
        prod.join();

    cv.notify_all();

    for (auto &cons : consumers)
        cons.join();
}
```
활용 코드에서 주의 깊게 봐야할 것은 notify_all() 부분이다.  
분명히 일거리가 없어서 수면 상태로 돌입한 쓰레드들이 있을텐데 이 녀석들을 모두 깨워 consumer() 함수를 정상 종료시켜줘야 한다.  
안그러면 계속 수면 상태에 있어 join() 함수도 반환이 안될 것이고 프로그램이 더 나아가질 못한다.  
&nbsp;  

wait() 이외에도 wait_for(), wait_until() 등이 존재한다.  

```wait_for()```는 wait()에 시간 조건을 더 부여한 함수다.  
밑과 같이 사용이 가능하다.  
```c++
// 시간 조건 + Callable 사용
auto status = cv.wait_for(lock, std::chrono::seconds(10), [&]() -> bool { return !contents.empty() || completed == 200; });
if (!status)
{
    // 시간 초과
}
```
위 예시에서는 쓰레드의 수면 상태가 10초를 초과하여 유지되면 시간 초과가 발생한다.   
10초 내에 쓰레드가 깨어나 ```!contents.empty() || completed == 200``` 조건이 true인 경우에만 시간 초과가 발생하지 않는다.  
시간 초과가 발생하면 수면 상태인 쓰레드를 깨우고 lock이 잠금 처리되며 timeout을 반환한다.  
```cv.wait_for(lock, std::chrono::seconds(10));``` 이렇게 시간 조건만 사용할 수도 있는데 해당 녀석이 사용된 라인에 도달하면 그 쓰레드는 바로 수면 모드로 돌입하고 카운트 다운을 시작한다.   
이 경우 ```notify_all()```, ```notify_one()```로 10초 안에 깨워줘야 timeout이 발생하지 않는다.  
&nbsp;  

```wait_until()```는 특정 시각까지 기다려준다.  
```wait_until()```와 ```wait_for()```는 시각과 시간의 차이만 있을뿐 나머지 기능은 동일하다.  
```wait_until()```는 밑과 같이 사용이 가능하다.  
```c++
// 해당 시점부터 시각 측정
auto now = std::chrono::system_clock::now();

// 측정 시점부터 10초 체크
auto status = cv.wait_until(lock, now + std::chrono::seconds(10), [&]() -> bool { return !contents.empty() || completed == 200; });
if (!status)
{
    // 시간 초과
}
```
```cv.wait_for(lock, std::chrono::seconds(10));```는 ```cv.wait_until(lock, std::chrono::system_clock::now() + std::chrono::seconds(10));```와 동일한 표현이다.  
&nbsp;  

#### Spurious Wakeup  

```std::condition_variable```를 다룰 때 유의해야 할 점이 있는데 바로 Spurious Wakeup 현상이다.  
Spurious Wakeup은 잠자던 쓰레드가 비정상적으로 깨어나는 현상을 말한다.  
말그대로 정말 비정상적이다.  
```notify_all()```, ```notify_one()``` 요런 녀석으로 수면 상태를 깨우지도 않았고, timeout이 발생한 것도 아닌데 그냥 깨어나는 경우가 있다!  
이는 비단 C++만의 문제가 아니라 쓰레드 관련하여 조건 변수를 사용하는 대부분의 프로그래밍 언어에서 발생하는 문제이다.  
&nbsp;  

정확히 어떤 경우에 해당 현상이 발생하는지 예시를 통해 알아보자.  
밑과 같은 생산자가 존재한다.  
```c++
void producer(std::queue<std::string> &contents, std::mutex &mut, std::condition_variable &cv)
{
    for (int i = 0; i < 5; i++)
    {
        mut.lock();
        contents.push("some data");
        mut.unlock();

        cv.notify_one();
    }
}
```
큐에 일거리를 추가한다.   

밑과 같은 소비자도 존재한다.  
```c++
void consumer(std::queue<std::string> &contents, std::mutex &mut, std::condition_variable &cv, int &completed)
{
    while (completed < 25)
    {
        std::unique_lock<std::mutex> lock(mut);

        if (contents.empty())
            cv.wait(lock);

        if (completed == 25)
            return;

        auto content = contents.front();
        contents.pop();
        completed++;
        lock.unlock();

        std::cout << content;
    }
}
```
총 25개의 일을 처리하기 전까지 수행되고 큐가 비어있다면 신호가 오기 전까지 기다린다.  

밑은 활용 코드이다.  
```c++
int main()
{
    std::queue<std::string> contents;
    std::mutex mut;
    std::condition_variable cv;
    int completed = 0;

    std::vector<std::thread> producers;
    for (int i = 0; i < 5; i++)
        producers.push_back(std::thread(producer,
                                        std::ref(contents),
                                        std::ref(mut),
                                        std::ref(cv)));

    std::vector<std::thread> consumers;
    for (int i = 0; i < 8; i++)
        consumers.push_back(std::thread(consumer,
                                        std::ref(contents),
                                        std::ref(mut),
                                        std::ref(cv),
                                        std::ref(completed)));

    for (auto &prod : producers)
        prod.join();

    cv.notify_all();

    for (auto &cons : consumers)
        cons.join();

    return 0;
}
```
언뜻보면 정상적으로 작동할 듯하지만 해당 코드를 계속해서 돌려보면 오류가 발생하게 되어있다.  
&nbsp;  

오류가 발생할 수 있는 부분은 consumer 함수 내부에 있다.    
```c++
void consumer(std::queue<std::string> &contents, std::mutex &mut, std::condition_variable &cv, int &completed)
{
    // 생략
    std::unique_lock<std::mutex> lock(mut);
    if (contents.empty())
        cv.wait(lock);
    if (completed == 25)
        return;
    auto content = contents.front();
    // 생략
}
```
만약 큐가 비어있는 상태이고 완료된 컨텐츠가 25개 미만인데 수면 상태인 쓰레드가 멋대로 깨어나버린다면?    
비어있는 큐에서 front() 함수가 호출되어 오류가 발생할 것이다.  
&nbsp;  

첫번째 해결 방법은 밑과 같이 wait() 보다 늦게 큐의 상태를 체크하는 것이다.  
```c++
void consumer(std::queue<std::string> &contents, std::mutex &mut, std::condition_variable &cv, int &completed)
{
    // 생략
    std::unique_lock<std::mutex> lock(mut);
    cv.wait(lock);
    if (contents.empty())
        continue;
    // 생략
}
```
멋대로 깨어나도 continue로 빈 큐 참조가 방지된다.  
&nbsp;  

두번째 해결 방법은 wait() 함수에 Callable 조건 함수를 같이 넘기는 것이다.  
```c++
void consumer(std::queue<std::string> &contents, std::mutex &mut, std::condition_variable &cv, int &completed)
{
    // 생략
    std::unique_lock<std::mutex> lock(mut);
    cv.wait(lock, [&]() -> bool { return !contents.empty() || completed == 25; });
    // 생략
}
```
멋대로 깨어나도 조건에 걸려 다시 잠들게 된다.  
```wait_until()```, ```wait_for()```도 시간만 지정해주면 Spurious Wakeup이 발생할 수 있기에 꼭 Callable 조건 함수를 인자에 같이 넣어 이를 방지해야 한다.  
&nbsp;  

### Atomic  

[여기에서](#경쟁-상태) 설명했듯이 대부분의 명령은 CPU 내부적으로 더 쪼개져 명령 수행 중 다른 쓰레드가 침범할 수 있다는 문제가 있다.  
Atomic 변수를 사용하면 원자적 명령이 수행되어 중간에 다른 쓰레드가 침범할 가능성이 없어진다.  
트랜잭션의 개념과 비슷한데 명령이 성공하던지 실패하던지 딱 이 두가지 결과만 도출된다.  
사용법을 한번 알아보자.  
&nbsp;  

```#include <atomic>```을 포함하여 사용이 가능하다.  
원자적 명령을 처리하는 정수형 변수는 밑과 같이 쓸 수 있다.  
```c++
std::atomic<int> num;
num.store(17); // 저장
num.load(); // 값 획득
```
store()와 load()는 원자적이기에 명령 수행도중 다른 쓰레드가 끼어들 틈이 없다.  
&nbsp;  

그 뿐만 아니라 밑과 같은 ```++```, ```-=```과 같은 연산자들도 원자적으로 오버로딩되어 있다.  
```c++
std::atomic<int> num(17);
num++;
num -= 17;
```
위 명령은 모두 thread-safe 하다.  
&nbsp;  

단 할당과 획득에 있어서는 신중해야 한다.  
```c++
std::atomic<int> num;
num = num + 17; // 원자적이지 않음
num.store(num.load() + 17); // 원자적임  
```
특정 연산자가 원자적인지 아닌지 헷갈린다면 확실하게 store(), load()를 이용하자.  
&nbsp;  

[여기에서](#mutex) 다뤘던 싱글 vs 멀티 쓰레드 예시 코드를 atomic을 사용해 바꿔보자.  
```c++
// 동일 구현부 생략

void th_func(std::atomic<int> &s)
{
    for (int i = 0; i < destin / 3; i++)
        s++;
}

int main()
{
    // 동일 구현부 생략

    std::atomic<int> atomic_sum(0);

    start_time = clock();
    std::thread th_1 = std::thread(th_func, std::ref(atomic_sum));
    std::thread th_2 = std::thread(th_func, std::ref(atomic_sum));
    std::thread th_3(th_func, std::ref(atomic_sum));
    th_1.join();
    th_2.join();
    th_3.join();
    end_time = clock();

    result = (double)(end_time - start_time) / 1e3;
    std::cout << "Sum Result : " << atomic_sum << '\n';
    std::cout << "Thread Func Time : " << result << "s\n";
}
```
기존에 사용하던 int에서 ```std::atomic<int>``` 자료형으로 바꾸었다.  
&nbsp;  

출력 결과는 밑과 같다.  
```
Sum Result : 2100000000  
Normal Func Time : 1.428s

Sum Result : 2100000000   
Thread Func Time : 34.692s
```
Mutex를 사용한 것보다 빠른 것을 볼 수 있다.  
&nbsp;  

이렇게만 보면 atomic이 좋아보이지만 껄끄러운 부분들이 몇몇 존재한다.   
일단 ```std::atomic<T>```에서 T 자리에 올 수 있는 자료형이 그렇게 많지는 않다.  
대표적으로 정수형, boolean, 포인터가 있다고 보면 된다.  
더 많은 정보는 [이곳에서](https://en.cppreference.com/w/cpp/atomic/atomic) 확인해보자.  
&nbsp;  

그리고 CPU마다 원자적인 명령을 내리지 못하는 것도 존재하기 때문에 밑과 같이 is_lock_free() 함수를 통해 알아봐야 한다.  
```c++
std::atomic<int> num;
if (num.is_lock_free())
{
    // CPU가 원자적 명령 생성 가능
}
else
{
    // CPU가 원자적 명령 생성 불가능
}
```
물론 is_lock_free()가 false인 경우에도 내부적으로 std::mutex를 이용해 명령이 처리되기에 thread-safe 하다.  
하지만 퍼포먼스가 중요한 부분이라면 이러한 요소를 다시 점검할 필요가 있다.  
&nbsp;  

#### 눈으로 보는 것이 다가 아니다.  

진짜 껄끄러운 것은 지금부터 시작이다.  
싱글 쓰레드에서 밑과 같은 명령이 어떤 순서로 수행될 것이라고 생각하는가?  
```c++
int a = 0, b = 0;
b = a + 3;
a = 1;
int c = 7;
```
명령 라인이 저렇게 쓰여졌다고 해도 컴파일러는 CPU 파이프라인을 고려해 라인에 쓰여진 순서대로 명령을 배치하지 않는다.  
```int c = 7;```가 제일 먼저 수행될 수도 있으며 ```b = a + 3;```이 끝나기도 전에 ```a = 1;```가 먼저 처리될 수도 있다.  
즉 메모리 영역의 값을 수정하는 명령들은 재배치될 수 있다.  
&nbsp;  

이를 이해하기 위해서는 파이프라이닝에 대해 살펴볼 필요가 있다.  
빨래를 하는 상황을 생각해보자.  
```세탁기 -> 건조기 -> 빨래 널기``` 이러한 프로세스를 거칠 것이다.  
각 절차는 30분이 소요된다고 하고 빨래해야 하는 옷이 너무 많아 3번에 나누어 진행하는 상황이다.  
먼저 생각할 수 있는 방법은 밑과 같다.  

|    -     |  30분  | 1시간  | 1시간 30분 | 2시간  | 2시간 30분 |   3시간   | 3시간 30분 | 4시간  | 4시간 30분 |
| :------: | :----: | :----: | :--------: | :----: | :--------: | :-------: | :--------: | :----: | :--------: |
| 빨랫감 1 | 세탁기 | 건조기 | 빨래 널기  |        |            |           |            |        |            |
| 빨랫감 2 |        |        |            | 세탁기 |   건조기   | 빨래 널기 |            |        |            |
| 빨랫감 3 |        |        |            |        |            |           |   세탁기   | 건조기 | 빨래 널기  |

4시간 30분이 걸려 빨랫감을 모두 세탁할 수 있었다.  
하지만 건조기를 돌릴 때 세탁기가 비어있고 빨래를 널때 건조기와 세탁기가 놀고 있다.  
결과적으로 비효율적이다.  
&nbsp;  

파이프라이닝 기법을 사용하면 밑과 같이 표현 할 수 있다.  

|    -     |  30분  | 1시간  | 1시간 30분 |   2시간   | 2시간 30분 |
| :------: | :----: | :----: | :--------: | :-------: | :--------: |
| 빨랫감 1 | 세탁기 | 건조기 | 빨래 널기  |           |            |
| 빨랫감 2 |        | 세탁기 |   건조기   | 빨래 널기 |            |
| 빨랫감 3 |        |        |   세탁기   |  건조기   | 빨래 널기  |

세탁기와 건조기가 놀고 있는 구간이 사라져 2시간 30분 만에 모든 빨랫감 세탁이 완료되었다.  
해당 예시와 마찬가지로 CPU도 하나의 명령어를 처리하기 위해 ```읽기 -> 해석하기 -> 실행하기 -> 결과쓰기``` 이러한 프로세스를 거친다.  
차이점이라 하면 각 절차에 걸리는 시간이 명령어마다 천차만별이라는 것이다.  
어떤 명령은 해석하는데 10초가 걸리는 반면 어떤 명령은 읽기부터 결과를 쓰는 절차를 완료하는데 3초가 걸릴 수가 있다.  
&nbsp;  

그럼 위에서 봤던 명령어들을 예시에 대입해보자.  
```b = a + 3;``` 명령은 ```읽기(1초) -> 해석하기(5초) -> 실행하기(2초) -> 결과쓰기(1초)```로 진행된다.  
```a = 1;``` 명령은 ```읽기(1초) -> 해석하기(2초) -> 실행하기(1초) -> 결과쓰기(1초)```로 진행된다.  
```int c = 7;``` 명령은 ```읽기(1초) -> 해석하기(1초) -> 실행하기(2초) -> 결과쓰기(1초)```로 진행된다.  
테이블로 최적화된 파이프라이닝을 표현하면 밑과 같다.  

|     -     |  1초  |   2초    |   3초    |   4초    |   5초    |   6초    |   7초    |   8초    |   9초    |   10초   |   11초   |   12초   |
| :-------: | :---: | :------: | :------: | :------: | :------: | :------: | :------: | :------: | :------: | :------: | :------: | :------: |
| b = a + 3 |       |          |   읽기   |          | 해석하기 | 해석하기 | 해석하기 | 해석하기 | 해석하기 | 실행하기 | 실행하기 | 결과쓰기 |
|   a = 1   |       |   읽기   | 해석하기 | 해석하기 | 실행하기 | 결과쓰기 |          |          |          |          |          |          |
| int c = 7 | 읽기  | 해석하기 | 실행하기 | 실행하기 | 결과쓰기 |          |          |          |          |          |          |          |

최적화에 따라 ```int c = 7;```, ```a = 1;```, ```b = a + 3;``` 순으로 명령이 수행된 것을 볼 수 있다.  
실제 라인에 명령이 쓰인 순서와 딴판이다.  
명령의 순서가 바뀌었어도 최종 결과는 같도록 컴파일러가 순서를 배치한다.    
물론 컴파일러 최적화에 따른 명령 재배치 과정은 훨씬 복잡하지만 대략 이러한 절차를 거쳐 명령 순서가 바뀐다는 것이다.  
&nbsp;  

CPU 캐시에 이미 변수가 저장되어 있냐 아니냐에 따라도 명령 순서가 바뀐다.  
```c++
a = 1; // 캐시에 없음
b = 1; // 캐시에 있음
```
위의 경우 b 변수가 캐시에 상주하고 있어 더 빠른 접근이 가능하기에 ```b = 1;``` 명령이 먼저 수행된다.  
&nbsp;  

그렇다면 우리는 명령어가 적힌 순서대로 수행되지 않는다는 사실을 알았다.  
하지만 최종 결과가 같다면 이게 어떤 경우에 문제가 될 수 있을까?  
바로 멀티 쓰레딩을 사용할 때 문제가 될 수 있다. (싱글 쓰레딩 환경에서는 전혀 문제가 되지 않는다.)  
```c++
void func_one(int *a, int *b)
{
    *b = 1;
    int x = *a;
    printf("x : %d \n", x); // printf()는 thread-safe 하다.
}

void func_two(int *a, int *b)
{
    *a = 1;
    int y = *b;
    printf("y : %d \n", y); // printf()는 thread-safe 하다.
}

int main()
{
    int a = 0, b = 0;
    auto th1 = std::thread(func_one, &a, &b);
    auto th2 = std::thread(func_two, &a, &b);
    th1.join();
    th2.join();
}
```
위 예시의 결과를 예측해보자.  
printf() 함수는 메모리 영역의 값을 수정하는 행위가 아니기에 명령어 재배치 대상에서 제외된다.  

1. ```a : 1 b : 1```  
    가능하다.  
    ```*b = 1;``` -> ```*a = 1;``` -> ```int x = *a;``` -> ```int y = *b;``` 요런 순서로 진행되면 된다.  

2. ```a : 0 b : 1``` 혹은 ```a : 1 b : 0```  
    가능하다.  
    func_one() 후에 순차적으로 func_two()가 수행되거나 그 반대 순서로 수행되면 된다.   

3. ```a : 0 b : 0```  
    놀랍게도... 가능하다.  
    ```int x = *a;``` -> ```int y = *b;``` -> ```*b = 1;``` -> ```*a = 1;``` 요런 순서로 진행되면 된다.  
    이런 순서가 가능한 이유는 각 쓰레드에서 명령어 재배치가 이루어졌기 때문이다.  

보면 알겠지만 각 쓰레드에서 명령어 재배치가 발생하고 그러한 여러 쓰레드가 정해진 순서 없이 여러 코어에서 멀티 쓰레드로 작동한다면 혼돈 그 자체가 된다.  
&nbsp;  

#### 동기화 문제  

CPU 캐시는 코어 별로 존재하기에 멀티 코어 환경에서 특정 쓰레드에서 변경한 값이 다른 쓰레드에서도 그 값이라는 보장이 없다.  
이를 보장하기 위해서는 특정 코어의 캐시 데이터가 변경될 때 다른 코어와 캐시 동기화 작업을 해줘야 하는데 이는 값 비싼 연산이기에 특수한 지시가 없다면 CPU는 매번 동기화를 진행하지 않는다.  
다음 예시를 보자.  
```c++
bool x = false;
bool y = false;
std::atomic<int> z = 0;

void write_x()
{
    x = true;
}

void write_y()
{
    y = true;
}

void read_x_then_y()
{
    while (!x)
    {
    }
    if (y)
        ++z;
}

void read_y_then_x()
{
    while (!y)
    {
    }
    if (x)
        ++z;
}

int main()
{
    std::thread a(write_x);
    std::thread b(write_y);
    std::thread c(read_x_then_y);
    std::thread d(read_y_then_x);
    a.join();
    b.join();
    c.join();
    d.join();
    std::cout << "z : " << z << std::endl;
}
```
위 예시의 결과를 예측해보자.  

1. ```z : 2```   
    가능하다.  
    ```write_x()``` -> ```write_y()``` -> ```read_x_then_y()``` -> ```read_y_then_x()``` 이런 경우면 가능하다.  

2. ```z : 1```  
    가능하다.  
    ```write_x()``` -> ```read_x_then_y()``` -> ```write_y()``` -> ```read_y_then_x()``` 이런 경우면 가능하다.  

3. ```z : 0```  
    이 경우도 가능하다.  
    코어가 두 개인 경우를 생각해보자.  
    ```
                -------------------------------------
    CPU 코어 1 → write_x() 수행 | read_x_then_y() 수행
                -------------------------------------

                -------------------------------------
    CPU 코어 2 → write_y() 수행 | read_y_then_x() 수행
                -------------------------------------
    ```
    CPU 코어 1에서 write_x() 함수가 수행된 후에 CPU 코어 2에서 x의 값이 true라는 보장이 없다.  
    캐시 동기화가 발생하기 전의 CPU 코어 2의 세계에서는 write_x()가 수행된 이후여도 x가 false로 작용한다.  
    즉 CPU 코어 1에서 x->true, y->false이고 CPU 코어 2에서 x->false, y->true인 모순적인 상황이 발생할 수 있다.  
    
CPU의 각 코어들이 항상 동기화가 된 상태가 아니기 때문에 예상치 못한 결과가 발생할 수 있다.  
&nbsp;  

#### 명령 순서 조절  

이렇게 눈에 보이는 데로 수행되지 않는 명령들을 통제하기 위해 std::atomic은 다양한 옵션을 제공한다.  
각 옵션들의 특징을 알아보자.  
&nbsp;  

##### memory_order_relexed  

제일 느슨하고 속도가 빠른 옵션이다.  
해당 옵션을 사용하면 쓰레드 수행부터 종료까지 메모리 연산의 순서가 어떻게 바뀌던 이상할 것이 없다.  
그러면 이 옵션은 어떤 곳에 사용할 수 있을까?  
```c++
void th_func(std::atomic<int> &s)
{
    for (int i = 0; i < 100; i++)
        s.fetch_add(1, std::memory_order_relaxed);
}

int main()
{
    std::vector<std::thread> vec;
    std::atomic<int> sum(0);

    for (int i = 0; i < 3; i++)
        vec.push_back(std::thread(th_func, std::ref(sum)));

    for (auto &th : vec)
        th.join();

    std::cout << (sum == 300 ? "Complete!" : "Something is Wrong!");
}
```
단순히 위 처럼 연산 순서를 고려할 필요가 없는 상황에 쓸 수 있다.  
join() 전에 더하기 연산이 어떤 순서로 수행되던 join() 이후에는 300이라는 결과가 확정이 되기 때문에 이러한 경우 속도가 빠른 std::memory_order_relaxed 옵션을 사용하는 것이 좋다.  
&nbsp;  

##### memory_order_release, memory_order_acquire   

memory_order_relexed보다 좀 더 엄격하다.  
memory_order_release가 사용된 쓰레드 내부 한정으로 memory_order_release가 쓰인 라인 **이전** 명령들이 memory_order_release가 쓰인 라인 이후로 재배치되는 것을 방지한다.  
반대로 memory_order_acquire는 사용된 쓰레드 내부 한정으로 memory_order_acquire가 쓰인 라인 **이후** 명령들이 memory_order_acquire가 쓰인 라인 **이전**으로 재배치되는 것을 방지한다.  
&nbsp;  

이해를 돕기 위한 예시는 밑과 같다.  
```c++
std::atomic<bool> is_ready;

void writer(std::atomic<int> *data)
{
    data[0].store(1, std::memory_order_relaxed);
    data[1].store(2, std::memory_order_relaxed);
    data[2].store(3, std::memory_order_relaxed);
    is_ready.store(true, std::memory_order_release);
}

void reader(std::atomic<int> *data)
{
    while (!is_ready.load(std::memory_order_acquire));

    std::cout << "data[0] : " << data[0].load(std::memory_order_relaxed) << std::endl;
    std::cout << "data[1] : " << data[1].load(std::memory_order_relaxed) << std::endl;
    std::cout << "data[2] : " << data[2].load(std::memory_order_relaxed) << std::endl;
}

int main()
{
    std::atomic<int> data[3] = { 0, };
    std::vector<std::thread> threads;

    threads.push_back(std::thread(writer, data));
    threads.push_back(std::thread(reader, data));

    for (int i = 0; i < 2; i++)
        threads[i].join();
}
```
writer() 함수에서 data들을 변경할 때 is_ready를 저장하는 라인을 넘어갈 수 없다.  
reader() 함수에서 data들을 읽을 때 is_ready를 읽는 라인 전으로 올라갈 수 없다.  
물론 위의 규칙을 지킨 상태에서 std::memory_order_relaxed가 사용된 명령들은 마음대로 재배치가 될 수 있다.  
확실한 점은 reader() 함수에서 data 값을 참조할 때 무조건 ```data = {1,2,3}``` 상태가 보장된다는 것이다.  
&nbsp;  

##### memory_order_acq_rel   

memory_order_release와 memory_order_acquire를 합쳐놓은 녀석이다.  
읽기, 쓰기를 모두 사용하는 명령에서 사용하면 좋다.  
&nbsp;  

##### memory_order_seq_cst      

std::atomic에 아무런 옵션도 설정하지 않으면 memory_order_seq_cst가 기본으로 설정된다.  
memory_order_acq_rel, memory_order_release, memory_order_acquire 요 녀석들은 [명령어 재배치 문제](#눈으로-보는-것이-다가-아니다)는 해결해주지만 [코어간 캐시 동기화 문제](#동기화-문제)는 해결해주지 않는다.  
즉 어떤 쓰레드에서는 1인 값이 다른 쓰레드에서는 2로 존재할 수 있다.  
하지만 memory_order_seq_cst 옵션을 사용하면 저장 버퍼에 대한 flush가 보장되기에 코어간 캐시 동기화 문제까지 해결된다. (모든 명령에 대한 순차적 일관성이 보장된다.)  
하지만 모든 옵션 중 가장 속도가 느리다.  
&nbsp;  

[해당 목차](#동기화-문제)에서 살펴본 예시를 memory_order_seq_cst 옵션을 사용하여 변경해보자.  
```c++
std::atomic<bool> x = false;
std::atomic<bool> y = false;
std::atomic<int> z = 0;

void write_x()
{
    x.store(true, std::memory_order_seq_cst);
}

void write_y()
{
    y.store(true, std::memory_order_seq_cst);
}

void read_x_then_y()
{
    while (!x.load(std::memory_order_seq_cst))
    {
    }
    if (y.load(std::memory_order_seq_cst))
        ++z;
}

void read_y_then_x()
{
    while (!y.load(std::memory_order_seq_cst))
    {
    }
    if (x.load(std::memory_order_seq_cst))
        ++z;
}

// 동일 구현부 생략
```
모든 쓰레드에서 동일한 값이 관찰되는 것이 보장되기에 z의 값이 0으로 나올 수 없다.  
&nbsp;  

## Task  

기존에 다루었던 std::thread는 **쓰레드 기반**이다.  
말 그대로 별도의 쓰레드를 만들어 활용하는 것에 초점이 맞춰져있다.  
흐름의 시작과 종료는 쓰레드의 수명으로 구분된다.     
쓰레드간 특정 값을 전달해 소통하던지 어떤 처리만 비동기로 진행하던지 어떻게 하던 개발자 마음이다.  

반면에 지금 다루려는 std::async, std::packaged_task, std::future, std::promise는 **테스크 기반**이다.  
특정 쓰레드에서 어떤 값을 미래에 전달 받는 것에 초점이 맞춰져있다.  
흐름의 시작과 종료가 특정 값의 획득으로 구분된다.  
테스크는 기본적으로 thread pool을 사용하여 쓰레드 기반의 상위 개념이라고 볼 수 있다.  
std::future, std::promise, std::async, std::packaged_task는 ```#include <future>```를 포함하여 사용할 수 있다.   
&nbsp;  

### Future, Promise  

std::future, std::promise는 내부적으로 std::condition_variable, std::mutex를 사용해 구현된 변수 동기화 구조체라고 보면된다.  
일단 std::condition_variable를 사용한 예시부터 보자.  
```c++
void worker(std::mutex *m, std::condition_variable *cv, std::string *data)
{
    m->lock();
    *data = "hello world";
    m->unlock();
    cv->notify_one();
}

int main()
{
    std::condition_variable cv;
    std::mutex m;
    std::string data;

    std::thread th(worker, &m, &cv, &data);

    std::unique_lock<std::mutex> lock(m);
    cv.wait(lock, [&]() -> bool { return !data.empty(); });
    lock.unlock();

    std::cout << data;

    th.join();
}
```
한 개의 쓰레드를 생성하여 data를 획득할 때까지 기다리는 코드이다.  
&nbsp;  

같은 동작을 하는 std::future, std::promise 예시를 보자.  
```c++
void worker(std::promise<std::string> *data)
{
    data->set_value("hello world");
}

int main()
{
    std::promise<std::string> p;
    std::future<std::string> data = p.get_future();

    std::thread th(worker, &p);

    // 생략 가능
    data.wait();

    std::cout << data.get();

    th.join();
}
```
코드가 훨씬 깔끔해졌다.  
사용법은 요약하면 밑과 같다.  

1. std::promise 변수를 std::future 변수와 연결해 약속한다.  
2. std::future의 wait() 함수를 통해 변수값이 설정되길 기다린다.  
3. std::promise의 set_value() 함수로 값을 설정해준다.  
4. std::future의 get() 함수를 통해 값을 획득한다.  

심지어 data.wait()은 data.get()을 수행될 때 알아서 처리되기에 생략해도 무방하다.  
주의할 점은 std::future의 get() 함수를 사용하면 저장된 객체가 이동하기 때문에 단 한 번만 사용해야 한다.  
&nbsp;  

get()을 여러번 사용하려면 밑과 같이 std::shared_future를 이용하면 된다.  
```c++
void producer(std::promise<std::string> *data)
{
    data->set_value("hello world");
}

void consumer(std::shared_future<std::string> *data)
{
    static int num = 0;
    printf("num: %d, data: %s\n", num++, data->get().c_str());
}

int main()
{
    std::promise<std::string> p;
    std::shared_future<std::string> data = p.get_future();

    std::thread th(producer, &p);

    std::vector<std::thread> vec;
    for (int i = 0; i < 5; i++)
        vec.push_back(std::thread(consumer, &data));

    th.join();
    for (auto &thread : vec)
        thread.join();
}
```
get()이 여러번 가능해 별도의 참조, 포인터 변수가 불필요하다.  
&nbsp;  

std::future에는 std::condition_variable와 같이 wait_for() 함수가 존재한다.  
```c++
while (true) {
    std::future_status status = data.wait_for(std::chrono::seconds(1));

    if (status == std::future_status::timeout) {
        // 아직 값 설정이 안됨.
    }
    else if (status == std::future_status::ready) {
        // std::promise의 set_value()로 값이 설정됨.
        break;
    }
}
```
위와 같이 사용할 수 있고 std::future에서는 [Spurious Wakeup](#spurious-wakeup) 현상이 발생하지 않는다.  
&nbsp;  

### Packaged Task  
&nbsp;  

### Async  
&nbsp;  

## Coroutine  

