#define OLC_PGE_APPLICATION
#include "olc_Core/olcPixelGameEngine.h"

#define OLC_PGEX_GRAPHICS2D
#include "olc_Core/olcPGEX_Graphics2D.h"

#define Screen_Width	1280
#define Screen_Height	720

// olc ���ӿ��� ��� �� ������ ���� https://community.onelonecoder.com/2020/05/20/how-to-attribute-credit-cite-the-olcpixelgameengine/
// ���� ���� ȭ�鿡 olc �ΰ� �ھ��ָ� �Ǵ� ��. �������� ����

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
		// �ʱ�ȭ
		spr_brick_tile = std::make_unique<olc::Sprite>("Resource/Tile_Brick.png");
		m_brick_tile_size = spr_brick_tile.get()->width;

		spr_space_tile = std::make_unique<olc::Sprite>("Resource/Tile_Space.png");
		m_space_tile_size = spr_brick_tile.get()->width;
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// �����Ӵ� �ѹ� ȣ��
		Clear(olc::DARK_CYAN);
		SetPixelMode(olc::Pixel::MASK); // ������ �ȼ��� �׸��� ����

		//for (int i = 0; i < 7; i++)
			//for (int j = 0; j < 7; j++)
				//DrawSprite(olc::vi2d(i, j) * m_spriteSize, sprTile.get());

		// ���� -> ����
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
		// ���� �߿��ϴ�. ȸ������ �׻� (0,0)���� ����.
		// �ް��ϸ� ȸ��, ������ �����ϰ� �̵��ϴ°� ���� �̷�� �� ���̴�.
		// ȸ���ÿ� ȸ������ �̹��� ���� ����̴�...
		// O-----X
		// -	 -
		// -	 -
		// -	 -
		// X-----X
		// �� O �κ��� ó�� ȸ�����̴�. (ó���� 0,0�� ��ġ�� ���̴�.)
		// ȸ�� ������ �ݽð� �����̴�.
		olc::GFX2D::Transform2D d2dVar;
		d2dVar.Translate(-sprTile.get()->width / 2.f, -sprTile.get()->height / 2.f);
		d2dVar.Scale(10, 10);
		d2dVar.Rotate(m_Angle = m_Angle <= -360 ? 0 : m_Angle - 3 * fElapsedTime);
		olc::GFX2D::DrawSprite(sprTile.get(), d2dVar);
		*/

		SetPixelMode(olc::Pixel::NORMAL); // ��� �ȼ� �׸���
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