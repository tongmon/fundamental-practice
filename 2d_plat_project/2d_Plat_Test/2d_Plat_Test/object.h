#pragma once
#include "olc_Core/olcPixelGameEngine.h"
#include "olc_Core/olcPGEX_Graphics2D.h"

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

