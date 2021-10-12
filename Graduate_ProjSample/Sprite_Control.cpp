#define OLC_PGE_APPLICATION
#include "olc_Core/olcPixelGameEngine.h"

class Example : public olc::PixelGameEngine
{
private:
	std::unique_ptr<olc::Sprite> sprTile;
	float m_blockSize;

public:
	Example()
	{
		sAppName = "Example";
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

		for (int i = 0; i < 15; i++)
			for (int j = 0; j < 15; j++)
				DrawSprite(olc::vi2d(i, j) * m_blockSize, sprTile.get());

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
