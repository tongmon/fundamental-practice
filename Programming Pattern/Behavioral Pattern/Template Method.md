# Template Method Pattern  

템플릿 메서드 패턴의 핵심은 **템플릿**이다.  
여기서 말하는 템플릿은 C++의 템플릿을 말하는 것이 아니고 어떤 모양을 잡아주는 붕어빵틀과 같은 템플릿을 의미한다.  
일단 특정 행위를 하는 구현부를 인터페이스에 만들어 놓는다.  
해당 인터페이스를 상속한 클래스에는 구현부에 사용된 함수들의 세부 구현이 위치한다.  
&nbsp;  

# 체스 예제  

템플릿 메소드 패턴을 이용한 체스 클래스를 만들어보자.  
먼저 **템플릿** 역할을 하는 Game 클래스는 밑과 같다.  
```c++
class Game
{
  protected:
    virtual void start() = 0;
    virtual bool have_winner() = 0;
    virtual void take_turn() = 0;
    virtual int get_winner() = 0;

    int current_player{0};
    int number_of_players;

  public:
    explicit Game(int number_of_players)
        : number_of_players{number_of_players}
    {
    }

    void run()
    {
        start();
        while (!have_winner())
            take_turn();
        std::cout << "Player " << get_winner() << " wins.\n";
    }
};
```
run() 함수를 보면 알겠지만 순수 가상 함수인 start(), have_winner(), take_turn(), get_winner()를 활용하여 특정 템플릿을 구성한다.  
세부 구현은 Game 인터페이스를 상속하는 클래스에게 맞긴다.  
굳이 start(), have_winner(), take_turn(), get_winner() 함수들을 순수 가상 함수로 만들 필요는 없지만 의도를 분명히 전달하기 위해 여기서는 그렇게 한다.  
&nbsp;  

다음은 세부 구현부가 위치하는 Chess 클래스를 보자.  
```c++
class Chess : public Game
{
    int turns{0}, max_turns{10}; // 10턴 후에 게임 종료

  public:
    explicit Chess()
        : Game{2}
    {
    }

  protected:
    void start() override
    {
        std::cout << "Starting a game of chess with " << number_of_players << " players\n";
    }
    bool have_winner() override
    {
        return turns == max_turns;
    }
    void take_turn() override
    {
        std::cout << "Turn " << turns << " taken by player " << current_player << "\n";
        turns++;
        current_player = (current_player + 1) % number_of_players;
    }
    int get_winner() override
    {
        return current_player;
    }
};
```
protected로 선언된 영역에서 체스 게임에 알맞은 로직이 start(), have_winner(), take_turn(), get_winner() 함수에 담겨 재정의되고 있다.   
Chess 클래스는 재정의할 함수들만 고려하면 된다.  
start(), have_winner(), take_turn(), get_winner()의 활용은 Game 인터페이스가 알아서 해준다.  
&nbsp;  

활용은 밑과 같다.  
```c++
Chess chess;
chess.run();
```
Chess 클래스에서 사용자에게 공개된 함수는 run() 밖에 없다.  
&nbsp;  

## 요약  

1. 템플릿 메서드에서 이용될 메서드를 순수 가상 함수로 둘지 실 구현체로 둘지는 개발자에 선택에 달렸다.  