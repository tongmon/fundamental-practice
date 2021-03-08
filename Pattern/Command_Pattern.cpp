#include <bits/stdc++.h>
using namespace std;

const char Buttons[4] = { 'X', 'Y', 'A', 'B' };

void Jump() {}
void FireGun() {}
void SwapWeapon() {}
void Evade() {}

/*
// 첫번째 방식

class InputHandler
{
public:
    bool isPressed(char In) 
    {
        // ...
        return true;
    }
    // 이런 방식은 행동 함수를 직접 호출하기에
    // 버튼 변경이 어렵다.
    // 여기서 버튼을 중점으로 보면 안된다.
    // 버튼은 그냥 A,B,X,Y 키로 고정되어 바뀌지 않는 녀석이라고 하고
    // 버튼에 딸린 어떤 행위를 바꿀 수 있느냐 아니냐를 따져보는 것이다.
    // 다시 봐보면 버튼에 딸린 행위를 바꿀 수 있는가?
    // 못 바꾼다... Jump 함수 자체의 내용을 공격으로
    // 바꾸면 바꿀 수는 있지만 굉장히 바보 같은 짓이다.
    void hadleInput()
    {
        if (isPressed(Buttons[0])) Jump();
        else if (isPressed(Buttons[1])) FireGun();
        else if (isPressed(Buttons[2])) SwapWeapon();
        else if (isPressed(Buttons[3])) Evade();
    }
};
*/

/*
// 두번째 방식

class Command
{
public:
    virtual ~Command() {}
    virtual void execute() = 0; // 버튼에 알맞은 행동이 새로 정의될 가상 함수
};

class JumpCommand : public Command
{
public:
    virtual void execute() { Jump(); }
};

class FireCommand : public Command
{
public:
    virtual void execute() { FireGun(); }
};

class SwapCommand : public Command
{
public:
    virtual void execute() { SwapWeapon(); }
};

class EvadeCommand : public Command
{
public:
    virtual void execute() { Evade(); }
};

class InputHandler_2
{
    Command* buttonX;
    Command* buttonY;
    Command* buttonA;
    Command* buttonB;
public:
    bool isPressed(char In)
    {
        // ...
        return true;
    }
    // 조금 더 개선된 방식을 보면 button 포인터에 해당하는
    // 행위를 execute 함수에 묶어서 사용하기에 버튼에 딸린 행위를
    // 교체하는데 유용하다.
    // 그런데 한계가 있는데 여기서 바꿀 수 있는 행위의 객체는 플레이어 뿐이다.
    // 즉 적에 대한 행위는 컨트롤이 안된다.
    void hadleInput()
    {
        if (isPressed(Buttons[0])) buttonX->execute();
        else if (isPressed(Buttons[1])) buttonY->execute();
        else if (isPressed(Buttons[2])) buttonA->execute();
        else if (isPressed(Buttons[3])) buttonB->execute();
    }
    // 이렇게 전 방식보다 쉽게 행동을 교체할 수 있다.
    void X_keySet(Command *A)
    {
        buttonX = new JumpCommand;
        // buttonX = A;
    }
};
*/

// 세번째 방식

class GameActor // 게임 내에서의 행위자
{
public:
    void Jump() {}
    void FireGun() {}
    void SwapWeapon() {}
    void Evade() {}
};

class Command
{
public:
    virtual ~Command() {}
    // 두번째 방식에서 게임에서의 행위자를 넘겨주는 곳이 추가되었다.
    virtual void execute(GameActor &actor) = 0;
};

class JumpCommand : public Command
{
public:
    virtual void execute(GameActor& actor) { actor.Jump(); }
};

class FireCommand : public Command
{
public:
    virtual void execute(GameActor& actor) { actor.FireGun(); }
};

class SwapCommand : public Command
{
public:
    virtual void execute(GameActor& actor) { actor.SwapWeapon(); }
};

class EvadeCommand : public Command
{
public:
    virtual void execute(GameActor& actor) { actor.Evade(); }
};

class InputHandler_3
{
    Command* buttonX;
    Command* buttonY;
    Command* buttonA;
    Command* buttonB;
public:
    bool isPressed(char In)
    {
        // ...
        return true;
    }
    // hadleInput 함수에서 행위에 대한 객체 포인터만 반환하기 때문에
    // hadleInput()->excute(Player) 이런 방식으로 사용하게 된다.
    // 이러면 플레이어가 누른 버튼에 따라 올바른 행동이 이행될 것이며
    // Player 말고 Enemy도 객체만 바꾸어주어 같은 행위를 하게 할 수 있다.
    Command* hadleInput()
    {
        if (isPressed(Buttons[0])) return buttonX;
        else if (isPressed(Buttons[1])) return buttonY;
        else if (isPressed(Buttons[2])) return buttonA;
        else if (isPressed(Buttons[3])) return buttonB;
    }
    void X_keySet(Command* A)
    {
        buttonX = new JumpCommand;
        // buttonX = A;
    }
};