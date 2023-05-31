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

기본 상태, 내부 상태가 트리거되는 이벤트가 동일하면 밑과 같이 작동함

1. 내부 상태의 가드 함수가 false를 반환 -> 기본 상태를 시도
2. 내부 상태의 가드 함수가 true를 반환 -> 내부 상태에 액션이 있다면 수행하고 그 후 자기 자신의 상태변화 없이 종료


```c++
#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/front/internal_row.hpp>
#include <boost/msm/front/state_machine_def.hpp>

namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace msm::front;

namespace
{
// events
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
struct to_ignore
{
};

// A "complicated" event type that carries some data.
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

// front-end: define the FSM structure
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

    // The list of FSM states
    struct Empty : public msm::front::state<>
    {
        // every (optional) entry/exit methods get the event passed.
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

        struct internal_guard_fct
        {
            template <class EVT, class FSM, class SourceState, class TargetState>
            bool operator()(EVT const &evt, FSM &, SourceState &, TargetState &)
            {
                std::cout << "Empty::internal guard functor\n";
                return false;
            }
        };
        struct internal_action_fct
        {
            template <class EVT, class FSM, class SourceState, class TargetState>
            void operator()(EVT const &, FSM &, SourceState &, TargetState &)
            {
                std::cout << "Empty::internal action functor" << std::endl;
            }
        };

        void internal_action(to_ignore const &)
        {
            std::cout << "Empty::(almost)ignoring event\n";
        }

        struct internal_transition_table : mpl::vector<Row<Empty, cd_detected, none, internal_action_fct, internal_guard_fct>>
        {
        };
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

    // sm_ptr still supported but deprecated as functors are a much better way to do the same thing
    struct Stopped : public msm::front::state<msm::front::default_base_state, msm::front::sm_ptr>
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
        void set_sm_ptr(player_ *pl)
        {
            m_player = pl;
        }
        player_ *m_player;
    };

    struct Playing : public msm::front::state<>
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

    // state not defining any entry or exit
    struct Paused : public msm::front::state<>
    {
    };

    // the initial state of the player SM. Must be defined
    typedef Empty initial_state;

    // transition actions
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
    void resume_playback(end_pause const &)
    {
        std::cout << "player::resume_playback\n";
    }
    void stop_and_open(open_close const &)
    {
        std::cout << "player::stop_and_open\n";
    }
    void stopped_again(stop const &)
    {
        std::cout << "player::stopped_again\n";
    }
    // guard conditions
    bool good_disk_format(cd_detected const &evt)
    {
        // to test a guard condition, let's say we understand only CDs, not DVD
        if (evt.disc_type != DISK_CD)
        {
            std::cout << "wrong disk, sorry" << std::endl;
            return false;
        }
        return true;
    }
    // used to show a transition conflict. This guard will simply deactivate one transition and thus
    // solve the conflict
    bool auto_start(cd_detected const &)
    {
        return false;
    }

    typedef player_ p; // makes transition table cleaner

    // Transition table for player
    struct transition_table : mpl::vector<
                                  //    Start     Event         Next      Action				 Guard
                                  //  +---------+-------------+---------+---------------------+----------------------+
                                  a_row<Stopped, play, Playing, &p::start_playback>,
                                  a_row<Stopped, open_close, Open, &p::open_drawer>,
                                  _row<Stopped, stop, Stopped>,
                                  //  +---------+-------------+---------+---------------------+----------------------+
                                  a_row<Open, open_close, Empty, &p::close_drawer>,
                                  //  +---------+-------------+---------+---------------------+----------------------+
                                  a_row<Empty, open_close, Open, &p::open_drawer>,
                                  row<Empty, cd_detected, Stopped, &p::store_cd_info, &p::good_disk_format>,
                                  row<Empty, cd_detected, Playing, &p::store_cd_info, &p::auto_start>,
                                  //  +---------+-------------+---------+---------------------+----------------------+
                                  a_row<Playing, stop, Stopped, &p::stop_playback>,
                                  a_row<Playing, pause, Paused, &p::pause_playback>,
                                  a_row<Playing, open_close, Open, &p::stop_and_open>,
                                  //  +---------+-------------+---------+---------------------+----------------------+
                                  a_row<Paused, end_pause, Playing, &p::resume_playback>,
                                  a_row<Paused, stop, Stopped, &p::stop_playback>,
                                  a_row<Paused, open_close, Open, &p::stop_and_open>
                                  //  +---------+-------------+---------+---------------------+----------------------+
                                  >
    {
    };
    // Replaces the default no-transition response.
    template <class FSM, class Event>
    void no_transition(Event const &e, FSM &, int state)
    {
        std::cout << "no transition from state " << state
                  << " on event " << typeid(e).name() << std::endl;
    }
};
// Pick a back-end
typedef msm::back::state_machine<player_> player;

//
// Testing utilities.
//
static char const *const state_names[] = {"Stopped", "Open", "Empty", "Playing", "Paused"};
void pstate(player const &p)
{
    std::cout << " -> " << state_names[p.current_state()[0]] << std::endl;
}

void test()
{
    player p;
    // needed to start the highest-level SM. This will call on_entry and mark the start of the SM
    p.start();
    // go to Open, call on_exit on Empty, then action, then on_entry on Open
    p.process_event(open_close());
    pstate(p);
    p.process_event(open_close());
    pstate(p);
    // will be rejected, wrong disk type
    p.process_event(
        cd_detected("louie, louie", DISK_DVD));
    pstate(p);
    p.process_event(
        cd_detected("louie, louie", DISK_CD));
    pstate(p);
    p.process_event(play());

    // at this point, Play is active
    p.process_event(pause());
    pstate(p);
    // go back to Playing
    p.process_event(end_pause());
    pstate(p);
    p.process_event(pause());
    pstate(p);
    p.process_event(stop());
    pstate(p);
    // event leading to the same state
    // no action method called as it is not present in the transition table
    p.process_event(stop());
    pstate(p);
    std::cout << "stop fsm" << std::endl;
    p.stop();
}
} // namespace

int main()
{
    test();
    return 0;
}
```