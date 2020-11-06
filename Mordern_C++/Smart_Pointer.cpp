#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

class Mech
{
	int Part;
public:
	Mech(int a = 0) : Part(a) { cout << "Mech 생성자가 호출 되었습니다.\n"; }
	~Mech() { cout << "Mech 소멸자가 호출 되었습니다.\n"; }
};

class Human
{
	int Cell;
public:
	Human(int a = 0) : Cell(a) { cout << "Human 생성자가 호출 되었습니다.\n"; }
	~Human() { cout << "Human 소멸자가 호출 되었습니다.\n"; }
};

class Nature
{
	int Lives;
public:
	shared_ptr<Nature> Ptr; // shared_ptr
	Nature(int a = 0) : Lives(a) 
	{ 
		cout << "Nature 생성자가 호출 되었습니다.\n"; 
	}
	~Nature() { cout << "Nature 소멸자가 호출 되었습니다.\n"; }
};

class Space
{
	int Stars;
public:
	weak_ptr<Space> Ptr; // weak_ptr
	Space(int a = 0) : Stars(a)
	{
		cout << "Space 생성자가 호출 되었습니다.\n";
	}
	~Space() { cout << "Space 소멸자가 호출 되었습니다.\n"; }
};


int main(void)
{
	// 기존의 동적 할당 후 해제 방법
	// delete 가 귀찮은데다가 실수할 확률이 매우 높다!
	int* Ary = new int[5];
	delete[] Ary;
	
	// 스마트 포인터는 알아서 동적 할당한 것들을 해제해준다. 
	// 따라서 포인터에 대한 메모리 누수 실수를 없애주는데 탁월하다.
	
	// 크기 5 짜리 int 형 배열을 unique_ptr로 선언
	// 유니크 ptr은 말 그대로 '유니크' 하기에 Ptr 이 외에 이 포인터를 가리키는 다른 포인터는 존재하지 못한다.
	unique_ptr<int[]>Ptr(new int[5]);

	// 따라서 유니크 포인터를 이동하고 싶다면 이렇게 전달해주어야 한다.
	auto Ptr_2 = move(Ptr); // 전달 후에 Ptr은 빈 껍데기 상태로 남는 것, 소멸을 알아서 해준다.

	// 이러면 유니크 포인터에 객체가 동적으로 할당되고 자동으로 해제된다.
	unique_ptr<Mech> Mech_Ptr = make_unique<Mech>(2); // auto Mech_Ptr = make_unique<Mech>(2); 이렇게 auto로 때려도 된다.
	
	// Human 형 배열 5개 동적 할당 후에 자동으로 해제되는 것을 볼 수 있다.
	unique_ptr<Human[]> Human_Ary(new Human[5]);

	// shared_ptr은 unique_ptr과 다르게 '유니크' 하지는 않고 여러 개의 포인터가 공존할 수 있다.
	// 이렇게 해서 얻는 장점은 소멸자를 쓸데없이 여러번 호출되는 상황을 피하게 해준다.
	
	// N_Ptr이 동적 객체를 하나 생성하고 이를 가리킨다.
	shared_ptr<Human> N_Ptr = make_shared<Human>(3);
	cout << "N_Ptr을 지목하는 포인터 개수: " << N_Ptr.use_count() << endl; // 처음엔 하나의 포인터만 가리키고 있다.
	// M_Ptr과 O_Ptr도 이를 가리킨다.
	auto M_Ptr = N_Ptr;
	auto O_Ptr = N_Ptr;
	// 총 자신에게 몇 개의 포인터가 달려있는지는 밑과 같이 알 수 있다.
	cout << "N_Ptr을 지목하는 포인터 개수: " << N_Ptr.use_count() << endl;

	// shared_ptr의 치명적 단점은 순환참조에 대한 오류를 방지하지 못한다는 것이다.
	// 이렇게 밑과 같이 순환 참조가 발생한다면 정상적으로 메모리 해제가 되지않는다.
	// 콘솔창에서 Nature의 소멸자가 정상적으로 호출되지 않았다는 것을 알 수 있다.
	shared_ptr<Nature> Error_1 = make_shared<Nature>(1);
	shared_ptr<Nature> Error_2 = make_shared<Nature>(2);
	Error_1->Ptr = Error_2;
	Error_2->Ptr = Error_1;

	// 위와 같은 문제를 방지하려면 마지막 스마트 포인터 종류인 weak_ptr을 이용해야 한다.
	// weak_ptr은 shared_ptr의 이러한 문제점을 보강하기 위해 객체가 파괴되었는지 아닌지 판단이 가능하다.
	// 따라서 Ptr이 weak_ptr로 선언된 Space 객체는 정상적으로 순환 참조 고리를 파괴하고 소멸자를 호출한다.
	shared_ptr<Space> Valid_1 = make_shared<Space>(1);
	shared_ptr<Space> Valid_2 = make_shared<Space>(2);
	Valid_1->Ptr = Valid_2;
	Valid_2->Ptr = Valid_1;
	// weak_ptr은 shared_ptr과 본질적으로 처리방식이 동일하나 weak_ptr은 use_count()가 증가하지 않고 1이 유지된다.
	// weak_ptr은 shared_ptr와 연산 시에 호환이 된다.
}