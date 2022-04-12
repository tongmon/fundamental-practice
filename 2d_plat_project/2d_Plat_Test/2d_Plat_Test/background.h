#pragma once
#include "olc_Core/olcPixelGameEngine.h"
#include "olc_Core/olcPGEX_Graphics3D.h"

class background
{
private:
	std::unique_ptr<olc::Sprite> m_sprite; // ��������Ʈ
	olc::GFX3D::mesh* m_mesh;
	olc::GFX3D::mat4x4 m_translation; // ��ȯ ��� SRT
	olc::GFX3D::vec3d m_scale;
	olc::GFX3D::vec3d m_transform;

public:

};

