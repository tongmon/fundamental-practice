# Bridge Pattern  

브릿지 패턴은 접착제처럼 두 가지를 함께 연결해주는 패턴이다.  
브릿지 자체는 연결하려는 것들에 대한 정보를 몰라도 된다.  
하지만 연결되는 것들은 서로에 대해 알아야 한다.  
&nbsp;  

원을 그리는 상황을 생각해보자.  
일단 화면에 그리기 위한 렌더러 인터페이스를 만들자.  
```c++
struct Renderer
{
    virtual void render_circle(float center_x, float center_y, float radius) = 0;
};
```
원의 중심과 반지름을 인자로 받는 순수 가상 함수를 만들었다.  
&nbsp;  

화면에 나타내는 방식은 벡터 방식과 레스터 방식이 있다.  
대부분의 PDF 파일은 벡터 기반의 벡터 그래픽 방식이다.  
모든 비트맵 파일은 픽셀 기반의 레스터 그래픽 방식이다.  
이 둘을 나눠 구현해보자.  
```c++
struct VectorRenderer : Renderer
{
    void render_circle(float center_x, float center_y, float radius)
    {
        /* 벡터 그래픽으로 원 그리는 구현부 */
    }
};

struct RasterRenderer : Renderer
{
    void render_circle(float center_x, float center_y, float radius)
    {
        /* 레스터 그래픽으로 원 그리는 구현부 */
    }
};
```
패턴에 대해 다루기 때문에 실제 구현부는 생략한다.  
&nbsp;  





