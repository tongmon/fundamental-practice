#include "olc_Core/olcPixelGameEngine.h"
#include "olc_Core/olcPGEX_Graphics2D.h"

#include "object.h"

const int32_t screen_width = 1280;
const int32_t screen_height = 720;

// olc ���ӿ��� ��� �� ������ ���� https://community.onelonecoder.com/2020/05/20/how-to-attribute-credit-cite-the-olcpixelgameengine/
// ���� ���� ȭ�鿡 olc �ΰ� �ھ��ָ� �Ǵ� ��. �������� ����

class PathFinder2D : public olc::PixelGameEngine
{
private:
	std::unique_ptr<olc::Sprite> spr_brick_tile; // ���� ��������Ʈ
	std::unique_ptr<olc::Sprite> spr_space_tile; // �� ���� ��������Ʈ
	int32_t m_space_tile_size; // �� ���� ��������Ʈ ũ��
	int32_t m_brick_tile_size; // ���� ��������Ʈ ũ��
	float m_Angle;

public:
	PathFinder2D()
	{
		sAppName = "2d draw grid";
		m_brick_tile_size = m_space_tile_size = 5;
		m_Angle = 0;
	}

	~PathFinder2D() {}

	bool OnUserCreate() override
	{
		// �ʱ�ȭ
		spr_brick_tile = std::make_unique<olc::Sprite>("Resource/Tile_Brick.png");
		m_brick_tile_size = spr_brick_tile.get()->width;

		spr_space_tile = std::make_unique<olc::Sprite>("Resource/Tile_Space.png");
		m_space_tile_size = spr_brick_tile.get()->width;
		return true;
	}

	bool OnUserInput(float fElapsedTime)
	{

	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// �����Ӵ� �ѹ� ȣ��
		Clear(olc::DARK_CYAN);
		SetPixelMode(olc::Pixel::MASK); // ������ �ȼ��� �׸��� ����

		// ���� -> ����
		auto AngleToRadian = [](float Angle)->float { return Angle * 3.14159f / 180.f; };

		Object one_brick("Resource/Tile_Brick.png");
		one_brick.Draw();

		/*
		// ���� �׸���
		int grid_width = 10, grid_height = 10;
		olc::GFX2D::Transform2D d2dVar;
		for (int i = 0; i < grid_height; i++) {
			for (int j = 0; j < grid_width; j++) {
				olc::GFX2D::DrawSprite(spr_brick_tile.get(), d2dVar);
				d2dVar.Translate(spr_brick_tile.get()->width, 0);
			}
			d2dVar.Translate(-grid_width * spr_brick_tile.get()->width, spr_brick_tile.get()->height);
		}
		*/

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
	PathFinder2D demo;
	if (demo.Construct(screen_width, screen_height, 1, 1, false, true))
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