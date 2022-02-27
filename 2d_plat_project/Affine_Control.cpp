#define OLC_PGE_APPLICATION
#include "olc_Core/olcPixelGameEngine.h"
#include "olc_Core/olcPGEX_Graphics2D.h"

class Example : public olc::PixelGameEngine
{
private:
	std::unique_ptr<olc::Sprite> sprTile;
	float m_blockSize;

public:
	Example()
	{
		sAppName = "2d affine method";
		m_blockSize = 5.f;
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		sprTile = std::make_unique<olc::Sprite>("./Resource/Tile_01.png");
		m_blockSize = sprTile.get()->width;
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame
		Clear(olc::DARK_CYAN);
		SetPixelMode(olc::Pixel::MASK); // 투명인 픽셀은 그리지 않음
		
		for (int i = 0; i < 7; i++)
			for (int j = 0; j < 7; j++)
				DrawSprite(olc::vi2d(i, j) * m_blockSize, sprTile.get());

		olc::GFX2D::Transform2D d2dVar;
		d2dVar.Scale(2, 2);
		d2dVar.Translate(100, 100);
		d2dVar.Rotate(30 * 3.14159f / 180.0);
		olc::GFX2D::DrawSprite(sprTile.get(), d2dVar);

		SetPixelMode(olc::Pixel::NORMAL); // 모든 픽셀 그리기
		return true;
	}
};

int main()
{
	Example demo;
	if (demo.Construct(1280, 720, 1, 1, false, true))
		demo.Start();

	return 0;
}
