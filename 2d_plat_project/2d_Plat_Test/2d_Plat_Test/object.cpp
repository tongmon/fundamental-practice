#include "object.h"

Object::Object(std::string file_path)
{
	if (!file_path.empty())
		m_sprite = std::make_unique<olc::Sprite>(file_path);
	m_scale = { 1.f, 1.f, 1.f, 1.f };
	m_transform = { 0.f, 0.f, 0.f, 1.f };
	m_angle = 0.f;
	m_mesh = new olc::GFX3D::mesh();
	
	m_mesh->tris =
	{
		{ 0.0f, 0.0f, 0.0f, 1.0f,	    0.0f, 1.0f, 0.0f, 1.0f,		 1.0f, 1.0f, 0.0f, 1.0f,	0.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f, 		1.0f, 1.0f, 0.0f, olc::WHITE, olc::WHITE, olc::WHITE },
		{ 0.0f, 0.0f, 0.0f, 1.0f,  		1.0f, 1.0f, 0.0f, 1.0f,		 1.0f, 0.0f, 0.0f, 1.0f,	0.0f, 0.0f, 0.0f,	1.0f, 1.0f, 0.0f, 		1.0f, 0.0f, 0.0f, olc::WHITE, olc::WHITE, olc::WHITE },
	};
}

Object::~Object()
{
	delete m_mesh;
}

void Object::Draw(olc::GFX3D::PipeLine& pipe)
{
	olc::GFX3D::mat4x4 mat_scale = olc::GFX3D::Math::Mat_MakeScale(m_scale.x, m_scale.y, m_scale.z); // ũ�� 
	olc::GFX3D::mat4x4 mat_translate = olc::GFX3D::Math::Mat_MakeTranslation(m_transform.x, m_transform.y, m_transform.z); // �̵�
	olc::GFX3D::mat4x4 mat_rotation_z = olc::GFX3D::Math::Mat_MakeRotationZ(AngleToRadian(m_angle)); // z�� ȸ�� (2d�� z�� ȸ���� ����Ѵ�.)
	m_translation = olc::GFX3D::Math::Mat_MultiplyMatrix(mat_translate, mat_scale);
	m_translation = olc::GFX3D::Math::Mat_MultiplyMatrix(m_translation, mat_rotation_z);
	
	// ������ ���� ����
	pipe.SetTransform(m_translation); // ��ȯ ��� ����
	pipe.SetTexture(m_sprite.get()); // �ؽ��� ����
	pipe.Render(m_mesh->tris, olc::GFX3D::RENDER_CULL_CW | olc::GFX3D::RENDER_DEPTH | olc::GFX3D::RENDER_TEXTURED);
}

void Object::SetSprite(std::string file_path)
{
	m_sprite = std::make_unique<olc::Sprite>(file_path);
}

/*
// ���� 2d ����
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
*/
