# State Pattern  

밑과 같은 상황을 생각해보자.  
```
졸음 --- 잠자기 ---> 정신이 듦
```
여기서 ```졸음```, ```정신이 듦```은 상태고 ```잠자기```는 동작이라고 볼 수 있다.  
위 예시처럼 ```상태가 동작을 제어하고, 상태는 바뀔 수 있다.```라는 아이디어에서 시작된 패턴이 상태 패턴이다.  

모든 행위가 특정 **상태**로 정의될 수 있다면 상황을 통제하기 굉장히 쉬워진다.  
정의되지 않은 상태는 발생하지 않으므로 안정적이다.  
주로 컴파일러, 임베디드, 게임 AI 등에 많이 활용된다.  

상태 패턴은 크게 두 가지 구현법으로 나뉜다.  

1. 동작이 정의된 실제 클래스를 상태로 사용한다.  
    해당 동작들은 상태가 변경될 때 클래스의 변화에 따라 변경된다.  

1. 상태, 동작을 enum과 같은 특정 식별자의 나열로 정의한다.  
    실제 동작에 대한 로직은 상태 기계(State Machine)라는 컴포넌트를 두어 수행한다.  

두 방식 모두 괜찮은 접근법이다.  
하지만 두 번째 방식이 훨씬 많이 사용된다.  
&nbsp;  

## Boost.MSM  

Boost의 [Meta State Machine(MSM)](https://www.boost.org/doc/libs/1_82_0/libs/msm/doc/HTML/index.html)은 상태를 표현하기 위해 유용한 [UML StateChart](https://en.wikipedia.org/wiki/UML_state_machine)를 코드에 적용하기 위해 탄생한 라이브러리이다.  
UML을 이용한 상태를 다루기에 간단한 상태부터 굉장히 복잡한 상태까지 모두 C++로 표현이 가능하다.  

MSM은 크게 [front-end](https://www.boost.org/doc/libs/1_82_0/libs/msm/doc/HTML/ch03s02.html)와 [back-end](https://www.boost.org/doc/libs/1_82_0/libs/msm/doc/HTML/ch03s05.html)로 나뉜다.  
front-end는 상태 구조체를 정의하는 부분이고 back-end는 구현된 상태 구조체를 실제로 사용하는 부분이다.  
front-end, back-end는 서로 맞물려 돌아가야 하기에 혼용해서 설명하겠다.  
&nbsp;  

### 음악 플레이어 예시  

아주 기초적인 MSM 예시를 보자.  
```c++

```
&nbsp;  

### SubState  

자식 상태.
그냥 상태 만들듯이 만들면 됨.

&nbsp;  

### Base State  

상태에서 특정 base class를 상속할 수 있음
특정 클래스의 함수를 계속해서 이용하게 되는 경우 코드량을 줄이기 위해 사용됨
또 상태에서 visitor 함수를 호출하기 위해 사용되기도 함

&nbsp;  

### 상태 생성자  

상태 생성자를 만들어 특정 인자를 넘겨 미리 생성해둘수 있음

### Flag   

Orthogonal State인 경우 AND로 검사 가능

&nbsp;  

### Orthogonal State  

CAPS LOCK과 Insert 각 키가 눌릴 때의 상태는 서로에게 영향을 주지 않는다.  
이렇게 동시 상태가 존재하는 경우 사용하게 됨.
위의 경우 조합이기에 총 4가지 상태가 있을 수 있음

&nbsp;  

### Deffered State  

현재 상태와 상관 없는 이벤트를 요청하면 큐에 담고있다가 deffered 상태 풀리면 바로 처리하는 기능

&nbsp;  

### History  

ShallowHistory는 특정 이벤트 발생시에만 substate가 어디서 끊겼는지 기억해서 거기서 재개
AlwaysHistroy는 어떤 이벤트가 발생하던 substate가 어디서 끊겼는지 기억해서 거기서 재개

&nbsp;  

### Internal transition  

내부 상태.
기본 상태와 다른 점이라면 전이될 목표 상태가 따로 없음
기본 상태보다 내부 상태 호출이 우선순위임.
목표가 없기에 일부 action, guard만 수행하기에 유용함.