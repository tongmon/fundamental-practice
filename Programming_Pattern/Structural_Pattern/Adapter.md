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
    float x;
    float y;
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
    Square(float x, float y, float witdh, float height)
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
그리기 함수가 요구하는 인자는 점 배열이고 실제 선도 점의 집합으로 표현이 된다.   
하지만 우리가 정의한 선 구조체는 시작점, 끝점으로 구성되어 있기에 형태가 맞지 않다.  
이때 Line 자료형을 std::vector<Point>로 맞춰주는 어댑터를 만들어 해결이 가능하다.  
&nbsp;  

## 어댑터  

밑과 같이 선분을 점 집합으로 변환하여 저장하는 어댑터를 만들자.  
```c++
struct LineToPoints
{
    LineToPoints(const Line &line)
    {
        float dx = line.end.x - line.start.x;
        float dy = line.end.y - line.start.y;

        Point max{std::max(line.start.x, line.end.x), std::max(line.start.y, line.end.y)};
        Point min{std::min(line.start.x, line.end.x), std::min(line.start.y, line.end.y)};

        if (!dx)
            for (float x = min.x; x <= max.x; x += 0.1)
                points.push_back(Point{x, line.start.y});
        else if (!dy)
            for (float y = min.y; y <= max.y; y += 0.1)
                points.push_back(Point{line.start.x, y});
        else if (dx < dy)
            for (float x = min.x; x <= max.x; x += 0.1)
                points.push_back(Point{x, x * dx / dy});
        else
            for (float y = min.y; y <= max.y; y += 0.1)
                points.push_back(Point{y * dy / dx, y});
    }

    std::vector<Point>::iterator begin() { return points.begin(); }
    std::vector<Point>::iterator end() { return points.end(); }

    std::vector<Point> points;
};
```
&nbsp;  

이렇게 하면 밑과 같이 사용할 수 있다.  
```c++
Line line{Point{1, 2}, Point{11, 12}};
DrawPoints(LineToPoints{line}.points);
```
하지만 points 멤버 변수 사용이 뭔가 아쉽다.  
&nbsp;  

LineToPoints를 살짝 바꿔보자.  
```c++
struct LineToPoints
{
    // 생략

    operator std::vector<Point>()
    {
        return points;
    }

private:
    std::vector<Point> points;
};
```
points 멤버 변수는 숨기고 형변환 오버로딩 함수를 추가하였다.  
&nbsp;  

이렇게 하면 밑과 같이 더 깔끔하게 표현할 수 있다.  
```c++
Line line{Point{1, 2}, Point{11, 12}};
DrawPoints(LineToPoints{line});
```
&nbsp;  

## 캐싱  

LineToPoints 어댑터는 좋지만 아직 개선할 점이 남아있다.  
같은 선분이라도 그리기 함수가 시행되면 계산을 계속해서 수행한다는 점이 문제다.  
캐싱을 도입해서 해결해보자.  
&nbsp;  

unordered_map의 해싱을 활용하기 위해서는 사전 작업이 꽤나 요구된다.  
일단 밑과 같이 Line에 대한 해시 방식을 정의한다.  
```c++
namespace std
{
    template <typename T>
    void hash_combine(size_t &seed, const T &v)
    {
        hash<T> hasher;
        seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    template <>
    struct hash<Line>
    {
        size_t operator()(const Line &t) const
        {
            size_t seed = hash<float>{}(t.start.x);
            hash_combine(seed, t.start.y);
            hash_combine(seed, t.end.x);
            hash_combine(seed, t.end.y);
            return seed;
        }
    };
};
```
hash_combine은 Boost 라이브러리의 것과 동일한데 표준이 아니라 직접 정의하여 사용했다.  
&nbsp;  

Line 구조체도 밑과 같이 바꿔준다.  
```c++
struct Line
{
    Point start;
    Point end;

    bool operator==(const Line &other) const
    {
        return start.x == other.start.x &&
               start.y == other.start.y &&
               end.x == other.end.x &&
               end.y == other.end.y;
    }

    friend struct std::hash<Line>;
};
```
친구 구조체로 해시 방법을 등록하고 **"=="** 연산자를 재정의해주면 unordered_map에서 사용자 정의 자료형을 사용하기 위한 사전준비는 끝난다.  
&nbsp;  

LineToPoints 어댑터가 캐싱을 활용할 수 있게 바꿔준다.  
```c++
struct LineToPoints
{
    LineToPoints(const Line &line)
    {
        this->line = line;
        if (cache.find(line) != cache.end())
            return;

        std::vector<Point> points;

        // 동일한 구현부 생략

        cache[line] = points;
    }

    std::vector<Point>::iterator begin() { return cache[line].begin(); }
    std::vector<Point>::iterator end() { return cache[line].end(); }

    operator std::vector<Point>()
    {
        return cache[line];
    }

private:
    Line line;
    static inline std::unordered_map<Line, std::vector<Point>> cache;
};
```
캐싱을 활용하기 위해 전역 멤버 변수 cache 해쉬 맵과 각 어댑터마다 ID 역할을 하는 line 멤버 변수가 추가되었다.  
이제 어댑터 사용마다 캐시가 되어있는지를 검사하고 캐시된 값을 찾을 수 없는 경우에만 연산을 진행한다.  
&nbsp;  

## 요약  

1. 어댑터는 사용하기 어려운 인터페이스에 중간 다리를 놓아 사용하기 쉽게 바꿔주는 패턴이다.  

2. 보통 데이터 표현 방식을 맞추는 일이 많아 임시 데이터를 생성하게 되는데 이때 캐싱을 활용하면 좋다.  

3. 오랫동안 사용되지 않은 캐시 데이터의 삭제, 캐시된 객체가 변경된 경우 무효해진 캐시 데이터의 삭제 등등... 의 기능들을 추가한다면 더욱 완벽하다.  