#pragma once
#include "olc_Core/olcPixelGameEngine.h"
#include "olc_Core/olcPGEX_Graphics2D.h"

class Object
{
private:
	std::unique_ptr<olc::Sprite> m_sprite; // 스프라이트
	olc::vf2d m_scale;
	olc::vf2d m_transform;
	float m_angle;
public:
	Object(std::string file_path);
	~Object();
	olc::vf2d& Scale() { return m_scale; } // 스케일 getter
	const olc::vf2d& Scale() const { return m_scale; } // // 스케일 setter
	olc::vf2d& Transform() { return m_transform; } // 이동 변위 getter
	const olc::vf2d& Transform() const { return m_transform; } // 이동 변위 setter
	float& Angle() { return m_angle; } // 회전 각도 getter
	const float& Angle() const { return m_angle; } // 회전 각도 setter
	float Width() { return m_scale.x * m_sprite.get()->width; } // 물체의 현재 너비
	float Height() { return m_scale.y * m_sprite.get()->height; } // 물체의 현재 높이
	void Draw();
};

