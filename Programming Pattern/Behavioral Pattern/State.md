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

### CD Player 예시  

아주 기초적인 MSM 예시를 보자.  
UML을 보기 전에 등장할 용어에 대해 알아야 한다.  
* Event  
    ```시작 상태``` ----> ```끝 상태```로 전이를 일으키는 이벤트를 뜻한다.  
    trigger 역할을 하기에 이벤트가 없으면 상태는 변하지 않는다.  
    **E**로 표시하겠다.  

* Guard  
    ```시작 상태``` ----> ```끝 상태```로 전이가 가능한지 불가능한지 Guard가 반환 하는 값을 통해 알 수 있다.  
    Guard가 false를 반환한다면 이벤트가 발생해도 ```시작 상태```에 머무른다.  
    true를 반환해야만 ```끝 상태```로 전이될 수 있다.  
    **G**로 표시하겠다.  

* Action  
    ```시작 상태``` ----> ```끝 상태```로 전이가 확정된 경우 발생하는 동작을 의미한다. (상태가 아니라 특정 동작이다.)   
    전이 중간에 수행되기에 ```시작 상태``` --- ```Action``` ---> ```끝 상태``` 이러한 순서라고 보면된다.  
    **A**로 표시하겠다.  

먼저 UML은 밑과 같이 생겼다.  
```mermaid
---
title : CD Player UML
---

stateDiagram-v2
    [*] --> Empty
    Empty --> Open: E﹕open_close\nA﹕open_drawer
    Open --> Empty: E﹕open_close\nA﹕close_drawer
    Paused --> Open: E﹕open_close\nA﹕stop_and_open
    Playing --> Paused: E﹕pause\nA﹕pause_playback
    Playing --> Open: E﹕open_close\nA﹕stop_and_open
    Paused --> Playing: E﹕end_pause\nA﹕ResumePlayback\nG﹕AlwaysReturnTrue
    Stopped --> Stopped: E﹕stop\nA﹕stopped_again
    Stopped --> Open: E﹕open_close\nA﹕open_drawer
    Stopped --> Playing: E﹕play\nA﹕start_playback
    Paused --> Stopped: E﹕stop\nA﹕stop_playback
    Empty --> Stopped: E﹕cd_detected\nA﹕store_cd_info\nG﹕good_disk_format
    Empty --> Playing: E﹕cd_detected\nA﹕store_cd_info\nG﹕auto_start
    Playing --> Stopped: E﹕stop\nA﹕stop_playback
```
UML을 잘 보면 Empty에서 발생되는 cd_detected 이벤트로만 Playing, Stopped 두 개로 이어지는데 이러면 충돌이 날 수 있다.  
이러한 충돌을 방지하려고 auto_start라는 Guard가 false를 반환해 Empty에서 Playing으로 연결되는 trigger인 cd_detected 이벤트를 비활성화한다.  
&nbsp;  

위 UML 관계가 정의된 코드는 밑과 같다.  
```c++
// back-end header
#include <boost/msm/back/state_machine.hpp>

// front-end header
#include <boost/msm/front/state_machine_def.hpp>

// funtor row type header
#include <boost/msm/front/functor_row.hpp>

#pragma region 이벤트 정의
struct play
{
};

struct end_pause
{
};

struct stop
{
};

struct pause
{
};

struct open_close
{
};

// 좀 더 복잡한 이벤트들은 이벤트 객체에 특정 데이터가 같이 들어감.
enum DiskTypeEnum
{
    DISK_CD = 0,
    DISK_DVD = 1
};
struct cd_detected
{
    cd_detected(std::string name, DiskTypeEnum diskType)
        : name(name),
          disc_type(diskType)
    {
    }

    std::string name;
    DiskTypeEnum disc_type;
};
#pragma endregion

// front-end: Finite State Machine(FSM)이 정의된 player_ 객체
// boost::msm::front::state_machine_def<자기 자신>를 상속하여 지정할 수 있다.
struct player_ : public boost::msm::front::state_machine_def<player_>
{
    // FSM 객체를 start() 함수로 호출하면 on_entry() 함수가 작동
    template <class Event, class FSM>
    void on_entry(Event const &, FSM &)
    {
        std::cout << "entering: Player" << std::endl;
    }

    // FSM 객체를 stop() 함수로 호출하면 on_exit() 함수가 작동
    template <class Event, class FSM>
    void on_exit(Event const &, FSM &)
    {
        std::cout << "leaving: Player" << std::endl;
    }

#pragma region FSM 객체에서 사용하는 상태 정의
    // Empty 상태
    // 모든 상태는 boost::msm::front::state<>를 상속해야 한다.
    struct Empty : public boost::msm::front::state<>
    {
        // 상태에 진입하면 on_entry() 함수가 호출됨
        // 인자의 의미는 밑과 같음
        // Event => play, end_pause와 같은 이벤트 객체, 자신의 on_entry() 함수를 호출한 이벤트가 위치한다.  
        // FSM => 해당 상태를 호출한 FSM 객체, 여기선 player_
        template <class Event, class FSM>
        void on_entry(Event const &, FSM &)
        {
            std::cout << "entering: Empty" << std::endl;
        }

        // 상태에서 빠져나가면 on_exit() 함수가 호출됨
        template <class Event, class FSM>
        void on_exit(Event const &, FSM &)
        {
            std::cout << "leaving: Empty" << std::endl;
        }
    };

    // Open 상태
    struct Open : public boost::msm::front::state<>
    {
        template <class Event, class FSM>
        void on_entry(Event const &, FSM &)
        {
            std::cout << "entering: Open" << std::endl;
        }
        template <class Event, class FSM>
        void on_exit(Event const &, FSM &)
        {
            std::cout << "leaving: Open" << std::endl;
        }
    };

    // Stop 상태
    struct Stopped : public boost::msm::front::state<>
    {
        template <class Event, class FSM>
        void on_entry(Event const &, FSM &)
        {
            std::cout << "entering: Stopped" << std::endl;
        }
        template <class Event, class FSM>
        void on_exit(Event const &, FSM &)
        {
            std::cout << "leaving: Stopped" << std::endl;
        }
    };

    // Playing 상태
    struct Playing : public boost::msm::front::state<>
    {
        template <class Event, class FSM>
        void on_entry(Event const &, FSM &)
        {
            std::cout << "entering: Playing" << std::endl;
        }
        template <class Event, class FSM>
        void on_exit(Event const &, FSM &)
        {
            std::cout << "leaving: Playing" << std::endl;
        }
    };

    // Paused 상태
    // on_entry(), on_exit()를 필수로 구현할 필요는 없다.
    struct Paused : public boost::msm::front::state<>
    {
    };
#pragma endregion

    // FSM이 start() 함수로 시작되고 어느 상태에 놓이는지 결정함.
    // initial_state를 특정 상태 자료형으로 정의해주면 됨.
    // 즉 player_는 생성되면 Empty 상태에 놓임.
    using initial_state = Empty;

#pragma region Action Callable 정의
    // 밑에 정의된 Callable들은 Action으로 [시작 상태] ---> [끝 상태] 이렇게 변할 때 그 사이에서 수행되는 동작이라고 보면 된다.
    // 즉 [시작 상태]가 [끝 상태]로 도달하는 것이 확정되면 Action은 [끝 상태] 도달 전에 발생하고 그 후에 현재 상태는 [끝 상태]에 도달한다.
    void start_playback(play const &)
    {
        std::cout << "player::start_playback\n";
    }
    void open_drawer(open_close const &)
    {
        std::cout << "player::open_drawer\n";
    }
    void close_drawer(open_close const &)
    {
        std::cout << "player::close_drawer\n";
    }
    void store_cd_info(cd_detected const &)
    {
        std::cout << "player::store_cd_info\n";
    }
    void stop_playback(stop const &)
    {
        std::cout << "player::stop_playback\n";
    }
    void pause_playback(pause const &)
    {
        std::cout << "player::pause_playback\n";
    }
    void stop_and_open(open_close const &)
    {
        std::cout << "player::stop_and_open\n";
    }
    void stopped_again(stop const &)
    {
        std::cout << "player::stopped_again\n";
    }

    // 이렇게 Funtor를 정의해서 사용할 수도 있다.
    // 각 operator() 인자의 의미는 다음과 같다.
    // Evt -> 해당 Action과 관련된 이벤트
    // Fsm -> ResumePlayback를 호출한 FSM 객체
    // SourceState -> 시작 상태 객체
    // TargetState -> 끝 상태 객체
    struct ResumePlayback
    {
        template <class Fsm, class Evt, class SourceState, class TargetState>
        void operator()(Evt const &, Fsm &fsm, SourceState &src, TargetState &)
        {
            std::cout << "player::resume_playback\n";
        }
    };
#pragma endregion

#pragma region Guard Callable 정의
    // Guard Callable은 특정 상태가 다른 상태로 이동할 수 있는지 조건을 검사하는 곳에 이용되는 Callable이다.
    // Callable의 반환형은 bool 자료형이여야 하며 Guard Callable의 인자는 상태 전이 시 사용된 이벤트 객체여야 한다.

    // good_disk_format() 함수는 cd_detected 이벤트에 DISK_CD가 담겨져서 전달되지 않으면 다음 상태로 이동하는 것을 막는 역할을 한다.
    bool good_disk_format(cd_detected const &evt)
    {
        if (evt.disc_type != DISK_CD)
        {
            std::cout << "wrong disk, sorry" << std::endl;
            return false;
        }
        return true;
    }
    // 이벤트가 동일해 충돌이 발생하는 경우 Guard Callable에서 false를 반환하여 이를 방지할 수 있다.
    bool auto_start(cd_detected const &)
    {
        return false;
    }

    // Guard Callable도 Action Callable과 마찬가지로 Funtor를 이용할 수 있다.
    struct AlwaysReturnTrue
    {
        template <class EVT, class FSM, class SourceState, class TargetState>
        bool operator()(EVT const &, FSM &fsm, SourceState &, TargetState &)
        {
            return true;
        }
    };
#pragma endregion

#pragma region 상태 전이 테이블 정의
    // 상태와 상태를 연결하는 방식은 밑과 같이 boost::mpl::vector의 템플릿 인자로 넘겨 이루어진다.
    // 템플릿 인자로 넘기는 방식은 두 가지가 존재한다.
    // 1. Basic 방식
    // Basic 방식에서는 함수를 이용하며 row, a_row, g_row, _row 이렇게 4가지를 활용할 수 있다.
    // 1-1. _row (액션와 가드 모두 없음)
    // Stopped 상태에서 play 이벤트가 발생할 때 Open 상태로 변경되는 관계 => _row<Stopped, play, Open>
    //
    // 1-2. a_row (액션만 있음)
    // Stopped 상태에서 play 이벤트가 발생할 때 Open 상태로 변경되는 관계, 변경 시에 player_::open 함수가 수행됨 => a_row<Stopped, play, Open, &player_::open>
    //
    // 1-3. g_row (가드만 있음)
    // Stopped 상태에서 play 이벤트가 발생할 때 Open 상태로 변경되는 관계, 상태 전이가 가능한지 검사하는 player_::can_open 함수가 존재함 => g_row<Stopped, play, Open, &player_::can_open>
    //
    // 1-4. row (액션, 가드 모두 있음)
    // Stopped 상태에서 play 이벤트가 발생할 때 Open 상태로 변경되는 관계, 상태 전이가 가능한지 검사하는 player_::can_open 함수가 존재함, 변경 시에 player_::open 함수가 수행됨 => g_row<Stopped, play, Open, &player_::open, &player_::can_open>
    //
    // 2. Funtor 방식
    // Funtor 방식에서는 이름 그대로 함수가 아니고 Funtor를 이용하며 boost::msm::front::Row만 존재한다.
    // Boost에서는 Funtor 방식을 추천한다.
    // Row의 인자 순서는 Row<시작 상태, 이벤트, 끝 상태, 액션 Funtor, 가드 Funtor> 와 같다.
    // 만약 인자 중 하나라도 빠져야 한다면 boost::msm::front::none을 이용하면 된다.
    // Stopped 상태에서 play 이벤트가 발생할 때 Open 상태로 변경되는 관계 => Row<Stopped, play, Open, boost::msm::front::none, boost::msm::front::none>

    struct transition_table : boost::mpl::vector<
                                  a_row<Stopped, play, Playing, &player_::start_playback>,
                                  a_row<Stopped, open_close, Open, &player_::open_drawer>,
                                  _row<Stopped, stop, Stopped>,
                                  a_row<Open, open_close, Empty, &player_::close_drawer>,
                                  a_row<Empty, open_close, Open, &player_::open_drawer>,
                                  row<Empty, cd_detected, Stopped, &player_::store_cd_info, &player_::good_disk_format>,
                                  row<Empty, cd_detected, Playing, &player_::store_cd_info, &player_::auto_start>,
                                  a_row<Playing, stop, Stopped, &player_::stop_playback>,
                                  a_row<Playing, pause, Paused, &player_::pause_playback>,
                                  a_row<Playing, open_close, Open, &player_::stop_and_open>,
                                  boost::msm::front::Row<Paused, end_pause, Playing, ResumePlayback, AlwaysReturnTrue>,
                                  a_row<Paused, stop, Stopped, &player_::stop_playback>,
                                  a_row<Paused, open_close, Open, &player_::stop_and_open>>
    {
    };
#pragma endregion

    // 정의되지 않은 상태 전이는 밑 함수가 받게 된다.
    // 인자 중 state는 상태에게 할당된 인덱스를 의미한다.
    // 해당 상태 인덱스 규칙은 pstate() 함수를 설명한 주석에서 다룬다.
    template <class FSM, class Event>
    void no_transition(Event const &e, FSM &, int state)
    {
        std::cout << "no transition from state " << state
                  << " on event " << typeid(e).name() << std::endl;
    }
};

// FSM을 사용하려면 boost::msm::back::state_machine<FSM 객체>를 이용해야 한다.
// 이름이 길어지니 using, typedef 등을 이용해 줄여서 쓰는 것이 대부분이다.
using player = boost::msm::back::state_machine<player_>;

// 현재 상태 출력
// current_state()를 이용해 현재 상태의 배열을 얻는다.
// 여기서 배열을 얻는다는 말이 이상하게 들릴 수 있는데 이는 FSM의 영역이 동시에 여러개 존재할 수 있기 때문이다.
// 직교 영역(Orthogonal regions)을 설명할 때 좀 더 자세히 다룰 것이다.
// 일단 현재 다루고 있는 player라는 FMS의 영역은 하나이니 current_state()의 첫번째 값만 확인하면 된다.
// 따라서 current_state()[0]를 통해 현재 상태를 확인할 수 있다.
// 인덱스가 정해지는 규칙은 간단한데 다음 예시를 보면 이해가 쉽다.
//
// Row<One, some_event, Two>
// Row<Two, some_event, SomeState>
// Row<Three, some_event, Five>
// Row<Four, some_event, Two>
//
// 위와 같은 관계가 정의되어 있을 때 인덱스는 밑과 같이 정해진다.
// One : 0, Two: 1, Three: 2, Four: 3, SomeState: 4, Five : 5
// [시작 상태] 위에서 아래로 번호가 매겨진다.
// [시작 상태] 목록 끝을 만났다면 다시 [끝 상태] 목록의 상단으로 이동해서 아래로 내려가면서 번호가 매겨진다.
static char const *const state_names[] = {"Stopped", "Open", "Empty", "Playing", "Paused"};
void pstate(player const &p)
{
    std::cout << " -> " << state_names[p.current_state()[0]] << std::endl;
}

int main()
{
    player p;

    // FSM 객체의 on_entry()를 작동시키기 위해 start() 함수 호출
    // 초기 상태가 Empty이기에 Empty의 on_entry()도 작동한다.
    p.start();

    // 이벤트 호출은 process_event() 함수로 가능하다.  
    // 현재 Empty 상태에서 Open 상태로 이동
    // Empty의 on_exit()가 작동하고 그 후 Open의 on_entry()가 작동함.
    p.process_event(open_close());
    pstate(p);

    p.process_event(open_close());
    pstate(p);

    // DISK_DVD가 전달된 이벤트는 Guard Callble에 의해 무시된다.
    p.process_event(cd_detected("louie, louie", DISK_DVD));
    pstate(p);

    p.process_event(cd_detected("louie, louie", DISK_CD));
    pstate(p);

    p.process_event(play());
    p.process_event(pause());
    pstate(p);

    // go back to Playing
    p.process_event(end_pause());
    pstate(p);

    p.process_event(pause());
    pstate(p);

    // Stopped 상태로 이동
    p.process_event(stop());
    pstate(p);

    // Stopped 상태에서 stop 이벤트가 발생해도 다시 Stopped 상태다.
    p.process_event(stop());
    pstate(p);
    std::cout << "stop fsm" << std::endl;

    // FSM 종료시 stop() 함수 호출하여 FSM의 on_exit() 함수 수행.
    p.stop();

    return 0;
}
```
코드가 굉장히 많지만 주석을 읽어보면 어떤 일을 하는지 알 수 있다.  
&nbsp;  

상태의 개수가 10개가 넘어가면 밑과 같이 매크로를 수정해줘야 한다.  
```c++
#define FUSION_MAX_VECTOR_SIZE 20 // 기본 값은 10
```
헤더가 선언되기 전에 추가해야 한다.  
&nbsp;  

상태 테이블에 정의된 관계 개수의 제한은 20이기에 매크로를 수정해줘야 한다.  
```c++
#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_VECTOR_SIZE 30 // 기본 값은 20
#define BOOST_MPL_LIMIT_MAP_SIZE 30 // 기본 값은 20 
```
주의할 점은 50개를 초과하여 매크로를 수정할 수는 없다.  
당연히 이 녀석도 헤더가 선언되기 전에 추가해야 한다.  

상태 테이블에 50개가 넘어가는 관계를 정의해야 한다면 Boost의 mp11 라이브러리를 사용해야 한다.  
mp11의 mp_list는 템플릿 인자 개수에 제한이 없다.  
```c++
// 최대 50개까지 관계 설정 가능
struct transition_table : boost::mpl::vector<boost::msm::front::Row<SourceState, Event, TargetState>>
{
};

// 관계 설정 개수 무제한
using transition_table = boost::mp11::mp_list<boost::msm::front::Row<SourceState, Event, TargetState>>;
```
mp_list를 사용하는 방식이 비교적 최신이다.  
&nbsp;  

#### Deffered State  

만약 위의 FSM의 Empty 상태에서 pause 이벤트가 발생한다면 어떻게 될까?  
처리할 수 있는 상태 전이가 없어서 no_transition() 함수가 수행될 것이다.  

하지만 상태 이벤트의 지연 처리가 필요할 때가 있다.  
Empty 상태에서 pause 이벤트가 발생해도 no_transition() 함수가 수행되며 이벤트가 기각되지 않고 이벤트 큐에 저장했다가 FSM의 상태가 pause 이벤트를 처리할 수 있을 때 그 이벤트를 처리하는 Deffered State 기능을 Boost MSM은 제공한다.  

[CD Player 코드](#cd-player-예시)에서 상태를 살짝 바꿔보자.  
```c++
struct Empty : public boost::msm::front::state<>
{
    // play 이벤트가 Empty 상태에 도착해도 처리하지 않고 이벤트 큐에 저장만 해둠
    using deferred_events = mpl::vector<play, stop>;

    template <class Event, class FSM>
    void on_entry(Event const &, FSM &)
    {
        std::cout << "entering: Empty" << std::endl;
    }
    template <class Event, class FSM>
    void on_exit(Event const &, FSM &)
    {
        std::cout << "leaving: Empty" << std::endl;
    }
};
```
deferred_events가 정의되면 Empty 상태에서 play, stop 이벤트가 도착해도 이벤트 큐에 추가할 뿐 처리하지 않는다.  
상황을 보면 이해가 쉽다.  
``` 
Empty --> play [아무 반응 없음, 이벤트 큐에 play 추가]
Empty --> cd_detected [바로 처리됨] --> Stopped
Stopped --> play [이벤트 큐에 있던 이벤트를 이 시점에 처리] --> Playing
```
Stopped에 도착을 하면 이벤트 큐에 들어있는 잔여 이벤트를 수행하기에 자동으로 Playing 상태로 넘어간다.  
&nbsp;  

문제는 아래와 같은 상태이다.  
```
Empty --> play [아무 반응 없음, 이벤트 큐에 play 추가]
Empty --> open_close [바로 처리됨] --> Open
Open --> play [이벤트 큐에 있던 이벤트를 이 시점에 처리] --> [no_transition() 함수 호출]
```
위와 같은 상황을 방지하려면 Open 상태 구조체에도 deferred_events를 추가해줘야 한다.  
&nbsp;  

이렇게 일일이 deferred_events를 각 상태마다 적어주기 귀찮다면 activate_deferred_events 기능을 이용하면 된다.  
해당 기능은 FSM에 직접 입력한다.  
```c++
struct player_ : public boost::msm::front::state_machine_def<player_>
{
    using activate_deferred_events = int;

    // 구현부 생략
};
```
activate_deferred_events가 위와 같이 정의되면 player_ FSM에 존재하는 모든 상태는 처리할 수 없는 이벤트가 도착하면 no_transition() 함수를 실행하지 않고 이벤트 큐에 넣어버린다.  
&nbsp;  

### SubState  

특정 상태 내부에 또 다른 자식 상태(SubState)들이 존재할 수 있다.  
예를 들어 아픈 상태라면 감기, 독감, 골절 등 내부적으로 상태가 또 나뉠 수가 있다.  

CD Player 예시를 SubState가 있는 예시로 바꿔보자.  
Guard는 모두 PrintState이기에 생략한다.  
```mermaid
---
title : CD Player With SubState UML
---

stateDiagram-v2
    state Playing {
        [*] --> Song1
        Song1 --> Song2: E﹕next_song\nA﹕StartNextSong
        Song2 --> Song3: E﹕next_song\nA﹕StartNextSong
        Song3 --> Song2: E﹕previous_song\nA﹕StartPreviousSong
        Song2 --> Song1: E﹕previous_song\nA﹕StartPreviousSong
    }
    [*] --> Empty
    Empty --> Open: E﹕open_close\nA﹕OpenDrawer
    Open --> Empty: E﹕open_close\nA﹕CloseDrawer
    Paused --> Open: E﹕open_close\nA﹕StopAndOpen
    Playing --> Paused: E﹕pause\nA﹕PausePlayBack
    Playing --> Open: E﹕open_close\nA﹕StopAndOpen
    Paused --> Playing: E﹕end_pause\nA﹕ResumePlayback
    Stopped --> Stopped: E﹕stop\nA﹕StoppedAgain
    Stopped --> Open: E﹕open_close\nA﹕OpenDrawer
    Stopped --> Playing: E﹕play\nA﹕StartPlayback
    Paused --> Stopped: E﹕stop\nA﹕StopPlayBack
    Empty --> Stopped: E﹕cd_detected\nA﹕StoreCdInfo
    Playing --> Stopped: E﹕stop\nA﹕StopPlayBack
```
CD Player는 Playing 상태 내부에 다양한 SubState가 추가되어 이제 음악을 넘기면서 들을 수가 있다.  
&nbsp;  

위 UML을 코드에 적용하면 밑과 같다.  
```c++
// back-end header
#include <boost/msm/back/state_machine.hpp>

// front-end header
#include <boost/msm/front/state_machine_def.hpp>

// funtor row type header
#include <boost/msm/front/functor_row.hpp>

namespace msm = boost::msm;
namespace mpl = boost::mpl;

// MainState에 사용될 이벤트
struct play
{
};
struct end_pause
{
};
struct stop
{
};
struct pause
{
};
struct open_close
{
};
struct cd_detected
{
    cd_detected(std::string name)
        : name(name)
    {
    }

    std::string name;
};

// SubState에 사용될 이벤트
struct next_song
{
};
struct previous_song
{
};

// 상태 출력용 Guard
struct PrintState
{
    template <class Fsm, class Evt, class SourceState, class TargetState>
    bool operator()(Evt const &event, Fsm &fsm, SourceState &src, TargetState &trg)
    {
        std::cout << "Current State Index: " << fsm.current_state()[0] << "\n";
        std::cout << "Source: " << typeid(src).name() << " --- "
                  << "Event: " << typeid(event).name() << " ---> "
                  << "Target: " << typeid(trg).name() << "\n";
        return true;
    }
};

struct player_ : public msm::front::state_machine_def<player_>
{
    template <class Event, class FSM>
    void on_entry(Event const &, FSM &)
    {
        std::cout << "entering: Player" << std::endl;
    }
    template <class Event, class FSM>
    void on_exit(Event const &, FSM &)
    {
        std::cout << "leaving: Player" << std::endl;
    }

    struct Empty : public msm::front::state<>
    {
        template <class Event, class FSM>
        void on_entry(Event const &, FSM &)
        {
            std::cout << "entering: Empty" << std::endl;
        }
        template <class Event, class FSM>
        void on_exit(Event const &, FSM &)
        {
            std::cout << "leaving: Empty" << std::endl;
        }
    };
    struct Open : public msm::front::state<>
    {
        template <class Event, class FSM>
        void on_entry(Event const &, FSM &)
        {
            std::cout << "entering: Open" << std::endl;
        }
        template <class Event, class FSM>
        void on_exit(Event const &, FSM &)
        {
            std::cout << "leaving: Open" << std::endl;
        }
    };
    struct Stopped : public msm::front::state<>
    {
        template <class Event, class FSM>
        void on_entry(Event const &, FSM &)
        {
            std::cout << "entering: Stopped" << std::endl;
        }
        template <class Event, class FSM>
        void on_exit(Event const &, FSM &)
        {
            std::cout << "leaving: Stopped" << std::endl;
        }
    };

    // SubState를 포함하는 Playing 상태를 정의한다.
    // FSM을 정의할 때와 같이 msm::front::state_machine_def<자기 자신>를 상속하면 된다.
    // Playing 내부에 상태를 정의하는 경우에도 FSM에 상태를 정의하는 것과 별반 다르지 않다.
    // 참고로 Playing_ 객체는 player_ 외부에 정의해도 작동한다.
    // 이 예시에서는 편의를 위해 안에다 정의했다.
    struct Playing_ : public msm::front::state_machine_def<Playing_>
    {
        // Playing 상태 진입시 on_entry() 함수 수행
        template <class Event, class FSM>
        void on_entry(Event const &, FSM &)
        {
            std::cout << "entering: Playing" << std::endl;
        }

        // Playing 상태 탈출시 on_exit() 함수 수행
        template <class Event, class FSM>
        void on_exit(Event const &, FSM &)
        {
            std::cout << "leaving: Playing" << std::endl;
        }

        // SubState들 정의
        struct Song1 : public msm::front::state<>
        {
            template <class Event, class FSM>
            void on_entry(Event const &, FSM &)
            {
                std::cout << "starting: First song" << std::endl;
            }
            template <class Event, class FSM>
            void on_exit(Event const &, FSM &)
            {
                std::cout << "finishing: First Song" << std::endl;
            }
        };
        struct Song2 : public msm::front::state<>
        {
            template <class Event, class FSM>
            void on_entry(Event const &, FSM &)
            {
                std::cout << "starting: Second song" << std::endl;
            }
            template <class Event, class FSM>
            void on_exit(Event const &, FSM &)
            {
                std::cout << "finishing: Second Song" << std::endl;
            }
        };
        struct Song3 : public msm::front::state<>
        {
            template <class Event, class FSM>
            void on_entry(Event const &, FSM &)
            {
                std::cout << "starting: Third song" << std::endl;
            }
            template <class Event, class FSM>
            void on_exit(Event const &, FSM &)
            {
                std::cout << "finishing: Third Song" << std::endl;
            }
        };

        // SubState를 품고 있는 Playing 상태는 당연히 initial_state를 지정해줘야 한다.
        using initial_state = Song1;

        struct StartNextSong
        {
            template <class Fsm, class Evt, class SourceState, class TargetState>
            void operator()(Evt const &, Fsm &fsm, SourceState &src, TargetState &)
            {
                std::cout << "Playing::start_next_song\n";
            }
        };
        struct StartPreviousSong
        {
            template <class Fsm, class Evt, class SourceState, class TargetState>
            void operator()(Evt const &, Fsm &fsm, SourceState &src, TargetState &)
            {
                std::cout << "Playing::start_prev_song\n";
            }
        };

        // Transition table for Playing
        struct transition_table : mpl::vector<
                                      //      Start     Event         Next      Action               Guard
                                      //    +---------+-------------+---------+---------------------+----------------------+
                                      msm::front::Row<Song1, next_song, Song2, StartNextSong, PrintState>,
                                      msm::front::Row<Song2, previous_song, Song1, StartPreviousSong, PrintState>,
                                      msm::front::Row<Song2, next_song, Song3, StartNextSong, PrintState>,
                                      msm::front::Row<Song3, previous_song, Song2, StartPreviousSong, PrintState>
                                      //    +---------+-------------+---------+---------------------+----------------------+
                                      >
        {
        };

        // 이벤트를 처리하지 못하는 상황에 수행되는 no_transition() 함수 정의
        template <class FSM, class Event>
        void no_transition(Event const &e, FSM &, int state)
        {
            std::cout << "no transition from state " << state
                      << " on event " << typeid(e).name() << std::endl;
        }
    };

    // SubState 사용을 용이하게 만들기 위해 이름 줄이기
    using Playing = msm::back::state_machine<Playing_>;

    struct Paused : public msm::front::state<>
    {
    };

    // 기본 FSM도 당연히 initial_state를 지정해준다.
    using initial_state = Empty;

    // Action 정의
    struct StartPlayback
    {
        template <class Fsm, class Evt, class SourceState, class TargetState>
        void operator()(Evt const &, Fsm &fsm, SourceState &src, TargetState &)
        {
            std::cout << "player::StartPlayback\n";
        }
    };
    struct OpenDrawer
    {
        template <class Fsm, class Evt, class SourceState, class TargetState>
        void operator()(Evt const &, Fsm &fsm, SourceState &src, TargetState &)
        {
            std::cout << "player::OpenDrawer\n";
        }
    };
    struct CloseDrawer
    {
        template <class Fsm, class Evt, class SourceState, class TargetState>
        void operator()(Evt const &, Fsm &fsm, SourceState &src, TargetState &)
        {
            std::cout << "player::CloseDrawer\n";
        }
    };
    struct StoreCdInfo
    {
        template <class Fsm, class Evt, class SourceState, class TargetState>
        void operator()(Evt const &, Fsm &fsm, SourceState &src, TargetState &)
        {
            std::cout << "player::StoreCdInfo\n";
        }
    };
    struct StopPlayBack
    {
        template <class Fsm, class Evt, class SourceState, class TargetState>
        void operator()(Evt const &, Fsm &fsm, SourceState &src, TargetState &)
        {
            std::cout << "player::StopPlayBack\n";
        }
    };
    struct PausePlayBack
    {
        template <class Fsm, class Evt, class SourceState, class TargetState>
        void operator()(Evt const &, Fsm &fsm, SourceState &src, TargetState &)
        {
            std::cout << "player::PausePlayBack\n";
        }
    };
    struct ResumePlayBack
    {
        template <class Fsm, class Evt, class SourceState, class TargetState>
        void operator()(Evt const &, Fsm &fsm, SourceState &src, TargetState &)
        {
            std::cout << "player::ResumePlayBack\n";
        }
    };
    struct StopAndOpen
    {
        template <class Fsm, class Evt, class SourceState, class TargetState>
        void operator()(Evt const &, Fsm &fsm, SourceState &src, TargetState &)
        {
            std::cout << "player::StopAndOpen\n";
        }
    };
    struct StoppedAgain
    {
        template <class Fsm, class Evt, class SourceState, class TargetState>
        void operator()(Evt const &, Fsm &fsm, SourceState &src, TargetState &)
        {
            std::cout << "player::StoppedAgain\n";
        }
    };

    // 상태 관계 정의 테이블
    struct transition_table : mpl::vector<
                                  msm::front::Row<Stopped, play, Playing, StartPlayback, PrintState>,
                                  msm::front::Row<Stopped, open_close, Open, OpenDrawer, PrintState>,
                                  msm::front::Row<Stopped, stop, Stopped, StoppedAgain, PrintState>,
                                  msm::front::Row<Open, open_close, Empty, CloseDrawer, PrintState>,
                                  msm::front::Row<Empty, open_close, Open, OpenDrawer, PrintState>,
                                  msm::front::Row<Empty, cd_detected, Stopped, StoreCdInfo, PrintState>,
                                  msm::front::Row<Playing, stop, Stopped, StopPlayBack, PrintState>,
                                  msm::front::Row<Playing, pause, Paused, PausePlayBack, PrintState>,
                                  msm::front::Row<Playing, open_close, Open, StopAndOpen, PrintState>,
                                  msm::front::Row<Paused, end_pause, Playing, ResumePlayBack, PrintState>,
                                  msm::front::Row<Paused, stop, Stopped, StopPlayBack, PrintState>,
                                  msm::front::Row<Paused, open_close, Open, StopAndOpen, PrintState>>
    {
    };

    template <class FSM, class Event>
    void no_transition(Event const &e, FSM &, int state)
    {
        std::cout << "no transition from state " << state
                  << " on event " << typeid(e).name() << std::endl;
    }
};

using player = msm::back::state_machine<player_>;

int main()
{
    player p;

    p.start();

    p.process_event(open_close());

    p.process_event(open_close());

    p.process_event(cd_detected("louie, louie"));

    p.process_event(play());

    // 현재 Playing 상태에 도달했다.
    // 바로 pause 이벤트로 탈출할 수도 있지만 SubState를 실행해보자.
    // Playing을 진입하면서 첫 번째 곡이 활성화된다.
    p.process_event(next_song());

    // 두 번째 곡이 활성화
    p.process_event(next_song());

    // 세 번째 곡이 활성화
    p.process_event(previous_song());

    // 두 번째 곡이 활성화되어 있는 상태에서 pause 이벤트로 Playing 상태 탈출
    p.process_event(pause());

    // 현재 pause 상태
    p.process_event(end_pause());

    p.process_event(pause());

    p.process_event(stop());

    p.process_event(stop());

    p.process_event(play());

    // FSM 종료
    std::cout << "stop fsm" << std::endl;
    p.stop();

    // 밑과 같이 재시작도 가능하다.
    std::cout << "restart fsm" << std::endl;
    p.start();

    return 0;
}
```
SubState를 담고 있는 상태도 내부 FSM이기에 크게 다르지 않다.  
&nbsp;  

#### History  

SubState를 이용할 때 불편한 점이 있다.  
SubState를 담고 있는 상태를 빠져나갔다가 다시 해당 상태로 돌아오면 어디 SubState까지 진행했었는지 기억을 못한다.  
```
Playing --> Song1 --> Song2 -- [pause 이벤트 발생] --> Paused
[end_pause 이벤트 발생] --> Playing -- [Playing은 과거에 어떤 SubState까지 진행했는지 기억을 못함] --> Song1 
```
Song2를 재생하다가 멈추고 다시 재생해도 Playing 상태가 초기화되어 Song1이 재생되어 버린다.  
&nbsp;  

이러한 문제점을 해결하기 위해 Boost MSM은 History라는 기능을 제공한다.  
History를 이용하면 SubState를 담고 있는 상태가 초기화되지 않고 어디까지 진행했었는지 기억하고 있다.  
[SubState 예시](#substate) 코드를 수정해보자.  
```c++
// 동일한 구현부 생략 

struct player_ : public msm::front::state_machine_def<player_>
{
    // 동일한 구현부 생략 

    using Playing = msm::back::state_machine<Playing_, msm::back::ShallowHistory<mpl::vector<end_pause>>>;
};
```
바뀐 것은 SubState를 담고 있는 상태인 Playing 자료형의 선언부 밖에 없다.  
```msm::back::ShallowHistory<mpl::vector<end_pause>>``` 이 부분만 추가해주면 end_pause 이벤트를 통해 Playing 상태를 재진입할 때 예전에 수행되던 SubState부터 시작된다.  

모든 이벤트에 대해서 History 기능을 수행하고 싶다면 밑과 같이 사용하면 된다.  
```c++
// 동일한 구현부 생략 

struct player_ : public msm::front::state_machine_def<player_>
{
    // 동일한 구현부 생략 

    using Playing = msm::back::state_machine<Playing_, msm::back::AlwaysHistory>;
};
```
특정 이벤트로 재진입한 경우 History 기능을 이용하고 싶다면 ShallowHistory를, 모든 이벤트에 대해 History 기능을 이용하고 싶다면 AlwaysHistory를 사용하면 된다.  
&nbsp;  

### Orthogonal Zone  

Caps Lock과 Insert 키가 눌릴 때의 상태는 서로에게 영향을 주지 않는다.  
따라서 이러한 경우 이 둘의 조합을 따져야 한다.  
```None```, ```Caps Lock```, ```Insert```, ```Caps Lock + Insert``` 이렇게 4개의 상태가 존재한다.  

지금까지 배운 정보로 UML을 만들어 본다면 밑과 같다.  
```mermaid
---
title : Caps Lock and Insert Key UML
---

stateDiagram-v2
    None: None
    CapsLock: Caps Lock
    Insert: Insert   
    Insert_Caps: Caps Lock + Insert
    [*] --> None
    None --> CapsLock
    None --> Insert
    None --> Insert_Caps
    CapsLock --> None
    CapsLock --> Insert
    CapsLock --> Insert_Caps
    Insert --> None
    Insert --> CapsLock
    Insert --> Insert_Caps
    Insert_Caps --> None
    Insert_Caps --> CapsLock
    Insert_Caps --> Insert
```
4개의 상태를 표현할 뿐인데 12개의 이벤트가 필요하다.  
&nbsp;  

하지만 동시 상태 영역(Orthogonal Zone)을 이용하면 깔끔해진다.  
```mermaid
---
title : Orthogonal Zone UML
---

stateDiagram-v2
    CL_and_In: Caps Lock and Insert
    state CL_and_In {       
        ZoneA: Zone A
        state ZoneA {
            CapsOff: Caps Lock Off
            CapsOn: Caps Lock On
            [*] --> CapsOff
            CapsOff --> CapsOn
            CapsOn --> CapsOff
        }
        ZoneB: Zone B
        state ZoneB {
            InOff: Insert Off
            InOn: Insert On
            [*] --> InOff
            InOff --> InOn
            InOn --> InOff
        }
    }
```
FSM이 동시 상태를 가질 수 있기에 4개의 이벤트로 서로 다른 4개의 상태를 표현할 수 있다.  
&nbsp;  

위 UML을 코드에 적용해보자.  
```c++
// back-end header
#include <boost/msm/back/state_machine.hpp>

// front-end header
#include <boost/msm/front/state_machine_def.hpp>

// funtor row type header
#include <boost/msm/front/functor_row.hpp>

namespace msm = boost::msm;
namespace mpl = boost::mpl;

// 이벤트 정의
struct caps_lock_on
{
};
struct caps_lock_off
{
};
struct insert_on
{
};
struct insert_off
{
};

// 상태 출력용 Guard
struct PrintState
{
    template <class Fsm, class Evt, class SourceState, class TargetState>
    bool operator()(Evt const &event, Fsm &fsm, SourceState &src, TargetState &trg)
    {
        for (size_t i = 0; i < Fsm::nr_regions::value; i++)
            std::cout << "Zone " << i << " State Index: " << fsm.current_state()[i] << "\n";

        std::cout << "Source: " << typeid(src).name() << " --- "
                  << "Event: " << typeid(event).name() << " ---> "
                  << "Target: " << typeid(trg).name() << "\n";
        return true;
    }
};

struct KeyBoardFsm : public msm::front::state_machine_def<KeyBoardFsm>
{
    template <class Event, class FSM>
    void on_entry(Event const &, FSM &)
    {
        std::cout << "entering: KeyBoardFsm" << std::endl;
    }
    template <class Event, class FSM>
    void on_exit(Event const &, FSM &)
    {
        std::cout << "leaving: KeyBoardFsm" << std::endl;
    }

    // 상태 정의
    struct CapsLockOff : public msm::front::state<>
    {
    };
    struct CapsLockOn : public msm::front::state<>
    {
    };
    struct InsertOff : public msm::front::state<>
    {
    };
    struct InsertOn : public msm::front::state<>
    {
    };

    // Guard 정의

    // Orthogonal Zone 시작 상태 정의
    using initial_state = mpl::vector<CapsLockOff, InsertOff>;

    struct transition_table : mpl::vector<
                                  msm::front::Row<CapsLockOff, caps_lock_on, CapsLockOn, msm::front::none, PrintState>,
                                  msm::front::Row<CapsLockOn, caps_lock_off, CapsLockOff, msm::front::none, PrintState>,
                                  msm::front::Row<InsertOff, insert_on, InsertOn, msm::front::none, PrintState>,
                                  msm::front::Row<InsertOn, insert_off, InsertOff, msm::front::none, PrintState>>
    {
    };

    template <class FSM, class Event>
    void no_transition(Event const &e, FSM &, int state)
    {
        std::cout << "no transition from state " << state
                  << " on event " << typeid(e).name() << std::endl;
    }
};

using KeyBoardState = msm::back::state_machine<KeyBoardFsm>;

int main()
{
    KeyBoardState ks;

    ks.start();

    ks.process_event(caps_lock_on()); // Caps Lock

    ks.process_event(insert_on()); // Caps Lock + Insert

    ks.process_event(caps_lock_off()); // Insert

    ks.process_event(insert_off()); // None

    ks.stop();

    return 0;
}
```
initial_state의 선언부가 달라졌다.  
```mpl::vector<CapsLockOff, InsertOff>```처럼 시작 상태를 여러개 지정해주면 된다.  

또 하나 볼 것은 current_state() 함수다.  
전에 current_state()가 배열을 반환한다고 했는데 이유는 위 예시처럼 Zone이 여럿인 경우가 있기 때문이다.  
```current_state()[0]```은 initial_state에서 첫 번째로 위치한 CapsLockOff 상태가 속해있는 Zone의 현재 상태를 나타낸다.  
```current_state()[1]```은 InsertOff 상태가 속해있는 Zone의 현재 상태를 의미한다.  
상태 인덱스는 상태 전이 테이블을 보면 CapsLockOff : 0, CapsLockOn : 1, InsertOff : 2, InsertOn : 3 으로 지정된 것을 알 수 있다.  
&nbsp;  

#### Flag   

current_state()를 이용해서 현재 FSM의 상태를 확인하는 것은 직관적이지도 않고 한계가 명확하다.  
따라서 Boost MSM은 Flag 기능을 제공한다.  
위의 [Caps Lock, Insert 예제](#orthogonal-zone)에 Flag를 추가해보자.  
```c++
// 동일 구현부 생략

// flag 구조체 정의
struct Key_On
{
};

struct KeyBoardFsm : public msm::front::state_machine_def<KeyBoardFsm>
{
    // 동일 구현부 생략

    struct CapsLockOff : public msm::front::state<>
    {
    };
    struct CapsLockOn : public msm::front::state<>
    {
        // 해당 상태에 도달해야만 플래그가 켜진다.
        using flag_list = mpl::vector<Key_On>;
    };
    struct InsertOff : public msm::front::state<>
    {
    };
    struct InsertOn : public msm::front::state<>
    {
        using flag_list = mpl::vector<Key_On>;
    };
};

// 동일 구현부 생략

int main()
{
    KeyBoardState ks;

    ks.start();

    ks.process_event(caps_lock_on());

    // is_flag_active의 기본 옵션은 OR 연산이다.
    // 하나의 키만 켜져도 플래그 값은 true이다.
    if (ks.is_flag_active<Key_On>())
        std::cout << "At least one key turned on\n";

    // AND 옵션을 주면 Insert 키는 켜지지 않았기에 false가 반환된다.
    if (ks.is_flag_active<Key_On, KeyBoardState::Flag_AND>())
        std::cout << "All key turned on\n";

    ks.process_event(insert_on());

    // Insert 키가 켜지면 모든 키가 켜진 상태이기에 true가 반환된다.
    if (ks.is_flag_active<Key_On, KeyBoardState::Flag_AND>())
        std::cout << "All key turned on\n";

    ks.process_event(insert_off());

    ks.process_event(caps_lock_off());

    // 키가 하나도 안켜진 상태이기에 false가 반환된다.  
    if (ks.is_flag_active<Key_On>())
        std::cout << "At least one key turned on\n";

    ks.stop();

    return 0;
}
```
설명은 주석에 모두 쓰여있다.  
Key_On라는 flag 구조체 하나로 ```모든 버튼이 꺼진 상태```, ```모든 버튼이 켜진 상태```, ```하나의 버튼이라도 켜진 상태``` 이렇게 3가지 상태를 모두 알 수 있다.  
flag_list는 mpl::vector 자료형이기에 ```mpl::vector<flag_1, flag_2 ...>``` 이렇게 한번에 복수의 flag를 설정할 수도 있다.  
&nbsp;  

### Internal transition  

Boost MSM에는 내부적인 상태 전이가 존재한다.  
기본 상태 전이와 큰 차이점으로는 전이될 목표 상태가 따로 없다는 것이다.  
그리고 상태 내부적으로 발생되는 전이기에 on_entry(), on_exit() 함수도 수행되지 않는다.  
자신의 상태를 유지하면서 특정 Action을 반복적으로 수행하고 싶은 경우 사용하게 된다.  

게임의 특정 상황을 예시로 들어보자.  
캐릭터는 독에 중독된 상태, 마비 상태 둘 중 하나가 될 수 있다.  
UML로 표현하면 밑과 같다.  
```mermaid
---
title : Debuff State UML
---

flowchart TD

    subgraph Poisoned[Poisoned]
        PoisonedInternalState(Internal State) --> |Event: alert_poisoned\nAction: poison_tick| PoisonedInternalState
    end

    subgraph Paralysis[Paralysis]
        ParalysisInternalState(Internal State) --> |Event: be_cured\nAction: paralysis_tick\nGuard: paralysis_guard| ParalysisInternalState
    end

    Init[Init] --> None(None)
    None -->|Event: get_poisoned| Poisoned
    None -->|Event: get_paralysis| Paralysis
    Poisoned -->|Event: be_cured| None
    Paralysis -->|Event: be_cured| None

```
poison_tick, paralysis_tick 등의 특정 액션을 수행하기 위해 내부 상태 전이를 따로 정의하였다.  

코드 적용법은 밑과 같다.  
```c++
// back-end header
#include <boost/msm/back/state_machine.hpp>

// front-end header
#include <boost/msm/front/state_machine_def.hpp>

// funtor row type header
#include <boost/msm/front/functor_row.hpp>

namespace msm = boost::msm;
namespace mpl = boost::mpl;

// 이벤트 정의
struct alert_poisoned
{
};
struct get_poisoned
{
};
struct get_paralysis
{
};
struct be_cured
{
    bool is_paralysis;
    be_cured(bool ps = false)
        : is_paralysis{ps}
    {
    }
};

struct DebuffStatus : public msm::front::state_machine_def<DebuffStatus>
{
    template <class Event, class FSM>
    void on_entry(Event const &, FSM &)
    {
        std::cout << "entering: DebuffStatus" << std::endl;
    }
    template <class Event, class FSM>
    void on_exit(Event const &, FSM &)
    {
        std::cout << "leaving: DebuffStatus" << std::endl;
    }

    // 상태 정의
    struct None : public msm::front::state<>
    {
        template <class Event, class FSM>
        void on_entry(Event const &, FSM &)
        {
            std::cout << "entering: None" << std::endl;
        }
        template <class Event, class FSM>
        void on_exit(Event const &, FSM &)
        {
            std::cout << "leaving: None" << std::endl;
        }
    };
    struct Poisoned : public msm::front::state<>
    {
        template <class Event, class FSM>
        void on_entry(Event const &, FSM &)
        {
            std::cout << "entering: Poisoned" << std::endl;
        }
        template <class Event, class FSM>
        void on_exit(Event const &, FSM &)
        {
            std::cout << "leaving: Poisoned" << std::endl;
        }

        struct poison_tick
        {
            template <class EVT, class FSM, class SourceState, class TargetState>
            void operator()(EVT const &, FSM &, SourceState &, TargetState &)
            {
                std::cout << "You are poisoned!" << std::endl;
            }
        };

        // 내부 상태 전이 테이블 정의
        // Funtor를 이용하는 방식이 훨씬 간단하니 함수를 이용하는 방식은 생략한다.
        // msm::front::Internal<Event, Action, Guard> 순으로 적어주면 된다.
        // Action이나 Guard가 빠져야 한다면 Row와 같은 방식으로 msm::front::none을 적거나 인자를 생략해주면 된다.
        struct internal_transition_table : mpl::vector<
                                               msm::front::Internal<alert_poisoned, poison_tick>>
        {
        };
    };
    struct Paralysis : public msm::front::state<>
    {
        template <class Event, class FSM>
        void on_entry(Event const &, FSM &)
        {
            std::cout << "entering: Paralysis" << std::endl;
        }
        template <class Event, class FSM>
        void on_exit(Event const &, FSM &)
        {
            std::cout << "leaving: Paralysis" << std::endl;
        }

        struct paralysis_tick
        {
            template <class EVT, class FSM, class SourceState, class TargetState>
            void operator()(EVT const &, FSM &, SourceState &, TargetState &)
            {
                std::cout << "You are paralysis!" << std::endl;
            }
        };
        struct paralysis_guard
        {
            template <class EVT, class FSM, class SourceState, class TargetState>
            bool operator()(EVT const &evt, FSM &, SourceState &, TargetState &)
            {
                if (evt.is_paralysis)
                    std::cout << "You can't go back to None State!\n";
                return evt.is_paralysis;
            }
        };
        struct internal_transition_table : mpl::vector<
                                               msm::front::Internal<be_cured, paralysis_tick, paralysis_guard>>
        {
        };
    };

    // 시작 상태 정의
    using initial_state = mpl::vector<None>;

    struct transition_table : mpl::vector<
                                  msm::front::Row<None, get_poisoned, Poisoned>,
                                  msm::front::Row<None, get_paralysis, Paralysis>,
                                  msm::front::Row<Poisoned, be_cured, None>,
                                  msm::front::Row<Paralysis, be_cured, None>>
    {
    };

    template <class FSM, class Event>
    void no_transition(Event const &e, FSM &, int state)
    {
        std::cout << "no transition from state " << state
                  << " on event " << typeid(e).name() << std::endl;
    }
};

using DebuffState = msm::back::state_machine<DebuffStatus>;

int main()
{
    DebuffState df;

    df.start();

    // 중독 상태 돌입
    df.process_event(get_poisoned());

    // on_entry(), on_exit()는 수행되지 않고 poisone_tick 액션만 수행됨
    df.process_event(alert_poisoned());
    df.process_event(alert_poisoned());

    // 중독 상태 탈출
    df.process_event(be_cured());

    // 마비 상태 돌입
    df.process_event(get_paralysis());

    // 마비 상태 탈출 시도...는 실패한다.
    // internal transition은 기본 transition보다 우위이다.
    // paralysis_guard의 반환 값은 true이기에 paralysis_guard만 수행된다.
    df.process_event(be_cured(true));

    // 요번에는 마비 상태에서 탈출한다.
    // paralysis_guard의 반환 값이 false이기에 internal transition은 막히고 기본 상태 전이가 수행된다.
    df.process_event(be_cured(false));

    df.stop();

    return 0;
}
```
대부분의 설명은 주석에 적혀있다.  
중요한 부분은 내부 상태 전이가 기본 상태 전이보다 우위라는 것이다.  
Funtor를 이용한 internal_transition_table 정의 방식이 워낙 편하기에 함수를 이용한 internal_transition_table 정의 방식은 생략한다.  
궁금하다면 [이곳](https://www.boost.org/doc/libs/1_82_0/libs/msm/doc/HTML/ch03s02.html#internal-transitions)을 참고하자.  
&nbsp;  

### Base State  

상태에서 특정 base class를 상속할 수 있음
특정 클래스의 함수를 계속해서 이용하게 되는 경우 코드량을 줄이기 위해 사용됨
또 상태에서 visitor 함수를 호출하기 위해 사용되기도 함

&nbsp;  

### 상태 생성자  

상태 생성자를 만들어 특정 인자를 넘겨 미리 생성해둘수 있음


&nbsp;  


### 가짜 진입, 가짜 종료점, 직접 진입  

서브 상태의 내부의 특정 상태로 바로 진입하고 싶을 수 있는데 이때 직접 진입을 사용하면 됨
서브 상태는 항상 진입점이 존재하는데 해당 진입점을 사용하지 않고 다른 진입점을 추가적으로 만들고 싶다면 가짜 진입점을 만들면 됨.
서브 상태는 명시적인 종료 지점이 없는데 가짜 종료점을 만들어 종료 지점을 만들 수 있음

### 이벤트 상속  

```Row<Digit1, digit, Digit2>``` 요게 밑처럼 되지 않도록 가능
```
Row<Digit1, char_0, Digit2>,
Row<Digit1, char_1, Digit2>,
Row<Digit1, char_2, Digit2>,
Row<Digit1, char_3, Digit2>,
Row<Digit1, char_4, Digit2>,
Row<Digit1, char_5, Digit2>,
Row<Digit1, char_6, Digit2>,
...
```
