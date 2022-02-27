#define OLC_PGE_APPLICATION
#include "olcGameEngine/olcPixelGameEngine.h"

#define resolution_W 1280
#define resolution_H 720

class Example : public olc::PixelGameEngine
{
private:
	std::unique_ptr<olc::Sprite> m_sprVar;
	std::unique_ptr<olc::Decal> m_decalVar;

	olc::vf2d m_decPos;
	olc::vf2d m_decScale;
	olc::vf2d m_decCenter;
	float_t m_decalAngle[2];

public:
	Example()
	{
		sAppName = "2D Decal Method";
		m_decScale = { 5.f,5.f };
		m_decPos = { 0.f,0.f };
		m_decalAngle[0] = 0.f;
		m_decalAngle[1] = 0.f;
	}

public:
	bool OnUserCreate() override
	{
		// 초기화
		m_sprVar = std::make_unique<olc::Sprite>("../Resources/skeleton_1.png");

		// Decal을 이용해야 GPU를 사용하기에 빠른 그래픽 연산이 가능
		m_decalVar = std::make_unique<olc::Decal>(m_sprVar.get());

		// 중심은 기존은 왼쪽 상단이였는데 이를 가운데로 옮긴다.
		m_decCenter = { m_sprVar.get()->width / 2.f, m_sprVar.get()->height / 2.f };
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// 프레임당 한번 호출
		Clear(olc::DARK_CYAN);
		SetPixelMode(olc::Pixel::MASK); // 투명인 픽셀은 그리지 않음

		// DrawRotatedDecal, 회전은 시계 방향 (단위는 360진법), 색상 지정도 용이
		// 따로 Scale, Pos, Angle, Center, 색상을 정해놓은 구조체를 만들어 사용해야 편함
		m_decPos = { resolution_W / 2.f - 300, resolution_H / 2.f };
		DrawRotatedDecal(m_decPos, m_decalVar.get(), m_decalAngle[0] += 4 * fElapsedTime, m_decCenter, m_decScale);

		m_decPos = { resolution_W / 2.f + 300, resolution_H / 2.f };
		DrawRotatedDecal(m_decPos, m_decalVar.get(), m_decalAngle[1] -= 4 * fElapsedTime, m_decCenter, m_decScale, olc::DARK_MAGENTA);

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
