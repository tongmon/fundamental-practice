#define OLC_PGE_APPLICATION
#include "olc_Core/olcPixelGameEngine.h"

class Example : public olc::PixelGameEngine
{
private:
	olc::vf2d m_rectPos;
	olc::vf2d m_ballPos;
	float m_ballRad;

public:
	Example()
	{
		sAppName = "Example";
		m_rectPos = { 64, 110 };
		m_ballPos = { 64, 64 };
		m_ballRad = 7.f;
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		if (GetKey(olc::Key::LEFT).bHeld || GetKey(olc::Key::A).bHeld)
			m_rectPos.x -= 100.0f * fElapsedTime;
		if (GetKey(olc::Key::RIGHT).bHeld || GetKey(olc::Key::D).bHeld)
			m_rectPos.x += 100.0f * fElapsedTime;

		m_ballPos = { float(GetMouseX()), float(GetMouseY()) };
		
		if (GetMouseWheel() > 0) 
			m_ballRad += 1.0f;
		if (GetMouseWheel() < 0) 
			m_ballRad -= 1.0f;
		if (m_ballRad < 5.0f) 
			m_ballRad = 5.0f;

		// called once per frame
		Clear(olc::DARK_CYAN);

		// Draw Boundary
		DrawLine(10, 10, ScreenWidth() - 10, 10, olc::YELLOW);
		DrawLine(10, 10, 10, ScreenHeight() - 10, olc::YELLOW);
		DrawLine(ScreenWidth() - 10, 10, ScreenWidth() - 10, ScreenHeight() - 10, olc::YELLOW);

		FillRect(m_rectPos.x, m_rectPos.y, 10, 10, olc::BLACK);

		FillCircle(m_ballPos, int(m_ballRad), olc::DARK_RED);

		return true;
	}
};

int main()
{
	Example demo;
	if (demo.Construct(128, 128, 4, 4, false, true))
		demo.Start();

	return 0;
}
