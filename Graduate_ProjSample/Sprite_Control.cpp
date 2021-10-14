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
		// �ʱ�ȭ
		sprTile = std::make_unique<olc::Sprite>("../Resources/skeleton_1.png");
		m_spriteSize = sprTile.get()->width;
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

		// ������ ��������...
		auto AngleToRadian = [](float Angle)->float {return Angle * 3.14159f / 180.f; };

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
		d2dVar.Rotate(m_Angle -= 3 * fElapsedTime);
		d2dVar.Translate(resolution_W / 2, resolution_H / 2);
		olc::GFX2D::DrawSprite(sprTile.get(), d2dVar);

		SetPixelMode(olc::Pixel::NORMAL); // ��� �ȼ� �׸���
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