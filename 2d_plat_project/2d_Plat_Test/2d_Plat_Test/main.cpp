#define OLC_PGE_APPLICATION
#include "olc_Core/olcPixelGameEngine.h"

#define OLC_PGEX_GRAPHICS2D
#include "olc_Core/olcPGEX_Graphics2D.h"

#define Screen_Width	1280
#define Screen_Height	720

// olc 게임엔진 사용 후 배포시 참고 https://community.onelonecoder.com/2020/05/20/how-to-attribute-credit-cite-the-olcpixelgameengine/
// 게임 시작 화면에 olc 로고만 박아주면 되는 듯. 나머지는 무료

class PathFinder_2D : public olc::PixelGameEngine
{
private:
	std::unique_ptr<olc::Sprite> spr_brick_tile;
	std::unique_ptr<olc::Sprite> spr_space_tile;
	int32_t m_space_tile_size;
	int32_t m_brick_tile_size;
	float m_Angle;

public:
	PathFinder_2D()
	{
		sAppName = "2d draw grid";
		m_brick_tile_size = m_space_tile_size = 5;
		m_Angle = 0;
	}

public:
	bool OnUserCreate() override
	{
		// 초기화
		spr_brick_tile = std::make_unique<olc::Sprite>("Resource/Tile_Brick.png");
		m_brick_tile_size = spr_brick_tile.get()->width;

		spr_space_tile = std::make_unique<olc::Sprite>("Resource/Tile_Space.png");
		m_space_tile_size = spr_brick_tile.get()->width;
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

		// 각도 -> 라디안
		auto AngleToRadian = [](float Angle)->float { return Angle * 3.14159f / 180.f; };

		int grid_width = 10, grid_height = 10;
		olc::GFX2D::Transform2D d2dVar;
		for (int i = 0; i < grid_height; i++) {
			for (int j = 0; j < grid_width; j++) {
				olc::GFX2D::DrawSprite(spr_brick_tile.get(), d2dVar);
				d2dVar.Translate(spr_brick_tile.get()->width, 0);
			}
			d2dVar.Translate(- grid_width * spr_brick_tile.get()->width, spr_brick_tile.get()->height);
		}

		/*
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
		d2dVar.Rotate(m_Angle = m_Angle <= -360 ? 0 : m_Angle - 3 * fElapsedTime);
		olc::GFX2D::DrawSprite(sprTile.get(), d2dVar);
		*/

		SetPixelMode(olc::Pixel::NORMAL); // 모든 픽셀 그리기
		return true;
	}
};

int main()
{
	PathFinder_2D demo;
	if (demo.Construct(Screen_Width, Screen_Height, 1, 1, false, true))
		demo.Start();

	return 0;
}

/*
int main()
{
	vector<vector<int>> Map = {
		{0,0,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0},
		{0,0,1,0,1,1,1,1,1,0,1,1,1,0,1,0,0,0,0,0},
		{0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,0},
		{0,0,1,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,0,0},
		{0,0,1,0,0,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0},
		{0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0},
		{0,0,1,0,1,0,1,0,0,1,0,0,0,1,0,1,0,1,1,0},
		{0,0,1,0,1,0,1,0,0,1,0,0,0,1,0,1,0,0,0,0},
		{0,0,1,0,1,0,1,0,0,1,0,1,1,1,0,1,1,0,1,0},
		{0,1,1,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0},
		{0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};
	AstarAlgorithm(Map, { 1,1 }, { 17,17 }, false);

	vector<vector<int>> PlatformerMap = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
		{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0},
		{0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};

	AstarAlgorithm(Map, { 1,1 }, { 17,17 }, false);
}
*/