#pragma once
#include "olc_Core/olcPixelGameEngine.h"
#include "olc_Core/olcPGEX_Graphics3D.h"

// semi-2D
// z-order가 추가됨.
class Object
{
private:
	std::unique_ptr<olc::Sprite> m_sprite; // 스프라이트
	olc::GFX3D::mesh* m_mesh;
	olc::GFX3D::mat4x4 m_translation; // 변환 행렬 SRT
	olc::GFX3D::vec3d m_scale;
	olc::GFX3D::vec3d m_transform;
	float m_angle;
	float AngleToRadian(float angle) { return angle * 3.14159f / 180.f; }
public:
	Object(std::string file_path = "");
	~Object();
	olc::GFX3D::vec3d& Scale() { return m_scale; } // 스케일 getter
	const olc::GFX3D::vec3d& Scale() const { return m_scale; } // // 스케일 setter
	olc::GFX3D::vec3d& Transform() { return m_transform; } // 이동 변위 getter
	const olc::GFX3D::vec3d& Transform() const { return m_transform; } // 이동 변위 setter
	float& Angle() { return m_angle; } // 회전 각도 getter (radian 아님, 양각은 축에서 시계방향 회전)
	const float& Angle() const { return m_angle; } // 회전 각도 setter
	void SetSprite(std::string file_path);
	float Width() { return m_scale.x; } // 물체의 현재 너비
	float Height() { return m_scale.y; } // 물체의 현재 높이
	void Draw(olc::GFX3D::PipeLine& pipe);
};

/*
#include "olc_Core/olcPGEX_Graphics2D.h"

// 완전 2d 전용
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
*/