#define OLC_PGE_APPLICATION
#include "olcGameEngine/olcPixelGameEngine.h"

#define OLC_PGEX_GRAPHICS2D
#include "olcGameEngine/olcPGEX_Graphics2D.h"

#define resolution_W 1280
#define resolution_H 720

class Example : public olc::PixelGameEngine
{
private:
	std::unique_ptr<olc::Sprite> sprTile;
	int32_t m_spriteSize;
	float m_Angle;

public:
	Example()
	{
		sAppName = "2d affine method";
		m_spriteSize = 5;
		m_Angle = 0;
	}

public:
	bool OnUserCreate() override
	{
		// 초기화
		sprTile = std::make_unique<olc::Sprite>("../Resources/skeleton_1.png");
		m_spriteSize = sprTile.get()->width;
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// 프레임당 한번 호출
		Clear(olc::DARK_CYAN);
		SetPixelMode(olc::Pixel::MASK); // 투명인 픽셀은 그리지 않음
		
		//for (int i = 0; i < 7; i++)
			//for (int j = 0; j < 7; j++)
				//DrawSprite(olc::vi2d(i, j) * m_spriteSize, sprTile.get());

		// 각도를 라디안으로...
		auto AngleToRadian = [](float Angle)->float {return Angle * 3.14159f / 180.f; };

		// 순서 중요하다. 회전축은 항상 (0,0)으로 생각.
		// 앵간하면 회전, 스케일 조절하고 이동하는게 뜻대로 이루어 질 것이다.
		// 회전시에 회전축은 이미지 왼쪽 상단이다...
		// O-----X
		// -	 -
		// -	 -
		// -	 -
		// X-----X
		// 즉 O 부분이 처음 회전축이다. (처음엔 0,0에 위치할 것이다.)
		// 회전 방향은 반시계 방향이다.
		olc::GFX2D::Transform2D d2dVar;
		d2dVar.Translate(-sprTile.get()->width / 2.f, -sprTile.get()->height / 2.f);
		d2dVar.Scale(10, 10);
		d2dVar.Rotate(m_Angle -= 3 * fElapsedTime);
		d2dVar.Translate(resolution_W / 2, resolution_H / 2);
		olc::GFX2D::DrawSprite(sprTile.get(), d2dVar);

		SetPixelMode(olc::Pixel::NORMAL); // 모든 픽셀 그리기
		return true;
	}
};

int main()
{
	Example demo;
	if (demo.Construct(resolution_W, resolution_H, 1, 1, false, true))
		demo.Start();

	return 0;
}