#include "object.h"

Object::Object(std::string file_path)
{
	m_sprite = std::make_unique<olc::Sprite>(file_path);
	m_scale = { 1.f, 1.f };
	m_transform = { 0.f, 0.f };
	m_angle = 0.f;
}

Object::~Object()
{

}

void Object::Draw()
{
	static olc::GFX2D::Transform2D matrix_2d;

	matrix_2d.Translate(m_transform.x, m_transform.y);
	matrix_2d.Scale(m_scale.x, m_scale.y);
	matrix_2d.Rotate(m_angle);

	olc::GFX2D::DrawSprite(m_sprite.get(), matrix_2d);
}
