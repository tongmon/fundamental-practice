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
	olc::GFX3D::mat4x4 mat_scale = olc::GFX3D::Math::Mat_MakeScale(m_scale.x, m_scale.y, m_scale.z); // 크기 
	olc::GFX3D::mat4x4 mat_translate = olc::GFX3D::Math::Mat_MakeTranslation(m_transform.x, m_transform.y, m_transform.z); // 이동
	olc::GFX3D::mat4x4 mat_rotation_z = olc::GFX3D::Math::Mat_MakeRotationZ(AngleToRadian(m_angle)); // z축 회전 (2d라 z축 회전만 고려한다.)
	m_translation = olc::GFX3D::Math::Mat_MultiplyMatrix(mat_translate, mat_scale);
	m_translation = olc::GFX3D::Math::Mat_MultiplyMatrix(m_translation, mat_rotation_z);
	
	// 파이프 라인 설정
	pipe.SetTransform(m_translation); // 변환 행렬 설정
	pipe.SetTexture(m_sprite.get()); // 텍스쳐 설정
	pipe.Render(m_mesh->tris, olc::GFX3D::RENDER_CULL_CW | olc::GFX3D::RENDER_DEPTH | olc::GFX3D::RENDER_TEXTURED);
}

void Object::SetSprite(std::string file_path)
{
	m_sprite = std::make_unique<olc::Sprite>(file_path);
}

/*
// 완전 2d 전용
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
