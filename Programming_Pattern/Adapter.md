# Adapter Pattern  

한국은 220V를 사용하고 미국은 110V를 사용해서 콘센트 모양이 다르다.  
이를 위해 해외여행 준비물로 보통 어댑터를 포함하는데 이때 사용되는 어댑터와 같은 역할을 해서 어댑터 패턴이다.  
즉 어댑터 패턴은 인터페이스가 용도에 맞지 않을 때 중간에서 용도에 맞게 변환하는 역할을 해준다.  
&nbsp;  

직선으로 구성된 도형을 그리는 상황을 가정해보자.  
도형은 선으로 이루어져 있고 선은 점으로 구성된다.  
```c++
struct Point
{
    int x;
    int y;
};

struct Line
{
    Point start;
    Point end;
};
```
위와 같은 기본적인 구조체를 만들어준다.  
&nbsp;  

도형은 직선 여러 개를 합쳐 구성되기 때문에 밑과 같은 구조체를 상속해야 할 것이다.  
```c++
struct BasicShape
{
    std::vector<Line> lines;
};
```
&nbsp;  

그러면 사각형 클래스는 밑과 같을 것이다.  
```c++
class Square : BasicShape
{
public:
    Square(int x, int y, int witdh, int height)
    {
        lines.push_back(Line{Point{x, y}, Point{x + witdh, y}});
        lines.push_back(Line{Point{x + witdh, y}, Point{x + witdh, y + height}});
        lines.push_back(Line{Point{x + witdh, y + height}, Point{x, y + height}});
        lines.push_back(Line{Point{x, y + height}, Point{x, y}});
    }

    std::vector<Line>::iterator begin() { return lines.begin(); }
    std::vector<Line>::iterator end() { return lines.end(); }
};
```
각 꼭짓점을 받는 생성자를 만들고 begin() / end() 함수를 통해 선 집합의 시작과 끝을 반환한다.  
&nbsp;  

이제 사각형을 그려보자.  
밑과 같은 그리기 함수가 존재한다고 하자.  
```c++
void DrawPoints(const std::vector<Point> &points)
{
    std::for_each(points.begin(), points.end(), [](auto &point) { /*점 그리기 로직*/ });
}
```
해당 함수만 존재할 때 사각형을 직접적으로 그릴 수 있는 방법은 없다.  
그리기 함수가 요구하는 인자도 점 배열이고 실제 선도 점의 집합으로 표현이 된다.   
하지만 우리가 정의한 선 구조체는 시작점, 끝점으로 구성되어 있기에 형태가 맞지 않다.  
이때 Line 자료형을 std::vector<Point>로 맞춰주는 어댑터를 만들어 해결이 가능하다.  
&nbsp;  

## 어댑터  

