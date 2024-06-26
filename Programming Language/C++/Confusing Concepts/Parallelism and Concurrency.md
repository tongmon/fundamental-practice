# Multi Thread  

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
만약 ```const int &```라면 std::cref()를 이용한다.  
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

### 명령어 재배치  

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

1. ```x : 1 y : 1```  
    가능하다.  
    ```*b = 1;``` -> ```*a = 1;``` -> ```int x = *a;``` -> ```int y = *b;``` 요런 순서로 진행되면 된다.  

2. ```x : 0 y : 1``` 혹은 ```x : 1 y : 0```  
    가능하다.  
    func_one() 후에 순차적으로 func_two()가 수행되거나 그 반대 순서로 수행되면 된다.   

3. ```x : 0 y : 0```  
    놀랍게도... 가능하다.  
    ```int x = *a;``` -> ```int y = *b;``` -> ```*b = 1;``` -> ```*a = 1;``` 요런 순서로 진행되면 된다.  
    이런 순서가 가능한 이유는 각 쓰레드에서 명령어 재배치가 이루어졌기 때문이다.  

보면 알겠지만 각 쓰레드에서 명령어 재배치가 발생하고 그러한 여러 쓰레드가 정해진 순서 없이 여러 코어에서 멀티 쓰레드로 작동한다면 혼돈 그 자체가 된다.  
&nbsp;  

### 캐시 일관성 문제  

CPU 캐시는 코어 별로 존재하기에 멀티 코어 환경에서 특정 쓰레드에서 변경한 값이 다른 쓰레드에서도 항상 그 값이라는 보장이 없다.  
이를 보장하기 위해서는 특정 코어의 캐시 데이터가 변경될 때 다른 코어와 캐시 동기화 작업을 해줘야 하는데 이는 값 비싼 연산이기에 특수한 지시가 없다면 CPU는 매번 동기화를 진행하지 않는다.  
물론 매번 동기화를 하지 않아 그 시점을 예측할 수 없다는 것이지 코어 간 동기화가 필요한 변수가 존재한다면 언젠가는 동기화가 된다.  
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
    while (!x);
    if (y)
        ++z;
}

void read_y_then_x()
{
    while (!y);
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
```std::atomic<int>``` 이 녀석에 대해선 추후에 설명하겠지만 지금은 간단하게 [경쟁 상태](#경쟁-상태)가 해결된 thread-safe한 자료형이라고 이해하자.  
위에서 설명한 [명령어 재배치](#명령어-재배치) 문제는 일단 제외하고 생각해보자.  
위 예시의 결과를 예측하면 밑과 같다.  

1. ```z : 2```   
    가능하다.  
    ```write_x()``` -> ```write_y()``` -> ```read_x_then_y()``` -> ```read_y_then_x()``` 이런 경우면 가능하다.  

2. ```z : 1```  
    가능하다.  
    ```write_x()``` -> ```read_x_then_y()``` -> ```write_y()``` -> ```read_y_then_x()``` 이런 경우면 가능하다.  

3. ```z : 0```  
    가능하다!
    코어가 4개인 경우를 생각해보자.    
    ```
                -------------------------------------
    CPU 코어 1 → write_x() 수행
                -------------------------------------

                -------------------------------------
    CPU 코어 2 → write_y() 수행
                -------------------------------------

                -------------------------------------
    CPU 코어 3 →                 read_x_then_y() 수행
                -------------------------------------

                -------------------------------------
    CPU 코어 4 →                 read_y_then_x() 수행
                -------------------------------------
    ```
    지면에 서있는 상태의 사람은 땅바닥이 자신의 아래에 위치한다고 생각할 것이다.  
    거꾸로 매달려 있는 상태의 사람은 땅바닥이 자신의 위에 위치한다고 생각할 것이다.  
    이는 상황을 보는 관점이 **상대적**이기 때문에 그렇다.  
    CPU 코어도 마찬가지로 이런 상대성이 적용된다.  
    write_x(), write_y()가 실제로 동시에 시작되고 끝났어도 **코어 3**과 **코어 4**가 볼 때는 그렇지 않다.  
    **코어 3**은 ```write_x()``` -> ```read_x_then_y()``` -> ```write_y()``` 이러한 순서로 관측했다.  
    **코어 4**는 ```write_y()``` -> ```read_y_then_x()``` -> ```write_x()``` 이러한 순서로 관측했다.  
    이렇게 되면 결과적으로 **코어 3**에서 ```x: true, y: false```이고 **코어 4**에서 ```x: false, y: true```인 모순적인 상황이 실제로 발생할 수 있다.  
    
CPU의 각 코어들이 항상 동기화가 된 상태가 아니기 때문에 예상치 못한 결과가 발생할 수 있다.  
&nbsp;  

### 어떻게 해결하지...?  

C++에서는 std::mutex와 std::atomic을 통해 앞에 설명한 3가지 문제를 방지할 수 있다.    
상황에 따라 두가지를 선택해 사용하면 된다.  
이 두가지에 대해 한번 알아보자.  
&nbsp;  

### Mutex  

```#include <mutex>```를 포함하여 사용할 수 있다.  
std::mutex는 특정 쓰레드에게 다른 쓰레드가 끼어들 수 없는 공간(임계 영역)을 제공한다.  
이로 인해 [경쟁 상태](#경쟁-상태)가 해결된다.  
임계 영역의 시작은 lock()으로 알리며 끝은 unlock()으로 알린다.  
lock()과 unlock() 사이에서 공유 변수(전역 변수, 포인터 변수 등...)를 읽거나 수정할 때는 동기화가 보장된 상태이다.  
즉 임계 영역 내에서는 [일관성 문제](#캐시-일관성-문제)가 해결된다.  
&nbsp;  

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

아직 [명령어 재배치](#명령어-재배치) 문제에 대해 다루지 않았다.  
이는 lock(), unlock()을 사용하면 자연스럽게 해결된다.  
```c++
void prevent_reorder()
{
    int x = 0;
    int y = 1;
    int z = 2;
}
```
위와 같은 함수가 있다면 x, y, z 중에 뭐가 먼저 초기화될지 알 수 없다.  
&nbsp;  

lock(), unlock()은 울타리 역할을 하기에 명령어들이 lock(), unlock()을 뛰어넘어 재배치될 수 없다.  
std::mutex를 사용한 밑 코드를 보자.  
```c++
void prevent_reorder(std::mutex &mut)
{
    int x = 0;
    mut.lock();
    mut.unlock();
    int y = 1;
    int z = 2;
}
```
여기선 명확하게 y, z보다 x가 먼저 초기화된다.  
하지만 y, z 중 어떤 것이 먼저 초기화될지 알 수 없다.  
이렇게 lock(), unlock()을 적절히 사용하여 [명령어 재배치](#명령어-재배치) 문제를 해결할 수 있다.  
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

std::mutex를 사용할 때는 유의할 점이 있는데 바로 **데드락 현상**이다.  
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

해결 방법은 wait() 함수에 Callable 조건 함수를 같이 넘기는 것이다.  
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
num.fetch_add(17); // 위 명령을 원자적으로 수행함
```
특정 연산자가 원자적인지 아닌지 헷갈린다면 확실하게 store(), load(), fetch_add() 등의 ```std::atomic```에서 공식적으로 제공하는 함수를 이용하자.  
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

```std::atomic<T>```에서 T 자리에 올 수 있는 자료형이 그렇게 많지는 않다.  
T 자료형의 크기가 x64 기준으로 128bit를 넘어가면 내부적으로 std::mutex를 이용하기에 속도가 느려진다. (x86 기준으로 64bit)  
또 클래스, 구조체의 경우 [Object Alignment](#object-alignment)를 따진다.  
&nbsp;  

x64 플랫폼을 기준으로 살펴보자.  
밑과 같은 구조체가 있다.  
```c++
struct A
{
    double x;
    double y;
}
```
크기가 딱 128bit이고 8byte 기준으로 정렬되어 있다.  
이 녀석은 lock-free하다.  
&nbsp;  

같은 맥락으로 밑과 같은 녀석도 lock-free하다.  
```c++
struct B
{
    double x;
    int y;
}
```
패딩으로 인해 실제 크기가 딱 128bit로 맞춰지기 때문이다.  
&nbsp;  

그러면 밑과 같은 경우는 어떻게 될까?  
```c++
struct C
{
    int x;
    int y;
    int z;
}
```
4byte 기준으로 정렬되기에 실제 크기는 96bit다.  
128bit를 충족하지 못하여 lock-free가 아니다.  
&nbsp;  

위와 같이 구조체의 생김새마다 동작이 달라지고 CPU마다 원자적인 명령을 내리지 못하는 자료형도 존재하기 때문에 밑과 같이 is_lock_free() 함수를 통해 알아봐야 한다.  
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

원자적인 특성 덕분에 [경쟁 상태](#경쟁-상태)는 해결이 되었다지만 [명령어 재배치](#명령어-재배치), [일관성 문제](#캐시-일관성-문제)를 해결하기 위한 방법은 아직 설명하지 않았다.  
std::atomic은 나머지 문제들을 해결할 수 있도록 다양한 옵션을 제공한다.  
각 옵션들의 특징을 알아보자.  
&nbsp;  

#### memory_order_relaxed  

제일 느슨하고 속도가 빠른 옵션이다.  
싱글 쓰레드 관점으로 결과가 동일하게 나온다는 것이 보장된다는 가정하에 해당 옵션이 사용된 명령은 마음대로 배치될 수 있다.  
즉 [경쟁 상태](#경쟁-상태)만 해결된다.  
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

#### memory_order_release, memory_order_acquire   

memory_order_relexed보다 좀 더 엄격하다.  

memory_order_release가 쓰인 라인 **이전** 명령들은 memory_order_release가 쓰인 라인 이후로 재배치될 수 없다.    
release 기능으로 해당 옵션이 사용된 명령이 수행되면 해당 명령 전에 수행되었던 명령들로 인해 바뀐 캐시 내용들이 공유 메모리에 올라간다.  

반대로 memory_order_acquire가 쓰인 라인 **이후** 명령들은 memory_order_acquire가 쓰인 라인 **이전**으로 재배치될 수 없다.  
acquire 기능으로 해당 옵션이 사용된 명령이 수행되면 공유 메모리의 정보를 가져와 해당 명령이 수행된 쓰레드의 캐시 메모리를 업데이트한다.  
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
is_ready 변수를 쓰고 읽으면서 동기화가 진행되기에 reader() 함수에서 data 값을 참조할 때 무조건 ```data = {1,2,3}``` 상태가 보장된다.   
&nbsp;  

#### memory_order_acq_rel   

memory_order_release와 memory_order_acquire를 합쳐놓은 녀석이다.  
읽기, 쓰기를 모두 사용하는 compare_exchange_weak(), fetch_add()와 같은 명령에서 사용하면 좋다.  
&nbsp;  

#### memory_order_seq_cst  

std::atomic에 아무런 옵션도 설정하지 않으면 memory_order_seq_cst가 기본으로 설정된다.  
memory_order_acq_rel, memory_order_release, memory_order_acquire 요 녀석들은 [명령어 재배치 문제](#명령어-재배치)는 해결해주지만 코어간 [캐시 일관성 문제](#캐시-일관성-문제)는 해결해주지 않는다.  
즉 CPU 코어에 따라 관측이 상대적이라 쓰레드에 따라 특정 변수의 상태가 다를 수 있다.  
memory_order_seq_cst 옵션을 사용하면 절대적인 시간선이 생겨 모든 CPU의 코어가 같은 상황을 동일한 관점에서 관측하게 된다. (모든 명령에 대한 순차적 일관성이 보장된다.)  
간단하게 보이는 코드 그대로 동작한다는 것이다.   
하지만 모든 옵션 중 가장 속도가 느리다. (특히 ARM 프로세서에서 차이가 극명하다.)   
&nbsp;  

[해당 목차](#캐시-일관성-문제)에서 살펴본 예시를 memory_order_seq_cst 옵션을 사용하여 변경해보자.  
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
    while (!x.load(std::memory_order_seq_cst));
    if (y.load(std::memory_order_seq_cst))
        ++z;
}

void read_y_then_x()
{
    while (!y.load(std::memory_order_seq_cst));
    if (x.load(std::memory_order_seq_cst))
        ++z;
}

// 동일 구현부 생략
```
절대적인 시간선이 생겨 ```write_x()``` -> ```write_y()```로 진행된다고 하면 모든 CPU 코어에서 저 순서로 관찰하게 된다.  
즉 특정 쓰레드에서 ```x: false, y: true```로 관찰되었으면 다른 모든 쓰레드에서도 x, y 값이 동일하다는 것이 보장된다.  
모든 쓰레드에서 동일한 값이 관찰되기에 z의 값이 0으로 나올 수 없다.  
단일 원자 변수 기준의 읽기, 쓰기 순서가 아니라 전역적인 읽기, 쓰기 순서를 강제하고 싶다면 memory_order_seq_cst 옵션을 사용하면 된다.  
&nbsp;  

#### 원자 연산의 특성   

위에서 거의 다 등장했지만 ```std::atomic```에서 제공하는 연산은 크게 Read, Write, RMW(Read-Modify_Write)로 나뉜다.  
Read에는 ```load()```가 속한다.  
Write에는 ```store()```가 속한다.  
RMW에는 대표적으로 ```compare_exchange_weak()```, ```fetch_add()``` 등이 속한다.  
이 중 RMW 연산은 Read 시점에 항상 갱신된 최신 값을 획득한다는 점에서 매우 유용하다.  
&nbsp;  

```load()```는 특정 쓰레드에서 원자적으로 값을 읽기는 하지만 쓰레드의 실행 순서는 예측할 수 없기 때문에 읽은 값이 어떻게 튀어나올지 모른다.  
또 캐시에 해당 값이 이미 있는 상태라면 메모리에서 읽어오지 않고 캐시에서 읽어올 수도 있기에 최신 갱신된 값을 항상 획득한다는 보장도 없다.  
그래서 ```if()```문만 사용하여 다루기 힘들고 ```while()```문을 통해 특정 값이 획득될 때까지 기다려줘야 안전하게 사용할 수 있다.  
물론 코드 문맥에 따라 memory_order 설정도 잘해줘야 한다.  

```store()```도 특정 쓰레드에서 특정 값을 원자적으로 저장해주기는 하지만 값을 저장했다고 해서 캐시 정보가 바로 메모리로 올라가지 않을뿐만 아니라 쓰레드의 실행 관측 순서를 예측할 수 없기에 언제 어떻게 값을 덮어씌울지 모른다.  
그래서 적절한 memory_order를 넘겨 동기화 시점을 확실히 해줘야 한다.  

반면 ```fetch_add()```와 같은 RMW 연산은 명확하다.  
```fetch_add()```는 ```x++```과 같이 특정 값이 더해지기 전의 값을 반환하는 함수다.   
중요한 것은 해당 반환 값은 고유하기에 각 쓰레드는 각기 다른 반환 값을 획득하는 것이 보장된다.  
이는 주어진 memory_order가 어떻든 보장된다.   
RMW 연산에서 사용되는 memory_order는 해당 원자 연산을 제외한 주변의 연산들 순서에 영향을 미치기 위해서 사용한다.  
이러한 특성으로 인해 ```if()```문과 함께 사용하여 다루기 쉽다.  
&nbsp;  

#### Lock-Free 알고리즘  

지금까지 ```std::atomic```을 다룬 이유는 결국 lock-free 기법을 이용하기 위함이다.  
std::mutex를 이용한 방식은 특정 쓰레드가 잠금을 획득하는 동안 다른 쓰레드는 아무것도 못하고 대기만 하게 된다.  
이러한 특성 때문에 특정 쓰레드는 한번도 사용되지 못하고 대기만 하는 기아현상이 발생할 수 있다.    
또 특정 쓰레드가 잠금을 획득한 상태로 죽어버리면 다른 쓰레드들은 잠금 획득을 못해 대기만 하여 프로그램이 뻗어버리는 문제도 있다.  
이러한 문제를 std::atomic을 이용한 lock-free 기법을 통해 해결할 수 있다.  

단점이라면 구현이 매우 까다롭고 약간의 헛점으로도 문제가 많이 발생하기에 lock-free 기법을 이용한 코드가 thread-safe한지 완벽한 검증이 이루어져야 한다.  
속도적인 측면에서 볼 때 lock-free 기법이 std::mutex를 이용한 lock 기법보다 평균적으로 우세하지만 그에 비해 들어가는 노력이 굉장하기 때문에 lock-free를 설계할 것이라면 퍼포먼스와 설계 시간을 잘 비교해봐야 할 것이다.  
심화 내용이니 이러한 것이 있다 정도만 이해하고 넘어가도 된다.  
더 자세한 내용을 알고 싶다면 ```C++ Concurrency in Action``` 책을 참고하자.  
&nbsp;  

기존의 ```std::stack<>```은 thread-safe하지 않다.  
스택 자료구조를 std::mutex를 이용해 만들어보고 그 후에 lock-free 기법을 이용하여 std::mutex를 이용하지 않도록 변형해보자.  
&nbsp;  

thread-safe한 스택은 연결 리스트 형태를 취한다.  
따라서 밑과 같은 노드를 이용할 것이다.  
```c++
template <typename T>
struct Node
{
    std::shared_ptr<T> data;
    std::shared_ptr<Node> next;
    Node(const T& data, std::shared_ptr<Node> next = nullptr)
    {
        this->data = std::make_shared<T>(data);
        this->next = next;
    }
};
```
&nbsp;  

std::mutex를 이용한 스택은 밑과 같다.  
```c++
template <typename T>
class lstack
{
    std::mutex mut;
    size_t m_size;
    std::shared_ptr<Node<T>> m_top;

public:
    lstack()
    {
        m_top = nullptr;
        m_size = 0;
    }

    ~lstack()
    {
        while (m_top)
            m_top = m_top->next;
    }

    size_t size()
    {
        return m_size;
    }

    bool empty()
    {
        return !size();
    }

    const T& top()
    {
        return *m_top.get()->data;
    }

    std::shared_ptr<T> pop()
    {
        std::unique_lock<std::mutex> ul(mut);
        std::shared_ptr<T> ret;
        if (empty())
            return ret;
        ret.swap(m_top->data);
        m_top = m_top->next;
        m_size--;
        return ret;
    }

    void push(const T& data)
    {
        std::unique_lock<std::mutex> ul(mut);
        m_top = std::make_shared<Node<T>>(data, m_top);
        m_size++;
    }
};
```
pop()과 push()가 mutex를 사용하여 여러 쓰레드에서 동시에 진행해도 안전하다.  
&nbsp;  

위의 lock 방식 말고 lock-free 기법을 이용한 방식으로 스택을 만들어보자.  
lock-free 기법은 CAS(Compare and Swap)를 활용한다.  
CAS는 쓰레드에 저장된 로컬 캐시 데이터와 메모리에 저장된 데이터를 비교하여 두 개가 같으면 메모리 데이터를 특정 값으로 교체하는 연산이다.   
&nbsp;  

CAS 방식을 C++에서 사용하려면 RMW 연산인 ```compare_exchange_weak()```, ```compare_exchange_strong()``` 함수를 이용해야 한다.  
내부적으로 대략 밑과 같이 구현되어 있다.  
```c++
template<typename T>
bool atomic<T>::compare_exchange_strong(T& old_var, const T& new_val)
{
    if(*this == old_var)
    {
        *this = new_val;
        return true;
    }
    old_var = *this;
    return false;
}
```
```compare_exchange_weak()```도 기능자체는 ```compare_exchange_strong()```와 같다.  
하지만 하드웨어에 따라 비정상적으로 실패할 확률이 있는데 로컬 캐시 데이터와 메모리에 저장된 데이터가 같아도 ```compare_exchange_weak()```는 false를 반환할 수 있다.  
따라서 ```compare_exchange_weak()```을 이용할 때는 무조건 반복문과 함께 사용해야 한다.  
구현부를 보면 현재 아토믹 변수가 old_var 값과 같은지 비교하여 같으면 new_val로 바꾸고 다르면 old_var를 현재 아토믹 변수의 값으로 바꾼다.   
해당 함수는 내부적으로 ```CMPXCHG```라는 어셈블리 명령으로 바뀌어 원자적이니 std::mutex를 이용하지 않고 thread-safe를 보장할 수 있다. (ARM 프로세서는 ```CMPXCHG``` 대신에 ```LL/SC```를 사용한다.)  
&nbsp;  

lock-free 스택을 구현하는 방식에는 위험 포인터, 해제 미루기, 레퍼런스 카운팅 등 여러가지가 있지만 제일 널리 쓰이는 레퍼런스 카운팅 방식만 다루겠다.  
일단 밑과 같은 노드를 이용한다.  
```c++
template<typename T>
struct CountedNode;

template <typename T>
struct CountedNodePtr
{
    std::int32_t external_cnt;
    CountedNode<T>* ptr;
};

template<typename T>
struct CountedNode
{
    std::shared_ptr<T> data;
    std::atomic_int32_t internal_cnt;
    CountedNodePtr<T> next;
    CountedNode(const T& data)
    {
        this->data = std::make_shared<T>(data);
        internal_cnt = 0;
    }
};
```
방식 이름처럼 노드 내부에 참조 개수가 존재한다.  
특이한 점은 노드 포인터에도 외부 참조 개수가 존재한다는 것이다.  
이는 실제 구현부를 보면 이해가 가겠지만 미리 설명하자면 여러 쓰레드가 같은 노드에 대한 포인터를 동시에 역참조할 수 있다.  
이 상태에서 특정 스레드가 노드 포인터를 해제하게 되면 포인터 다른 쓰레드들은 해제된 포인터에 대해 역참조를 하고 있는 상태가 되기 때문에 위험하다.  
따라서 노드 자체에 존재하는 내부 참조 카운터말고 노드 포인터와 함께 외부 참조 카운터가 존재하게 된다.  
&nbsp;  

스택 구현부는 밑과 같다.  
```c++
template<typename T>
class lfstack
{
    std::atomic<CountedNodePtr<T>> m_top;
    std::atomic_size_t m_size;

    void increase_top_cnt(CountedNodePtr<T> &old_top) // ②
    {
        CountedNodePtr<T> new_top;
        do
        {
            new_top = old_top;
            ++new_top.external_cnt;
        } while (!m_top.compare_exchange_strong(old_top, new_top));
        old_top.external_cnt = new_top.external_cnt;
    }

public:
    lfstack()
    {
        m_top = { 0,nullptr };
        m_size = 0;
    }

    ~lfstack()
    {
        CountedNodePtr<T> top = m_top.load(), next;
        while (top.ptr)
        {
            next = top.ptr->next;
            delete top.ptr;
            top = next;
        }
    }

    size_t size()
    {
        return m_size.load();
    }

    bool empty()
    {
        return !size();
    }

    const T& top()
    {
        return *m_top.load().ptr->data.get();
    }

    std::shared_ptr<T> pop()
    {
        CountedNodePtr<T> old_top = m_top.load();
        while (true)
        {
            increase_top_cnt(old_top);
            CountedNode<T>* const ptr = old_top.ptr;
            if (!ptr)
                return nullptr;

            if (m_top.compare_exchange_strong(old_top, ptr->next)) // ③
            {
                std::shared_ptr<T> ret = std::move(ptr->data);
                const std::int32_t ex_cnt_apply_to_in_cnt = old_top.external_cnt - 2;
                if (ptr->internal_cnt.fetch_add(ex_cnt_apply_to_in_cnt) == -ex_cnt_apply_to_in_cnt)
                    delete ptr;
                m_size.fetch_sub(1);
                return ret;
            }
            else if (ptr->internal_cnt.fetch_sub(1) == 1)  // ④
                delete ptr;
        }
    }

    void push(T const& data) // ①
    {
        m_size.fetch_add(1);
        CountedNodePtr<T> new_node;
        new_node.ptr = new CountedNode<T>(data);
        new_node.external_cnt = 1;
        new_node.ptr->next = m_top.load();
        while (!m_top.compare_exchange_weak(new_node.ptr->next, new_node));
    }
};
```
일단 m_top, m_size는 원자 변수이다.  
m_top에 이용된 구조체는 크기가 알맞기에 lock-free하다.  
주석에 매겨진 순서대로 분석해보자.  

일단 ①부터 보자.  
```push```하게 되는 노드는 m_top에서 참조할 것이기에 외부 참조 카운터가 1이다. (내부 카운터는 pop을 할 때 이용하기에 0으로 놔둔다.)   
lock이 없이 여러 개의 쓰레드가 동시에 push를 하려고 덤비기 때문에 이곳에서 CAS 함수인 compare_exchange_weak를 활용하는 것을 볼 수 있다.  
제일 최신의 ```new_node.ptr->next``` 변수(즉 로컬 m_top 변수)를 가진 쓰레드만이 원자적인 m_top을 교체할 수 있다.  

②는 참조 카운터 증가 함수이다.  
pop에서 로컬 변수로 노드 포인터를 이용하기에 참조 개수를 증가시켜야 하기에 해당 함수를 사용한다.  
해당 함수도 제일 최신 m_top 변수에 외부 참조 카운터의 변경을 적용해야 하기에 CAS 함수를 이용한다.  

③에서는 ```increase_top_cnt()```와 ③ 사이 로직들을 수행할 때 다른 쓰레드에서 m_top을 변경했을 수 있기에 old_top이 지금도 최신인지 확인하기 위해 CAS 함수를 사용한다.  
old_top이 최신인 것이 확인되면 m_top은 pop된 걸로 간주되어 ```ptr->next```로 변경된다.  
그리고 old_top의 데이터가 옮겨지며 내부 참조 카운터에 외부 참조 카운터 값이 적용된다.  
이때 m_top이 pop되어 1이 깎이고 pop() 함수에서 로컬로 참조하고 있던 old_top도 참조를 해제할 것이기에 1이 깎여 총 2를 추가적으로 깎아 외부 참조 카운터를 적용하게 된다.  
여기서 외부 참조를 적용한 내부 참조 카운터 값이 0이면 그대로 노드를 해제하면 된다.  
아니라면 다른 쓰레드에서 해제해줘야 한다.  

④에서는 내부 참조 카운터를 획득하여 하나를 뺀다.  
하나를 뺀 값이 0이 된다면 ③에서 노드 해제를 안했다는 것이기에 ④를 수행한 쓰레드에서 노드를 해제해준다.  
&nbsp;  

지금 lfstack을 보면 memory_order가 memory_order_seq_cst로 설정되어 최적화가 하나도 안되어 있다.  
최적화를 해보자.  
```c++
template<typename T>
class lfstack
{
    std::atomic<CountedNodePtr<T>> m_top;
    std::atomic_size_t m_size;

    void increase_top_cnt(CountedNodePtr<T> &old_top)
    {
        CountedNodePtr<T> new_top;
        do
        {
            new_top = old_top;
            ++new_top.external_cnt;
        } while (!m_top.compare_exchange_strong(old_top, new_top,
                 std::memory_order_acquire,
                 std::memory_order_relaxed)); // ④
        old_top.external_cnt = new_top.external_cnt;
    }

public:
    lfstack()
    {
        m_top = { 0,nullptr };
        m_size = 0;
    }

    ~lfstack()
    {
        CountedNodePtr<T> top = m_top.load(), next;
        while (top.ptr)
        {
            next = top.ptr->next;
            delete top.ptr;
            top = next;
        }
    }

    size_t size()
    {
        return m_size.load();
    }

    bool empty()
    {
        return !size();
    }

    const T& top()
    {
        return *m_top.load().ptr->data.get();
    }

    std::shared_ptr<T> pop()
    {
        CountedNodePtr<T> old_top = m_top.load(std::memory_order_relaxed); // ⑤
        while (true)
        {
            increase_top_cnt(old_top);
            CountedNode<T>* const ptr = old_top.ptr;
            if (!ptr)
                return nullptr;

            if (m_top.compare_exchange_strong(old_top, ptr->next,
                std::memory_order_relaxed,
                std::memory_order_relaxed)) // ⑥
            {
                std::shared_ptr<T> ret = std::move(ptr->data);
                const std::int32_t ex_cnt_apply_to_in_cnt = old_top.external_cnt - 2;
                if (ptr->internal_cnt.fetch_add(ex_cnt_apply_to_in_cnt, std::memory_order_release) == -ex_cnt_apply_to_in_cnt) // ⑦
                    delete ptr;
                m_size.fetch_sub(1, std::memory_order_relaxed); // ⑧
                return ret;
            }
            else if (ptr->internal_cnt.fetch_sub(1, std::memory_order_relaxed) == 1) // ⑨
            {
                std::int32_t&& temp = ptr->internal_cnt.load(std::memory_order_acquire); // ⑩
                delete ptr;
            }
        }
    }

    void push(T const& data)
    {
        m_size.fetch_add(1, std::memory_order_relaxed); // ①
        CountedNodePtr<T> new_node;
        new_node.ptr = new CountedNode<T>(data);
        new_node.external_cnt = 1;
        new_node.ptr->next = m_top.load(std::memory_order_relaxed); // ②
        while (!m_top.compare_exchange_weak(new_node.ptr->next, new_node, 
               std::memory_order_release,
               std::memory_order_relaxed)); // ③
    }
};
```
각 memory_order들은 그냥 정해진 것이 아니고 합당한 이유가 존재한다.  

①을 보면 m_size는 결과적으로 순서는 중요하지 않고 증가, 감소만 되면 되기에 memory_order_relaxed를 이용한다.  

②에서 m_top을 원자적 읽기로 획득하고 있는데 이는 compare_exchange_weak 함수 이전에만 발생하면 된다.  

③에서 compare_exchange_weak가 성공하면 memory_order_release, 실패하면 memory_order_relaxed로 설정하고 있다.  
실패하면 어짜피 m_top은 교체되지 않기에 push() 함수 내부의 명령 순서가 중요하지 않다.  
하지만 성공하면 m_top이 바뀌기에 new_node 설정이 모두 끝난 뒤에 compare_exchange_weak가 수행되어야 하여 memory_order_release로 설정했다.  

④에서 compare_exchange_strong가 실패하면 명령어 순서가 의미없다.  
하지만 성공하면 최신 메모리 정보도 캐시에 갱신해줘야 하고 pop() 함수 내부의 명령어들이 멋대로 compare_exchange_strong 전으로 역류하여 수행되는 것을 막아야 하기에 memory_order_acquire 옵션이 설정된다.  
이러면 old_top 변수에 대한 무결성도 보장된다.  

⑤에서 m_top을 어떻게 읽어오던 increase_top_cnt()에서 최신 m_top을 획득하기 때문에 상관없다.  

⑥에서 compare_exchange_strong은 실패하던 성공하던 명령어 순서는 의미없다.  
이미 increase_top_cnt()에서 동기화에 대한 로직은 모두 수행했다.  

⑦에서 fetch_add를 평가할 때는 ptr을 해제하는 로직으로 이어지기에 조심해야 한다.  
ret에 데이터에 ```ptr->data```가 옮겨졌다는 것을 다른 쓰레드들에게 알리기에 위해 memory_order_release가 사용되어야 한다.  

⑧에서 m_size의 값은 어디든 상관없이 감소만 되면 된다.  

⑨에서 fetch_sub에서 반환되는 값은 memory_order 상관없이 쓰레드마다 고유하기에 memory_order_relaxed로 수행해도 상관없다.  

⑩에서 ptr을 해제하기 전에 캐시 데이터를 memory_order_acquire를 이용하여 최신으로 갱신하고 가야한다.  
다른 쓰레드에서 ```std::move(ptr->data)```가 수행된 내용이 ```delete ptr```을 수행하는 쓰레드의 캐시에 갱신되지 않았을 수가 있기 때문이다.  
temp 변수는 단지 nodiscard인 load() 함수의 ```[nodiscard]``` 컴파일 경고를 없애기 위해 사용하였다. (경고가 상관없다면 temp 변수를 지워도 된다.)    

설명을 보면 알겠지만 lock-free 구조를 이용하는 것은 굉장히 어렵다.  
lock-free 구조를 구현하기 전에 꼭 사용해야 하는지 생각해보자.  
&nbsp;  

#### ABA 문제  

lock-free 구조를 설계할 때는 ABA 문제를 고려해야 한다.  
위에서 구현한 레퍼런스 카운팅 방식의 lfstack은 포인터와 참조 카운터를 함께 사용하기에 ABA 문제가 해결되어 있다.  

ABA 문제는 포인터만을 이용하여 CAS 함수를 이용할 때 발생한다.  
왜냐하면 시스템에서 할당 해제된 포인터를 재사용하기 때문이다.  

1. 현재 lock-free 스택에는 top에서 bottom까지 A, B, C 이러한 순서로 데이터가 담겨져있다.  

2. 쓰레드 1에서 pop 함수를 수행하다가 ```top.compare_exchange_weak(local_A, next)```가 진행되기 직전에 잠시 멈췄다.  
    next는 A의 다음 노드인 B를 가리키고 있다.  

3. 쓰레드 1이 멈춘 사이에 쓰레드 2에서 pop 함수를 두 번 수행하여 현재 lock-free 스택에는 C 데이터만이 담겨져있다.  

4. 쓰레드 2에서 pop된 A, B 데이터를 모두 활용하고 할당 해제한 후 새로운 D 데이터에 대해 push 함수를 수행한다.  
    특이한 점은 할당 해제된 A의 주소를 삽입된 D가 재활용하여 현재 A와 D의 주소가 같은 상황이다. 

5. 멈췄던 쓰레드 1이 진행되면서 ```top.compare_exchange_weak(local_A, next)```가 D를 가리키고 있던 top과 local_A의 주소가 같다고 판단되어 수행된다.  
    top은 해제된 B 데이터를 가리키고 있는 next 포인터로 교체된다.  

이렇게 lock-free 스택은 사용불가 상태가 되어버린다.  
이를 해결하기 위해 위에서 언급한 위험 포인터, 해제 미루기, 레퍼런스 카운팅 등의 방식이 등장한 것이다.  
&nbsp;  

#### std::atomic 이해를 위한 링크  

[Atomic operations and Memory Visibility](https://stackoverflow.com/questions/66054666/memory-order-relaxed-and-visibility)   
[RMW with Memory Order](https://stackoverflow.com/questions/40649104/fetch-add-with-acq-rel-memory-order)  
[ABA Problem](https://en.wikipedia.org/wiki/ABA_problem)  
[std::memory_order_seq_cst vs std::memory_order_acq_rel](https://stackoverflow.com/questions/12340773/how-do-memory-order-seq-cst-and-memory-order-acq-rel-differ)  
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

std::future는 내부적으로 std::condition_variable, std::mutex를 사용해 구현된 변수 동기화 구조체라고 보면된다.  
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

std::thread에서는 밑과 같이 값을 반환하는 함수를 처리하지 못한다.  
```c++
int get_partial_sum(std::vector<int> *vec, int s, int e)
{
    return std::accumulate(vec->begin() + s, vec->begin() + e, 0);
}
```
하지만 std::packaged_task를 사용하면 가능하다.  
&nbsp;  

밑은 1 ~ 9까지의 합을 3개의 쓰레드로 나누어 돌리는 예시이다.  
```c++
int get_partial_sum(std::vector<int> *vec, int s, int e)
{
    return std::accumulate(vec->begin() + s, vec->begin() + e, 0);
}

int main()
{
    std::vector<std::future<int>> futures;
    std::vector<int> ary{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<std::thread> vec;

    for (int i = 0; i < 3; i++)
    {
        std::packaged_task<int(std::vector<int> *, int, int)> task(get_partial_sum);
        futures.push_back(task.get_future());
        vec.push_back(std::thread(std::move(task), &ary, i * 3, (i + 1) * 3));
    }

    int sum = 0;
    for (auto &val : futures)
        sum += val.get();
    std::cout << sum;

    for (auto &th : vec)
        th.join();
}
```
사용법은 간단하다.  

1. std::packaged_task에 적당한 Callable을 넣어 생성한다.  
2. 생성된 std::packaged_task를 std::future에 연결한다.  
3. std::thread를 생성할 때 Callable 대신 std::packaged_task를 std::move() 함수를 통해 넘긴다.  

주의할 점은 std::packaged_task는 복사가 불가능하기에 명시적으로 std::move()를 이용하여 옮겨야 한다.  
&nbsp;  

### Async  

std::promise, std::packaged_task 이런 녀석들은 std::thread를 task 기반으로 사용할 때 도움을 주기 위한 것이라 쓰레드 생성은 결국엔 std::thread를 이용해야 한다.  
std::async는 쓰레드 생성까지 해주기 때문에 std::thread를 대체할 수 있다.  
위에서 살펴본 [예제](#packaged-task)를 std::async 사용하여 바꿔보자.  
```c++
// 동일 함수 생략

int main()
{
    std::vector<std::future<int>> futures;
    std::vector<int> ary{1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (int i = 0; i < 3; i++)
        futures.push_back(std::async(std::launch::async, get_partial_sum, &ary, i * 3, (i + 1) * 3));

    int sum = 0;
    for (auto &val : futures)
        sum += val.get();
    std::cout << sum;
}
```
std::thread를 사용할 때보다 훨씬 간결해졌다.  
단지 std::async가 전달하는 std::future를 저장했다가 값이 필요할 때 get()으로 획득하면 된다.  
궁금한 것이라면 std::async의 옵션일 것이다.  
std::async는 3가지 선택지를 제공한다.  

1. std::launch::async  
    std::async 호출시 바로 쓰레드를 생성하여 비동기적으로 작업을 수행한다.   
2. std::launch::deferred  
    std::async가 전달한 std::future 변수의 get()이나 wait() 함수가 호출될 때 쓰레드를 생성하고 동기적으로 작업을 시작한다.  
3. 아무런 옵션을 주지 않는 경우  
    어떤 정책으로 쓰레드가 생성되고 종료되는지 보장할 수 없다.  

std::async를 활용하는 경우 std::thread의 join() 함수를 std::future의 get() 함수가 대신한다고 생각하면 된다.   
&nbsp;  

## Thread Pool  

쓰레드 풀이란 쓰레드를 사용할 만큼 미리 여러개 만들어 놓은 집합이다.  
쓰레드를 이용할 때마다 그때 그때 생성하여 사용하면 되는데 왜 굳이 쓰레드 풀을 사용할까?  
쓰레드 풀을 사용할 때 얻을 수 있는 장점은 밑과 같다.  

1. **쓰레드 생성, 소멸에 대한 오버헤드가 적어진다.**  
    미리 만들어 놓은 쓰레드를 사용하기에 새 쓰레드 작업이 필요할 때마다 새로운 쓰레드를 생성하고 폐기할 필요가 없어 오버헤드가 적다.  
2. **사용할 전체 쓰레드 개수에 대한 제한을 둘 수 있다.**  
    만약 8코어 CPU를 사용 중인데 생성된 쓰레드의 개수가 20개라고 하면 12개의 쓰레드는 분명히 대기 상태에 빠지게 되고 필요없는 곳에 시스템 자원이 낭비된다.  
    차리리 8개의 쓰레드만 생성해놓고 수행해야 할 작업을 리스트에 저장해놓고 뽑아 수행하는 것이 효과적이다.  
3. **쓰레드 작업 방식을 통제할 수 있다.**  
    쓰레드 스케쥴링 방식을 유동적으로 조정할 수 있다.  
    또 특정 작업을 몇 분마다 주기적으로 수행하는 등 쓰레드 작업 방식을 정의하는 데 유연하다.  

내부적으로 별도의 thread pool을 가지고 있는 std::async는 위의 1,2번 장점은 챙길 수 있지만 3번에 대해서는 통제가 어렵기에 std::thread를 이용한 별도의 쓰레드 풀을 만들어 사용하기도 한다.  
&nbsp;  

그렇다면 thread pool을 한번 구현해보자.  
먼저 thread pool 클래스의 멤버 변수부터 보자.  
```c++
class thread_pool
{
    size_t m_thread_num;                       // 총 thread 개수
    std::vector<std::thread> m_worker_threads; // 쓰레드 보관 벡터
    std::queue<std::function<void()>> m_jobs;  // 할 일에 대한 큐
    std::condition_variable m_cv_jobs;         // 큐의 thread-safe를 위한 조건 변수
    std::mutex m_mut_job;                      // 큐의 thread-safe를 위한 뮤텍스
    bool m_stop_all;                           // 모든 쓰레드를 종료 시키는 플래그
};
```
주석에 적힌 설명 그대로다.  
제일 먼저 들어온 작업부터 처리하기 위해 std::queue를 사용했다.  
std::queue에서 작업을 참조할 때는 thread-safe해야 하기에 m_cv_jobs, m_mut_job와 같은 상호배제에 대한 변수들도 존재한다.  
&nbsp;  

생성자는 밑과 같다.  
```c++
class thread_pool
{
    // 동일 구현부 생략

  public:
    thread_pool(size_t thread_num)
        : m_thread_num(thread_num), m_stop_all(false)
    {
        m_worker_threads.reserve(m_thread_num);
        for (size_t i = 0; i < m_thread_num; i++)
            m_worker_threads.push_back(std::thread([this]() -> void { this->worker(); }));
    }
};
```
지정된 숫자만큼 쓰레드를 미리 생성한다.  
worker()는 실제 작업이 처리되는 함수로 바로 밑에서 설명한다.  
&nbsp;  

worker() 함수는 밑과 같다.  
```c++
class thread_pool
{
    // 동일 구현부 생략

  private:
    void worker()
    {
        while (true)
        {
            std::unique_lock<std::mutex> lock(m_mut_job);
            m_cv_jobs.wait(lock, [this]() -> bool { return !this->m_jobs.empty() || this->m_stop_all; });
            if (m_stop_all && m_jobs.empty())
                return;

            std::function<void()> job = std::move(m_jobs.front());
            m_jobs.pop();
            lock.unlock();

            job();
        }
    }
};
```
생산자-소비자 패턴에서 소비자에 해당한다.  
대기 상태에서 깨어날 때 작업이 있으면 처리하고 없다면 다시 잠든다.  
m_stop_all가 설정되어 있고 남아있는 작업이 없다면 그대로 종료된다.  
&nbsp;  

다음으로는 수행할 작업을 리스트에 추가하는 push_job() 함수를 알아보자.  
```c++
class thread_pool
{
    // 동일 구현부 생략

  public:
    template <typename F, typename... Args>
    std::future<std::invoke_result_t<F, Args...>> push_job(F &&func, Args &&...args)
    {
        if (m_stop_all)
            throw std::runtime_error("thread pool is in exist state!");

        using ret_type = std::invoke_result_t<F, Args...>;

        auto job = std::make_shared<std::packaged_task<ret_type()>>(std::bind(std::forward<F>(func), std::forward<Args>(args)...));
        std::future<ret_type> job_result = job.get()->get_future();

        m_mut_job.lock();
        m_jobs.push([job]() -> void { (*job)(); });
        m_mut_job.unlock();

        m_cv_jobs.notify_one();

        return job_result;
    }
};
```
템플릿이 많이 사용되어 복잡해 보이지만 하나 하나 뜯어보면 생각보다 쉽다.  
&nbsp;  

일단 작업을 넘겨줘야 하니 작업에 대한 Callable이 F 타입으로 존재한다.  
작업과 같이 넘겨줄 인수들도 템플릿 파라메터 팩 Args 타입으로 존재한다.  
```c++
template <typename F, typename... Args>
```
&nbsp;  

std::invoke_result_t을 이용해 Callable인 F 자료형의 반환 타입을 알아낸다.  
```c++
using ret_type = std::invoke_result_t<F, Args...>;
```
예를 들어 ```float add(int a, int b)```라면 여기선 ret_type은 float형이 된다.  
&nbsp;  

std::packaged_task를 생성해준다.  
```c++
auto job = std::make_shared<std::packaged_task<ret_type()>>(std::bind(std::forward<F>(func), std::forward<Args>(args)...));
```
std::packaged_task를 스마트 포인터로 동적 할당하여 push_job() 함수가 종료되어도 수명이 유지되어 m_jobs 멤버 변수에 추가된 작업 정보가 사라지지 않는다.  
std::bind()를 통해 함수의 인자를 고정시킨다.  
std::forward를 통해 불필요한 복사를 막는다.  
&nbsp;  

작업시킬 함수의 반환값을 받기 위한 std::future를 받아온다.  
```c++
std::future<ret_type> job_result = job.get()->get_future();
```
&nbsp;  

생성된 std::packaged_task를 람다 함수에 넣고 m_jobs 작업 목록에 추가시켜준다.  
```c++
m_mut_job.lock();
m_jobs.push([job]() -> void { (*job)(); });
m_mut_job.unlock();
```
std::queue는 thread-safe하지 않기에 mutex로 감싸준다.  
람다 함수에서 캡쳐를 ```[job]``` 이렇게 넘긴 이유는 std::shared_ptr의 참조 카운터를 하나 증가시키기 위해서이다.  
따라서 해당 람다 함수가 사라지지 않는 이상 생성된 std::packaged_task의 수명도 유지된다.  
&nbsp;  

m_jobs에 작업이 추가되었으니 수면 상태인 쓰레드 중 하나를 깨워 일을 시키면 된다.  
```c++
m_cv_jobs.notify_one();
```
&nbsp;  

다음은 소멸자를 보자.  
```c++
class thread_pool
{
    // 동일 구현부 생략

    ~thread_pool()
    {
        m_stop_all = true;
        m_cv_jobs.notify_all();

        for (auto &th : m_worker_threads)
            th.join();
    }
};
```
notify_all() 함수를 통해 자고 있던 나머지 쓰레드들도 같이 종료시켜준다.  
&nbsp;  

전체 코드는 밑과 같다.  
```c++
class thread_pool
{
    size_t m_thread_num;                       // 총 thread 개수
    std::vector<std::thread> m_worker_threads; // 쓰레드 보관 벡터
    std::queue<std::function<void()>> m_jobs;  // 할 일에 대한 큐
    std::condition_variable m_cv_jobs;         // 큐의 thread-safe를 위한 조건 변수
    std::mutex m_mut_job;                      // 큐의 thread-safe를 위한 뮤텍스
    bool m_stop_all;                           // 모든 쓰레드를 종료 시키는 플래그

  public:
    thread_pool(size_t thread_num)
        : m_thread_num(thread_num), m_stop_all(false)
    {
        m_worker_threads.reserve(m_thread_num);
        for (size_t i = 0; i < m_thread_num; i++)
            m_worker_threads.push_back(std::thread([this]() -> void { this->worker(); }));
    }

    ~thread_pool()
    {
        m_stop_all = true;
        m_cv_jobs.notify_all();

        for (auto &th : m_worker_threads)
            th.join();
    }

    template <typename F, typename... Args>
    std::future<std::invoke_result_t<F, Args...>> push_job(F &&func, Args &&...args)
    {
        if (m_stop_all)
            throw std::runtime_error("thread pool is in exist state!");

        using ret_type = std::invoke_result_t<F, Args...>;

        auto job = std::make_shared<std::packaged_task<ret_type()>>(std::bind(std::forward<F>(func), std::forward<Args>(args)...));
        std::future<ret_type> job_result = job.get()->get_future();

        m_mut_job.lock();
        m_jobs.push([job]() -> void { (*job)(); });
        m_mut_job.unlock();

        m_cv_jobs.notify_one();

        return job_result;
    }

  private:
    void worker()
    {
        while (true)
        {
            std::unique_lock<std::mutex> lock(m_mut_job);
            m_cv_jobs.wait(lock, [this]() -> bool { return !this->m_jobs.empty() || this->m_stop_all; });
            if (m_stop_all && m_jobs.empty())
                return;

            std::function<void()> job = std::move(m_jobs.front());
            m_jobs.pop();
            lock.unlock();

            job();
        }
    }
};
```
&nbsp;  

해당 thread_pool 클래스를 밑과 같이 활용할 수 있다.  
```c++
int add_and_print(int a, int b)
{
    printf("%d + %d = %d\n", a, b, a + b);
    return a + b;
}

struct Number
{
    int number;

    Number(int n = 0)
        : number{n}
    {
    }

    float get_and_print(float num)
    {
        printf("Number: %f\n", num);
        return num;
    }

    void operator()(int a, int b)
    {
        printf("Big Number: %d\n", std::max(std::max(a, b), number));
    }
};

int main()
{
    thread_pool pool(2);
    auto ret_1 = pool.push_job(add_and_print, 3, 4);

    Number num;
    auto ret_2 = pool.push_job(&Number::get_and_print, &num, 3.14f);

    auto ret_3 = pool.push_job(Number(10), 7, 8);

    auto ret_4 = pool.push_job([]() -> void { printf("Just Lambda...\n"); });

    int sum = ret_1.get();
    float fnum = ret_2.get();
    ret_3.get();
    ret_4.get();

    std::cout
        << "Result from add_and_print(): " << sum
        << "\nResult from get_and_print(): " << fnum;
}
```
push_job() 함수가 템플릿으로 짜여져 있어 위와 같이 다양한 Callable을 대처할 수 있다.  
&nbsp;  

## False Sharing 문제  

멀티 쓰레드 사용을 잘못하면 오히려 싱글 쓰레드를 사용할 때보다 성능이 더 하락하는 경우가 존재한다.  
밑의 예제를 보자.  
```c++
void sum(int *sum, int f, int l)
{
    for (int i = f; i < l; i++)
        *sum += 1;
}

int main()
{
    const int dest = 100000000;
    clock_t start_time, end_time;
    double result = 0;

    int multi_ret[2] = { 0, };
    int single_ret = 0;

#pragma region Single Thread Process
    start_time = clock();
    sum(&single_ret, 0, dest);
    end_time = clock();
    result = (double)(end_time - start_time) / 1e3;
    std::cout << "Sum Result : " << single_ret << '\n';
    std::cout << "Single Thread Time : " << result << "s\n\n";
#pragma endregion

#pragma region Muti Thread Process
    start_time = clock();
    std::thread th1(sum, &multi_ret[0], 0, dest / 2);
    std::thread th2(sum, &multi_ret[1], dest / 2, dest);
    th1.join();
    th2.join();
    end_time = clock();
    result = (double)(end_time - start_time) / 1e3;
    std::cout << "Sum Result : " << multi_ret[0] + multi_ret[1] << '\n';
    std::cout << "Multi Thread Time : " << result << "s\n";
#pragma endregion

    return 0;
}
```
멀티 쓰레드를 이용할 때 multi_ret 배열을 이용해 따로 계산한 뒤에 마지막에 더해주기에 별다른 문제가 없어 보인다.  
그렇다면 위 예시에서는 싱글 쓰레드보다 멀티 쓰레드가 더 빠를까?  
&nbsp;  

출력 결과는 밑과 같다.  
```
Sum Result : 100000000
Single Thread Time : 0.134s

Sum Result : 100000000
Multi Thread Time : 0.156s
```
놀랍게도 멀티 쓰레드가 더 느리다!  
이는 CPU 코어마다 한번에 읽어들이는 캐시 라인 크기과 관련이 있다.  
&nbsp;  

대부분의 CPU는 캐시 라인의 크기가 64 byte로 연속적으로 나열된 데이터들을 한번에 읽어 처리하게 된다.  
그렇다면 위 코드 예시에서 멀티 쓰레드를 사용할 때 코어 두 개의 캐시 상태는 밑과 같다.  
```
-----------------------Core 1-----------------------
|                                                  |
| multi_ret[0] | multi_ret[1] | 나머지 56 byte...   |
|                                                  |
----------------------------------------------------

-----------------------Core 2-----------------------
|                                                  |
| multi_ret[1] | 나머지 60 byte...                  |
|                                                  |
----------------------------------------------------
```
코어 1과 코어 2 모두 ```multi_ret[1]``` 이라는 같은 공간을 사용하고 있다.  
연속적인 메모리의 데이터를 64 byte 만큼 끊어 가져오기에 이렇게 나타난다.  
&nbsp;  

그렇다면 이게 속도 저하랑 무슨 연관인가?  
이렇게 같은 공간이 각기 다른 코어의 캐시 라인에 동시에 존재해 공유되면 CPU는 데이터 일관성을 위해 코어 간 캐시 동기화 작업을 진행한다.  
즉 multi_ret 배열이 사용될 때마다 코어간 동기화가 발생할 수 있는 것이다.  
이러한 동기화 작업은 [여기](#캐시-일관성-문제)에서 언급한 것처럼 값 비싼 연산이기에 싱글 쓰레드보다 더 느려진 것이다.  
이를 해결하기 위해서는 두 가지 접근 방법이 있다.  
&nbsp;  

첫번째는 Padding을 이용하여 동일한 변수가 공유되지 않도록 막는 것이다.  
```c++
// 동일 함수 생략  

int main()
{
    // 동일 구현부 생략 

    int multi_ret[17] = { 0, };

    // 동일 구현부 생략 

    std::thread th1(sum, &multi_ret[0], 0, dest / 2);
    std::thread th2(sum, &multi_ret[16], dest / 2, dest);

    // 동일 구현부 생략 

    std::cout << "Sum Result : " << multi_ret[0] + multi_ret[16] << '\n';

    // 동일 구현부 생략 

    return 0;
}
```
위와 같이 각 코어의 연산 결과가 저장될 변수들 사이에 64byte 크기의 간격을 두어 계산하게 되면 같은 변수가 각기 다른 코어의 캐시 라인에 동시에 존재할 수 없기에 동기화가 발생하지 않아 연산 속도가 월등히 빨라진다.  
그렇다면 굳이 ```int multi_ret[17] = { 0, };``` 이러한 배열을 만들지 않고 그냥 ```int ret1 = 0, ret2 = 0;``` 이렇게 해버리면 더 편하지 않나 생각할 수 있는데 int형 변수 두 개를 따로 선언을 해도 메모리에는 연속적으로 쌓일 확률이 높기에 ```int ret1 = 0, ret2 = 0;``` 이거나 ```int multi_ret[2] = { 0, };``` 이거는 False Sharing이 발생한다.  
&nbsp;  

두번째는 각 쓰레드마다 로컬 변수를 만들어 그곳에서 연산을 진행하는 것이다.  
밑과 같이 sum() 함수를 바꿔주면 된다.  
```c++
void sum(int *sum, int f, int l)
{
    int local = 0;
    for (int i = f; i < l; i++)
        local += 1;
    *sum = local;
}
```
sum() 함수 내부의 로컬 변수 local을 이용해 연산을 처리하고 있다.  
각 쓰레드 로컬 변수 간의 간격은 캐시 라인 크기보다 충분히 크기에 동기화가 발생하지 않는다.  
동기화가 발생할 수 있는 부분은 ```*sum = local;``` 라인인데 반복적으로 ```*sum``` 변수를 사용하는 것이 아니기에 속도적으로 크게 상관없다.  
&nbsp;  

C++에서는 CPU의 캐시 라인 크기를 알려주는 ```std::hardware_destructive_interference_size``` 요러한 상수값도 제공한다.  
대부분 64byte로 지정되어 있지만 특수한 디바이스를 타겟으로 만들어지는 프로그램은 캐시 라인 크기를 따로 확인해 봐야 할 것이다.  
&nbsp;  

### Object Alignment  

False Sharing은 캐시 라인의 크기에 영향을 많이 받는다.  
위에서 살펴본 예제들은 int 자료형과 같이 4byte의 고정 크기를 가지고 있는 자료형을 예로 들어 False Sharing이 어떻게 발생하는지 예측하기 쉬웠다.  
하지만 복잡한 구조체나 클래스의 경우는 어떻게 될까?  
&nbsp;  

밑과 같이 특정 구조체의 크기를 출력하는 예시가 있다.  
```c++
struct Object
{
    int num;
    char ch;
    bool boolean;
};

int main()
{
    std::cout << sizeof(Object) << "byte\n";
    return 0;
}
```
출력 결과는 int형 4byte + char형 1byte + bool형 1byte 이렇게 해서 6byte 이렇게 출력될 것 같다.  
하지만 결과는 8byte다...  
&nbsp;  

이유는 구조체나 클래스 내부의 멤버 데이터가 메모리 상에 정렬이 될 때 멤버들 중에 가장 큰 크기를 기준으로 padding 되기 때문이다.  
따라서 Object 구조체의 메모리 저장 구조는 밑과 같다.  
```
-------------------------------------------------------------------
| int [4 byte] | char [1 byte] | bool [1 byte] | padding [2 byte] |
-------------------------------------------------------------------
```
padding 부분은 컴파일러가 최적화를 위해서 임의로 채운 용량이다.  
&nbsp;  

밑과 같이 ch와 num 변수의 자리만 바꿔보자.  
```c++
struct Object
{
    char ch;
    int num;
    bool boolean;
};
```
크기가 어떻게 나올 것 같은가?  
답은 12byte다.  
4byte 정렬인 것은 기존과 동일하다.  
&nbsp;  

다만 저장 순서에 따라 크기가 바뀔 뿐이다.  
```
--------------------------------------------------------------------------------------
| char [1 byte] | padding [3 byte] | int [4 byte] | bool [1 byte] | padding [3 byte] |
--------------------------------------------------------------------------------------
```
이렇게 멤버 변수의 위치만 바뀌어도 구조체 용량이 달라진다.  
&nbsp;  

그렇다면 밑의 경우는 어떻게 될까?  
```c++
struct Child
{
    int num;
    char ch;
    bool boolean;
};

struct Parent
{
    int id;
    Child a;
};
```
Child는 제일 큰 크기인 int의 4byte로 정렬되어 총 8byte의 크기가 된다.  
Parent는 그러면 8byte로 정렬되어 16byte 크기가 될 것 같지만 아니다.  
Parent는 Child의 4byte 정렬 기준을 승계받아 동일하게 4byte로 정렬되어 12byte의 크기가 된다.  
&nbsp;  

Parent 클래스가 밑과 같이 변경된다면 어떻게 될까?  
```c++
struct Parent
{
    double id;
    Child a;
};
```
당연하게도 double의 8byte 정렬 기준이 Child의 정렬 기준보다 더 크기에 Parent 크기는 16byte가 된다.  
&nbsp;  

정렬 방식을 사용자 임의로 바꾸고 싶다면 alignas() 키워드를 이용하면 된다.  
```c++
struct alignas(8) Parent
{
    int id;
    Child a;
};
```
이렇게 하면 Parent는 기존의 4byte 정렬이 아닌 ```alignas()```로 주어진 8byte 정렬을 이용하여 크기가 16byte가 된다.  
멀티 쓰레딩을 이용할 때 인자로 구조체를 주고 받는다면 False Sharing을 방지하기 위해 Object Alignment를 꼭 생각해보자.  
&nbsp;  

# Coroutine  

코루틴이란 중단점을 가지는 함수다.  
대충 예를 들면 밑과 같이 표현할 수 있다.  
```c++
int co_func(int num)
{
    return num;
    [suspend_point 1]

    return num * 10;
    [suspend_point 2]

    return num + 5;
    [suspend_point 3]
}
```
위 함수는 중단점이 3개인 함수다.  
물론 설명을 위해 대략적인 모습을 구현한 것이지 실제 C++의 코루틴을 위와 같은 모습으로 사용한다는 것은 아니다.  
&nbsp;  

코루틴 함수 co_func()는 같은 인자를 넘기더라도 호출할 때마다 반환값이 달라진다.  
```c++
std::cout << co_func(10) << " " << co_func(10) << " " << co_func(10) << std::endl;
```
위 코드의 결과 값은 ```10 100 15```가 된다.  
즉 return으로 값을 반환한다고 함수가 완전히 종료되는 것이 아니고 중단점 전까지 수행했던 정보들을 모두 가진 상태로 코루틴 함수를 재개할 수 있다.  
코루틴을 사용하여 직관적이지 않은 재귀함수를 재귀가 없는 순회 함수로 바꿀 수도 있고 쓰레드 풀과 함께 사용하여 비동기 로직을 간략화하는 곳에 쓰이기도 한다.  
이렇게 코루틴을 잘 활용하면 다양한 곳에서 이득을 볼 수 있다.  
&nbsp;  

C++20에서는 코루틴을 공식적으로 지원한다.  
하지만 C++ 답게 기본적인 틀만 제공하고 나머지 세부적인 요소는 직접 구현해서 사용해줘야 한다.  
먼저 대략적인 사용법을 알아보자.  
밑과 같은 구조체는 필수적으로 구현해줘야 한다.  
```c++
// 코루틴 함수의 반환형은 최소한 밑과 같은 클래스 형식을 갖춰야 한다. (클래스 이름은 맘대로 지정해도 된다.)
class task
{
  public:
    // 코루틴을 이용하기 위해 promise_type 이라는 동일한 이름의 sub struct 타입이 정의되어야 한다.
    struct promise_type
    {
        // 사용자 정의 "코루틴 반환 객체"를 반환 한다
        task get_return_object()
        {
            return task{std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        // 코루틴 함수 최초 실행 시 호출된다.
        // awaitable 객체를 반환 한다.
        auto initial_suspend()
        {
            return std::suspend_always{};
        }

        // 코루틴의 마지막 반환을 나타내는 co_return을 사용하는 경우 상황에 따라 구현된다.
        auto return_void()
        {
            return;
        }

        // 코루틴 함수의 완전한 종료시 호출된다.
        auto final_suspend() noexcept
        {
            return std::suspend_always{};
        }

        // 코루틴 수행 중 예외 발생 시 호출
        void unhandled_exception()
        {
            std::exit(1);
        }
    };

    // std::coroutine_handle<promise_type> 을 인자로 받아 멤버 변수를 초기화 하는 생성자가 있어야 한다.
    task(std::coroutine_handle<promise_type> handler)
        : co_handler(handler)
    {
    }

    // 소멸자에서 std::coroutine_handle<promise_type> 타입의 코루틴 핸들러 멤버 변수의 destroy를 호출 해야 한다.
    ~task()
    {
        if (co_handler)
            co_handler.destroy();
    }

    // 코루틴 반환 자료형에는 std::coroutine_handle<promise_type> 타입의 멤버 변수가 있어야 한다.
    std::coroutine_handle<promise_type> co_handler;
};
```
구체적인 주석 설명은 추후에 다시 설명하니 구조 위주로 보자.   
모든 코루틴 함수의 반환형은 위와 같은 클래스 형태를 갖춰야 한다.  
위 클래스의 세부 구현에 따라 코루틴의 동작 결과가 달라지게 된다.  
&nbsp;  

밑과 같이 활용할 수 있다.  
```c++
task co_func()
{
    std::cout << "Hello\n";
    co_await std::suspend_always{};
    std::cout << "World\n";
}

int main()
{
    task co_task = co_func();

    std::cout << "coroutine first start!\n";

    co_task.co_handler.resume();

    std::cout << "coroutine second start!\n";

    co_task.co_handler.resume();
}
```
출력 결과는 밑과 같다.  
```text
coroutine first start!
Hello
coroutine second start!
World
```
co_func()의 중단점은 ```co_await std::suspend_always{};``` 이렇게 잡아주었다.  
코드를 보면 알겠지만 코루틴 함수를 호출한다고 무조건 수행되는 것이 아니다.  
```std::coroutine_handle<promise_type>``` 자료형의 resume() 함수를 호출해야 중단점으로 구분되어 수행된다.  
&nbsp;  

이 정도가 대략적인 사용법이고 세부적으로 들어가면 코루틴의 사용법은 크게 4가지로 나눌 수 있다.  

1. co_await을 이용하여 함수에 중단점을 찍는 방법  
2. co_yield를 이용하여 함수에 중단점을 찍으면서 값을 반환하는 방법  
3. co_return을 이용하여 함수의 마지막 중단점을 찍는 방법  
4. 코루틴 함수와 반복자를 함께 사용하는 방법  

4가지에 대해 세부적으로 알아보고 마지막으로 task 클래스를 템플릿화하는 것으로 마무리하겠다.  
&nbsp;  

## co_await  

co_await을 이용하면 코루틴 함수에 중단점을 찍을 수 있다.  
중단점에도 종류가 있는데 코루틴 함수가 멈추는 중단점은 ```std::suspend_always{};``` 요 녀석으로 설정한다.  
중단점이긴 하지만 코루틴 함수가 멈추지 않는 중단점은 ```std::suspend_never{};``` 요 녀석으로 설정한다.  
```std::suspend_always{};```, ```std::suspend_never{};``` 구조를 알면 커스텀 중단점도 만들 수 있다.  
중단점 구조체들을 awaitable 객체라고 부른다.  
먼저 ```std::suspend_always{};```와 ```std::suspend_never{};```의 차이를 간단히 알아보자.  
&nbsp;  

밑과 같은 코루틴 함수라면 resume()을 호출하면 Hello가 출력된다.   
```c++
task co_func()
{
    std::cout << "Hello ";
    co_await std::suspend_always{};
    std::cout << "World\n";
}
```
중단점에 걸려 World는 출력되지 않는다.  
resume()을 한 번 더 호출해야 World가 출력될 것이다.  
&nbsp;  

C++에 구현되어 있는 ```std::suspend_always```의 모습은 밑과 같다.  
```c++
_EXPORT_STD struct suspend_always {
    _NODISCARD constexpr bool await_ready() const noexcept {
        return false;
    }

    constexpr void await_suspend(coroutine_handle<>) const noexcept {}
    constexpr void await_resume() const noexcept {}
};
```
await_suspend(), await_resume()는 빈 껍데기일 뿐이고 await_ready()에서 false를 반환해주어 코루틴 함수가 멈춰설 수 있던 것이다.  
&nbsp;  

반면에 밑과 같이 ```std::suspend_never``` 를 사용한 코루틴 함수라면 resume() 호출시 Hello World가 모두 출력된다.  
```c++
task co_func()
{
    std::cout << "Hello ";
    co_await std::suspend_never{};
    std::cout << "World\n";
}
```
이와 같이 ```std::suspend_never```는 중단하지 않는 아이러니한 중단점이다.  
&nbsp;  

C++에 구현되어 있는 ```std::suspend_never{};```의 모습은 밑과 같다.  
```c++
_EXPORT_STD struct suspend_never {
    _NODISCARD constexpr bool await_ready() const noexcept {
        return true;
    }

    constexpr void await_suspend(coroutine_handle<>) const noexcept {}
    constexpr void await_resume() const noexcept {}
};
```
await_ready()에서 true를 반환해주어 중단점에 걸려도 그대로 통과하게 된다.  
&nbsp;  

이렇게 awaitable 객체(밑에서는 ```std::suspend_always```를 사용했다고 가정)를 만나면 컴파일러는 co_func()을 밑과 해석하게 된다.  
```c++
task co_func()
{
    std::cout << "Hello ";

    // std::suspend_always{};는 밑과 같이 바뀜
    std::suspend_always awaitable;
    if (!awaitable.await_ready())
        awaitable.await_suspend([코루틴 핸들]); // resume()이 호출되기 전까지 해당 라인에서 대기
    awaitable.await_resume();

    std::cout << "World\n";
}
```
```std::suspend_always``` 중단점이 멈췄던 이유는 await_ready() 반환값이 false이기에 await_suspend()가 호출되어서 그렇다.  
await_ready(), await_suspend(), await_resume() 함수만 구성해주면 커스텀 awaitable 객체를 만들 수도 있다.  
&nbsp;  

예를 들어 밑과 같은 awaitable이 있다고 하자.  
```c++
struct custom_suspend
{
    bool await_ready() const noexcept
    {
        std::cout << "await_ready() called in thread : " << std::this_thread::get_id() << "\n";
        return false;
    }
    void await_suspend(std::coroutine_handle<> handle) const noexcept
    {
        std::thread t([handle]() {
            handle.resume();
        });
        t.detach();
    }
    void await_resume() const noexcept
    {
        std::cout << "await_resume() called in thread : " << std::this_thread::get_id() << "\n";
    }
};
```
await_suspend() 함수가 호출되면 다른 쓰레드에서 코루틴 함수를 진행시켜버린다.  
&nbsp;  

co_func() 함수에 custom_suspend 중단점을 이용해보면 독특한 결과가 도출된다.  
```c++
task co_func()
{
    std::cout << "co_func() called in thread : " << std::this_thread::get_id() << "\n";

    co_await custom_suspend{};

    std::cout << "co_func() called in thread : " << std::this_thread::get_id() << "\n";
}

int main()
{
    task co_task = co_func();
    std::cout << "main thread id: " << std::this_thread::get_id() << "\n";
    co_task.co_handler.resume();
    std::cout << "main thread id: " << std::this_thread::get_id() << "\n";

    // await_suspend()에서 detach()된 쓰레드의 수행이 끝날 때 까지 대기하는 역할
    _sleep(10);
}
```
결과는 밑과 같다.  
```
main thread id: 12852
co_func() called in thread : 12852
await_ready() called in thread : 12852
main thread id: 12852
await_resume() called in thread : 18224
co_func() called in thread : 18224
```
이렇게 코루틴 함수의 특정 부분만 다른 쓰레드에서 수행되게 만들 수도 있다.  
&nbsp;  

## co_yield  

함수에 중단점을 찍어주는 co_await과 다르게 co_yield는 중단점을 찍어주면서 함수에서 특정 값을 반환하는 경우 사용된다.  
co_yield를 사용하려면 promise_type 구조체를 co_yield에 맞게 재정의해줘야 한다.  
[여기](#coroutine)에서 만들었던 task 클래스 내부의 promise_type 구조체를 수정해보자.  
```c++
class task
{
    // 동일 구현부 생략

    struct promise_type
    {
        // 동일 구현부 생략

        int value;

        std::suspend_always yield_value(int value)
        {
            this->value = value;
            return {};
        }
    };
};
```
yield_value() 함수의 반환형은 awaitable 객체다.  
즉 커스텀 awaitable 객체도 반환이 가능하다.   
&nbsp;  

co_yield를 이용한 함수를 만들어보자.  
```c++
task co_func()
{
    co_yield 7;
    co_yield 77;
    co_yield 777;
}
```
호출할 때마다 반환 값이 달라지는 함수다.  
&nbsp;  

사용법은 밑과 같다.  
```c++
auto func = co_func();

func.co_handler.resume();
std::cout << func.co_handler.promise().value << " ";

func.co_handler.resume();
std::cout << func.co_handler.promise().value << " ";

func.co_handler.resume();
std::cout << func.co_handler.promise().value;
```
resume()을 호출하고 promise().value를 통해 값을 획득한다.  
위 예시의 실행 결과는 ```7 77 777```이 된다.  
&nbsp;  

## co_return  

co_return은 코루틴 함수의 완전한 종료를 알리는 역할을 한다.  
완전한 종료라는 것은 코루틴 함수에 할당된 메모리 자체가 해제된다는 말이다.  
즉 co_return이 수행되면 코루틴 할당 변수가 블록을 벗어날 때 해제되며 호출되는 final_suspend() 함수가 호출된다. 
명시적으로 co_return을 꼭 해줘야 할 필요는 없고 개발자에 선택에 달렸다.  
구현할 promise_type에는 return_void()나 return_value()가 선택적으로 구현되어 있어야 한다.  
값을 반환하지 않고 코루틴 종료를 명시하고 싶다면 return_void()를 구현하고, 값을 반환하며 코루틴 종료를 명시하고 싶다면 return_value()를 구현하면 된다.  
두 함수 모두 구현해 놓을 수는 없다.  
&nbsp;  

promise_type 구조체에 return_void()는 밑과 같이 정의할 수 있다.  
```c++
class task
{
    // 동일 구현부 생략

    struct promise_type
    {
        // 동일 구현부 생략

        auto return_void()
        {
            return;
        }
    };
};
```
그냥 void 반환형 함수다.  
&nbsp;  

밑 두 함수는 동일한 역할을 한다.  
```c++
task co_func_ex()
{
    std::cout << "coroutine is good!\n";
    co_await std::suspend_always{};
    std::cout << "coroutine is hard!\n";
    co_return;
}

task co_func_im()
{
    std::cout << "coroutine is good!\n";
    co_await std::suspend_always{};
    std::cout << "coroutine is hard!\n";
}
```
즉 return_void() 함수를 이용하는 co_return은 명시적으로 적어주지 않아도 된다.  
&nbsp;  

밑과 같이 co_yield를 이용해 특정 값을 반환하는 함수에서도 ```co_return;```을 사용할 수 있다.  
```c++
task co_func()
{
    co_yield 1;
    co_yield 2;
    co_yield 3;
    co_return;
}
```
&nbsp;  

밑 처럼 co_return이 명시적으로 적히지 않은 함수에서 co_return은 언제 수행될까?  
```c++
task co_func()
{
    co_yield 1;
    co_yield 2;
    co_yield 3;
}

auto co_task = co_func();
co_task.resume();
co_task.resume();
co_task.resume();
co_task.resume();
```
co_func()는 3번의 호출까지 각기 다른 값을 반환한다.  
그 후 4번의 호출 시점에서 숨겨져 있던 ```co_return;```을 통해 return_void() 함수가 실행된다.  
&nbsp;  

특정 값을 반환하는 co_return을 만들고 싶다면 promise_type 구조체에 return_value()를 정의하면 된다.  
```c++
class task
{
    // 동일 구현부 생략

    struct promise_type
    {
        // 동일 구현부 생략

        auto return_value(int value)
        {
            this->value = value;
            return;
        }
    };
};
```
모든 원리는 return_void() 함수를 이용하는 co_return과 같고 추가적으로 값을 반환할 뿐이다.  
&nbsp;  

밑과 같은 함수에서는 3번째 resume()이 진행될 때 777을 반환하고 final_suspend() 함수가 수행될 것이다.  
```c++
task co_func()
{
    co_yield 7;
    co_yield 77;
    co_return 777;
}
```
값을 반환하는 co_return을 사용한다면 코루틴 함수에 명시적으로 co_return을 사용해줘야 한다.  
&nbsp;  

## done  

코루틴 함수에 iterator를 적용하여 배열처럼 작동하도록 만들 수 있다.  
밑과 같은 코루틴 반환 클래스가 존재한다.  
```c++
class ary_task
{
  public:
    struct promise_type
    {
        int value;

        ary_task get_return_object()
        {
            return ary_task{std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        auto initial_suspend()
        {
            return std::suspend_always{};
        }

        auto return_void()
        {
            return;
        }

        auto final_suspend() noexcept
        {
            return std::suspend_always{};
        }

        void unhandled_exception()
        {
            std::exit(1);
        }

        auto yield_value(int value)
        {
            this->value = value;
            return std::suspend_always{};
        }
    };

    ary_task(std::coroutine_handle<promise_type> handler)
        : co_handler(handler)
    {
    }

    ~ary_task()
    {
        if (co_handler)
            co_handler.destroy();
    }

    std::coroutine_handle<promise_type> co_handler = nullptr;
};
```
int 형을 반환하는 코루틴 함수에 맞춰 구현되었다.  
&nbsp;  

밑과 같이 범위에 대한 수를 반환하는 함수가 있다.  
```c++
ary_task create_ranged_ary(int first, int last)
{
    for (int i = first; i <= last; i++)
        co_yield i;
}
```
create_ranged_ary(1, 10)이라면 호출할 때마다 1,2...10까지 계속해서 반환 값이 바뀔 것이다.  
&nbsp;  

create_ranged_ary() 함수를 배열처럼 사용해보자.  
```c++
auto range_task = create_ranged_ary(1, 10);
while (true)
{
    range_task.co_handler.resume();
    if (range_task.co_handler.done())
        break;
    std::cout << range_task.co_handler.promise().value << ' ';
}
```
done() 함수는 final_suspend()가 호출되었다면 true 값을 반환한다.  
11번째 resume()이 수행되는 시점에 co_return을 통해 final_suspend()가 호출되니 출력 값은 ```1 2 3 4 5 6 7 8 9 10```가 될 것이다.  
&nbsp;  

더 나아가 iterator를 적용해 범위 기반 for문에서도 사용할 수 있게 만들자.  
먼저 ary_task 클래스 내부에 iterator를 정의해준다.  
```c++
class task
{
    // 동일 구현부 생략

    class iterator
    {
        std::coroutine_handle<promise_type> co_handler;

      public:
        iterator(std::coroutine_handle<promise_type> handler)
            : co_handler(handler)
        {
        }

        const int &operator*() const
        {
            return co_handler.promise().value;
        }

        iterator &operator++()
        {
            co_handler.resume();
            if (co_handler.done())
                co_handler = nullptr;
            return *this;
        };

        void operator++(int)
        {
            ++*this;
        }

        bool operator!=(const iterator &r) const
        {
            return co_handler != r.co_handler;
        }
    };

    iterator begin()
    {
        if (co_handler)
        {
            co_handler.resume();
            if (co_handler.done())
                return {nullptr};
        }
        return {co_handler};
    }

    iterator end()
    {
        return {nullptr};
    }
};
```
코루틴 iterator를 구성할 때 주의해야할 것은 done() 함수의 사용 시점이다.  
위 코드에서도 resume()을 사용한 뒤 꼭 done() 함수로 체크하는 것을 볼 수 있다.  
&nbsp;  

이렇게 iterator가 구현되었다면 밑과 같이 사용할 수 있다.  
```c++
for (auto iter = range_task.begin(); iter != range_task.end(); ++iter)
    std::cout << *iter << ' ';

for (auto value : range_task)
    std::cout << value << ' ';
```
range_task는 함수지만 마치 배열처럼 사용되고 있다.  
&nbsp;  

## 템플릿 적용  

템플릿을 이용해 코루틴 반환 클래스를 구현해보자.  
```c++
template <typename T, class AWAITABLE = std::suspend_always>
class task
{
  private:
    class Impl;

    struct promise_base
    {
        auto initial_suspend()
        {
            return AWAITABLE{};
        }

        auto final_suspend() noexcept
        {
            return AWAITABLE{};
        }

        void unhandled_exception()
        {
            std::exit(1);
        }
    };

    template <typename U>
    struct promise_child : public promise_base
    {
        U value;

        task get_return_object()
        {
            return task{std::make_shared<Impl>(std::coroutine_handle<promise_child>::from_promise(*this))};
        }

        template <typename R>
        void return_value(R &&val)
        {
            value = std::forward<R>(val);
        }

        template <typename R>
        auto yield_value(R &&val)
        {
            value = std::forward<R>(val);
            return AWAITABLE{};
        }
    };

    template <>
    struct promise_child<void> : public promise_base
    {
        task get_return_object()
        {
            return task{std::make_shared<Impl>(std::coroutine_handle<promise_child>::from_promise(*this))};
        }

        void return_void()
        {
        }
    };

  public:
    using promise_type = typename promise_child<T>;

    class iterator
    {
        std::coroutine_handle<promise_type> handler;

      public:
        iterator(std::coroutine_handle<promise_type> handler)
            : handler(handler)
        {
        }

        template <typename R = T>
        std::enable_if_t<std::is_same_v<R, T> && !std::is_void_v<R>, const R &> operator*() const
        {
            return handler.promise().value;
        }

        iterator &operator++()
        {
            handler.resume();
            if (handler.done())
                handler = nullptr;
            return *this;
        };

        void operator++(int)
        {
            ++*this;
        }

        bool operator!=(const iterator &r) const
        {
            return handler != r.handler;
        }
    };

    iterator begin()
    {
        if (!resume() || done()) // co_return만 있는 함수를 위해 operator++() 수행을 방지해야 함
            return {nullptr};
        return {handle()};
    }

    iterator end()
    {
        return {nullptr};
    }

    task()
        : impl(nullptr)
    {
    }

    task(std::shared_ptr<Impl> impl)
        : impl(impl)
    {
    }

    task(const task &other)
        : impl(other.impl)
    {
    }

    bool done() const
    {
        return !impl || !impl->handle || impl->handle.done();
    }

    bool resume() const
    {
        if (done())
            return false;
        impl->handle.resume();
        return true;
    }

    promise_type &promise()
    {
        return impl->handle.promise();
    }

    std::coroutine_handle<promise_type> handle() const
    {
        return impl->handle;
    }

    template <typename R = T>
    std::enable_if_t<std::is_same_v<R, T> && !std::is_void_v<R>, const R &> value()
    {
        return promise().value;
    }

  private:
    class Impl
    {
      public:
        Impl(std::coroutine_handle<promise_type> handle)
            : handle(handle)
        {
        }

        ~Impl()
        {
            if (handle)
                handle.destroy();
        }

        std::coroutine_handle<promise_type> handle;
    };

    std::shared_ptr<Impl> impl;
};
```
코루틴 반환형에 대한 클래스의 구조가 길어졌는데 이는 promise_type에서 return_void()와 return_value()를 함께 정의하지 못하는 문제를 피해가기 위해 pimpl 패턴을 사용했기 때문이다.  
복잡해 보이지만 뜯어보면 이해하기 쉽다.  
value()와 operator*()는 템플릿 인자가 void인 경우에 std::enable_if_t를 통해 비활성화 된다.  
&nbsp;  

## 활용  

코루틴을 어떻게 사용하는지 알았으니 이제 어디다가 활용할 수 있는지를 알아보자.  
&nbsp;  

### 반복문에서의 활용  

코루틴을 이용하면 함수를 배열처럼 이용할 수 있다.  
```c++
task<void> void_func()
{
    std::cout << "coroutine\n";
    co_await std::suspend_always{};
    std::cout << "is\n";
    co_await std::suspend_always{};
    std::cout << "good\n";
}

task<int> int_func()
{
    co_yield 1;
    co_yield 2;
    int num = 3;
    co_yield num;
    co_return 4;
}

int main()
{
    auto void_task = void_func();
    for (auto iter = void_task.begin(); iter != void_task.end(); iter++)
        ;

    auto int_task = int_func();
    for (const auto &num : int_task)
        std::cout << num << " ";
    std::cout << int_task.value();
}
```
한 가지 유의점이라면 위에서 구현한 task 클래스에서 void 자료형이 아닌 코루틴 함수는 return_void() 대신에 return_value()가 정의되어 있기에 co_return을 생략할 수 없어 반드시 아무 값이라도 co_return에 넘겨 명시해줘야 한다.  
&nbsp;  

결과 출력 값은 밑과 같다.  
```
coroutine
is
good
1 2 3 4
```
&nbsp;  

### Callback Hell 벗어나기  

Boost.Asio와 같은 통신 API를 이용하다보면 Callback 인자를 넘기는 함수들을 매우 많이 쓰게 되는데 코드의 가독성이 굉장히 떨어진다.  
&nbsp;  

예를 들어 밑과 같은 사칙연산 Callback들이 존재한다고 해보자.  
```c++
void SomeFuncWithAddCallBack(int one, int two, std::function<void(int)> print_func)
{
    print_func(one + two);
}

void SomeFuncWithSubCallBack(int one, int two, std::function<void(int)> print_func)
{
    print_func(one - two);
}

void SomeFuncWithMultCallBack(int one, int two, std::function<void(int)> print_func)
{
    print_func(one * two);
}

void SomeFuncWithDivCallBack(int one, int two, std::function<void(int)> print_func)
{
    print_func(one / two);
}
```
각 함수의 내부 구현은 간단하지만 비동기로 동작해야 한다고 가정하자.  
예를 들어 ```SomeFuncWithAddCallBack()``` 함수는 one과 two 더하기가 끝난 후 다른 쓰레드에서 ```print_func()``` 함수가 수행이 되는 상황이라고 생각해보자.  
&nbsp;  

이러한 상황에서 더하기, 빼기, 곱하기, 나누기를 순차적으로 수행시키고 싶다면 밑과 같은 구현을 생각할 수 있다.  
```c++
int one = 12, two = 4;
SomeFuncWithAddCallBack(one, two, [&](int result)
                        {
                            std::cout << one << " + " << two << " = " << result << "\n";

                            SomeFuncWithSubCallBack(one, two, [&](int result)
                                                    {
                                                        std::cout << one << " - " << two << " = " << result << "\n";

                                                        SomeFuncWithMultCallBack(one, two, [&](int result)
                                                                                 {
                                                                                     std::cout << one << " * " << two << " = " << result << "\n";

                                                                                     SomeFuncWithDivCallBack(one, two, [&](int result)
                                                                                                             {
                                                                                                                 std::cout << one << " / " << two << " = " << result << "\n";
                                                                                                             });
                                                                                 });
                                                    });
                        });
```
위와 같이 Callback 내부의 Callback이 즐비하여 가독성이 떨어진다.  
&nbsp;  

```
12 + 4 = 16
12 - 4 = 8
12 * 4 = 48
12 / 4 = 3
```
출력 결과는 위와 같다.  
Callback이 비동기이기에 순차적인 진행을 위해서 Callback 내부에 다음에 수행되어야 할 로직을 계속 적어나가야 하기에 구현이 늘어진다.  
&nbsp;  

코루틴을 사용하면 이런 Callback Hell 현상을 직관적으로 해결할 수 있다.  
먼저 기존 함수를 Wrapping하는 awaitable 객체들을 정의해줘야 한다.  
```c++
struct AddTask
{
    int one, two;

    bool await_ready() const noexcept
    {
        return false;
    }
    void await_suspend(std::coroutine_handle<> handle) const noexcept
    {
        SomeFuncWithAddCallBack(one, two, [&](int result)
                                {
                                    std::cout << one << " + " << two << " = " << result << "\n";
                                    handle.resume();
                                });
    }
    void await_resume() const noexcept
    {
    }
};

struct SubTask
{
    int one, two;

    bool await_ready() const noexcept
    {
        return false;
    }
    void await_suspend(std::coroutine_handle<> handle) const noexcept
    {
        SomeFuncWithSubCallBack(one, two, [&](int result)
                                {
                                    std::cout << one << " - " << two << " = " << result << "\n";
                                    handle.resume();
                                });
    }
    void await_resume() const noexcept
    {
    }
};

struct MultTask
{
    int one, two;

    bool await_ready() const noexcept
    {
        return false;
    }
    void await_suspend(std::coroutine_handle<> handle) const noexcept
    {
        SomeFuncWithMultCallBack(one, two, [&](int result)
                                {
                                    std::cout << one << " * " << two << " = " << result << "\n";
                                    handle.resume();
                                });
    }
    void await_resume() const noexcept
    {
    }
};

struct DivTask
{
    int one, two;

    bool await_ready() const noexcept
    {
        return false;
    }
    void await_suspend(std::coroutine_handle<> handle) const noexcept
    {
        SomeFuncWithDivCallBack(one, two, [&](int result)
                                {
                                    std::cout << one << " / " << two << " = " << result << "\n";
                                    handle.resume();
                                });
    }
    void await_resume() const noexcept
    {
    }
};
```
중요한 부분은 ```await_suspend()``` 함수에 넘겨지는 Callback 함수 내부에서 ```handle.resume()```를 수행하여 코루틴 함수가 자동으로 다음 Task를 수행하도록 만들어주고 있다는 것이다.  
즉 현재 Task가 끝나는 시점에 맞춰 다음 Task에게 시작 신호를 주어 세부적인 구현을 다음 Task에게 넘겨줄 수 있어 코드 분업화가 더 잘된다.  
&nbsp;  

최종적으로 밑과 같이 위에서 정의한 awaitable 객체들을 이용해주면 된다.  
```c++
task<void> CoFunc()
{
    int one = 12, two = 4;
    co_await AddTask{ one, two };
    co_await SubTask{ one, two };
    co_await MultTask{ one, two };
    co_await DivTask{ one, two };
}

auto co_func = CoFunc();
co_func.resume();
```
내부적으로는 Callback을 이용하고 있지만 코루틴을 이용하면 겉에서 티가 나지도 않고 출력 결과도 동일하며 코드 이해가 직관적으로 된다.  