# Composite Pattern  

특정 객체들의 집합을 동일한 인터페이스를 이용해 순회 처리하기 위한 패턴이다.  
배열을 이용한 방법, ```begin() / end()``` 함수를 재정의하는 방법, ```std::vector<T>```를 상속하는 방법 등 여러가지가 존재한다.  
이 방식 중... ```begin() / end()``` 함수를 재정의하는 덕 타이핑 기법은 숨겨진 인터페이스에 의존하는 것이기에 위험한 상황이 발생될 수 있어서 추천되지 않는다.   
&nbsp;  

## 배열에 기반한 속성  

생명체 클래스를 컴포지트 패턴을 이용하여 개선해보자.  
밑과 같은 생명체 클래스가 존재한다.  
```c++
class Creature
{
    int strength, agility, intelligence;

public:
    const int &strength() const { return strength; }
    int &strength() { return strength; }
    const int &agility() const { return agility; }
    int &agility() { return agility; }
    const int &intelligence() const { return intelligence; }
    int &intelligence() { return intelligence; }
};
```
```getter / setter```가 정의되어 있는 평범한 클래스이다.  
별 문제가 보이지 않는다.  
&nbsp;  

하지만 문제는 필드들을 집합적으로 사용할 때 발생한다.  
```c++
class Creature
{
    int strength, agility, intelligence;

public:
    // getter / setter 생략

    int sum() const
    {
        return strength + agility + intelligence;
    }

    double average() const
    {
        return sum() / 3.0;
    }

    int max() const
    {
        return std::max(std::max(strength, agility), intelligence);
    }
};
```
만약 생명체에 근력, 민첩성, 지능 외의 health라는 건강 멤버 변수가 추가된다면 어떻게 될까?  
sum(), average(), max()의 구현부는 그에 맞춰 모두 변해야 하는데... 최악이다.  
새로운 능력치가 추가될 때 마다 함수의 구현부를 맨날 바꾸는 것은 굉장히 비효율적이고 개발자가 수정하면서 실수할 확률도 높다.  
&nbsp;  

```c++
class Creature
{
    enum Abilities
    {
        strengh,
        agility,
        intelligence,
        count
    };
    std::array<int, count> abilities;

public:
    const int &
    strength() const { return abilities[strengh]; }
    int &strength() { return abilities[strengh]; }
    const int &agility() const { return abilities[agility]; }
    int &agility() { return abilities[agility]; }
    const int &intelligence() const { return abilities[intelligence]; }
    int &intelligence() { return abilities[intelligence]; }

    int sum() const
    {
        return std::accumulate(abilities.begin(), abilities.end(), 0);
    }

    double average() const
    {
        return sum() / (double)count;
    }

    int max() const
    {
        return *std::max_element(abilities.begin(), abilities.end());
    }
};
```