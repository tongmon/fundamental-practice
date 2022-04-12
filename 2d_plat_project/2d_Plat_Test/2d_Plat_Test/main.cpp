#include "olc_Core/olcPixelGameEngine.h"
#include "olc_Core/olcPGEX_Graphics2D.h"

#include "object.h"

const int32_t screen_width = 1280;
const int32_t screen_height = 720;

// olc 게임엔진 사용 후 배포시 참고 https://community.onelonecoder.com/2020/05/20/how-to-attribute-credit-cite-the-olcpixelgameengine/
// 게임 시작 화면에 olc 로고만 박아주면 되는 듯. 나머지는 무료

class PathFinder2D : public olc::PixelGameEngine
{
private:
	olc::GFX3D::vec3d m_up;
	olc::GFX3D::vec3d m_eye;
	olc::GFX3D::vec3d m_looktarget;

	Object m_tile_brick;
	Object m_space_brick;

public:
	PathFinder2D()
	{
		sAppName = "2d draw grid";
		
		float eye_z = -3.0f;

		m_up = { 0.0f, 1.0f, 0.0f };
		m_eye = { 0.0f, 0.0f, eye_z };
		m_looktarget = { 0.0f, 0.0f, 0.0f };
	}

	~PathFinder2D() {}

	// 초기화
	bool OnUserCreate() override
	{
		// 3D뷰 활성화
		// 2D에서 활동해도 3D가 편함
		olc::GFX3D::ConfigureDisplay();

		m_tile_brick.SetSprite("Resource/Tile_Brick.png");
		m_space_brick.SetSprite("Resource/Tile_Space.png");

		return true;
	}

	bool OnUserInput(float fElapsedTime)
	{

	}

	// 프레임당 한번 호출
	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::DARK_CYAN); // 백 버퍼 클리어하는 색상 설정
		//SetPixelMode(olc::Pixel::MASK); // 투명인 픽셀은 그리지 않음, 3d 모드에서 비활성화
		olc::GFX3D::ClearDepth();

		olc::GFX3D::PipeLine pipe;
		pipe.SetProjection(90.0f, (float)ScreenHeight() / (float)ScreenWidth(), 0.1f, 1000.0f, 0.0f, 0.0f, (float)ScreenWidth(), (float)ScreenHeight());
		pipe.SetCamera(m_eye, m_looktarget, m_up);

		/*
		// 빛 설정... 끄는 것과 아닌 것 차이 확인 요망
		olc::GFX3D::vec3d lightdir = { 1.0f, 1.0f, -1.0f };
		pipe.SetLightSource(0, olc::GFX3D::LIGHT_AMBIENT, olc::Pixel(100, 100, 100), { 0,0,0 }, lightdir);
		pipe.SetLightSource(1, olc::GFX3D::LIGHT_DIRECTIONAL, olc::WHITE, { 0,0,0 }, lightdir);
		*/
		
		static float angle = 0.f;
		m_space_brick.Transform() = { -0.5, -0.5 };
		//m_space_brick.Angle() = angle--;

		m_space_brick.Draw(pipe);

		/*
		// 격자 그리기
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

		//SetPixelMode(olc::Pixel::NORMAL); // 모든 픽셀 그리기
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