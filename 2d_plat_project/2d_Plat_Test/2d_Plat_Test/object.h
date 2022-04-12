#pragma once
#include "olc_Core/olcPixelGameEngine.h"
#include "olc_Core/olcPGEX_Graphics3D.h"

// semi-2D
// z-order�� �߰���.
class Object
{
private:
	std::unique_ptr<olc::Sprite> m_sprite; // ��������Ʈ
	olc::GFX3D::mesh* m_mesh;
	olc::GFX3D::mat4x4 m_translation; // ��ȯ ��� SRT
	olc::GFX3D::vec3d m_scale;
	olc::GFX3D::vec3d m_transform;
	float m_angle;
	float AngleToRadian(float angle) { return angle * 3.14159f / 180.f; }
public:
	Object(std::string file_path = "");
	~Object();
	olc::GFX3D::vec3d& Scale() { return m_scale; } // ������ getter
	const olc::GFX3D::vec3d& Scale() const { return m_scale; } // // ������ setter
	olc::GFX3D::vec3d& Transform() { return m_transform; } // �̵� ���� getter
	const olc::GFX3D::vec3d& Transform() const { return m_transform; } // �̵� ���� setter
	float& Angle() { return m_angle; } // ȸ�� ���� getter (radian �ƴ�, �簢�� �࿡�� �ð���� ȸ��)
	const float& Angle() const { return m_angle; } // ȸ�� ���� setter
	void SetSprite(std::string file_path);
	float Width() { return m_scale.x; } // ��ü�� ���� �ʺ�
	float Height() { return m_scale.y; } // ��ü�� ���� ����
	void Draw(olc::GFX3D::PipeLine& pipe);
};

/*
#include "olc_Core/olcPGEX_Graphics2D.h"

// ���� 2d ����
class Object
{
private:
	std::unique_ptr<olc::Sprite> m_sprite; // ��������Ʈ
	olc::vf2d m_scale;
	olc::vf2d m_transform;
	float m_angle;
public:
	Object(std::string file_path);
	~Object();
	olc::vf2d& Scale() { return m_scale; } // ������ getter
	const olc::vf2d& Scale() const { return m_scale; } // // ������ setter
	olc::vf2d& Transform() { return m_transform; } // �̵� ���� getter
	const olc::vf2d& Transform() const { return m_transform; } // �̵� ���� setter
	float& Angle() { return m_angle; } // ȸ�� ���� getter
	const float& Angle() const { return m_angle; } // ȸ�� ���� setter
	float Width() { return m_scale.x * m_sprite.get()->width; } // ��ü�� ���� �ʺ�
	float Height() { return m_scale.y * m_sprite.get()->height; } // ��ü�� ���� ����
	void Draw();
};
*/