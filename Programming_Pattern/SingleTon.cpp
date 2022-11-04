#include <bits/stdc++.h>
using namespace std;

/*
싱글톤 패턴을 간단히 C++로 짜봤다.
특징은 전역 멤버 함수를 사용했다는 것이고
전역 멤버 함수의 특징은 네임스페이스만 가지고 호출이 가능하다는 것이다.
밑의 나와있지만 객체생성이 없이 SingleTon::SetFloat(2) 이런 짓이 가능하다.
객체 생성이 없기에 this 포인터다. 따라서 this 포인터에 영향을 받지 않는
static 멤버 변수, 함수들만 함수 내부에서 사용이 가능하다.
이 패턴은 좋아 보이지만 멀티스레딩 환경에서 여러 개의 객체가 생길 수 있는 문제가 있다.
*/

class SingleTon
{
public:
    SingleTon(const SingleTon&) = delete;

    static SingleTon& Get() {
        static SingleTon inst;
        return inst;
    }

    static float GetFloat() { return Get().FloatInternal(); }
    static void SetFloat(float Num) { Get().mSingleTonMember = Num; }
private:
    SingleTon() { mSingleTonMember = 1.f; }
    float FloatInternal() { return mSingleTonMember; }
    float mSingleTonMember;
};

int main()
{
    cout << SingleTon::GetFloat() << '\n';
    SingleTon::SetFloat(2);
    cout << SingleTon::GetFloat();
}